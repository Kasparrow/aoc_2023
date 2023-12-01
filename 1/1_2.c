#include <stdio.h>
#include <ctype.h>
#include <string.h>

#define ONE     "eno\0"
#define TWO     "owt\0"
#define THREE   "eerht\0"
#define FOUR    "ruof\0"
#define FIVE    "evif\0"
#define SIX     "xis\0"
#define SEVEN   "neves\0"
#define EIGHT   "thgie\0"
#define NINE    "enin\0"

int get_value(char* buffer) {

    if (strstr(buffer, ONE) == buffer)
        return 1;
    if (strstr(buffer, TWO) == buffer)
        return 2;
    if (strstr(buffer, THREE) == buffer)
        return 3;
    if (strstr(buffer, FOUR) == buffer)
        return 4;
    if (strstr(buffer, FIVE) == buffer)
        return 5;
    if (strstr(buffer, SIX) == buffer)
        return 6;
    if (strstr(buffer, SEVEN) == buffer)
        return 7;
    if (strstr(buffer, EIGHT) == buffer)
        return 8;
    if (strstr(buffer, NINE) == buffer)
        return 9;

    return -1;
}

void clear_buffer(char* b) {
    b[0] = b[1] = b[2] = b[3] = b[4] = '\0';
}

void shift_buffer(char* b, char c) {
    b[4] = b[3];
    b[3] = b[2];
    b[2] = b[1];
    b[1] = b[0];
    b[0] = c;
}

int main(int argc, char **argv) {
    char c;
    char buffer[6] = { '\0', '\0', '\0', '\0', '\0', '\0' }; 
    int first, last, result, current_value;

    result = 0;
    first = last = current_value = -1;

    while ((c = getchar()) != EOF) {
        if (c == '\n') {
            result += first * 10 + last;
            first = last = current_value = -1;
            clear_buffer(buffer);
            continue;
        }

        shift_buffer(buffer, c);

        if (isdigit(c)) {
            current_value = c - '0';
        } else {
            current_value = get_value(buffer);
        }

        if (current_value > 0) {
            if (first == -1) {
                first = last = current_value;
            } else {
                last = current_value;
            }
        }
    }

    printf("%d\n", result);

    return 0;
}
