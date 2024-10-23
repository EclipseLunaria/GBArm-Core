#include "test_macros.h"
#include "registers.h"

void ASSERT_REGISTER_EQUALS(reg_t reg, uint32_t expected, CpuRegister* registers) {
    uint32_t value;
    read_register(reg, registers, &value);
    CU_ASSERT_EQUAL(value, expected);
}
