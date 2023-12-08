#include <stdio.h>
#include <math.h>

#define ACE 12
#define KING 11
#define QUEEN 10
#define JACK 9
#define TEN 8

enum { SINGLE, PAIR, THREE_OF_A_KIND, FOUR_OF_A_KIND, FIVE_OF_A_KIND };

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
        /* printf("%4d : ", (INPUT_SIZE - i)); */
        /* print_binary(ranked_bet[i*2]); */
        /* printf(" : %llu \n", ranked_bet[i*2 + 1]); */

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
                score += 0;
                ++counts[JACK];
                break;
            case 'T':
                score += (TEN + 1)*pow(ACE+1, 5-i);
                ++counts[TEN];
                break;
            default:
                score += (buffer[i] - '0' - 1)*pow(ACE+1, 5-i);
                ++counts[buffer[i] - '0' - 2];
                break;
        }
    }

    scanf(" %llu", &bet);

    int schemes[FIVE_OF_A_KIND + 1] = { 0 };
    int max_scheme_index = -1;

    for (int card = 0; card <= ACE; ++card) {
        if (card == JACK || counts[card] == 0) continue;
        int scheme_index = counts[card] - 1;

        ++schemes[scheme_index];
        
        if (scheme_index > max_scheme_index)
            max_scheme_index = scheme_index;
    }

    printf("%s ", buffer);

    /* for (int scheme_index = 0; scheme_index < 5; ++scheme_index) { */
    /*     if (schemes[scheme_index] == 0) continue; */
    /*     printf("%d: %d - ", scheme_index+1, schemes[scheme_index]); */
    /* } */

    /* printf(" J:%d ====== ", counts[JACK]); */

    --schemes[max_scheme_index];
    ++schemes[max_scheme_index + counts[JACK]];


    /* for (int scheme_index = 0; scheme_index < 5; ++scheme_index) { */
    /*     if (schemes[scheme_index] == 0) continue; */
    /*     printf("%d: %d - ", scheme_index+1, schemes[scheme_index]); */
    /* } */

    if (schemes[FIVE_OF_A_KIND] == 1)
        score |= 1ULL << 63;
    else if (schemes[3] == 1) {
        score |= 1ULL << 62;
    } else if (schemes[THREE_OF_A_KIND] == 1 && schemes[PAIR] == 1) {
        score |= 1ULL << 61;
    }  else if (schemes[THREE_OF_A_KIND] == 1) {
        score |= 1ULL << 60;
    } else if (schemes[PAIR] == 2) {
        score |= 1ULL << 59;
    } else if (schemes[PAIR] == 1) {
        score |= 1ULL << 58;
    }


    printf("%020llu\n", score);
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

