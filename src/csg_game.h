#ifndef CSG_GAME_H
#define CSG_GAME_H

typedef enum {
    GAME_MAZE,
    GAME_MATH_QUIZ,
    GAME_TYPE_RACER,
} csg_game_type;

typedef struct {
    int score;
    csg_game_type game_type;
} csg_game_result;

csg_game_result csg_game_result_create(csg_game_type game_type, int score);

#endif
