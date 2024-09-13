#include <CUnit/CUnit.h>
#include <CUnit/Basic.h>
#include "test_macros.h"
#include "core.h"
#include "utils.h"

void test_sLen(){
    char * word = "hello";
    CU_ASSERT_EQUAL(strlen(word), 5)
}

void test_toLower_all_caps(){
    char all_caps[] = "HELLO WORLD\0";
    toLower(all_caps);
    printf("%s", all_caps);
    CU_ASSERT_TRUE(strcmp("hello world",all_caps) == 0)
}

int add_utils_tests(){
    CU_pSuite suite = CU_add_suite("Utils Tests",0,0);

    if (suite == NULL) return CU_get_error();

    ADD_TEST(test_sLen);
    ADD_TEST(test_toLower_all_caps);
    // Register specified shift amount tests 
    return CUE_SUCCESS;
}