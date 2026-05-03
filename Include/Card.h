#ifndef CARD_H
#define CARD_H

class Card {
private:
    int rank; // A=1, 2..10, J=11, Q=12, K=13
    int suit; // 1=Bich, 2=Chuon, 3=Ro, 4=Co

public:
    Card();
    Card(int r, int s);

    int getValue() const;
};

#endif
