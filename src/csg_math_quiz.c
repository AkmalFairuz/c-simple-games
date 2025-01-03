#include "csg_math_quiz.h"

// [get_random_operation] adalah fungsi yang mengembalikan operasi matematika secara acak.
static enum Operation get_random_operation(const int mode) {
    if (mode == 1) {
        return rand() % 2;
    }
    if (mode == 2) {
        return rand() % 2 + 2;
    }
    return -1;
}

// [get_operation_symbol] adalah fungsi yang mengembalikan simbol operasi matematika dari enum [Operation].
static char get_operation_symbol(const enum Operation operation) {
    switch (operation) {
        case increment: return '+';
        case decrement: return '-';
        case multiply: return '*';
        case divide: return '/';
    }
    return '?';
}

// [evaluate_complex_expression] adalah fungsi yang menghitung hasil dari ekspresi matematika yang kompleks.
static double evaluate_complex_expression(int numbers[], enum Operation operations[], const int count) {
    double result = numbers[0];

    for (int i = 0; i < count; i++) {
        switch (operations[i]) {
            case increment:
                result += numbers[i + 1];
            break;
            case decrement:
                result -= numbers[i + 1];
            break;
            case multiply:
                result *= numbers[i + 1];
            break;
            case divide:
                if (numbers[i + 1] != 0) {
                    result /= numbers[i + 1];
                } else {
                    result = 0;
                }
            break;
        }
    }
    return result;
}

// [generateQuestion] adalah fungsi yang menghasilkan pertanyaan matematika secara acak.
static int generateQuestion(const int min, const int max, int *questionNumber, const int maxOperations) {
    const int numCount = maxOperations + 1;
    int numbers[numCount];
    const int modeSeed = get_random_int(1, 2);
    enum Operation operations[maxOperations];

    for (int i = 0; i < numCount; i++) {
        numbers[i] = get_random_int(min, max);
    }
    for (int i = 0; i < maxOperations; i++) {
        operations[i] = get_random_operation(modeSeed);
        if (operations[i] == divide && numbers[i + 1] == 0) {
            numbers[i + 1] = get_random_int(1, max);
        }
    }

    printf("Question %d: ", (*questionNumber)++);
    printf("%d", numbers[0]);
    for (int i = 0; i < maxOperations; i++) {
        printf(" %c %d", get_operation_symbol(operations[i]), numbers[i + 1]);
    }
    printf(" = ?\n");

    double result = evaluate_complex_expression(numbers, operations, maxOperations);
    if (maxOperations > 1) {
        result = round(result * 100.0) / 100.0;
    }

    const time_t start = time(NULL);
    double answer;
    printf("Your answer (30 seconds): ");
    const int retScanf = scanf("%lf", &answer);
    getchar();
    if (retScanf != 1) {
        printf("Invalid input! You lose a point.\n");
        return -1;
    }

    if (time(NULL) - start > 30) {
        printf("Time's up! You lose a point.\n");
        return -1;
    }

    if (fabs(answer - result) < 0.01) {
        printf("Correct! You answered in %d seconds.\n", (int) (time(NULL) - start));
        return 30 - (int) (time(NULL) - start);
    } else {
        printf("Wrong! The correct answer is: %.2f\n", result);
        return 30 - (int) (time(NULL) - start);
    }
}

// [game_math] adalah fungsi yang menjalankan game matematika.
static int game_math() {
    clear();
    srand(time(NULL));

    const int min = 10;
    const int max = 100;
    int score = 0, questionNumber = 1;
    const int maxOperations = 3;

    for (int i = 0; i < 5; i++) {
        printf("Current score: %d\n\n", score);
        score += generateQuestion(min, max, &questionNumber, maxOperations);
        sleep(2);
        clear();
    }

    printf("Game over! Your final score is: %d\n", score);

    if (score > 3) {
        printf("Excellent job!\n");
    } else if (score > 0) {
        printf("Good effort!\n");
    } else {
        printf("Better luck next time!\n");
    }

    PRESS_ENTER_TO_CONTINUE();

    return score;
}

// [csg_math_quiz_start] adalah fungsi yang memulai game matematika. Fungsi ini mengembalikan [csg_game_result].
csg_game_result csg_math_quiz_start(void) {
    return csg_game_result_create(GAME_MATH_QUIZ, game_math());
}
