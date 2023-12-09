#include <stdio.h>
#include <math.h>

#define PATH_SIZE 293
#define INPUT_SIZE 794
void scan_path(char* path);
void scan_map(int* map);
int position_to_index(char* position);
void print_index_as_position(int index);
int in_end_position(int position, int* positions, int n);

int main(int argc, char** argv) {
    char path[PATH_SIZE + 1] = { '\0' };
    int map[(26 + 26 * 26 + 26 * 26 * 26)*2];

    scanf("%s\n", path);
    scan_map(map);

    int i, current_position;
    unsigned long long result;

    i = 0;
    current_position = position_to_index("AAA");
    result = 0ULL;

    for (i = 0; current_position != position_to_index("ZZZ");) {
        switch(path[i % INPUT_SIZE]) {
            case '\0':
                i = 0;
                continue;
            case 'L':
                  current_position = map[current_position*2];
                  break;
            case 'R':
                  current_position = map[current_position*2 + 1];
                  break;
            default:
                  break;
        }
        
        ++result;
        ++i;
    }

    printf("Result (1) %llu\n", result);

    // cat 8.input | grep -E "^..A"
    int current_positions[6] = {
        position_to_index("MPA"),
        position_to_index("AAA"),
        position_to_index("DVA"),
        position_to_index("TDA"),
        position_to_index("FJA"),
        position_to_index("XPA"),
    };

    int end_positions[6] = {
        position_to_index("DGZ"),
        position_to_index("MVZ"),
        position_to_index("CJZ"),
        position_to_index("MSZ"),
        position_to_index("ZZZ"),
        position_to_index("QFZ"),
    };

    int frequences[6] = { 0, 0, 0, 0, 0, 0 };
    int filled_frequence = 0;

    i = 0;
    result = 0ULL;
    
    int exit, min_frequence;

    while (1) {
        char direction = path[i % INPUT_SIZE];

        if(direction == '\0') {
            i = 0;
            continue;
        }

        exit = 1;

        for (int j = 0; j < 6; ++j) {
            switch(direction) {
                case 'L':
                      current_positions[j] = map[current_positions[j]*2];
                      break;
                case 'R':
                      current_positions[j] = map[current_positions[j]*2 + 1];
                      break;
                default:
                      break;
            }


            if (in_end_position(current_positions[j], end_positions, 6) && frequences[j] == 0) {
                if (filled_frequence == 0)
                    min_frequence = result+1;
                frequences[j] = result+1;
                filled_frequence++;
            }
            
        }

        if (filled_frequence == 6) {
            break;
        }
        ++i;
        ++result;
    }

    unsigned long long result_2;
    for (result_2 = min_frequence; ; result_2 +=min_frequence) {
        int exit = 1;
        for (int j = 0; j < 6; ++j) {
            exit = exit && ((result_2 % frequences[j]) == 0);
        }

        if (exit) break;
    }

    printf("Result (2) %llu\n", result_2);

    return 0;
}

int in_end_position(int position, int* positions, int n) {
    for (int i = 0; i < n; ++i)
        if (position == positions[i])
            return 1;
    return 0;
}

void scan_map(int* map) {
    char index[4], right[4],  left[4];

    for (int j = 0; j < INPUT_SIZE; ++j) {
        scanf("%s%s%s", index, left, right);
        int i = position_to_index(index);
        map[i*2] = position_to_index(left);
        map[i*2+1] = position_to_index(right);
    }
}

int position_to_index(char* position) {
    return (position[0] - 'A') * 26 * 26 + (position[1] - 'A') * 26 + position[2] - 'A';
}

void print_index_as_position(int index) {
    printf("%c", (index / (26 * 26)) + 'A');
    index %= (26 * 26);
    printf("%c", index / 26 + 'A');
    index %= 26;
    printf("%c", index + 'A');
}

