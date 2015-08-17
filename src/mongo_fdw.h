#ifndef MONGO_FDW_H
#define MONGO_FDW_H

#define STRING_OPTION_ADDRESS    "address"
#define STRING_OPTION_PORT       "port"
#define STRING_OPTION_DATABASE   "database"
#define STRING_OPTION_COLLECTION "collection"

/**
 * MongoDB Foreign wrapper options.
 *
 */
typedef struct ForeignOptions {
  char * host;
  int32  port;
  char * database;
  char * collection;
} ForeignOptions;

extern Datum mongo_fdw_handler(PG_FUNCTION_ARGS);
extern Datum mongo_fdw_validator(PG_FUNCTION_ARGS);

#endif


