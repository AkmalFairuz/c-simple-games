#include "csg_login.h"

static csg_user current_logged_user = {.username = ""};

// [csg_prompt_login] adalah fungsi yang meminta input username dan password dari user.
void csg_prompt_login() {
    create_file_if_not_exists("users.txt");

    clear();
    char temp[100];

    printf("Before you can play the game, please enter your username.\n\n");

    while(true) {
        printf("Username: ");
        scanf("%[^\n]", temp);
        getchar();

        if(is_valid_username(temp)) {
            break;
        }

        printf("Invalid username. Username must be between 2 and 20 characters and only contain alphanumeric characters.\n");
    }

    FILE* fp = load_file("users.txt", "r");
    csg_user temp_user;
    while(fscanf(fp, "%[^|]|%d|%d|%d|%d\n", temp_user.username, &temp_user.type_racer_highest_score, &temp_user.maze_highest_score, &temp_user.math_quiz_highest_score, &temp_user.exp) == 5) {
        if(strcmp(temp_user.username, temp) == 0) {
            current_logged_user = temp_user;
            break;
        }
    }
    fclose(fp);

    // Jika tidak ada user yang ditemukan, maka buat user baru.
    if(strcmp(current_logged_user.username, "") == 0) {
        current_logged_user = (csg_user) {.type_racer_highest_score = 0, .maze_highest_score = 0, .math_quiz_highest_score = 0, .exp = 0};
        strcpy(current_logged_user.username, temp);
        register_user(current_logged_user);

        printf("User %s created! Welcome!\n", current_logged_user.username);
    }

    printf("Logged in as %s\n", current_logged_user.username);
    PRESS_ENTER_TO_CONTINUE();
}

// [get_current_username] adalah fungsi yang mengisi [username] dengan username yang sedang login. Fungsi
// ini akan me-set [username] menjadi string kosong jika tidak ada username yang sedang login.
void get_current_username(char* username) {
    strcpy(username, current_logged_user.username);
}

// [register_user] adalah fungsi yang menambahkan user baru ke dalam file [users.txt].
static void register_user(csg_user user) {
    FILE* fp = load_file("users.txt", "a");
    fprintf(fp, "%s|%d|%d|%d|%d\n", user.username, user.type_racer_highest_score, user.maze_highest_score, user.math_quiz_highest_score, user.exp);
    fclose(fp);
}

// [is_valid_username] adalah fungsi yang mengembalikan true jika username valid dan false jika tidak.
static bool is_valid_username(const char* username) {
    if(strlen(username) < 2 || strlen(username) > 20) {
        return false;
    }
    for(int i = 0; i < strlen(username); i++) {
        if(!(username[i] >= 'a' && username[i] <= 'z') && !(username[i] >= 'A' && username[i] <= 'Z') && !(username[i] >= '0' && username[i] <= '9')) {
            return false;
        }
    }
    return true;
}

// [update_user] adalah fungsi yang mengupdate data user yang sedang login.
static void update_user(csg_user user) {
    FILE* fp = load_file("users.txt", "r"); // Membuka file untuk membaca
    FILE* temp_fp = load_file("temp_users.txt", "w"); // Membuka file sementara untuk menulis ulang

    csg_user temp;

    while (fscanf(fp, "%[^|]|%d|%d|%d|%d\n",
                  temp.username,
                  &temp.type_racer_highest_score,
                  &temp.maze_highest_score,
                  &temp.math_quiz_highest_score,
                  &temp.exp) == 5) {
        if (strcmp(temp.username, user.username) == 0) {
            // Menulis data yang diperbarui untuk user yang sesuai
            fprintf(temp_fp, "%s|%d|%d|%d|%d\n",
                    user.username,
                    user.type_racer_highest_score,
                    user.maze_highest_score,
                    user.math_quiz_highest_score,
                    user.exp);
        } else {
            // Menulis ulang data user lainnya
            fprintf(temp_fp, "%s|%d|%d|%d|%d\n",
                    temp.username,
                    temp.type_racer_highest_score,
                    temp.maze_highest_score,
                    temp.math_quiz_highest_score,
                    temp.exp);
        }
    }

    fclose(fp);
    fclose(temp_fp);

    // Menimpa file lama dengan file baru
    remove("users.txt");
    rename("temp_users.txt", "users.txt");
}

// [get_current_type_racer_highest_score] adalah fungsi yang mengisi [score] dengan highest score dari game type racer.
void get_current_type_racer_highest_score(int* score) {
    *score = current_logged_user.type_racer_highest_score;
}

// [get_current_maze_highest_score] adalah fungsi yang mengisi [score] dengan highest score dari game maze.
void get_current_maze_highest_score(int* score) {
    *score = current_logged_user.maze_highest_score;
}

// [get_current_math_quiz_highest_score] adalah fungsi yang mengisi [score] dengan highest score dari game math quiz.
void get_current_math_quiz_highest_score(int* score) {
    *score = current_logged_user.math_quiz_highest_score;
}

// [get_current_exp] adalah fungsi yang mengisi [exp] dengan exp dari user yang sedang login.
void get_current_exp(int* exp) {
    *exp = current_logged_user.exp;
}

void set_current_type_racer_highest_score(int score) {
    current_logged_user.type_racer_highest_score = score;
    update_user(current_logged_user);
}

// [set_current_maze_highest_score] adalah fungsi yang mengubah highest score dari game maze.
void set_current_maze_highest_score(int score) {
    current_logged_user.maze_highest_score = score;
    update_user(current_logged_user);
}

// [set_current_math_quiz_highest_score] adalah fungsi yang mengubah highest score dari game math quiz.
void set_current_math_quiz_highest_score(int score) {
    current_logged_user.math_quiz_highest_score = score;
    update_user(current_logged_user);
}

// [add_current_exp] adalah fungsi yang menambahkan exp ke user yang sedang login.
void add_current_exp(int exp) {
    current_logged_user.exp += exp;
    update_user(current_logged_user);
}

// [get_all_users] adalah fungsi yang mengembalikan array of csg_user yang berisi semua user yang ada di file [users.txt].
void get_all_users(csg_user* users, int* total_user) {
    FILE* fp = load_file("users.txt", "r");
    // Asumsi maksimal user adalah 1000.
    int total = 0;
    while(fscanf(fp, "%[^|]|%d|%d|%d|%d\n", users[total].username, &users[total].type_racer_highest_score, &users[total].maze_highest_score, &users[total].math_quiz_highest_score, &users[total].exp) == 5) {
        total++;
    }
    *total_user = total;
    fclose(fp);
}

// [show_user_info] adalah fungsi yang menampilkan informasi user berdasarkan username.
void show_user_info(const char* username) {
    csg_user users[2048];
    int n = 0;
    get_all_users(users, &n);

    for(int i = 0; i < n; i++) {
        if(strcmp(users[i].username, username) == 0) {
            printf("%-30s: %s\n", "Username", users[i].username);
            printf("%-30s: %d\n", "Type Racer Highest Score", users[i].type_racer_highest_score);
            printf("%-30s: %d\n", "Maze Highest Score", users[i].maze_highest_score);
            printf("%-30s: %d\n", "Math Quiz Highest Score", users[i].math_quiz_highest_score);
            printf("%-30s: %d\n", "Exp", users[i].exp);
            return;
        }
    }

    printf("User not found.\n");
}

// [show_my_info] adalah fungsi yang menampilkan informasi user yang sedang login.
void show_my_info() {
    show_user_info(current_logged_user.username);
}

// [prompt_show_user_info] adalah fungsi yang meminta input username dan menampilkan informasi user berdasarkan username tersebut.
void prompt_show_user_info() {
    clear();
    char temp[100];
    printf("Enter username: ");
    scanf("%[^\n]", temp);
    getchar();
    clear();

    show_user_info(temp);
}