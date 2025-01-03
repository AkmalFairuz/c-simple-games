#include "csg_inc.h"

// [load_file] adalah wrapper/pembungkus dari fungsi [fopen] yang digunakan untuk membuka file.
// Bedanya, fungsi ini akan langsung keluar dari program jika file gagal dibuka.
FILE* load_file(const char *file_name, const char *mode) {
    //debug("Loading file '%s' with mode '%s'", file_name, mode);
    FILE *file = fopen(file_name, mode);
    if(file == NULL) {
        fatal("Failed to open file %s", file_name);
    }
    //debug("File '%s' loaded successfully", file_name);
    return file;
}

// [create_file_if_not_exists] adalah fungsi yang digunakan untuk membuat file jika file tidak ada.
void create_file_if_not_exists(const char *file_name) {
    FILE *file = fopen(file_name, "r");
    if(file == NULL) {
        file = fopen(file_name, "w");
        fclose(file);
    }else {
        fclose(file);
    }
}

// [set_cursor] adalah fungsi yang digunakan untuk mengatur posisi kursor di layar.
// Ini digunakan untuk mencetak karakter di posisi tertentu di terminal.
void set_cursor(const int x, const int y) {
    const HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    const COORD coord = {x, y};
    SetConsoleCursorPosition(hOut, coord);
}

// [loaded_words] adalah array yang digunakan untuk menyimpan kata-kata yang diambil dari file [words.txt].
// Ini akan digunakan pada game type racer.
char loaded_words[1005][50];
// [is_words_loaded] adalah penanda yang digunakan untuk menandakan apakah kata-kata sudah diambil dari file [words.txt] atau belum.
bool is_words_loaded = false;
// [loaded_words_count] adalah jumlah kata yang sudah diambil dari file [words.txt].
int loaded_words_count;

// [load_words] adalah fungsi yang digunakan untuk mengambil kata-kata dari file [words.txt].
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

// [generate_sentences] adalah fungsi yang digunakan untuk menghasilkan kalimat acak dari kata-kata yang sudah diambil dari file [words.txt].
// Fungsi ini akan dipanggil pada game type racer.
void generate_sentences(const int words_count, char generated_words[][50]) {
    if(!is_words_loaded) {
        load_words();
    }

    for(int i = 0; i < words_count; i++) {
        const char* selected_word = loaded_words[rand() % loaded_words_count];
        strcpy(generated_words[i], selected_word);
    }
}

// [get_random_int] adalah fungsi yang digunakan untuk menghasilkan bilangan bulat acak dari [min] sampai [max].
int get_random_int(const int min, const int max) {
    return rand() % (max - min + 1) + min;
}