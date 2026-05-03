#include "Hand.h"

void Hand::themBai(const Card& c) {
    cards.push_back(c);
}

int Hand::tinhDiem() const {
    int tong = 0;
    for (int i = 0; i < (int)cards.size(); i++) {
        tong += cards[i].getValue();
    }
    return tong % 10;
}

void Hand::xoaBai() {
    cards.clear();
}
