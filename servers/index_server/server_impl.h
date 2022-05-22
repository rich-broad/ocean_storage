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

#include <json2pb/pb_to_json.h>
#include "index.pb.h"
#include "transaction_rocksdb_impl.h"

namespace ocean_kv {
class IndexServiceImpl : public IndexService {
public:
    IndexServiceImpl() {};
    virtual ~IndexServiceImpl() {};
    virtual void GetIndexInfo(google::protobuf::RpcController* cntl_base,
                      const GetIndexInfoRequest* request,
                      GetIndexInfoResponse* response,
                      google::protobuf::Closure* done);
    virtual void SetIndexInfo(google::protobuf::RpcController* cntl_base,
                      const SetIndexInfoRequest* request,
                      SetIndexInfoResponse* response,
                      google::protobuf::Closure* done);

    void Init();
private:
    TransactionRocksDB *_transaction_db;
};
}  // namespace ocean_kv
