#include "csg_math_quiz.h"
#include "csg_prompt.h"

// [print_main_menu_options] adalah fungsi yang menampilkan pilihan menu utama.
static void print_main_menu_options() {
    clear();

    begin_print_option();
    print_option("Type Racer");
    print_option("Maze");
    print_option("Math Quiz");
    print_option("Leaderboard");
    print_option("Show my stats");
    print_option("See other users' stats");
    print_option("Credits");
    print_option("Exit");
    end_print_option();
}

// [csg_main_menu_start] adalah fungsi yang menampilkan main menu dan meminta input dari user.
void csg_main_menu_start(void) {
    print_main_menu_options();

    const int total_option = 8;

    int selected = 0;
    while (true) {
        const int key = menu_arrow_selector(total_option, &selected);

        if (key == KEY_ESC) {
            break;
        }

        if (key == KEY_ENTER) {
            clear();
            switch (selected) {
                case 0:
                    while(true) {
                        csg_game_result result = csg_type_racer_start();
                        add_current_exp(result.score / 10);

                        int current_highest_score;
                        get_current_type_racer_highest_score(&current_highest_score);
                        clear();
                        if(result.score > current_highest_score) {
                            set_current_type_racer_highest_score(result.score);
                            printf("Congratulations! You have achieved a new high score in Type Racer!\n");
                            printf("Previous high score: %d\n", current_highest_score);
                            printf("New high score: %d\n", result.score);
                        }else {
                            printf("You got %d points in Type Racer. Your highest score is %d.\n", result.score, current_highest_score);
                        }
                        PRESS_ENTER_TO_CONTINUE();

                        clear();
                        if(!ask_yes_no("Do you want to play type racer again?")) {
                            break;
                        }
                    }
                    break;
                case 1:
                    while(true) {
                        csg_game_result result = csg_maze_start();
                        add_current_exp(result.score / 5);

                        int current_highest_score;
                        get_current_maze_highest_score(&current_highest_score);
                        clear();
                        if(result.score > current_highest_score) {
                            set_current_maze_highest_score(result.score);
                            printf("Congratulations! You have achieved a new high score in maze!\n");
                            printf("Previous high score: %d\n", current_highest_score);
                            printf("New high score: %d\n", result.score);
                        }else {
                            printf("You got %d points in maze. Your highest score is %d.\n", result.score, current_highest_score);
                        }
                        PRESS_ENTER_TO_CONTINUE();

                        clear();
                        if(!ask_yes_no("Do you want to play maze again?")) {
                            break;
                        }
                    }
                    break;
                case 2:
                    while(true) {
                        csg_game_result result = csg_math_quiz_start();
                        add_current_exp(result.score / 8);

                        int current_highest_score;
                        get_current_math_quiz_highest_score(&current_highest_score);
                        clear();
                        if(result.score > current_highest_score) {
                            set_current_math_quiz_highest_score(result.score);
                            printf("Congratulations! You have achieved a new high score in math quiz!\n");
                            printf("Previous high score: %d\n", current_highest_score);
                            printf("New high score: %d\n", result.score);
                        }else {
                            printf("You got %d points in math quiz. Your highest score is %d.\n", result.score, current_highest_score);
                        }
                        PRESS_ENTER_TO_CONTINUE();

                        clear();
                        if(!ask_yes_no("Do you want to play math quiz again?")) {
                            break;
                        }
                    }
                    break;
                case 3:
                    csg_leaderboard_menu();
                    break;
                case 4:
                    clear();
                    show_my_info();
                    PRESS_ENTER_TO_CONTINUE();
                    clear();
                    break;
                case 5:
                    clear();
                    prompt_show_user_info();
                    PRESS_ENTER_TO_CONTINUE();
                    clear();
                    break;
                case 6:
                    printf("Created by: \n");
                    printf("   1. AkmalFairuz\n");
                    printf("   2. Kristantowinata\n");
                    printf("   3. Takiyo0\n");
                    PRESS_ENTER_TO_CONTINUE();
                    break;
                case 7:
                    exit(0);
            }

            print_main_menu_options();
        }
    }
}
