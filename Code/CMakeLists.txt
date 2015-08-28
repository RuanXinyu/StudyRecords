cmake_minimum_required(VERSION 3.2)
project(Learn)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
include_directories(Include)
link_directories(Libs)
link_libraries(gtest pthread)

set(SOURCE_FILES main.cpp)
add_executable(Learn ${SOURCE_FILES} LeetCode/NoClassification.h LeetCode/NoClassification.cpp Algorithm/LinkedList.h Algorithm/LinkedList.cpp Algorithm/StackAndQueue.h Algorithm/StackAndQueue.cpp Basic/String.h Basic/String.cpp LeetCode/Question000To009.h LeetCode/Question000To009.cpp Basic/StdFun.h Basic/StdFun.cpp Basic/SmartPtr.h Basic/SmartPtr.cpp Algorithm/Array.h Algorithm/Array.cpp Basic/MyMalloc.h Basic/MyMalloc.cpp Algorithm/Search.h Algorithm/Search.cpp CrackingCodeInterview/ZipString.cpp Algorithm/GeneralFun.h Algorithm/GeneralFun.cpp)