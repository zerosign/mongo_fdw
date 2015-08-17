#include "mongo_fdw.h"

PG_MODULE_MAGIC;
PG_FUNCTION_INFO_V1(mongo_fdw_handler);
PG_FUNCTION_INFO_V1(mongo_fdw_validator);

Datum mongo_fdw_handler(PG_FUNCTION_ARGS) {
  const FdwRoutine * routine = makeNode(FdwRoutine);

  routine->GetForeignRelSize = NULL;
  routine->GetForeignPaths = NULL;
  routine->GetForeignPlan = NULL;
  routine->ExplainForeignScan = NULL;
  routine->BeginForeignScan = NULL;
  routine->IterateForeignScan = NULL;
  routine->ReScanForeignScan = NULL;
  routine->EndForeignScan = NULL;
  routine->AnalyzeForeignTable = NULL;

  PG_RETURN_POINTER(routine);
}

Datum mongo_fdw_validator(PG_FUNCTION_ARGS) {
  const List * options = untransformRelOptions(PG_GETARG_DATUM(0));
  Oid context_id = PG_GETARG_OID(1);

  PG_RETURN_VOID();
}
