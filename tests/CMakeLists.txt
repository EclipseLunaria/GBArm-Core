cmake_minimum_required(VERSION 3.10)

project(arm_core_tests C) 

include_directories(../include)
include_directories(../internal)
add_subdirectory(lib/cunit/CUnit)

add_executable(run_tests
    test_main.c
    test_macros.h
    test_macros.c
    ../include/core.h
    ../src/registers.c
    ../src/branch.c
    ../src/cpu.c
    ../src/memory_bus.c
    ../src/alu.c
    ../src/barrel_shifter.c
    ../src/constants.c
    ../src/instruction.c
    ../src/multiply.c
    ../src/data_transfer.c
    ../src/psr.c
    ../src/interrupt.c
    ../src/utils.c

    ./alu_tests.c
    ./barrel_shifter_tests.c
    ./data_transfer_tests.c
    ./instruction_tests.c
    ./memory_bus_tests.c
    ./multiply_tests.c
    ./multiply_long_tests.c
    ./register_tests.c
    ./utils_tests.c
    )

target_link_libraries(run_tests
    cunit
)
