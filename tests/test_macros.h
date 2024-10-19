#ifndef TEST_MACROS_H
#define TEST_MACROS_H

#include <CUnit/Basic.h>
#include <CUnit/CUnit.h>

#include "types.h"

#define ADD_TEST(test)                             \
    if (NULL == CU_add_test(suite, #test, test)) { \
        CU_cleanup_registry();                     \
        return CU_get_error();                     \
    }

void ASSERT_REGISTER_EQUALS(reg_t reg, uint32_t expected, CpuRegister* registers);

#define CU_ASSERT_THROWS_ERROR(func) CU_ASSERT_TRUE(func < 0)
#endif
