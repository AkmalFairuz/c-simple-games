#include "csg_game.h"

csg_game_result csg_game_result_create(const double score) {
    return (csg_game_result) {.score = score };
}
