#include "csg_main_menu.h"

#include "csg_prompt.h"

static void print_main_menu_options() {
    clear();

    printf("\n\n");
    printf("     Type Racer\n");
    printf("     Maze\n");
    printf("     Math Quiz\n");
    printf("     Credits\n");
    printf("     Exit\n");
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
                        if(!ask_yes_no("Do you want to play again?")) {
                            break;
                        }
                    }
                    break;
                case 1:
                    printf("NOT IMPLEMENTED YET");
                    PRESS_ENTER_TO_CONTINUE();
                    break;
                case 2:
                    printf("NOT IMPLEMENTED YET");
                    PRESS_ENTER_TO_CONTINUE();
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
