cmake_minimum_required(VERSION 3.19.2)
project(proiect)

set(CMAKE_CXX_STANDARD 14)

if (MSVC)
    add_compile_options(/W4)
else ()
    add_compile_options(-Wall -Wextra -pedantic -g -Werror)
    if ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang")
        add_compile_options(-stdlib=libstdc++)
    endif ()
endif ()

add_executable(proiect main.cpp src/User.cpp src/Admin.cpp src/Tranzactie.cpp src/Interface.cpp src/Message.cpp src/UserBusiness.cpp includes/UserBusiness.h)

install(TARGETS ${PROJECT_NAME} DESTINATION bin)