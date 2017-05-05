cmake_minimum_required(VERSION 3.5)
project(ReversiCpp)

set(CMAKE_CXX_STANDARD 11)

find_package(Boost COMPONENTS system REQUIRED)
include_directories(${Boost_INCLUDE_DIR})

set(SOURCE_FILES
        main.cpp
        Runner.h
        RemoteServer.h
        package/Reversi.cpp
        package/Reversi.h
        package/IReversi.h
        World.h)

add_executable(ReversiCpp ${SOURCE_FILES})

link_directories(${Boost_LIBRARY_DIR})
target_link_libraries(ReversiCpp ${Boost_LIBRARIES} pthread)

