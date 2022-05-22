// Licensed to the Apache Software Foundation (ASF) under one
// or more contributor license agreements.  See the NOTICE file
// distributed with this work for additional information
// regarding copyright ownership.  The ASF licenses this file
// to you under the Apache License, Version 2.0 (the
// "License"); you may not use this file except in compliance
// with the License.  You may obtain a copy of the License at
//
//   http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing,
// software distributed under the License is distributed on an
// "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY
// KIND, either express or implied.  See the License for the
// specific language governing permissions and limitations
// under the License.

#include <gflags/gflags.h>
#include <butil/logging.h>
#include <brpc/server.h>
#include "simple_kv.pb.h"
#include "simple_example.h"

DEFINE_int32(port, 8000, "TCP Port of this server");
DEFINE_string(listen_addr, "", "Server listen address, may be IPV4/IPV6/UDS."
            " If this is set, the flag port will be ignored");
DEFINE_int32(idle_timeout_s, -1, "Connection will be closed if there is no "
             "read/write operations during the last `idle_timeout_s'");
DEFINE_int32(logoff_ms, 2000, "Maximum duration of server's LOGOFF state "
             "(waiting for client to close connection before server stops)");

namespace ocean_kv {
class SimpleKVServiceImpl : public SimpleKVService {
public:
    SimpleKVServiceImpl() {};
    virtual ~SimpleKVServiceImpl() {};
    virtual void Get(google::protobuf::RpcController* cntl_base,
                      const GetRequest* request,
                      GetResponse* response,
                      google::protobuf::Closure* done);
    virtual void Set(google::protobuf::RpcController* cntl_base,
                      const SetRequest* request,
                      SetResponse* response,
                      google::protobuf::Closure* done);

    void Init();
private:
    SimpleRocksDB *db;
};

void SimpleKVServiceImpl::Init() {
    db = new SimpleRocksDB();
    db->Init();
}

void SimpleKVServiceImpl::Get(google::protobuf::RpcController* cntl_base,
                      const GetRequest* request,
                      GetResponse* response,
                      google::protobuf::Closure* done) {
    brpc::ClosureGuard done_guard(done);

    brpc::Controller* cntl = static_cast<brpc::Controller*>(cntl_base);
    
    std::string value = db->Get(request->key());

    LOG(INFO) << "Received request[log_id=" << cntl->log_id() 
              << "] from " << cntl->remote_side() 
              << " to " << cntl->local_side()
              << ": " << request->key() << "=" << value
              << " (attached=" << cntl->request_attachment() << ")";

    // Fill response.
    response->set_value(value);
}


void SimpleKVServiceImpl::Set(google::protobuf::RpcController* cntl_base,
                      const SetRequest* request,
                      SetResponse* response,
                      google::protobuf::Closure* done) {
    brpc::ClosureGuard done_guard(done);

    brpc::Controller* cntl = static_cast<brpc::Controller*>(cntl_base);

    LOG(INFO) << "Received request[log_id=" << cntl->log_id() << "] from " << cntl->remote_side() 
              << " to " << cntl->local_side() << ": request_key: " << request->key() << " value: " <<  request->value()
              << " (attached=" << cntl->request_attachment() << ")";

    db->Set(request->key(), request->value());

    LOG(INFO) << "end...";

    // Fill response.
    response->set_code(0);
}



}  // namespace ocean_kv

int main(int argc, char* argv[]) {
    // Parse gflags. We recommend you to use gflags as well.
    GFLAGS_NS::ParseCommandLineFlags(&argc, &argv, true);
    // Generally you only need one Server.
    brpc::Server server;
    // Instance of your service.
    ocean_kv::SimpleKVServiceImpl service_impl;
    service_impl.Init();
    // Add the service into server. Notice the second parameter, because the
    // service is put on stack, we don't want server to delete it, otherwise
    // use brpc::SERVER_OWNS_SERVICE.
    if (server.AddService(&service_impl, 
                          brpc::SERVER_DOESNT_OWN_SERVICE) != 0) {
        LOG(ERROR) << "Fail to add service";
        return -1;
    }

    butil::EndPoint point;
    if (!FLAGS_listen_addr.empty()) {
        if (butil::str2endpoint(FLAGS_listen_addr.c_str(), &point) < 0) {
            LOG(ERROR) << "Invalid listen address:" << FLAGS_listen_addr;
            return -1;
        }
    } else {
        point = butil::EndPoint(butil::IP_ANY, FLAGS_port);
    }
    // Start the server.
    brpc::ServerOptions options;
    options.idle_timeout_sec = FLAGS_idle_timeout_s;
    if (server.Start(point, &options) != 0) {
        LOG(ERROR) << "Fail to start EchoServer";
        return -1;
    }

    // Wait until Ctrl-C is pressed, then Stop() and Join() the server.
    server.RunUntilAskedToQuit();
    return 0;
}
