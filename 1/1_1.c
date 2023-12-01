#include <stdio.h>
#include <ctype.h>

int main(int argc, char **argv) {
    char c;
    int first, last, result;

    result = 0;
    first = last = -1;

    while ((c = getchar()) != EOF) {
        if (c == '\n') {
            result += first * 10 + last;
            first = last = -1;
        }

        else if (isdigit(c)) {
            if (first == -1) {
                first = last = c - '0';
            } else {
                last = c - '0';
            }
        }

    }

    printf("%d\n", result);

    return 0;
}
