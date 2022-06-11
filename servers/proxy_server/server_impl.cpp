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
#include "proxy.pb.h"
#include "server_impl.h"

namespace ocean_kv {
namespace proxy {

void ProxyServiceImpl::Init() {
    
}

void ProxyServiceImpl::Get(google::protobuf::RpcController* cntl_base,
                      const GetRequest* request,
                      GetResponse* response,
                      google::protobuf::Closure* done) {
    brpc::ClosureGuard done_guard(done);
    brpc::Controller* cntl = static_cast<brpc::Controller*>(cntl_base);

    LOG(INFO) << "Received request[log_id=" << cntl->log_id() << "] from " << cntl->remote_side() 
              << " to " << cntl->local_side() << ": request_key: " << request->key();

    LOG(INFO) << "end...";

    // Fill response.
    response->set_code(0);
}

void ProxyServiceImpl::Put(google::protobuf::RpcController* cntl_base,
                      const PutRequest* request,
                      PutResponse* response,
                      google::protobuf::Closure* done) {
    brpc::ClosureGuard done_guard(done);
    brpc::Controller* cntl = static_cast<brpc::Controller*>(cntl_base);

    LOG(INFO) << "Received request[log_id=" << cntl->log_id() << "] from " << cntl->remote_side() 
              << " to " << cntl->local_side() << ": request_key: " << request->key();

    LOG(INFO) << "end...";

    // Fill response.
    response->set_code(0);
}

void ProxyServiceImpl::Delete(google::protobuf::RpcController* cntl_base,
                      const DeleteRequest* request,
                      DeleteResponse* response,
                      google::protobuf::Closure* done) {
    brpc::ClosureGuard done_guard(done);
    brpc::Controller* cntl = static_cast<brpc::Controller*>(cntl_base);

    LOG(INFO) << "Received request[log_id=" << cntl->log_id() << "] from " << cntl->remote_side() 
              << " to " << cntl->local_side() << ": request_key: " << request->key();

    LOG(INFO) << "end...";

    // Fill response.
    response->set_code(0);
}


}
}  // namespace ocean_kv

