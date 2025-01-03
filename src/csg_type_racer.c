#include "csg_type_racer.h"

// [print_words] adalah fungsi yang mencetak kata-kata yang harus diketikkan oleh pemain. Fungsi ini akan menandai
static void print_words(int count_word, char words[50][50], int type_state[][50], int current_word, int current_letter) {
    for (int i = 0; i < count_word; i++) {
        const int len = strlen(words[i]);
        for (int j = 0; j < len; j++) {
            if (i == current_word && j == current_letter) {
                printf(ANSI_BLUE);
            }else {
                switch(type_state[i][j]) {
                    case CORRECT_TYPED:
                        printf(ANSI_GREEN);
                        break;
                    case WRONG_TYPED:
                        printf(ANSI_RED);
                        break;
                    case NOT_TYPED:
                        break;
                }
            }
            printf("%c", words[i][j]);
            printf(ANSI_RESET);
        }
        printf(" ");
    }
    fflush(stdout);
}

// [csg_type_racer_start] adalah fungsi yang digunakan untuk memulai game type racer.
csg_game_result csg_type_racer_start(void) {
    clear();

    char words[100][50];
    const int count_word = 25;
    int total_chars = 0;

    generate_sentences(count_word, words);

    int type_state[count_word][50];
    memset(type_state, NOT_TYPED, sizeof(type_state));

    printf("Type the following sentence as fast as you can:\n\n");
    for (int i = 0; i < count_word; i++) {
        printf("%s ", words[i]);
        total_chars += strlen(words[i]) + 1;
    }
    total_chars -= 1; // Remove the last space
    printf("\n\n");

    printf("Press ENTER to start typing...");
    getch();
    clear();

    int i = 0, j = 0;
    int correct_chars = 0;
    const clock_t start_time = clock();
    set_cursor(i, j);
    bool ignore_space = false;
    while (i < count_word) {
        set_cursor(0, 0);
        print_words(count_word, words, type_state, i, j);
        set_cursor(0, 0);
        const char input = getch();
        set_cursor(0, 0);

        if (input == KEY_BACKSPACE){
            if (j > 0) {
                j--;
                type_state[i][j] = NOT_TYPED;
            } else if (i > 0) {
                i--;
                j = strlen(words[i]) - 1;
                type_state[i][j] = NOT_TYPED;
            }
        } else if (input == ' '){
            if(ignore_space) {
                ignore_space = false;
            }else {
                for(int k = 0; k < strlen(words[i]); k++) {
                    if(type_state[i][k] == 0) {
                        type_state[i][k] = WRONG_TYPED;
                    }
                }

                i++;
                j = 0;
            }
        } else {
            if (input == words[i][j]){
                type_state[i][j] = CORRECT_TYPED;
                correct_chars++;
            } else {
                type_state[i][j] = WRONG_TYPED;
            }
            j++;
            if (j >= strlen(words[i])) {
                i++;
                ignore_space = true;
                j = NOT_TYPED;
            }
        }
    }

    const clock_t endTime = clock();
    const double accuracy = (correct_chars * 100.0) / total_chars;
    const double timeTaken = (double)(endTime - start_time) / CLOCKS_PER_SEC;
    const double wpm = ((correct_chars / 5.0) / (timeTaken / 60.0));
    const double score = wpm * accuracy;
    clear();

    printf("Time taken: %.2f seconds\n", timeTaken);
    printf("Words per minute: %.2f\n", wpm);
    printf("Typing Accuracy: %.2f%%\n", accuracy);

    PRESS_ENTER_TO_CONTINUE();

    return csg_game_result_create(GAME_TYPE_RACER, (int) score);
}
