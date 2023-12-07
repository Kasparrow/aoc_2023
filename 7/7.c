#include <stdio.h>

#define ACE 12
#define KING 11
#define QUEEN 10
#define JACK 9
#define TEN 8

// sol 6440

#define INPUT_SIZE 1000

int scan_input(unsigned long* ranked_bet);

int main(int argc, char** argv) {
    // 0: scores, 1: bet
    unsigned long ranked_bet[INPUT_SIZE * 2];

    while(scan_input(ranked_bet));


}

int scan_input(unsigned long* ranked_bet) {
    unsigned long i, score, card_mask, bet;
    char c;

    int counts[ACE+1];

    for (i = 0; i < 5; ++i) {
        switch((c = getchar())) {
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
                ++counts[c - '0' - 2];
                break;
        }
    }

    scanf(" %ld", ranked_bet);

    score = 0;

    for (i = 0; i < 13; ++i) {
        if (counts[i] == 0) continue;

        if (counts[i] == 1) {
            // special case
            if (i == 2) continue;
            card_mask = 1 << (i - 3);
        } else {
            card_mask = 1 << (i - 2);
            card_mask <<= (counts[i] - 1) * 13;
        }

        score |= card_mask;
    }

    printf("lx\n", score);

    

    // insert score and bet in array

    if (getchar() == '\n')
        return 1;

    return 0;
}
