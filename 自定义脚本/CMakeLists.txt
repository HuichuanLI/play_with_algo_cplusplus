cmake_minimum_required(VERSION 3.20)
project(play_with_algo)

set(CMAKE_CXX_STANDARD 17)

set(SOURCE_FILES Main.cpp Parser.cpp Utils.hpp Interpreter.cpp Nyx.cpp Builtin.cpp Nyx.hpp Utils.cpp Ast.cpp )
add_executable(play_with_algo ${SOURCE_FILES})

