#include <stdio.h>
#include <string.h>
#include "include/CUnit/Basic.h"

// gcc -o test unit_test.c -Iinclude -Llib -L/opt/homebrew/lib


static int sum(int a, int b)
{
    if (a > 4) {
        return 0;
    }
    return (a + b);
}

static int suite_init(void)
{
    return 0;
}

static int suite_clean(void)
{
    return 0;
}

static void test_sum(void)
{
    CU_ASSERT_EQUAL(sum(1, 2), 3);
    CU_ASSERT_EQUAL(sum(5, 2), 7);
}

int main()
{
    CU_pSuite pSuite = NULL;

    /* initialize the CUnit test registry */
    if (CUE_SUCCESS != CU_initialize_registry()) {
        return CU_get_error();
    }

    /* add a suite to the registry */
    pSuite = CU_add_suite("suite_sum", suite_init, suite_clean);
    if (NULL == pSuite) {
        CU_cleanup_registry();
        return CU_get_error();
    }

    /* add the tests to the suite */
    if ((NULL == CU_add_test(pSuite, "test_sum", test_sum))) {
        CU_cleanup_registry();
        return CU_get_error();
    }

    /* Run all tests using the CUnit Basic interface */
    CU_basic_set_mode(CU_BRM_VERBOSE);
    CU_basic_run_tests();

    /* Clean up registry and return */
    CU_cleanup_registry();
    return CU_get_error();
}
