project(arm_core)

include_directories(./include)
include_directories(./internal)

set(ARM_CORE_HEADERS
    include/core.h
    include/alu.h
    include/barrel_shifter.h
    include/constants.h
    include/error.h
    include/memory_bus.h
    include/multiply.h
    include/registers.h
    include/types.h
    include/utils.h
)

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
)

add_library(arm_core STATIC ${ARM_CORE_SOURCES})

target_include_directories(arm_core PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:include>
)

