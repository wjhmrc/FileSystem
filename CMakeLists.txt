cmake_minimum_required(VERSION 3.14)
project(FileSystem)

set(CMAKE_CXX_STANDARD 17)

add_executable(FileSystem main.cpp user/Login.cpp user/Login.h user/User.h user/User.cpp control/Control.cpp control/Control.h fileControl/FileControl.cpp fileControl/FileControl.h)