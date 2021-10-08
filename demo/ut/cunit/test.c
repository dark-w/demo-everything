#include <CUnit/Basic.h>

#include "foo.h"

void test_add(void)
{
    CU_ASSERT(33 == add(11, 22));
    CU_ASSERT(-77 == add(-33, -44));
}

int main(void)
{
    CU_pSuite pSuite;

    CU_initialize_registry();
    pSuite = CU_add_suite("Suite 1", NULL, NULL);
    CU_add_test(pSuite, "test of add()", test_add);

    int fails = CU_basic_run_tests();

    CU_cleanup_registry();
    return fails > 0;
}
