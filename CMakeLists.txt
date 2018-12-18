cmake_minimum_required(VERSION 3.12)
project(P2P)

set(CMAKE_CXX_STANDARD 14)
SET(CMAKE_CXX_FLAGS -pthread)

add_executable(P2P main.cpp NetworkManager.cpp NetworkManager.h RemoteNode.cpp RemoteNode.h)