#include <string.h>

#include "munit.h"

#include "schreme_hash.h"

static MunitResult insert_small(const MunitParameter params[], void* data)
{
  uint32_t key = 8;
  const char* payload = "value1";
  schreme_tbl_val val;
  int payload_size = strlen(payload);
  val.size = payload_size;
  val.data = (uint8_t*) payload;
  
  schreme_fkey_lookup_table tbl;
  schreme_fkey_lookup_table_init(&tbl);
  schreme_fkey_lookup_table_insert(&tbl, key, val);

  val.size = 0;
  val.data = NULL;
  schreme_fkey_lookup_table_lookup(&tbl, key, &val);

  munit_assert( val.size == payload_size );
  munit_assert( memcmp(val.data, payload, payload_size)  == 0 );
}

static MunitTest tests[] =
{
  {"insert_small", insert_small, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL},
  {NULL, NULL, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL}
};

static const MunitSuite test_suite =
{
  "schreme_hash",
  tests,
  NULL,
  1,
  MUNIT_SUITE_OPTION_NONE
};

int main(int argc, char* argv[MUNIT_ARRAY_PARAM(argc + 1)])
{
  return munit_suite_main(&test_suite, NULL, argc, argv);
}
