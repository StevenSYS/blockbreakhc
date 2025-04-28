cmake_minimum_required(VERSION 3.25)

project(BlockBreakC LANGUAGES C VERSION 1.1)

set(CMAKE_C_FLAGS_DEBUG "-g -Wall")
set(CMAKE_C_FLAGS_RELEASE "-s -O2")

if (WIN32)
	set(CMAKE_C_FLAGS "-Wl,-subsystem,windows")
endif()

file(GLOB SOURCE_FILES "src/*.c")

find_package(SDL3 REQUIRED)
include_directories(${SDL3_INCLUDE_DIRS})

configure_file(src/progInfo.h.in ${CMAKE_CURRENT_SOURCE_DIR}/src/progInfo.h @ONLY)

add_executable(${PROJECT_NAME} ${SOURCE_FILES})
target_link_libraries(${PROJECT_NAME} SDL3)
target_include_directories(${PROJECT_NAME} PRIVATE src)