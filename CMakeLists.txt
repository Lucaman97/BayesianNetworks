cmake_minimum_required(VERSION 3.20)
project(Progetto)

set(CMAKE_CXX_STANDARD 20)

include_directories(bayesian_network)

# bayesian_network/Node.h bayesian_network/Edge.h bayesian_network/Graph.h
add_executable(BayesianNetworks bayesian_network/tinyxml2.cpp bayesian_network/tinyxml2.h bayesian_network/CPTable.cpp bayesian_network/CPTable.h bayesian_network/Graph.cpp bayesian_network/Node.cpp bayesian_network/Edge.cpp bayesian_network/main.cpp)

