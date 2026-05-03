#include "Card.h"

Card::Card() {
    rank = 1;
    suit = 1;
}

Card::Card(int r, int s) {
    rank = r;
    suit = s;
}

int Card::getValue() const {
    if (rank >= 10) return 0;
    return rank;
}
