#include "src/csg.h"

int main(void) {
    srand(time(NULL));

#ifdef _WIN32
    // Tujuannya adalah agar kita bisa mencetak karakter unicode (seperti ASCII Art) di Windows.
    SetConsoleOutputCP(CP_UTF8);
#endif

    csg_prompt_login();

    csg_main_menu_start();
    return 0;
}
