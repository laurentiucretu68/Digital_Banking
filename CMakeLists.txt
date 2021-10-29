cmake_minimum_required(VERSION 3.19.2)
project(proiect)

set(CMAKE_CXX_STANDARD 14)

add_executable(proiect main.cpp src/User.cpp src/Admin.cpp src/Tranzactie.cpp src/Interface.cpp src/Messages.cpp includes/Messages.h)