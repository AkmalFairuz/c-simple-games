#include "csg_type_racer.h"

static void print_words(const int count_word, char words[50][50], int cek_benar[count_word][50], int current_word, int current_letter) {
    for (int i = 0; i < count_word; i++) {
        const int len = strlen(words[i]);
        for (int j = 0; j < len; j++) {
            if (i == current_word && j == current_letter) {
                printf(ANSI_BLUE);
            }else {
                switch(cek_benar[i][j]) {
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

csg_game_result csg_type_racer_start(void) {
    clear();

    char words[100][50];
    int count_word = 25;
    int total_chars = 0;

    generate_sentences(count_word, words);

    int cek_benar[count_word][50];
    memset(cek_benar, NOT_TYPED, sizeof(cek_benar));

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
        print_words(count_word, words, cek_benar, i, j);
        set_cursor(0, 0);
        const char input = getch();
        set_cursor(0, 0);

        if (input == 8){
            if (j > 0) {
                j--;
                cek_benar[i][j] = NOT_TYPED;
            } else if (i > 0) {
                i--;
                j = strlen(words[i]) - 1;
                cek_benar[i][j] = NOT_TYPED;
            }
        } else if (input == ' '){
            if(ignore_space) {
                ignore_space = false;
            }else {
                for(int k = 0; k < strlen(words[i]); k++) {
                    if(cek_benar[i][k] == 0) {
                        cek_benar[i][k] = WRONG_TYPED;
                    }
                }

                i++;
                j = 0;
            }
        } else {
            if (input == words[i][j]){
                cek_benar[i][j] = CORRECT_TYPED;
                correct_chars++;
            } else {
                cek_benar[i][j] = WRONG_TYPED;
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
    printf("\n\n\n\n");
    printf("\nTime taken: %.2f seconds\n", timeTaken);
    printf("Words per minute: %.2f\n", wpm);
    printf("Typing Accuracy: %.2f%%\n", accuracy);
    printf("Press ENTER to continue...");
    getchar();

    return csg_game_result_create(score);
}
