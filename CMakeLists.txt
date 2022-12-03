cmake_minimum_required(VERSION 3.23)
project(advent_of_code_2022)


function(add_input TARGET INPUT_FILE)
    set(input_path ${CMAKE_CURRENT_SOURCE_DIR}/${INPUT_FILE})
    set(output_path ${CMAKE_CURRENT_BINARY_DIR}/${INPUT_FILE})
    get_filename_component(output_dir ${output_path} DIRECTORY)
    add_custom_command(
            OUTPUT ${output_path}
            COMMAND ${CMAKE_COMMAND} -E make_directory ${output_dir}
            COMMAND ${CMAKE_COMMAND} -E copy ${input_path} ${output_dir}
            DEPENDS ${input_path}
            IMPLICIT_DEPENDS CXX ${input_path}
            VERBATIM)
    set_source_files_properties(${output_path} PROPERTIES GENERATED TRUE)
    target_sources(${TARGET} PRIVATE ${output_path})

endfunction()


set(CMAKE_CXX_STANDARD 23)

# Libraries
add_subdirectory(lib/aoc)

# Sources
add_subdirectory(src/day_01)
add_subdirectory(src/day_02)
