cmake_minimum_required(VERSION 3.25)

project(BlockBreakC LANGUAGES C VERSION 1.2)

set(IMPL "GLFW3" CACHE STRING "The implementation to build with")
set(HSSIMPL "Dummy" CACHE STRING "The high score saving implementation to build with")
option(BUILD_USING_MSVCRT20 "Build ${PROJECT_NAME} using msvcrt20 (Mingw-w64 Required)" OFF)
option(BUILD_SHARED_LIBS "Build implementation as a shared library" OFF)
option(BUILD_ONLY_LIBRARY "Build only the implementation library file")

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -DFONT_WIDTH=8 -DFONT_HEIGHT=8")
set(CMAKE_C_FLAGS_DEBUG "-g -Wall")
set(CMAKE_C_FLAGS_RELEASE "-s -O2")

if(WIN32)
	set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wl,-subsystem,windows")
	if(BUILD_USING_MSVCRT20)
		set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -mcrtdll=msvcrt20")
	endif()
elseif(NOT WIN32 AND BUILD_USING_MSVCRT20)
	message(FATAL_ERROR "To build using msvcrt20 you must be compiling for Windows")
endif()

add_subdirectory(src/impl)

if(NOT BUILD_ONLY_LIBRARY)
	if(HSSIMPL STREQUAL "Dummy")
		set(HSSIMPL_FILES "src/impl/highScore/dummy.c")
	else()
		message(FATAL_ERROR "Invalid high score saving implementation, the only possible value is \"Dummy\"")
	endif()
	
	file(GLOB SOURCE_FILES "src/*.c")
	add_executable(${PROJECT_NAME} ${HSSIMPL_FILES} ${SOURCE_FILES})
	target_link_libraries(${PROJECT_NAME} Impl)
	target_include_directories(${PROJECT_NAME} PRIVATE src)
endif()