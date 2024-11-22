#ifndef CSG_INC_H
#define CSG_INC_H

/* BEGIN Required Libraries */
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <stdbool.h>
#include <time.h>
#include <conio.h>
#include <windows.h>
#include <stdint.h>
/* END Required Libraries */

/* BEGIN Macros */
#define ll long long int // i hate long long int
#define clear() system("cls")
#define fatal(format, ...) \
    printf(format, ##__VA_ARGS__); \
    printf("\n"); \
    exit(1);

#ifndef PRODUCTION_READY
#define debug(format, ...) \
    printf("[DEBUG] "); \
    printf(format, ##__VA_ARGS__); \
    printf("\n");
#else
#define debug(format, ...) ;;
#endif

/* END Macros */

/* BEGIN Ansi */
#define ANSI_BLUE "\033[34m"
#define ANSI_GREEN "\033[32m"
#define ANSI_RED "\033[31m"
#define ANSI_RESET "\033[0m"
/* END Ansi */

/* BEGIN Functions */
void set_cursor(int x, int y);
void generate_sentences(int words_count, char generated_words[][50]);
FILE* load_file(const char *file_name, const char *mode);
/* END Functions */

#endif
