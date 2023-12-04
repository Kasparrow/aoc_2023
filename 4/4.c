#include <stdio.h>

#define WINNING_NUMBER_SIZE 10
#define PLAYER_NUMBER_SIZE 25
#define INPUT_SIZE 202

int scan_line(int* id, int* winning_numbers, int* player_numbers);
int main(int argc, char** argv) {
    int id, i, j, total_points, loop_total_points, loop_count, count_copies;
    int winning_numbers[WINNING_NUMBER_SIZE];
    int player_numbers[PLAYER_NUMBER_SIZE];

    int copies[INPUT_SIZE];
    for (i = 0; i < INPUT_SIZE; ++i)
        copies[i] = 1;

    total_points = 0;

    while(scan_line(&id, winning_numbers, player_numbers)) {
        loop_total_points = 0;
        loop_count = 0;

        for (i = 0; i < 25; ++i) {
            for (j = 0; j < 10; ++j) {
                if (player_numbers[i] != winning_numbers[j]) continue;

                loop_total_points = loop_total_points != 0 ? loop_total_points * 2 : 1;
                ++loop_count;
                break;
            }
        }

        for (j = id; j < (id + loop_count) && j < INPUT_SIZE; ++j)
            copies[j] += copies[id-1];

        total_points += loop_total_points;
    }

    count_copies = 0;
    
    for (int i = 0; i < id; ++i)
        count_copies += copies[i];

    printf("total points : %d, count copies : %d\n", total_points, count_copies);
    return 0;
}

int scan_line(int* id, int* winning_numbers, int* player_numbers) {
    int i;
    scanf("Card %3d:", id);
    for (i = 0; i < WINNING_NUMBER_SIZE; ++i)
        scanf(" %d", &winning_numbers[i]);

    scanf(" |");

    for (i = 0; i < PLAYER_NUMBER_SIZE; ++i)
        scanf(" %d", &player_numbers[i]);

    if (getchar() == EOF)
        return 0;

    return 1;
}
