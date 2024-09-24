#ifndef TEST_MACROS_H
#define TEST_MACROS_H
#define ADD_TEST(test)                             \
    if (NULL == CU_add_test(suite, #test, test)) { \
        CU_cleanup_registry();                     \
        return CU_get_error();                     \
    }

#define CU_ASSERT_THROWS_ERROR(func) CU_ASSERT_TRUE(func < 0)
#endif