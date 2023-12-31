#include <stdio.h>

#define ACE 12
#define KING 11
#define QUEEN 10
#define JACK 9
#define TEN 8

// sol 6440

#define INPUT_SIZE 1000

typedef unsigned long long mask;

int scan_input(mask* ranked_bet, int i);
void print_binary(mask number);

int main(int argc, char** argv) {
    // 0: scores, 1: bet
    mask ranked_bet[INPUT_SIZE * 2] = { 0ULL };
    unsigned long long result;
    int i;
    
    i = 0;

    for (i = 0; i < INPUT_SIZE; ++i) {
        scan_input(ranked_bet, i);
    }

    result = 0ULL;

    for (i = 0; i < INPUT_SIZE; ++i) {
        printf("%4d : ", (INPUT_SIZE - i));
        print_binary(ranked_bet[i*2]);
        printf(" : %llu \n", ranked_bet[i*2 + 1]);

        result += ranked_bet[(i*2)+1] * (INPUT_SIZE - i);
    }

    printf("(1) %llu\n", result);

    return 0;
}

int scan_input(mask* ranked_bet, int r) {
    mask score, card_mask, bet;
    char buffer[6];
    int i;

    int counts[ACE+1] = {0};

    for (i = 0; i < 5; ++i) {
        switch((buffer[i] = getchar())) {
            case 'A':
                ++counts[ACE];
                break;
            case 'K':
                ++counts[KING];
                break;
            case 'Q':
                ++counts[QUEEN];
                break;
            case 'J':
                ++counts[JACK];
                break;
            case 'T':
                ++counts[TEN];
                break;
            default:
                ++counts[buffer[i] - '0' - 2];
                break;
        }
    }

    scanf(" %llu", &bet);


    score = 0ULL;

    for (i = 0; i < ACE+1; ++i) {
        card_mask = 0ULL;
        if (counts[i] == 0) continue;

        if (counts[i] == 1) {
            if (i == 0) continue;
            card_mask = 1ULL << (i - 1);
        } else {
            card_mask = 1ULL << i;
            card_mask <<= ((counts[i] - 2) * 13 + 12);
        }

        score |= card_mask;
    }

    // insert score and bet in array
    printf("%d\n", r);
    for (; r > 0; --r) {
        if (ranked_bet[(r-1)*2] > score) break;

        ranked_bet[r*2] = ranked_bet[(r-1)*2];
        ranked_bet[r*2+1] = ranked_bet[(r-1)*2 + 1];
    }

    ranked_bet[r*2] = score;
    ranked_bet[r*2+1] = bet;

    if (getchar() == EOF)
        return 0;

    return 1;
}

void print_binary(mask number) {
    int i;

    for (i = 0; i < 64; ++i) {
        if (i % 13 == 0 && i != 0) putchar('|');
        if (i % 4 == 0 && i != 0) putchar(' ');
        printf("%d", ((1ULL << (63 - i)) & number) > 0);
    }
}

