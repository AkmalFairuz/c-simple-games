#include "csg_inc.h"

FILE* load_file(const char *file_name, const char *mode) {
    debug("Loading file '%s' with mode '%s'", file_name, mode);
    FILE *file = fopen(file_name, mode);
    if(file == NULL) {
        fatal("Failed to open file %s", file_name);
    }
    debug("File '%s' loaded successfully", file_name);
    return file;
}

void set_cursor(const int x, const int y) {
    const HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    const COORD coord = {x, y};
    SetConsoleCursorPosition(hOut, coord);
}

char loaded_words[1005][50];
bool is_words_loaded = false;
int loaded_words_count;

static void load_words() {
    debug("Loading words...");
    FILE* file = load_file("words.txt", "r");
    loaded_words_count = 0;
    while(fscanf(file, "%[^\n]\n", loaded_words[loaded_words_count]) != EOF) {
        loaded_words_count++;
    }
    fclose(file);
    is_words_loaded = true;
    debug("Words loaded successfully");
}

void generate_sentences(const int words_count, char generated_words[][50]) {
    if(!is_words_loaded) {
        load_words();
    }

    for(int i = 0; i < words_count; i++) {
        const char* selected_word = loaded_words[rand() % loaded_words_count];
        strcpy(generated_words[i], selected_word);
    }
}

int get_random_int(const int min, const int max) {
    return rand() % (max - min + 1) + min;
}