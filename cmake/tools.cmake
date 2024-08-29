
function(set_standards)
	include(CMakeParseArguments)
	cmake_parse_arguments(SET_STANDARD "" "CPP_STD;C_STD" "" ${ARGN})

	if(NOT DEFINED SET_STANDARD_CPP_STD)
		set(SET_STANDARD_CPP_STD 17)
	endif()

	if (NOT DEFINED SET_STANDARD_C_STD)
		set(SET_STANDARD_C_STD 11)
	endif()

	set(CMAKE_CXX_STANDARD ${SET_STANDARD_CPP_STD} PARENT_SCOPE)
	set(CMAKE_CXX_STANDARD_REQUIRED ON PARENT_SCOPE)
	set(CMAKE_CXX_EXTENSIONS OFF PARENT_SCOPE)

	set(CMAKE_C_STANDARD ${SET_STANDARD_C_STD} PARENT_SCOPE)
	set(CMAKE_C_STANDARD_REQUIRED ON PARENT_SCOPE)
	set(CMAKE_C_EXTENSIONS OFF PARENT_SCOPE)

	if(MSVC_VERSION GREATER_EQUAL "1900" AND CMAKE_VERSION LESS 3.10)
		include(CheckCXXCompilerFlag)

		check_cxx_compiler_flag("/std:c++${SET_STANDARD_CPP_STD}" _cpp_latest_flag_supported)
		if(_cpp_latest_flag_supported)
			add_compile_options("/std:c++${SET_STANDARD_CPP_STD}")
		endif()

		check_cxx_compiler_flag("/std:c${SET_STANDARD_C_STD}" _c_latest_flag_supported)
		if(_c_latest_flag_supported)
			add_compile_options("/std:c${SET_STANDARD_C_STD}")
		endif()
	endif()
endfunction()
