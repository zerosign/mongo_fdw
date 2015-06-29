/*-------------------------------------------------------------------------
 *
 * mongo_fdw.h
 *
 * Type and function declarations for MongoDB foreign data wrapper.
 *
 * Copyright (c) 2012-2014 Citus Data, Inc.
 *
 *-------------------------------------------------------------------------
 */

#ifndef MONGO_FDW_H
#define MONGO_FDW_H

#include <bson.h>
#include <mongoc.h>

#include "fmgr.h"
#include "catalog/pg_foreign_server.h"
#include "catalog/pg_foreign_table.h"
#include "utils/datetime.h"
#include "nodes/pg_list.h"
#include "nodes/relation.h"
#include "utils/timestamp.h"


/* Defines for valid option names */
#define OPTION_NAME_ADDRESS "address"
#define OPTION_NAME_PORT "port"
#define OPTION_NAME_DATABASE "database"
#define OPTION_NAME_COLLECTION "collection"

/* Default values for option parameters */
#define DEFAULT_IP_ADDRESS "127.0.0.1"
#define DEFAULT_PORT_NUMBER 27017
#define DEFAULT_DATABASE_NAME "test"

/* Defines for sending queries and converting types */
#define EQUALITY_OPERATOR_NAME "="
#define INITIAL_ARRAY_CAPACITY 8
#define MONGO_TUPLE_COST_MULTIPLIER 5
#define MONGO_CONNECTION_COST_MULTIPLIER 5
#define POSTGRES_TO_UNIX_EPOCH_DAYS (POSTGRES_EPOCH_JDATE - UNIX_EPOCH_JDATE)
#define POSTGRES_TO_UNIX_EPOCH_USECS (POSTGRES_TO_UNIX_EPOCH_DAYS * USECS_PER_DAY)


/*
 * MongoValidOption keeps an option name and a context. When an option is passed
 * into mongo_fdw objects (server and foreign table), we compare this option's
 * name and context against those of valid options.
 */
typedef struct MongoValidOption
{
	const char *option_name;
	Oid option_context_id;

} MongoValidOption;


/* Array of options that are valid for mongo_fdw */
static const uint32 ValidOptionCount = 4;
static const MongoValidOption ValidOptionArray[] =
{
	/* foreign server options */
	{ OPTION_NAME_ADDRESS, ForeignServerRelationId },
	{ OPTION_NAME_PORT,  ForeignServerRelationId },

	/* foreign table options */
	{ OPTION_NAME_DATABASE, ForeignTableRelationId },
	{ OPTION_NAME_COLLECTION, ForeignTableRelationId }
};


/*
 * MongoFdwOptions holds the option values to be used when connecting to Mongo.
 * To resolve these values, we first check foreign table's options, and if not
 * present, we then fall back to the default values specified above.
 */
typedef struct MongoFdwOptions
{
	char *address_mame;
	int32 port_number;
	char *database_name;
	char *collection_name;
} MongoFdwOptions;


/*
 * MongoFdwExecState keeps foreign data wrapper specific execution state that we
 * create and hold onto when executing the query.
 */
typedef struct MongoFdwExecState {
  struct HTAB *column_mapping_hash;
  mongoc_client_t * client;
  mongoc_cursor_t * mongo_cursor;
  bson_t *query_document;
} MongoFdwExecState;


/*
 * ColumnMapping reprents a hash table entry that maps a column name to column
 * related information. We construct these hash table entries to speed up the
 * conversion from BSON documents to PostgreSQL tuples; and each hash entry maps
 * the column name to the column's tuple index and its type-related information.
 */
typedef struct ColumnMapping
{
	char column_name[NAMEDATALEN];
	uint32 column_index;
	Oid column_type_id;
	int32 column_type_mod;
	Oid column_array_type_id;
} ColumnMapping;


/* Function declarations related to creating the mongo query */
extern List * ApplicableOpExpressionList(RelOptInfo *baserel);
extern bson_t * QueryDocument(Oid relationId, List *opExpressionList);
extern List * ColumnList(RelOptInfo *baserel);

/* Function declarations for foreign data wrapper */
extern Datum mongo_fdw_handler(PG_FUNCTION_ARGS);
extern Datum mongo_fdw_validator(PG_FUNCTION_ARGS);


#endif   /* MONGO_FDW_H */
