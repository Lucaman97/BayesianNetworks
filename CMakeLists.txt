cmake_minimum_required(VERSION 3.20)
project(Progetto)

set(CMAKE_CXX_STANDARD 20)

include_directories(bayesian_network)

add_executable(BayesianNetworks bayesian_network/Graph.cpp bayesian_network/Node.cpp bayesian_network/Edge.cpp bayesian_network/main.cpp)
