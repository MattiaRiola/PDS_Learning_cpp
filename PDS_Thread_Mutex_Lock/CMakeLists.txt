cmake_minimum_required(VERSION 3.16)
project(PDS_Thread_Mutex_Lock)

set(CMAKE_CXX_STANDARD 20)

add_executable(PDS_Thread_Mutex_Lock main.cpp MyConcurrentClass.cpp MyConcurrentClass.h)