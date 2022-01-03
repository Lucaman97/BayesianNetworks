cmake_minimum_required(VERSION 3.20)
project(example1)

set(CMAKE_CXX_STANDARD 20)

add_executable(${PROJECT_NAME} example1.cpp)

target_link_libraries(${PROJECT_NAME} bayinf)



