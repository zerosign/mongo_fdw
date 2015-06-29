# mongo_fdw/Makefile
#
# Copyright (c) 2012-2014 Citus Data, Inc.
#

MODULE_big = mongo_fdw

#
# We assume we are running on a POSIX compliant system (Linux, OSX). If you are
# on another platform, change env_posix.os in MONGO_OBJS with the appropriate
# environment object file.
#

# MONGO_PATH = $(MONGO_DRIVER)/src
# MONGO_OBJS = $(MONGO_PATH)/bson.os $(MONGO_PATH)/encoding.os $(MONGO_PATH)/md5.os \
#              $(MONGO_PATH)/mongo.os $(MONGO_PATH)/numbers.os $(MONGO_PATH)/env_posix.os

PG_CPPFLAGS = --std=c99 -I/usr/include/libmongoc-1.0 -I/usr/include/libbson-1.0 -lsasl2 -lssl -lcrypto -lrt -lmongoc-1.0 -lbson-1.0 
OBJS = mongo_fdw.o mongo_query.o

EXTENSION = mongo_fdw
DATA = mongo_fdw--1.0.sql

$(MONGO_DRIVER)/%.os:
	$(MAKE) -C $(MONGO_DRIVER) $*.os

#
# Users need to specify their Postgres installation path through pg_config. For
# example: /usr/local/pgsql/bin/pg_config or /usr/lib/postgresql/9.1/bin/pg_config
#

PG_CONFIG = pg_config
PGXS := $(shell $(PG_CONFIG) --pgxs)
include $(PGXS)
