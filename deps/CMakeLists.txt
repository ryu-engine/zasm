
set(cur_dir ${CMAKE_CURRENT_SOURCE_DIR})
set(deps)


add_library(zasm_deps INTERFACE)
add_library(zasm::deps ALIAS zasm_deps)

target_link_libraries(zasm_deps INTERFACE ${deps})

unset(cur_dir)