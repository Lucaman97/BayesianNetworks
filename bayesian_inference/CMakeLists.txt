cmake_minimum_required(VERSION 3.20)
project(baynet)

set(CMAKE_CXX_STANDARD 20)

cmake_minimum_required(VERSION 3.20)
project(baynet)

set(CMAKE_CXX_STANDARD 20)

add_library(baynet STATIC src/Graph.cpp src/Node.cpp extern/tinyxml2/tinyxml2.cpp src/Utils.hpp src/Utils.cpp)

target_include_directories(baynet PUBLIC include extern/tinyxml2 extern/hashLibrary)


