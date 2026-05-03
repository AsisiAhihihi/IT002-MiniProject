#ifndef HAND_H
#define HAND_H

#include <vector>
#include "Card.h"
using namespace std;

class Hand {
private:
    vector<Card> cards;

public:
    void themBai(const Card& c);
    int tinhDiem() const;
    void xoaBai();
};

#endif
