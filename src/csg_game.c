#include "csg_game.h"

// [csg_game_result_create] adalah fungsi yang mengembalikan [csg_game_result] dengan nilai [score] yang diberikan.
csg_game_result csg_game_result_create(csg_game_type game_type, int score) {
    return (csg_game_result) {.game_type = game_type, .score = score};
}
