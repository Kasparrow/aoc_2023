#include <stdio.h>
#include <math.h>

#define ACE 12
#define KING 11
#define QUEEN 10
#define JACK 9
#define TEN 8

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
    mask score, card_mask, bet, card_ranking;
    char buffer[6];
    int i;

    int counts[ACE+1] = {0};
    card_ranking = 0UL;
    score = 0ULL;

    for (i = 0; i < 5; ++i) {
        switch((buffer[i] = getchar())) {
            case 'A':
                ++counts[ACE];
                score += ACE*pow(ACE+1, 5-i);
                break;
            case 'K':
                ++counts[KING];
                score += KING*pow(ACE+1, 5-i);
                break;
            case 'Q':
                score += QUEEN*pow(ACE+1, 5-i);
                ++counts[QUEEN];
                break;
            case 'J':
                score += JACK*pow(ACE+1, 5-i);
                ++counts[JACK];
                break;
            case 'T':
                score += TEN*pow(ACE+1, 5-i);
                ++counts[TEN];
                break;
            default:
                score += (buffer[i] - '0' - 2)*pow(ACE+1, 5-i);
                ++counts[buffer[i] - '0' - 2];
                break;
        }
    }

    scanf(" %llu", &bet);

    int scheme[5] = { 0 };

    for (i = 0; i < ACE+1; ++i) {
        scheme[counts[i] - 1]++;
    }

    if (scheme[4] == 1)
        score |= 1ULL << 63;
    else if (scheme[3] == 1) {
        score |= 1ULL << 62;
    } else if (scheme[2] == 1 && scheme[1] == 1) {
        score |= 1ULL << 61;
    }  else if (scheme[2] == 1) {
        score |= 1ULL << 60;
    } else if (scheme[1] == 2) {
        score |= 1ULL << 59;
    } else if (scheme[1] == 1) {
        score |= 1ULL << 58;
    }

    // insert score and bet in array
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

