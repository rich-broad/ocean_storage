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

// A client sending requests to server every 1 second.

#include <gflags/gflags.h>
#include <butil/logging.h>
#include <butil/time.h>
#include <brpc/channel.h>
#include "simple_kv.pb.h"

DEFINE_string(protocol, "baidu_std", "Protocol type. Defined in src/brpc/options.proto");
DEFINE_string(connection_type, "", "Connection type. Available values: single, pooled, short");
DEFINE_string(server, "0.0.0.0:8000", "IP Address of server");
DEFINE_string(load_balancer, "", "The algorithm for load balancing");
DEFINE_int32(timeout_ms, 100, "RPC timeout in milliseconds");
DEFINE_int32(max_retry, 3, "Max retries(not including the first RPC)"); 
DEFINE_int32(interval_ms, 1000, "Milliseconds between consecutive requests");

struct BrpcClient {
    // A Channel represents a communication line to a Server. Notice that 
    // Channel is thread-safe and can be shared by all threads in your program.
    brpc::Channel channel;
    ocean_kv::SimpleKVService_Stub *stub;
    void Init();
};

void BrpcClient::Init() {
    // Initialize the channel, NULL means using default options.
    brpc::ChannelOptions options;
    options.protocol = FLAGS_protocol;
    options.connection_type = FLAGS_connection_type;
    options.timeout_ms = FLAGS_timeout_ms/*milliseconds*/;
    options.max_retry = FLAGS_max_retry;
    if (channel.Init(FLAGS_server.c_str(), FLAGS_load_balancer.c_str(), &options) != 0) {
        LOG(ERROR) << "Fail to initialize channel";
        exit(-1);
    }
    // Normally, you should not call a Channel directly, but instead construct
    // a stub Service wrapping it. stub can be shared by all threads as well.
    stub = new ocean_kv::SimpleKVService_Stub(&channel);
}

BrpcClient *client = nullptr;

uint32_t Set(const std::string &key, const std::string &value) {
    // Send a request and wait for the response every 1 second.
    int log_id = 0;
    ocean_kv::SetRequest request;
    ocean_kv::SetResponse response;
    brpc::Controller cntl;

    request.set_key(key);
    request.set_value(value);

    cntl.set_log_id(log_id ++);  // set by user

    // Because `done'(last parameter) is NULL, this function waits until
    // the response comes back or error occurs(including timedout).
    client->stub->Set(&cntl, &request, &response, NULL);
    if (!cntl.Failed()) {
        LOG(INFO) << "Received response from " << cntl.remote_side()
            << " to " << cntl.local_side()
            << ": " << response.code() << " (attached="
            << cntl.response_attachment() << ")"
            << " latency=" << cntl.latency_us() << "us";
    } else {
        LOG(WARNING) << cntl.ErrorText();
    }
    return response.code();
}

std::string Get(const std::string &key) {
    int log_id = 0;
    ocean_kv::GetRequest request;
    ocean_kv::GetResponse response;
    brpc::Controller cntl;

    request.set_key(key);

    cntl.set_log_id(log_id ++);  // set by user

    // Because `done'(last parameter) is NULL, this function waits until
    // the response comes back or error occurs(including timedout).
    client->stub->Get(&cntl, &request, &response, NULL);
    if (!cntl.Failed()) {
        LOG(INFO) << "Received response from " << cntl.remote_side()
            << " to " << cntl.local_side()
            << "|: " << response.value() << "| (attached="
            << cntl.response_attachment() << ")"
            << " latency=" << cntl.latency_us() << "us";
    } else {
        LOG(WARNING) << cntl.ErrorText();
    }
    return response.value();
}

int main(int argc, char* argv[]) {
    // Parse gflags. We recommend you to use gflags as well.
    GFLAGS_NS::ParseCommandLineFlags(&argc, &argv, true);
    client = new BrpcClient();
    client->Init();
    
    LOG(INFO) << "set2" << Set("2", "test2");
    LOG(INFO) << "set1" << Set("1", "test1");

    LOG(INFO) << "get2" << Get("2");
    LOG(INFO) << "get1" << Get("1");
    

    LOG(INFO) << "Client is going to quit";
    return 0;
}
