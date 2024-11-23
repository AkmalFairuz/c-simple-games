#include "csg_maze.h"

csg_game_result csg_maze_start(void) {
    clear();
    csg_maze_game* game_ctx = malloc(sizeof(csg_maze_game));
    game_ctx->player_pos_x = 1;
    game_ctx->player_pos_y = 1;

    initialize_map(game_ctx);
    carve_maze(game_ctx, 1, 1);
    print_map(game_ctx);
    while (on_tick(game_ctx));

    free(game_ctx);

    return csg_game_result_create(0);
}

static void initialize_map(csg_maze_game *maze) {
    for(int i = 0; i < MAZE_GRID_HEIGHT; i++) {
        for(int j = 0; j < MAZE_GRID_WIDTH; j++) {
            maze->map_grid[i][j] = GRID_WALL;
        }
    }
}

static void carve_maze(csg_maze_game *maze, const int x, const int y) {
    maze->map_grid[y][x] = GRID_PATH;

    const int directions[4][2] = {
        {0, -1},  // Up
        {1, 0},   // Right
        {0, 1},   // Down
        {-1, 0}   // Left
    };

    int order[4] = {0, 1, 2, 3};
    shuffle_array(order, 4);

    for(int i = 0; i < 4; i++){
        const int dx = directions[order[i]][0];
        const int dy = directions[order[i]][1];
        const int nx = x + 2 * dx;
        const int ny = y + 2 * dy;

        if(nx > 0 && nx < MAZE_GRID_WIDTH - 1 && ny > 0 && ny < MAZE_GRID_HEIGHT - 1 && maze->map_grid[ny][nx] == 1){
            maze->map_grid[y + dy][x + dx] = GRID_PATH;
            carve_maze(maze, nx, ny);
        }
    }
}

void print_map(const csg_maze_game* maze){
    for(int i = 0; i < MAZE_GRID_HEIGHT - 1; i++){
        for(int j = 0; j < MAZE_GRID_WIDTH - 1; j++){
            if(i == maze->player_pos_y && j == maze->player_pos_x){
                printf("V ");
                continue;
            }
            printf("%s", maze->map_grid[i][j] ? "\u2588\u2588" : "  ");
        }
        printf("\n");
    }
}

void shuffle_array(int* array, const int n) {
    for (int i = 0; i < n; i++) {
        const int j = rand() % n;
        const int temp = array[i];
        array[i] = array[j];
        array[j] = temp;
    }
}

bool on_tick(csg_maze_game *maze) {
    const int key = getch();
    const int beforePosX = maze->player_pos_x;
    const int beforePosY = maze->player_pos_y;
    char* playerChar = "@";
    switch(key){
        case 'w':
            if(maze->map_grid[maze->player_pos_y - 1][maze->player_pos_x] == GRID_PATH){
                maze->player_pos_y--;
                playerChar = "Ʌ";
            }
        break;
        case 's':
            if(maze->map_grid[maze->player_pos_y + 1][maze->player_pos_x] == GRID_PATH){
                maze->player_pos_y++;
                playerChar = "V";
            }
        break;
        case 'a':
            if(maze->map_grid[maze->player_pos_y][maze->player_pos_x - 1] == GRID_PATH){
                maze->player_pos_x--;
                playerChar = "<";
            }
        break;
        case 'd':
            if(maze->map_grid[maze->player_pos_y][maze->player_pos_x + 1] == GRID_PATH){
                maze->player_pos_x++;
                playerChar = ">";
            }
        break;
    }

    set_cursor(beforePosX * 2, beforePosY);
    printf("  ");
    set_cursor(maze->player_pos_x * 2, maze->player_pos_y);
    printf("%s ", playerChar);
    set_cursor((MAZE_GRID_WIDTH * 2) - 1, MAZE_GRID_HEIGHT);
    fflush(stdout);

    if(maze->player_pos_x == MAZE_GRID_WIDTH - 3 && maze->player_pos_y == MAZE_GRID_HEIGHT - 3){
        clear();
        printf("You win!\n");
        getchar();
        return false;
    }
    return true;
}


