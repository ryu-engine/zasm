cmake_minimum_required(VERSION 3.25)

set(zasm_root ${CMAKE_CURRENT_SOURCE_DIR})

project(zasm
	VERSION 0.1.0
	DESCRIPTION "zasm - zen assembly language"
	LANGUAGES CXX
)

include(${zasm_root}/cmake/prelude.cmake)

file(GLOB_RECURSE zasm_headers CONFIGURE_DEPENDS ${zasm_root}/code/include/*.h)

add_library(${PROJECT_NAME} INTERFACE ${zasm_headers})
add_library(${PROJECT_NAMESPACE}::assembly ALIAS ${PROJECT_NAME})
# Should be zen::assembly

target_include_directories(${PROJECT_NAME} INTERFACE
	${zasm_root}/code/include
	${PROJECT_BINARY_DIR}/include
)
set_target_properties(${PROJECT_NAME} PROPERTIES
	CXX_VISIBILITY_PRESET hidden
	CXX_EXTENSIONS OFF
	C_EXTENSIONS OFF
	VISIBILITY_INLINES_HIDDEN 1
)

install(TARGETS ${PROJECT_NAME} DESTINATION ${zasm_out}/$<IF:$<CONFIG:Debug>,debug,release>/lib/)
install(
	FILES
		${zasm_headers}
	DESTINATION
		${zasm_out}/$<IF:$<CONFIG:Debug>,debug,release>/include
)
