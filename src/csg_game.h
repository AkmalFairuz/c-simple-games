#ifndef CSG_GAME_H
#define CSG_GAME_H

typedef struct {
    double score;
} csg_game_result;

csg_game_result csg_game_result_create(double score);

#endif
