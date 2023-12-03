#include <stdio.h>
#include <ctype.h>

#define GRID_SIZE   140
#define GEAR        '*'

int check_for_signs(char grid[][GRID_SIZE+1], int x, int y, int* x_gear, int* y_gear);
int ctoi(char c);
void fill_grid(char grid[][GRID_SIZE+1]);
int compute_sum_ratio(int gears[GRID_SIZE][GRID_SIZE][2]);


int main (int argc, char** argv) {
    char grid[GRID_SIZE][GRID_SIZE+1], c;
    // for each coordinate x,y : 
    // - gears[y][x][0] is the count of part number linked to the gear
    // - gears[y][x][1] the product of all the part number linked to the gear
    int gears[GRID_SIZE][GRID_SIZE][2] = { 0 };
    int i, j, power, current_number, part_result, gear_result, is_part, x_gear, y_gear, in_number;

    fill_grid(grid);

    part_result = gear_result = 0;
    x_gear = y_gear = -1;

    for (i = 0; i < GRID_SIZE; ++i) {
        power = 1;
        is_part = current_number = in_number = 0;

        for (j = GRID_SIZE; j >= 0; --j){
            in_number = isdigit(grid[i][j]);

            if (in_number) {
                current_number += ctoi(grid[i][j]) * power;
                power *= 10;
                is_part |= check_for_signs(grid, j, i, &x_gear, &y_gear);
            } 

            // cannot use else since we could have reach the start of the line
            if (j == 0 || !in_number) {
                part_result += is_part ? current_number : 0;

                if (x_gear > 0) {
                    int part_number_count = gears[y_gear][x_gear][0];
                    if (part_number_count == 0) {
                        gears[y_gear][x_gear][1] = current_number;
                    } else if (part_number_count == 1) {
                        gears[y_gear][x_gear][1] *= current_number;
                    } else {
                        // no need to compute as we only want to the gear that
                        // have exactly two linked part numbers
                    }
                    ++gears[y_gear][x_gear][0];
                }

                power = 1;
                is_part = current_number = 0;
                x_gear = -1;
                y_gear = -1;
            }
        }
    }

    printf("Parts number sum : %d, Gears ratio sum : %d\n", part_result, compute_sum_ratio(gears));
}

int check_for_signs(char grid[][GRID_SIZE+1], int x, int y, int* x_gear, int* y_gear) {
    int i, j, k, is_part;

    is_part = 0;

    for (i = y-1; i < y+2; ++i) {
        if (i < 0 || i >= GRID_SIZE) continue;

        for (j = x-1; j < x+2; j++) {
            if (j < 0 || j >= GRID_SIZE) continue;

            if (grid[i][j] != '.' && !isdigit(grid[i][j])) {
                if (grid[i][j] == GEAR) {
                    *x_gear = j;
                    *y_gear = i;
                    // early return as it seems that a number can only
                    // be linked to 1 gear
                    return 1;
                }
                is_part = 1;
            }
        }
    }

    return is_part;
}

int ctoi(char c) {
    return c - '0';
}

void fill_grid(char grid[][GRID_SIZE+1]) {
    int i;

    for (i = 0; i < GRID_SIZE; ++i) {
        scanf("%s", grid[i]);
    }
}

int compute_sum_ratio(int gears[GRID_SIZE][GRID_SIZE][2]) {
    int result, i, j;

    result = 0;

    for (i = 0; i < GRID_SIZE; ++i) {
        for (j = 0; j < GRID_SIZE; ++j) {
            if (gears[i][j][0] == 2)
                result += gears[i][j][1];
        }
    }

    return result;
}
