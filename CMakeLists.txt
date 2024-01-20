cmake_minimum_required(VERSION 3.13)

set(CMAKE_TRY_COMPILE_TARGET_TYPE "STATIC_LIBRARY")

project(uart_test
		VERSION 1.0
                DESCRIPTION "uart_test"
		LANGUAGES CXX C ASM)

SET(CMAKE_VERBOSE_MAKEFILE)

#include(${CMAKE_CURRENT_SOURCE_DIR}/gcc_stm32.cmake)

if (NOT CMAKE_SYSTEM_NAME STREQUAL CMAKE_HOST_SYSTEM_NAME )

# PC-Lint function
if (${INCLUDE_LINT})
if(EXISTS ${TOOLCHAIN_PREFIX}/pc-lint2.cmake)
    include(${TOOLCHAIN_PREFIX}/pc-lint2.cmake)
endif()
endif()

add_definitions(-DMCU_TARGET)

set(STARTUP_CODE_DIR ${CMAKE_CURRENT_SOURCE_DIR})

message("STARTUP_CODE_DIR = " ${STARTUP_CODE_DIR})

set(LINKER_SCRIPTS_DIR ${CMAKE_CURRENT_SOURCE_DIR})
message("LINKER_SCRIPTS_DIR = " ${LINKER_SCRIPTS_DIR})

message (STATUS "CMAKE_TOOLCHAIN_FILE = " ${CMAKE_TOOLCHAIN_FILE})
message(STATUS "CMAKE_CURRENT_SOURCE_DIR = " ${CMAKE_CURRENT_SOURCE_DIR})

set(CMAKE_ASM_FLAGS "${CMAKE_ASM_FLAGS} -Wall -fdata-sections -ffunction-sections")

set(GCC_COMPILE_FLAGS "${GCC_COMPILE_FLAGS} -Wall -fmessage-length=0 -ffunction-sections --specs=nano.specs")
set(GCC_CXX_COMPILE_FLAGS  "-Wall -fmessage-length=0 -ffunction-sections -fdata-sections -fomit-frame-pointer -mabi=aapcs -fno-unroll-loops -ffast-math -ftree-vectorize -fno-use-cxa-atexit --specs=nano.specs -std=c++11 -fno-exceptions -fno-rtti")

set(CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} ${GCC_CXX_COMPILE_FLAGS}")
set(CMAKE_C_FLAGS  "${CMAKE_C_FLAGS} ${GCC_COMPILE_FLAGS}")


# Cmake MCU Targets:
#include(${CMAKE_CURRENT_SOURCE_DIR}/uart_test_debug_sources_list.cmake)

message(STATUS "CMAKE_CXX_FLAGS = " ${CMAKE_CXX_FLAGS})
message(STATUS "CMAKE_C_FLAGS = " ${CMAKE_C_FLAGS})

if(COMMAND add_pc_lint)
# establish list of compile defifntiond
	set (comp_defs_list)
	list(APPEND comp_defs_list ${D_MCU})
	list(APPEND comp_defs_list ${D_MCU_EXACT})
	list(APPEND comp_defs_list ${D_HSE_VAL})

# fantastic loop
	foreach(s IN LISTS ${EXEC_NAME}_LIST_OF_SOURCES)

		set(t_name)
		string(REPLACE "/" "_" t_name ${s})

		add_pc_lint(
# compile defines
				"${comp_defs_list}"
# target
				${t_name}
				${EXEC_NAME}
				${s}
				)
	endforeach()
endif(COMMAND add_pc_lint)

else()
	message("Non-MCU target detected")

		include(${CMAKE_CURRENT_SOURCE_DIR}/uart_test_desktop.cmake)

	add_definitions(-DDESKTOP_TARGET)
		add_executable(tests ${GROUP_SRC_I386} ${LIST_OF_SOURCES})

endif()

MESSAGE("*********************")
message("CMAKE_SYSTEM_NAME = " ${CMAKE_SYSTEM_NAME} "      CMAKE_HOST_SYSTEM_NAME = " ${CMAKE_HOST_SYSTEM_NAME})
message("CMAKE_SYSTEM = " ${CMAKE_SYSTEM} "      CMAKE_HOST_SYSTEM = " ${CMAKE_HOST_SYSTEM})
MESSAGE("CMAKE_C_COMPILER = " ${CMAKE_C_COMPILER})
MESSAGE("CMAKE_BUILD_TYPE = " ${CMAKE_BUILD_TYPE})
MESSAGE("*********************")
