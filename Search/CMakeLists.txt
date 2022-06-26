cmake_minimum_required(VERSION 3.20)
project(play_with_algo)

set(CMAKE_CXX_STANDARD 14)

add_executable(play_with_algo   searchadavnced/8Puzzle-AStar.cpp searchadavnced/data/astar/2.in searchadavnced/8Puzzle-IDAStar.cpp)
