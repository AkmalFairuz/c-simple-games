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
        src/csg_main_menu.c
        src/csg_main_menu.h
        src/csg_prompt.c
        src/csg_prompt.h
        src/csg_maze.c
        src/csg_maze.h
        src/csg_math_quiz.c
        src/csg_math_quiz.h
        src/csg_login.h
        src/csg_login.c
        src/csg_leaderboard.c
        src/csg_leaderboard.h
)