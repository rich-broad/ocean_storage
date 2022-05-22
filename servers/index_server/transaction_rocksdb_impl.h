// Copyright (c) 2011-present, Facebook, Inc.  All rights reserved.
//  This source code is licensed under both the GPLv2 (found in the
//  COPYING file in the root directory) and Apache 2.0 License
//  (found in the LICENSE.Apache file in the root directory).

#include "rocksdb/db.h"
#include "rocksdb/options.h"
#include "rocksdb/slice.h"
#include "rocksdb/utilities/transaction.h"
#include "rocksdb/utilities/transaction_db.h"

using ROCKSDB_NAMESPACE::Options;
using ROCKSDB_NAMESPACE::ReadOptions;
using ROCKSDB_NAMESPACE::Snapshot;
using ROCKSDB_NAMESPACE::Status;
using ROCKSDB_NAMESPACE::Transaction;
using ROCKSDB_NAMESPACE::TransactionDB;
using ROCKSDB_NAMESPACE::TransactionDBOptions;
using ROCKSDB_NAMESPACE::TransactionOptions;
using ROCKSDB_NAMESPACE::WriteOptions;


class TransactionRocksDB {
private:
  // open DB
  Options _options;
  TransactionDBOptions _txn_db_options;
  TransactionDB* _txn_db;

  // 
  WriteOptions _write_options;
  ReadOptions _read_options;
  TransactionOptions _txn_options;

public:
  ~TransactionRocksDB(){
    delete _txn_db; 
    //ROCKSDB_NAMESPACE::DestroyDB(kDBPath, options);
  }
  void Init();
  uint32_t Set(const std::string &key, const std::string &value);
  std::string Get(const std::string &key);
};

