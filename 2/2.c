#include <stdio.h>
#include <string.h>

#define max(a, b) a > b ? a : b
#define MAX_RED 13
#define MAX_GREEN 14
#define MAX_BLUE 15


int scan_line(int* id, int* r, int* g, int* b) {
    int tmp;
    char color[7];

    scanf("Game %d:", id);

    do {
        scanf("%d %s", &tmp, color);

        if (color[0] == 'r') {
            *r = max(*r, tmp);
        } else if (color[0] == 'g') {
            *g = max(*g, tmp);
        } else if (color[0] == 'b') {
            *b = max(*b, tmp);
        }
    } while (strchr(color, ',') != NULL || strchr(color, ';') != NULL);

    if (getchar() == EOF) {
        return 0;
    }

    return 1;
}

int main(int argc, char** argv) {
    int id, r, g, b, sum_id, sum_power, i;

    r = g = b = sum_id = sum_power = 0;

    while(scan_line(&id, &r, &g, &b)) {
        if (r < MAX_RED && g < MAX_GREEN && b < MAX_BLUE) {
            sum_id += id;
        }

        sum_power += r * g * b;

        r = g = b = 0;
    }

    printf("sum_id : %d, sum_power: %d\n", sum_id, sum_power);

    return 0;
}
