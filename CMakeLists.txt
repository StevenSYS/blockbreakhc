cmake_minimum_required(VERSION 3.10)

set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})

project(BlockBreakC LANGUAGES C VERSION 1.2)

set(IMPL "GLFW3" CACHE STRING "The implementation to build with")
set(HSSIMPL "Dummy" CACHE STRING "The high score saving implementation to build with")
option(BUILD_FOR_OLDWIN "Build ${PROJECT_NAME} for Windows 95 or higher" OFF)
if (BUILD_FOR_OLDWIN)
	set(BUILD_USING_MSVCRT20 ON)
else()
	option(BUILD_USING_MSVCRT20 "Build ${PROJECT_NAME} using msvcrt20 (Windows Compiler Required)" OFF)
endif()
option(BUILD_SHARED_LIBS "Build the libraries as shared libraries" OFF)
option(BUILD_ONLY_IMPL "Build only the implementation library" OFF)
option(BUILD_AS_LIBRARY "Build the game as a library" OFF)

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -DFONT_WIDTH=8 -DFONT_HEIGHT=8")
set(CMAKE_C_FLAGS_DEBUG "-g -Wall")
set(CMAKE_C_FLAGS_RELEASE "-s -O2")

include_directories(
	"src/random"
	"src/impl"
)

if(BUILD_FOR_OLDWIN)
	set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -march=i586 -fcf-protection=none")
elseif(NOT WIN32 AND BUILD_FOR_OLDWIN)
	message(FATAL_ERROR "To build for Windows 95 or higher you must be compiling for Windows")
endif()

if(WIN32)
	set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wl,-subsystem,windows")
	if(BUILD_USING_MSVCRT20)
		set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -mcrtdll=msvcrt20")
	endif()
elseif(NOT WIN32 AND BUILD_USING_MSVCRT20)
	message(FATAL_ERROR "To build using msvcrt20 you must be compiling for Windows")
endif()

if(HSSIMPL STREQUAL "Dummy")
	set(HSSIMPL_FILES "src/impl/highScore/dummy.c")
else()
	message(FATAL_ERROR "Invalid high score saving implementation, the only possible value is \"Dummy\"")
endif()

add_library(Random "src/random/random.c")

add_subdirectory(src/impl)

if(NOT BUILD_ONLY_LIBRARY)
	file(GLOB SOURCE_FILES "src/*.c")
	
	if(BUILD_AS_LIBRARY)
		add_library(${PROJECT_NAME} ${HSSIMPL_FILES} ${SOURCE_FILES})
	else()
		add_executable(${PROJECT_NAME} ${HSSIMPL_FILES} ${SOURCE_FILES})
		target_include_directories(${PROJECT_NAME} PRIVATE src)
	endif()
	target_link_libraries(${PROJECT_NAME} Impl Random)
endif()