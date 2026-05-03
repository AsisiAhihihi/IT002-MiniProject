#ifndef GAMEPLAY_H
#define GAMEPLAY_H

#include "Common.h"
#include "Shoe.h"
#include "Hand.h"

class GamePlay {
private:
    Shoe* shoe;

    KetQua timKetQua(int diemPlayer, int diemBanker) const;
    bool bankerCanRutLa3(int diemBanker, int laThu3Player) const;

public:
    GamePlay(Shoe* s);
    KetQua choiMotVan();
};

#endif
