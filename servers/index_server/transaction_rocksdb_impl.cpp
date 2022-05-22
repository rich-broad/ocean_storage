// Copyright (c) 2011-present, Facebook, Inc.  All rights reserved.
//  This source code is licensed under both the GPLv2 (found in the
//  COPYING file in the root directory) and Apache 2.0 License
//  (found in the LICENSE.Apache file in the root directory).
#include "transaction_rocksdb_impl.h"

const std::string kDBPath = "/data/rocksdbs/rocksdb_transaction_db";

void TransactionRocksDB::Init() {
  _options.create_if_missing = true;
  Status s = TransactionDB::Open(_options, _txn_db_options, kDBPath, &_txn_db);
  assert(s.ok());
}

uint32_t TransactionRocksDB::Set(const std::string &key, const std::string &value) {
   // Start a transaction
   Transaction* txn = _txn_db->BeginTransaction(_write_options);
   assert(txn);
   // Write a key in this transaction
   Status s = txn->Put(key, value);
   assert(s.ok());

   // Commit transaction
   s = txn->Commit();
   assert(s.ok());
   delete txn;
   return 0;
}

std::string TransactionRocksDB::Get(const std::string &key) {
  std::string value;
  // get value
  Status s = _txn_db->Get(_read_options, key, &value);
  //assert(s.ok());
  return value;
}