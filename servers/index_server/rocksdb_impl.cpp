// Copyright (c) 2011-present, Facebook, Inc.  All rights reserved.
//  This source code is licensed under both the GPLv2 (found in the
//  COPYING file in the root directory) and Apache 2.0 License
//  (found in the LICENSE.Apache file in the root directory).
#include "rocksdb_impl.h"

const std::string kDBPath = "/data/rocksdbs/rocksdb_simple_db";

void SimpleRocksDB::Init() {
  // Optimize RocksDB. This is the easiest way to get RocksDB to perform well
  _options.IncreaseParallelism();
  _options.OptimizeLevelStyleCompaction();
  // create the DB if it's not already present
  _options.create_if_missing = true;

  // open DB
  Status s = DB::Open(_options, kDBPath, &_db);
  assert(s.ok());
}

uint32_t SimpleRocksDB::Set(const std::string &key, const std::string &value) {
  // Put key-value
  Status s = _db->Put(WriteOptions(), key, value);
  //assert(s.ok());
  return 0;
}

std::string SimpleRocksDB::Get(const std::string &key) {
  std::string value;
  // get value
  Status s = _db->Get(ReadOptions(), key, &value);
  //assert(s.ok());
  return value;
}