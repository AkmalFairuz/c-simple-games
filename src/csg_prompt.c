#include "csg_prompt.h"

// [menu_arrow_selector] adalah fungsi yang menampilkan menu dengan panah dan meminta input dari user. Parameter
// [total_option] adalah jumlah opsi yang akan ditampilkan. Parameter [selected] adalah indeks opsi yang dipilih.
// [selected] akan diubah oleh fungsi ini sesuai dengan input dari user.
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

// [ask_yes_no] adalah fungsi yang menampilkan pertanyaan dengan opsi Yes dan No. Fungsi ini akan mengembalikan
// true jika user memilih Yes dan false jika user memilih No.
bool ask_yes_no(const char *prompt) {
    clear();

    printf(prompt);
    begin_print_option();
    print_option("Yes");
    print_option("No");
    end_print_option();

    const int total_option = 2;
    int selected = 0;

    while (true) {
        const int key = menu_arrow_selector(total_option, &selected);
        if(key == KEY_ENTER) {
            return selected == 0;
        }
    }
}

// [print_option] adalah fungsi yang mencetak opsi pada menu.
void print_option(const char *option) {
    printf("     %s\n", option);
}

// [begin_print_option] adalah fungsi yang dipanggil sebelum mencetak opsi pada menu.
void begin_print_option() {
    printf("\n\n");
}

// [end_print_option] adalah fungsi yang dipanggil setelah mencetak opsi pada menu.
void end_print_option() {
}
