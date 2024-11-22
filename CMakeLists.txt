cmake_minimum_required(VERSION 3.28)
project(c_simple_games C)

set(CMAKE_C_STANDARD 11)

add_executable(c_simple_games
        main.c
        src/csg_inc.h
        src/csg.h
        src/csg_inc.c
        src/csg_type_racer.c
        src/csg_type_racer.h
        src/csg_game.c
        src/csg_game.h
)