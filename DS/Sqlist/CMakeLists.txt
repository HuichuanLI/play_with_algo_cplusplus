cmake_minimum_required(VERSION 3.10)
project(Dynamic-Array)

set(CMAKE_CXX_STANDARD 17)

add_executable(Array-Stack linkedlist.cpp DuLinkList.cpp mergelist.cpp sqlite.h reverseLinkedlist.cpp findmiddle.cpp findk.cpp delete.cpp ../../Search/sqsearch.cpp ../../Search/binarySearch.cpp)
