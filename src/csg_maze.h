#ifndef CSG_MAZE_H
#define CSG_MAZE_H

#include "csg.h"

#define MAZE_GRID_WIDTH 30
#define MAZE_GRID_HEIGHT 20

static const int GRID_WALL = 1;
static const int GRID_PATH = 0;

typedef struct {
    int map_grid[MAZE_GRID_HEIGHT][MAZE_GRID_WIDTH];
    int player_pos_x;
    int player_pos_y;
    time_t start_time;
    time_t finish_time;
    bool win;
} csg_maze_game;

static void initialize_map(csg_maze_game *maze);
static void print_map(const csg_maze_game *maze);
static void carve_maze(csg_maze_game *maze, int x, int y);
static void shuffle_array(int* array, int n);
static bool on_tick(csg_maze_game *maze);

csg_game_result csg_maze_start(void);

#endif
