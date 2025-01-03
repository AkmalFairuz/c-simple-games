#ifndef CSG_LOGIN_H
#define CSG_LOGIN_H
#include "csg_inc.h"

typedef struct {
    char username[100];
    int type_racer_highest_score;
    int maze_highest_score;
    int math_quiz_highest_score;
    int exp;
} csg_user;

void csg_prompt_login();
void get_current_username(char* username);
void get_current_type_racer_highest_score(int* score);
void get_current_maze_highest_score(int* score);
void get_current_math_quiz_highest_score(int* score);
void get_current_exp(int* exp);

void set_current_type_racer_highest_score(int score);
void set_current_maze_highest_score(int score);
void set_current_math_quiz_highest_score(int score);
void add_current_exp(int exp);

static void register_user(csg_user user);
static bool is_valid_username(const char* username);
static void update_user(csg_user user);

void get_all_users(csg_user* users, int* total_user);
void show_user_info(const char* username);
void show_my_info();
void prompt_show_user_info();

#endif

