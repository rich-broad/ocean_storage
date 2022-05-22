// Copyright (c) 2011-present, Facebook, Inc.  All rights reserved.
//  This source code is licensed under both the GPLv2 (found in the
//  COPYING file in the root directory) and Apache 2.0 License
//  (found in the LICENSE.Apache file in the root directory).
#include "simple_example.h"

const std::string kDBPath = "/data/rocksdbs/rocksdb_simple_example";

void SimpleRocksDB::Init() {
  // Optimize RocksDB. This is the easiest way to get RocksDB to perform well
  options.IncreaseParallelism();
  options.OptimizeLevelStyleCompaction();
  // create the DB if it's not already present
  options.create_if_missing = true;

  // open DB
  Status s = DB::Open(options, kDBPath, &db);
  assert(s.ok());
}

uint32_t SimpleRocksDB::Set(const std::string &key, const std::string &value) {
  // Put key-value
  Status s = db->Put(WriteOptions(), key, value);
  //assert(s.ok());
  return 0;
}

std::string SimpleRocksDB::Get(const std::string &key) {
  std::string value;
  // get value
  Status s = db->Get(ReadOptions(), key, &value);
  //assert(s.ok());
  return value;
}