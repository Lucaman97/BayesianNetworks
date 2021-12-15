cmake_minimum_required(VERSION 3.20)
project(bayinf)

set(CMAKE_CXX_STANDARD 20)

cmake_minimum_required(VERSION 3.20)
project(bayinf)

set(CMAKE_CXX_STANDARD 20)

add_library(bayinf STATIC src/Graph.cpp src/Node.cpp extern/tinyxml2/tinyxml2.cpp)

target_include_directories(bayinf PUBLIC include extern/tinyxml2 extern/hashLibrary)


