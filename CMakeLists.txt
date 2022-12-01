cmake_minimum_required(VERSION 3.23)
project(advent_of_code_2022)


function(add_input TARGET INPUT_FILE)
    set(current-input-path ${CMAKE_CURRENT_SOURCE_DIR}/input/${INPUT_FILE})
    set(output-input-path ${CMAKE_CURRENT_BINARY_DIR}/input/${INPUT_FILE})
    add_custom_command(
            OUTPUT ${output-input-path}
            COMMAND ${CMAKE_COMMAND} -E make_directory ${CMAKE_CURRENT_BINARY_DIR}/input
            COMMAND ${CMAKE_COMMAND} -E copy ${current-input-path} ${CMAKE_CURRENT_BINARY_DIR}/input
            DEPENDS ${current-input-path}
            IMPLICIT_DEPENDS CXX ${current-input-path}
            VERBATIM)
    set_source_files_properties(${output-input-path} PROPERTIES GENERATED TRUE)
    target_sources(${TARGET} PRIVATE ${output-input-path})

endfunction()


set(CMAKE_CXX_STANDARD 23)

# Libraries
add_subdirectory(lib/aoc)

# Sources
add_subdirectory(src/day_01)
