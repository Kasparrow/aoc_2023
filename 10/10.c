#include <stdio.h>
#include <string.h>

#define GRID_SIZE 140
#define NORTH_SYMBOLS "7|F"
#define SOUTH_SYMBOLS "J|L"
#define WEST_SYMBOLS "L-F"
#define EAST_SYMBOLS "J-7"
#define NORTH_END "L|JS"


void scan_grid(char* grid, char* state);
void print_grid(char* grid);
int north(int position);
int south(int position);
int west(int position);
int east(int position);
int x(int position);
int y(int position);
int next_position(char* grid, int current, int previous, int step, char* state);
int count_in_pipes(char* state);

int main(int argc, char** argv) {
    char grid[GRID_SIZE*GRID_SIZE], state[GRID_SIZE*GRID_SIZE] = { '.' }, c;
    int start_position = 0, start_x, start_y;

    scan_grid(grid, state);

    start_position = strchr(grid, 'S') - grid;
    start_x = start_position % GRID_SIZE;
    start_y = start_position / GRID_SIZE;

    int result = next_position(grid, start_position, -1, 0, state);
    printf("(1) %d", result / 2);
    int result_2 = count_in_pipes(state);
    printf("(2) %d", result_2);

    return 0;

}

void scan_grid(char* grid, char* state) {
    char c;
    int i = 0;

    while((c = getchar()) != EOF) {
        if (c == '\n') continue;
        state[i]='.';
        grid[i++] = c;
        
    }

}
void print_grid(char* grid) {
    int i = 0;
    while (i < GRID_SIZE * GRID_SIZE) {
        if (i % (GRID_SIZE) == 0)
            printf("\n%3d   ", i / GRID_SIZE);

        putchar(grid[i++]);
    }
}

int next_position(char* grid, int current, int previous, int step, char* state) {
    int next;
    // start
    state[current] = grid[current];
    if (previous == -1)  {
        if (strchr(NORTH_SYMBOLS, grid[north(current)]) != NULL) {
            next = north(current);
        } else if (strchr(EAST_SYMBOLS, grid[east(current)]) != NULL) {
            next = east(current);
        } else if (strchr(WEST_SYMBOLS, grid[west(current)]) != NULL) {
            next = west(current);
        } else if (strchr(SOUTH_SYMBOLS, grid[south(current)]) != NULL) {
            next = south(current);
        }

        return next_position(grid, south(current), current, step+1, state);
    }

    switch(grid[current]) {
        case '7':
            next = south(current) == previous ? west(current) : south(current);
            break;
        case '|':
            next = south(current) == previous ? north(current) : south(current);
            break;
        case 'F':
            next = south(current) == previous ? east(current) : south(current);
            break;
        case 'L':
            next = north(current) == previous ? east(current) : north(current);
            break;
        case '-':
            next = east(current) == previous ? west(current) : east(current);
            break;
        case 'J':
            next = north(current) == previous ? west(current) : north(current);
            break;
        case 'S':
            return step;
        default:
            break;
    }

    return next_position(grid, next, current, step + 1, state);
}

int count_in_pipes(char* state) {
    int i, count_left_north, result;

    i = result = 0;

    while (i < GRID_SIZE * GRID_SIZE) {
        if (state[i] != '.') {
            ++i;
            continue;
        }

        count_left_north = 0;

        // HORIZONTAL CHECK
        for (int j = (i/GRID_SIZE)*GRID_SIZE; j < i; j++) {
            if ((strchr(NORTH_END, state[j]) != NULL))
                ++count_left_north;
        }

        if (count_left_north % 2 == 1) {
            state[i] = 'I';
            result++;
        } else {
            state[i] = ' ';
        }

        ++i;
    }

    return result;
}

int north(int position) {
    return position - GRID_SIZE;
}

int south(int position) {
    return position + GRID_SIZE;
}

int west(int position) {
    return position -1;
}

int east(int position) {
    return position+1;
}

int x(int position) {
    return position % GRID_SIZE;
}

int y(int position) {
    return position / GRID_SIZE;
}
