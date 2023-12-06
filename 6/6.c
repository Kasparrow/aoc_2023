#include <stdio.h>

#define PART_2_TIME 61709066
#define PART_2_RECORD 643118413621041

void scan_input(unsigned long* times, unsigned long* records);

int main(int argc, char** argv) {
    unsigned long times[4], records[4];
    unsigned long i, j, tmp_result, result;

    scan_input(times, records);

    result = 1;

    for (i = 0; i < 4; i++) {
        tmp_result = 0;
        for (j = 0; j < times[i]; ++j) {
            if ((times[i] - j) * j > records[i]) {
                ++tmp_result;
            }
        }
        result *= tmp_result;
    }

    printf("Combination to win %ld\n", result);

    result = 0;
    for (j = 0; j < PART_2_TIME; ++j) {
        if ((PART_2_TIME - j) * j > PART_2_RECORD ) {
            ++result;
        }
    }

    printf("Combination to (2) win %ld\n", result);
    

    return 0;
}


void scan_input(unsigned long* times, unsigned long* records) {
    scanf("Time: %ld %ld %ld %ld\n", &times[0], &times[1], &times[2], &times[3]);
    scanf("Distance: %ld %ld %ld %ld\n", &records[0], &records[1], &records[2], &records[3]);
}
