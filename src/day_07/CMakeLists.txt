add_executable(day_07 day_07.cpp)
add_input(day_07 i)
target_include_directories(day_07 PRIVATE ${CMAKE_CURRENT_LIST_DIR})
target_link_libraries(day_07 PRIVATE aoc)