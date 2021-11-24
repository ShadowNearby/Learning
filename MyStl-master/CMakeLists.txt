cmake_minimum_required(VERSION 3.15)
project(MyStl)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(MyStl
#        test/deque_test.cpp
        test/list_test.cpp
#        test/map_test.cpp
#        test/queue_test.cpp
#        test/set_test.cpp
#        test/stack_test.cpp
#        test/unordered_map_test.cpp
#        test/unordered_set_test.cpp
#        test/vector_test.cpp
            )
