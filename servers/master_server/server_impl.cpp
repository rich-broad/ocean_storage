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
#include "master.pb.h"
#include "server_impl.h"

namespace ocean_kv {
namespace master {

void MasterServiceImpl::Init() {
    
}

void MasterServiceImpl::AllocFileId(google::protobuf::RpcController* cntl_base,
          const AllocFileIdRequest* request,
          AllocFileIdResponse* response,
          google::protobuf::Closure* done) {
    brpc::ClosureGuard done_guard(done);
    brpc::Controller* cntl = static_cast<brpc::Controller*>(cntl_base);

    LOG(INFO) << "Received request[log_id=" << cntl->log_id() << "] from " << cntl->remote_side() 
              << " to " << cntl->local_side() << ": request_key: " << request->file_id();

    LOG(INFO) << "end...";

    // Fill response.
    response->set_code(0);
}

void MasterServiceImpl::GetAllFileIds(google::protobuf::RpcController* cntl_base,
          const GetAllFileIdsRequest* request,
          GetAllFileIdsResponse* response,
          google::protobuf::Closure* done) {
    brpc::ClosureGuard done_guard(done);
    brpc::Controller* cntl = static_cast<brpc::Controller*>(cntl_base);

    LOG(INFO) << "Received request[log_id=" << cntl->log_id() << "] from " << cntl->remote_side() 
              << " to " << cntl->local_side() << ": request_key: " << request->page_size();

    LOG(INFO) << "end...";

    // Fill response.
    response->set_code(0);
}

void MasterServiceImpl::LockCluster(google::protobuf::RpcController* cntl_base,
          const LockClusterRequest* request,
          LockClusterResponse* response,
          google::protobuf::Closure* done) {
    brpc::ClosureGuard done_guard(done);
    brpc::Controller* cntl = static_cast<brpc::Controller*>(cntl_base);

    LOG(INFO) << "Received request[log_id=" << cntl->log_id() << "] from " << cntl->remote_side() 
              << " to " << cntl->local_side() << ": request_key: ";

    LOG(INFO) << "end...";

    // Fill response.
    response->set_code(0);
}

void MasterServiceImpl::UnLockCluster(google::protobuf::RpcController* cntl_base,
          const UnLockClusterRequest* request,
          UnLockClusterResponse* response,
          google::protobuf::Closure* done) {
    brpc::ClosureGuard done_guard(done);
    brpc::Controller* cntl = static_cast<brpc::Controller*>(cntl_base);

    LOG(INFO) << "Received request[log_id=" << cntl->log_id() << "] from " << cntl->remote_side() 
              << " to " << cntl->local_side() << ": request_key: ";

    LOG(INFO) << "end...";

    // Fill response.
    response->set_code(0);
}

void MasterServiceImpl::HeartBeat(google::protobuf::RpcController* cntl_base,
          const HeartBeatRequest* request,
          HeartBeatResponse* response,
          google::protobuf::Closure* done) {
    brpc::ClosureGuard done_guard(done);
    brpc::Controller* cntl = static_cast<brpc::Controller*>(cntl_base);

    LOG(INFO) << "Received request[log_id=" << cntl->log_id() << "] from " << cntl->remote_side() 
              << " to " << cntl->local_side() << ": request_key: " << request->server_name();

    LOG(INFO) << "end...";

    // Fill response.
    response->set_code(0);
}

}
}  // namespace ocean_kv

