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
#include "proxy.pb.h"

namespace ocean_kv {
namespace proxy {
class ProxyServiceImpl : public ProxyService {
public:
    ProxyServiceImpl() {};
    virtual ~ProxyServiceImpl() {};
    virtual void Get(google::protobuf::RpcController* cntl_base,
                      const GetRequest* request,
                      GetResponse* response,
                      google::protobuf::Closure* done);
    virtual void Put(google::protobuf::RpcController* cntl_base,
                      const PutRequest* request,
                      PutResponse* response,
                      google::protobuf::Closure* done);
    virtual void Delete(google::protobuf::RpcController* cntl_base,
                      const DeleteRequest* request,
                      DeleteResponse* response,
                      google::protobuf::Closure* done);

    void Init();
};
}
}  // namespace ocean_kv
