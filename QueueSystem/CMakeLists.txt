cmake_minimum_required(VERSION 3.20)
project(play_with_algo)

set(CMAKE_CXX_STANDARD 14)

add_executable(play_with_algo Event.h Node.h Queue.h QueueSystem.h ServiceWindow.h main.cpp)
