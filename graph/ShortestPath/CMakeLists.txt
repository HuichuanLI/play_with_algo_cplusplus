cmake_minimum_required(VERSION 3.20)
project(play_with_algo)

set(SOURCE_FILES main.cpp Edge.h DenseGraph.h SparseGraph.h ReadGraph.h IndexMinHeap.h Dijkstra.h)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})
add_executable(01_Weighted_Graph ${SOURCE_FILES})