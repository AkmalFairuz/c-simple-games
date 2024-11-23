#ifndef CSG_PROMPT_H
#define CSG_PROMPT_H

#include "csg.h"

void begin_print_option();
void print_option(const char *option);
void end_print_option();
int menu_arrow_selector(int total_option, int *selected);
bool ask_yes_no(const char *prompt);

#endif
