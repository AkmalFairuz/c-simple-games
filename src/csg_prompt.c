#include "csg_prompt.h"

int menu_arrow_selector(const int total_option, int *selected) {
    for(int i = 0; i < total_option; i++) {
        set_cursor(1, i + 2);
        if(i == *selected) {
            printf(ANSI_GREEN);
            printf(">>>");
        }else {
            printf(ANSI_RESET);
            printf("   ");
        }
        printf(ANSI_RESET);
    }

    set_cursor(0, 0);

    const int key = getch();
    if (key == KEY_ARROW_PREFIX){
        const int key2 = getch();
        switch (key2) {
            case KEY_ARROW_UP:
                *selected = (*selected - 1 + total_option) % total_option;
                break;
            case KEY_ARROW_DOWN:
                *selected = (*selected + 1) % total_option;
                break;
        }
        return key2;
    }
    return key;
}

bool ask_yes_no(const char *prompt) {
    clear();

    printf(prompt);
    printf("\n\n");

    printf("     Yes\n");
    printf("     No\n");

    const int total_option = 2;
    int selected = 0;

    while (true) {
        const int key = menu_arrow_selector(total_option, &selected);
        if(key == KEY_ENTER) {
            return selected == 0;
        }
    }
}
