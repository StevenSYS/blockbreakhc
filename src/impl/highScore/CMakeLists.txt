if(HSSIMPL STREQUAL "Dummy")
	set(HSSIMPL_FILES "dummy.c")
else()
	message(FATAL_ERROR "Invalid high score saving implementation, the only possible value is \"Dummy\"")
endif()

add_library(HSSImpl STATIC ${HSSIMPL_FILES})