#include <CUnit/CUnit.h>
#include <CUnit/Basic.h>
#include "test_macros.h"
#include "core.h"
#include "utils.h"

void test_ishexadecimal() {
    char * h1 = "0xFF";
    char * h2 = "0xGG";
    char * h3 = "abc";
    char * h4 = "FF";

    CU_ASSERT_TRUE(ishexadecimal(h1))
    CU_ASSERT_FALSE(ishexadecimal(h2))
    CU_ASSERT_FALSE(ishexadecimal(h3))
    CU_ASSERT_FALSE(ishexadecimal(h4))
}

void test_read_hexadecimal(){
    char * h1 = "0xFF";
    char * h2 = "0xGG";
    char * h3 = "abc";
    char * h4 = "FF";

    uint32_t v1;
    uint32_t v2;
    uint32_t v3;
    uint32_t v4;
    int s1 = readhexadecimal(h1, &v1);
    int s2 = readhexadecimal(h2, &v2);
    int s3 = readhexadecimal(h3, &v3);
    int s4 = readhexadecimal(h4, &v4);

    CU_ASSERT_EQUAL(s1, 1)
    CU_ASSERT_EQUAL(v1, 0xFF)

    CU_ASSERT_EQUAL(s2, 0)

    CU_ASSERT_EQUAL(s3, 1)
    CU_ASSERT_EQUAL(v3, 0xABC)
    
    CU_ASSERT_EQUAL(s4, 1)
    CU_ASSERT_EQUAL(v4, 0xFF)

}

int add_utils_tests(){
    CU_pSuite suite = CU_add_suite("Utils Tests",0,0);

    if (suite == NULL) return CU_get_error();
    ADD_TEST(test_ishexadecimal)
    ADD_TEST(test_read_hexadecimal)
    // Register specified shift amount tests 
    return CUE_SUCCESS;
}