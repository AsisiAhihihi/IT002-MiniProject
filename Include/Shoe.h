#ifndef SHOE_H
#define SHOE_H

#include <vector>
#include <random>
#include "Card.h"
using namespace std;

class Shoe {
private:
    vector<Card> cards;
    mt19937 rng;

public:
    Shoe(int soBo = 8);

    void taoMoi(int soBo = 8);
    void tronBai();
    Card rutBai();
    int soLaConLai() const;
};

#endif
