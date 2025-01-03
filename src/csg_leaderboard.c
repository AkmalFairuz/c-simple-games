#include "csg_leaderboard.h"

#include "csg_prompt.h"

// [print_leaderboard_menu_options] adalah fungsi yang menampilkan pilihan menu leaderboard.
void print_leaderboard_menu_options() {
    begin_print_option();
    print_option("View Math Quiz Leaderboard");
    print_option("View Maze Leaderboard");
    print_option("View Type Racer Leaderboard");
    print_option("Back");
    end_print_option();
}

// [csg_leaderboard_menu] adalah fungsi yang menampilkan menu leaderboard.
void csg_leaderboard_menu() {
    clear();
    const int total_option = 4;
    int selected = 0;

    print_leaderboard_menu_options();

    bool back = false;
    while(!back) {
        const int key = menu_arrow_selector(total_option, &selected);

        if(key == KEY_ESC) {
            break;
        }

        if(key == KEY_ENTER) {
            clear();
            switch(selected) {
                case 0:
                    show_math_quiz_leaderboard();
                    break;
                case 1:
                    show_maze_leaderboard();
                    break;
                case 2:
                    show_type_racer_leaderboard();
                    break;
                case 3:
                    back = true;
                    break;
            }
            clear();
            print_leaderboard_menu_options();
        }
    }
}

static void show_math_quiz_leaderboard() {
    clear();

    csg_user users[2048];
    int n = 0;
    get_all_users(users, &n);

    // Sort Using Bubble Sort
    for(int i = 0; i < n; i++) {
        for(int j = i + 1; j < n; j++) {
            if(users[i].math_quiz_highest_score < users[j].math_quiz_highest_score) {
                const csg_user temp = users[i];
                users[i] = users[j];
                users[j] = temp;
            }
        }
    }

    printf("Top 15 Highest Score in Math Quiz Leaderboard\n");
    printf("-----------------------------------------------\n");
    for(int i = 0; i < 15 && i < n; i++) {
        printf("%d. %-22s - %d\n", i + 1, users[i].username, users[i].math_quiz_highest_score);
    }
    printf("-----------------------------------------------\n");
    printf("\n");

    PRESS_ENTER_TO_CONTINUE();
}

static void show_maze_leaderboard() {
    clear();
    printf("Maze Leaderboard\n");

    csg_user users[2048];
    int n = 0;
    get_all_users(users, &n);

    // Sort using insertion sort
    for(int i = 1; i < n; i++) {
        const csg_user key = users[i];
        int j = i - 1;
        while(j >= 0 && users[j].maze_highest_score < key.maze_highest_score) {
            users[j + 1] = users[j];
            j = j - 1;
        }
        users[j + 1] = key;
    }

    printf("Top 15 Highest Score in Maze Leaderboard\n");
    printf("-----------------------------------------------\n");
    for(int i = 0; i < 15 && i < n; i++) {
        printf("%d. %-22s - %d\n", i + 1, users[i].username, users[i].maze_highest_score);
    }
    printf("-----------------------------------------------\n");
    printf("\n");

    PRESS_ENTER_TO_CONTINUE();
}

static void show_type_racer_leaderboard() {
    clear();
    printf("Type Racer Leaderboard\n");

    csg_user users[2048];
    int n = 0;
    get_all_users(users, &n);

    // Sort using selection sort
    for(int i = 0; i < n - 1; i++) {
        int min_idx = i;
        for(int j = i + 1; j < n; j++) {
            if(users[j].type_racer_highest_score > users[min_idx].type_racer_highest_score) {
                min_idx = j;
            }
        }
        const csg_user temp = users[min_idx];
        users[min_idx] = users[i];
        users[i] = temp;
    }

    printf("Top 15 Highest Score in Type Racer Leaderboard\n");
    printf("-----------------------------------------------\n");
    for(int i = 0; i < 15 && i < n; i++) {
        printf("%d. %-22s - %d\n", i + 1, users[i].username, users[i].type_racer_highest_score);
    }
    printf("-----------------------------------------------\n");
    printf("\n");

    PRESS_ENTER_TO_CONTINUE();
}
