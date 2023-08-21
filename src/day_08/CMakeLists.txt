add_executable(day_08 day_08.cpp)
add_input(day_08 i)
target_include_directories(day_08 PRIVATE ${CMAKE_CURRENT_LIST_DIR})
target_link_libraries(day_08 PRIVATE aoc)