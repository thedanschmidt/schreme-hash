#include <stdio.h>
#include <string.h>

#include "munit.h"

#include "schreme_hash.h"

static MunitResult insert_one(const MunitParameter params[], void* data)
{
  uint32_t key = 8;
  const char* payload = "value1";
  schreme_tbl_val val;
  int payload_size = strlen(payload) + 1;
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
  return MUNIT_OK;
}

static MunitResult insert_few(const MunitParameter params[], void* data)
{
  uint32_t keys[] = {3, 5, 424242, 999};
  const char* payloads[] = {"value1", "value2", "value3", 
                          "aaaaaaaaaaaaaaaaaaaabbbbbbbbbbbbzzzzzzzzzzzzzzzzz"};

  schreme_fkey_lookup_table tbl;
  schreme_fkey_lookup_table_init(&tbl);
  schreme_tbl_val val;
  for (int i = 0; i < 4; ++i)
  {
    int payload_size = strlen(payloads[i]) + 1;
    val.size = payload_size;
    val.data = (uint8_t*) payloads[i];
    schreme_fkey_lookup_table_insert(&tbl, keys[i], val);
  }

  val.size = 0;
  val.data = NULL;
  schreme_fkey_lookup_table_lookup(&tbl, 424242, &val);

  munit_assert( val.size == 7 );
  munit_assert( memcmp(val.data, "value3", 7)  == 0 );
  return MUNIT_OK;
}

static MunitTest tests[] =
{
  {"insert_one", insert_one, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL},
  {"insert_few", insert_one, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL},
  {NULL, NULL, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL}
};

static const MunitSuite test_suite =
{
  "schreme_table_",
  tests,
  NULL,
  1,
  MUNIT_SUITE_OPTION_NONE
};

int main(int argc, char* argv[MUNIT_ARRAY_PARAM(argc + 1)])
{
  return munit_suite_main(&test_suite, NULL, argc, argv);
}
