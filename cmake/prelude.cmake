
#======================================== TOP LEVEL CHECK =========================================#

if(CMAKE_SOURCE_DIR STREQUAL CMAKE_CURRENT_SOURCE_DIR)
	set(zasm_is_top_level TRUE)
else()
	set(zasm_is_top_level FALSE)
endif()

#======================================= SETUP DIRECTORIES ========================================#

macro(make_directory_if_not_exists dir)
	if (NOT IS_DIRECTORY ${dir})
		file(MAKE_DIRECTORY ${dir})
	endif()
endmacro()

string(TOLOWER ${CMAKE_CXX_COMPILER_ID} zasm_compiler_id)
set(zasm_out ${zasm_root}/out/${zasm_compiler_id})
make_directory_if_not_exists(${zasm_out})

#============================================ INCLUDES ============================================#

include(${zasm_root}/cmake/tools.cmake)
include(GenerateExportHeader)

#=========================================== UTILITIES ============================================#

find_program(CCACHE_FOUND ccache)
if (CCACHE_FOUND)
	message(STATUS "Ccache found")
	set_property(GLOBAL PROPERTY RULE_LAUNCH_COMPILE ccache)
endif()

#======================================= PLATFORM DETECTION =======================================#

string(TOLOWER ${CMAKE_HOST_SYSTEM_NAME} zasm_platform)

message(STATUS "Detected OS: ${zasm_platform}")

#========================================== CXX STANDARD ==========================================#

set_standards(
	CPP_STD 20
	C_STD   17
)

#========================================== DEFINITIONS ===========================================#

string(TOUPPER ${zasm_platform} _platform)
add_compile_definitions(
	ZASM_${_platform}                        # ZASM_WINDOWS, ZASM_LINUX, etc.
	ZASM_$<IF:$<CONFIG:Debug>,DEBUG,RELEASE> # ZASM_DEBUG, ZASM_RELEASE
	$<$<CXX_COMPILER_ID:MSVC>:_CRT_SECURE_NO_WARNINGS>
)
unset(_platform)

#========================================= COMPILER FLAGS =========================================#

