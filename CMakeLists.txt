cmake_minimum_required(VERSION 3.20)
project(Progetto)

set(CMAKE_CXX_STANDARD 20)

include_directories(bayesian_network)

#target_include_directories(src PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/src)

# bayesian_network/Node.h bayesian_network/Edge.h bayesian_network/Graph.h
#add_executable(BayesianNetworks test/main.cpp)
add_executable(BayesianNetworks bayesian_network/extern/hashLibrary/sha1.h bayesian_network/extern/tinyxml2/tinyxml2.cpp bayesian_network/extern/tinyxml2/tinyxml2.h bayesian_network/src/Graph.cpp bayesian_network/src/Node.cpp test/main.cpp)

