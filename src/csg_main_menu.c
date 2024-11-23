#include "csg_math_quiz.h"
#include "csg_prompt.h"

static void print_main_menu_options() {
    clear();

    begin_print_option();
    print_option("Type Racer");
    print_option("Maze");
    print_option("Math Quiz");
    print_option("Credits");
    print_option("Exit");
    end_print_option();
}

void csg_main_menu_start(void) {
    print_main_menu_options();

    const int total_option = 5;

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
                        csg_type_racer_start();
                        clear();
                        if(!ask_yes_no("Do you want to play type racer again?")) {
                            break;
                        }
                    }
                    break;
                case 1:
                    while(true) {
                        csg_maze_start();
                        clear();
                        if(!ask_yes_no("Do you want to play maze again?")) {
                            break;
                        }
                    }
                    break;
                case 2:
                    while(true) {
                        csg_math_quiz_start();
                        clear();
                        if(!ask_yes_no("Do you want to play math quiz again?")) {
                            break;
                        }
                    }
                    break;
                case 3:
                    printf("Created by: \n");
                    printf("   1. AkmalFairuz\n");
                    printf("   2. Kristantowinata\n");
                    printf("   3. Takiyo0\n");
                    PRESS_ENTER_TO_CONTINUE();
                    break;
                case 4:
                    exit(0);
            }

            print_main_menu_options();
        }
    }
}
