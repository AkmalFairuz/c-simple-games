#include "csg_maze.h"

// [csg_maze_start] adalah fungsi yang menjalankan game maze.
csg_game_result csg_maze_start(void) {
    clear();
    csg_maze_game* game_ctx = malloc(sizeof(csg_maze_game));
    game_ctx->player_pos_x = 1;
    game_ctx->player_pos_y = 1;

    initialize_map(game_ctx);
    carve_maze(game_ctx, 1, 1);
    print_map(game_ctx);
    game_ctx->win = false;
    game_ctx->start_time = time(NULL);
    while (on_tick(game_ctx));

    if(game_ctx->win) {
        int time_played = (int) (game_ctx->finish_time - game_ctx->start_time);
        int score = 1000 - time_played;
        if(score < 0) {
            score = 0;
        }
        return csg_game_result_create(GAME_MAZE, score);
    }

    free(game_ctx);

    return csg_game_result_create(GAME_MAZE, 0);
}

// [initialize_map] adalah fungsi yang menginisialisasi map maze. Mengisi semua grid dengan dinding.
static void initialize_map(csg_maze_game *maze) {
    for(int i = 0; i < MAZE_GRID_HEIGHT; i++) {
        for(int j = 0; j < MAZE_GRID_WIDTH; j++) {
            maze->map_grid[i][j] = GRID_WALL;
        }
    }
}

// [carve_maze] adalah fungsi yang membuat maze dengan algoritma recursive backtracking. Cara kerjanya adalah dengan membuat path yang berkelok-kelok.
// Fungsi ini dipanggil secara rekursif. Fungsi ini akan memanggil dirinya sendiri untuk membuat path.
static void carve_maze(csg_maze_game *maze, const int x, const int y) {
    // Kita set grid yang sedang dikerjakan menjadi path.
    maze->map_grid[y][x] = GRID_PATH;

    // Directions: Up, Right, Down, Left
    const int directions[4][2] = {
        {0, -1},  // Up/Atas
        {1, 0},   // Right/Kanan
        {0, 1},   // Down/Bawah
        {-1, 0}   // Left/Kiri
    };

    // Mendapatkan urutan arah secara acak. Antara ke atas, kanan, bawah, dan kiri.
    int order[4] = {0, 1, 2, 3};
    shuffle_array(order, 4);

    // Looping untuk setiap arah.
    for(int i = 0; i < 4; i++){
        // Mendapatkan mau ke arah mana.
        const int dx = directions[order[i]][0];
        const int dy = directions[order[i]][1];

        // Mendapatkan koordinat x dan y setelah bergerak 2 kali.
        const int nx = x + 2 * dx;
        const int ny = y + 2 * dy;

        // Cek apakah koordinat nx dan ny masih di dalam map dan masih berupa dinding.
        if(nx > 0 && nx < MAZE_GRID_WIDTH - 1 && ny > 0 && ny < MAZE_GRID_HEIGHT - 1 && maze->map_grid[ny][nx] == 1){
            // Set grid yang dilewati menjadi path.
            maze->map_grid[y + dy][x + dx] = GRID_PATH;

            // Panggil fungsinya lagi untuk membuat path.
            carve_maze(maze, nx, ny);
        }
    }
}

// [print_map] adalah fungsi yang digunakan untuk mencetak map maze.
void print_map(const csg_maze_game* maze){
    // Lakukan looping 2 kali, untuk setiap kooridnat x dan y.
    for(int i = 0; i < MAZE_GRID_HEIGHT - 1; i++){
        for(int j = 0; j < MAZE_GRID_WIDTH - 1; j++){
            // Cek apakah posisi player. Jika iya, maka cetak karakter V.
            if(i == maze->player_pos_y && j == maze->player_pos_x){
                printf("V ");
                continue;
            }
            // Cetak karakter dinding atau path.
            printf("%s", maze->map_grid[i][j] ? "\u2588\u2588" : "  ");
        }
        printf("\n");
    }
}

// [shuffle_array] adalah fungsi yang digunakan untuk mengacak array.
void shuffle_array(int* array, const int n) {
    for (int i = 0; i < n; i++) {
        const int j = rand() % n;
        const int temp = array[i];
        array[i] = array[j];
        array[j] = temp;
    }
}

// [on_tick] adalah fungsi yang dipanggil setiap tick/frame pada game maze.
bool on_tick(csg_maze_game *maze) {
    // Dapatkan input dari user.
    const int key = getch();

    // Simpan posisi player sebelum dipindahkan.
    const int beforePosX = maze->player_pos_x;
    const int beforePosY = maze->player_pos_y;

    char* playerChar = "@";

    switch(key){
        case 'w': // Atas
            if(maze->map_grid[maze->player_pos_y - 1][maze->player_pos_x] == GRID_PATH){
                maze->player_pos_y--; // Jika ke atas, maka kurangi posisi y.
                playerChar = "Ʌ";
            }
        break;
        case 's': // Bawah
            if(maze->map_grid[maze->player_pos_y + 1][maze->player_pos_x] == GRID_PATH){
                maze->player_pos_y++; // Jika ke bawah, maka tambahkan posisi y.
                playerChar = "V";
            }
        break;
        case 'a': // Kiri
            if(maze->map_grid[maze->player_pos_y][maze->player_pos_x - 1] == GRID_PATH){
                maze->player_pos_x--; // Jika ke kiri, maka kurangi posisi x.
                playerChar = "<";
            }
        break;
        case 'd': // Kanan
            if(maze->map_grid[maze->player_pos_y][maze->player_pos_x + 1] == GRID_PATH){
                maze->player_pos_x++; // Jika ke kanan, maka tambahkan posisi x.
                playerChar = ">";
            }
        break;
        case KEY_ESC: // Jika tombol ESC ditekan, maka keluar dari game.
            return false;
    }

    // Set cursor agar bisa mencetak karakter di posisi tertentu. Pada kasus ini, kita akan menghapus karakter sebelumnya
    // karena posisi player akan berubah.
    set_cursor(beforePosX * 2, beforePosY);
    // Cetak spasi untuk menghapus karakter sebelumnya.
    printf("  ");
    // Set cursor ke posisi player sekarang.
    set_cursor(maze->player_pos_x * 2, maze->player_pos_y);
    // Lalu cetak karakter player.
    printf("%s ", playerChar);
    // Set cursor ke posisi palin bawah kanan agar tidak mengganggu tampilan maze.
    set_cursor((MAZE_GRID_WIDTH * 2) - 1, MAZE_GRID_HEIGHT);
    // Panggil fflush agar output langsung dikirim ke terminal.
    fflush(stdout);

    // Cek apakah player sudah sampai di posisi akhir/tujuan.
    if(maze->player_pos_x == MAZE_GRID_WIDTH - 3 && maze->player_pos_y == MAZE_GRID_HEIGHT - 3){
        clear();
        printf("You win!\n");
        maze->win = true;
        maze->finish_time = time(NULL);
        printf("You finished the maze in %d seconds.\n", (int) (maze->finish_time - maze->start_time));
        PRESS_ENTER_TO_CONTINUE();
        return false;
    }
    return true;
}


