cmake_minimum_required(VERSION 3.28)
project(da_proj2)

set(CMAKE_CXX_STANDARD 11)

add_executable(da_proj2 src/main.cpp
        src/Parser.h
        src/Parser.cpp
        src/Vertex.cpp
        src/Graph.h
        src/Graph.cpp
        src/Coordinate.h
        src/Coordinate.cpp
        src/Edge.cpp
        src/Manager.h
        src/Manager.cpp
)