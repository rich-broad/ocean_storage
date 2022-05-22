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
#include "index.pb.h"
#include "server_impl.h"

namespace ocean_kv {

void IndexServiceImpl::Init() {
    _transaction_db = new TransactionRocksDB();
    _transaction_db->Init();
}

void IndexServiceImpl::GetIndexInfo(google::protobuf::RpcController* cntl_base,
                      const GetIndexInfoRequest* request,
                      GetIndexInfoResponse* response,
                      google::protobuf::Closure* done) {
    brpc::ClosureGuard done_guard(done);

    brpc::Controller* cntl = static_cast<brpc::Controller*>(cntl_base);
    
    std::string value = _transaction_db->Get(request->key());

    // Fill response.
    ocean_kv::IndexInfo* index_info = response->mutable_index_info();
    index_info->ParseFromString(value);
    response->set_code(0);

    LOG(INFO) << "Received request[log_id=" << cntl->log_id() 
              << "] from " << cntl->remote_side() 
              << " to " << cntl->local_side()
              << ": " << request->key()
              << " (attached=" << cntl->request_attachment() << ")";

    std::string json1;
    json2pb::ProtoMessageToJson(*index_info, &json1, json2pb::Pb2JsonOptions());
    LOG(INFO) << "======get1: |" << json1;
}


void IndexServiceImpl::SetIndexInfo(google::protobuf::RpcController* cntl_base,
                      const SetIndexInfoRequest* request,
                      SetIndexInfoResponse* response,
                      google::protobuf::Closure* done) {
    brpc::ClosureGuard done_guard(done);

    brpc::Controller* cntl = static_cast<brpc::Controller*>(cntl_base);

    LOG(INFO) << "Received request[log_id=" << cntl->log_id() << "] from " << cntl->remote_side() 
              << " to " << cntl->local_side() << ": request_key: " << request->key()
              << " (attached=" << cntl->request_attachment() << ")";

    std::string value;
    request->index_info().SerializeToString(&value);
    _transaction_db->Set(request->key(), value);

    LOG(INFO) << "end...";

    // Fill response.
    response->set_code(0);
}

}  // namespace ocean_kv

