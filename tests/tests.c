#include "munit.h"

#include "schreme_hash.h"

static MunitResult insert_small(const MunitParameter params[], void* data)
{
  munit_assert( 1 == 1 );
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
