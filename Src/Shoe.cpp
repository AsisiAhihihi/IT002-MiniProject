#include "Shoe.h"
#include <algorithm>

Shoe::Shoe(int soBo) : rng(random_device{}()) {
    taoMoi(soBo);
}

void Shoe::taoMoi(int soBo) {
    cards.clear();

    for (int d = 0; d < soBo; d++) {
        for (int r = 1; r <= 13; r++) {
            for (int s = 1; s <= 4; s++) {
                cards.push_back(Card(r, s));
            }
        }
    }

    tronBai();
}

void Shoe::tronBai() {
    shuffle(cards.begin(), cards.end(), rng);
}

Card Shoe::rutBai() {
    Card c = cards.back();
    cards.pop_back();
    return c;
}

int Shoe::soLaConLai() const {
    return (int)cards.size();
}
