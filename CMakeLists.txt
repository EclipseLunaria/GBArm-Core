cmake_minimum_required(VERSION 3.28)
project(arm_core)

include_directories(./include)
include_directories(./internal)


set(ARM_CORE_SOURCES
    src/alu.c
    src/barrel_shifter.c
    src/constants.c
    src/cpu.c
    src/instruction.c
    src/memory_bus.c
    src/multiply.c
    src/registers.c
    src/utils.c
    src/branch.c
    src/data_transfer.c
    src/psr.c   
)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)


add_executable(test_main
    ./src/main.c
    ${ARM_CORE_SOURCES}
    )
add_library(arm_core STATIC ${ARM_CORE_SOURCES})

target_include_directories(arm_core PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:include>
)

target_include_directories(arm_core PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/internal
)
