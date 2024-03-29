# Licensed to the Apache Software Foundation (ASF) under one
# or more contributor license agreements.  See the NOTICE file
# distributed with this work for additional information
# regarding copyright ownership.  The ASF licenses this file
# to you under the Apache License, Version 2.0 (the
# "License"); you may not use this file except in compliance
# with the License.  You may obtain a copy of the License at
#
#   http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing,
# software distributed under the License is distributed on an
# "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY
# KIND, either express or implied.  See the License for the
# specific language governing permissions and limitations
# under the License.

NEED_GPERFTOOLS=0
BRPC_PATH=../../../deploy/brpc-1.1.0
include $(BRPC_PATH)/config.mk
include ../../../deploy/rocksdb_7.2.2/make_config.mk
# Notes on the flags:
# 1. Added -fno-omit-frame-pointer: perf/tcmalloc-profiler use frame pointers by default
# 2. Added -D__const__= : Avoid over-optimizations of TLS variables by GCC>=4.8
CXXFLAGS+=$(CPPFLAGS) -std=c++17 -DNDEBUG -O2 -D__const__= -pipe -W -Wall -Wno-unused-parameter -fPIC -fno-omit-frame-pointer $(PLATFORM_LDFLAGS) $(PLATFORM_CXXFLAGS) $(EXEC_LDFLAGS)
ifeq ($(NEED_GPERFTOOLS), 1)
	CXXFLAGS+=-DBRPC_ENABLE_CPU_PROFILER
endif
HDRS+=$(BRPC_PATH)/output/include
HDRS+=../../../deploy/rocksdb_7.2.2/include
LIBS+=$(BRPC_PATH)/output/lib
LIBS+=../../../deploy/rocksdb_7.2.2

HDRPATHS=$(addprefix -I, $(HDRS))
LIBPATHS=$(addprefix -L, $(LIBS))
COMMA=,
SOPATHS=$(addprefix -Wl$(COMMA)-rpath$(COMMA), $(LIBS))

CLIENT_SOURCES = client.cpp
SERVER_SOURCES = server.cpp server_impl.cpp rocksdb_impl.cpp transaction_rocksdb_impl.cpp
PROTOS = $(wildcard *.proto)

PROTO_OBJS = $(PROTOS:.proto=.pb.o)
PROTO_GENS = $(PROTOS:.proto=.pb.h) $(PROTOS:.proto=.pb.cc)
CLIENT_OBJS = $(addsuffix .o, $(basename $(CLIENT_SOURCES))) 
SERVER_OBJS = $(addsuffix .o, $(basename $(SERVER_SOURCES))) 

ifeq ($(SYSTEM),Darwin)
 ifneq ("$(LINK_SO)", "")
	STATIC_LINKINGS += -lbrpc
 else
	# *.a must be explicitly specified in clang
	STATIC_LINKINGS += $(BRPC_PATH)/output/lib/libbrpc.a
 endif
	LINK_OPTIONS_SO = $^ $(STATIC_LINKINGS) $(DYNAMIC_LINKINGS)
	LINK_OPTIONS = $^ $(STATIC_LINKINGS) $(DYNAMIC_LINKINGS)
else ifeq ($(SYSTEM),Linux)
	STATIC_LINKINGS += -lbrpc
	LINK_OPTIONS_SO = -Xlinker "-(" $^ -Xlinker "-)" $(STATIC_LINKINGS) $(DYNAMIC_LINKINGS)
	LINK_OPTIONS = -Xlinker "-(" $^ -Wl,-Bstatic $(STATIC_LINKINGS) -Wl,-Bdynamic -Xlinker "-)" $(DYNAMIC_LINKINGS)
endif

STATIC_LINKINGS += ../../../deploy/rocksdb_7.2.2/librocksdb.a

ifndef DISABLE_JEMALLOC
	ifdef JEMALLOC
		PLATFORM_CXXFLAGS += -DROCKSDB_JEMALLOC -DJEMALLOC_NO_DEMANGLE
	endif
	EXEC_LDFLAGS := $(JEMALLOC_LIB) $(EXEC_LDFLAGS) -lpthread
	PLATFORM_CXXFLAGS += $(JEMALLOC_INCLUDE)
endif

ifneq ($(USE_RTTI), 1)
	#CXXFLAGS += -fno-rtti
endif

CFLAGS += -Wstrict-prototypes

.PHONY:all
all: index_client index_server

.PHONY:clean
clean:
	@echo "> Cleaning"
	rm -rf index_client index_server $(PROTO_GENS) $(PROTO_OBJS) $(CLIENT_OBJS) $(SERVER_OBJS)

index_client:$(PROTO_OBJS) $(CLIENT_OBJS)
	@echo "> Linking $@"
ifneq ("$(LINK_SO)", "")
	$(CXX) $(LIBPATHS) $(SOPATHS) $(LINK_OPTIONS_SO) -o $@
else
	$(CXX) $(LIBPATHS) $(LINK_OPTIONS) -o $@
endif

index_server:$(PROTO_OBJS) $(SERVER_OBJS)
	@echo "> Linking $@"
ifneq ("$(LINK_SO)", "")
	$(CXX) $(LIBPATHS) $(SOPATHS) $(LINK_OPTIONS_SO) -o $@
else
	$(CXX) $(LIBPATHS) $(LINK_OPTIONS) -o $@
endif

%.pb.cc %.pb.h:%.proto
	@echo "> Generating $@"
	$(PROTOC) --cpp_out=. --proto_path=. $(PROTOC_EXTRA_ARGS) $<

%.o:%.cpp
	@echo "> Compiling $@"
	$(CXX) -c $(HDRPATHS) $(CXXFLAGS) $< -o $@

%.o:%.cc
	@echo "> Compiling $@"
	$(CXX) -c $(HDRPATHS) $(CXXFLAGS) $< -o $@
