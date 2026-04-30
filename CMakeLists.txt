cmake_minimum_required(VERSION 4.1)
project(Minesweeper)

set(CMAKE_CXX_STANDARD 20)

add_executable(Minesweeper main.cpp
        Celula.h
        Celula.cpp
        Tabla.h
        Tabla.cpp
        Exceptii.h
        Exceptii.cpp
        Jucator.h
        Jucator.cpp
        )

add_executable(
        Program_compact Cod_complet.cpp
)

