cmake_minimum_required(VERSION 3.25)

project(BlockBreakC LANGUAGES C VERSION 1.2)

set(IMPL "GLFW3" CACHE STRING "Select which implementation to build")
option(BUILD_USING_MSVCRT20 "Build ${PROJECT_NAME} using msvcrt20 (Mingw-w64 Required)" OFF)

set(CMAKE_C_FLAGS_DEBUG "-g -Wall")
set(CMAKE_C_FLAGS_RELEASE "-s -O2")

if(WIN32)
	set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wl,-subsystem,windows")
	if(BUILD_USING_MSVCRT20)
		set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -mcrtdll=msvcrt20")
	endif()
else()
	if(BUILD_USING_MSVCRT20)
		message(FATAL_ERROR "To build using msvcrt20 you must be compiling for Windows")
	endif()
endif()

if(IMPL STREQUAL "SDL3")
	find_package(SDL3 REQUIRED)
	include_directories(${SDL3_INCLUDE_DIRS})
	set(IMPL_FILES "src/impl/sdl3.c")
	set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -DFONT_HEIGHT=8")
elseif(IMPL STREQUAL "GLUT")
	find_package(OpenGL REQUIRED)
	find_package(GLUT REQUIRED)
	include_directories(${OPENGL_INCLUDE_DIRS})
	set(IMPL_FILES "src/impl/glut.c")
	set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -DFONT_WIDTH=8 -DFONT_HEIGHT=8")
elseif(IMPL STREQUAL "GLFW3")
	find_package(OpenGL REQUIRED)
	find_package(glfw3 REQUIRED)
	include_directories(${OPENGL_INCLUDE_DIRS})
	set(IMPL_FILES "src/impl/glfw3.c")
	set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -DFONT_WIDTH=8 -DFONT_HEIGHT=8")
else()
	message(FATAL_ERROR "Invalid implementation, the possible values are \"SDL3\", \"GLUT\" or \"GLFW3\"")
endif()

file(GLOB SOURCE_FILES ${IMPL_FILES} "src/*.c")

add_executable(${PROJECT_NAME} ${SOURCE_FILES})
if(IMPL STREQUAL "SDL3")
	target_link_libraries(${PROJECT_NAME} SDL3::SDL3)
elseif(IMPL STREQUAL "GLUT")
	target_link_libraries(
		${PROJECT_NAME}
		${OPENGL_LIBRARY}
		${GLUT_glut_LIBRARY}
	)
elseif(IMPL STREQUAL "GLFW3")
	target_link_libraries(
		${PROJECT_NAME}
		${OPENGL_LIBRARY}
		glfw
	)
endif()
target_include_directories(${PROJECT_NAME} PRIVATE src)