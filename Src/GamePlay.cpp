#include "GamePlay.h"

GamePlay::GamePlay(Shoe* s) {
    shoe = s;
}

KetQua GamePlay::timKetQua(int diemPlayer, int diemBanker) const {
    if (diemPlayer > diemBanker) return PLAYER_THANG;
    if (diemBanker > diemPlayer) return BANKER_THANG;
    return HOA;
}

bool GamePlay::bankerCanRutLa3(int diemBanker, int laThu3Player) const {
    // laThu3Player = -1 nghia la Player khong rut la thu 3.
    if (laThu3Player == -1) return diemBanker <= 5;

    if (diemBanker <= 2) return true;
    if (diemBanker == 3) return laThu3Player != 8;
    if (diemBanker == 4) return laThu3Player >= 2 && laThu3Player <= 7;
    if (diemBanker == 5) return laThu3Player >= 4 && laThu3Player <= 7;
    if (diemBanker == 6) return laThu3Player == 6 || laThu3Player == 7;
    return false;
}

KetQua GamePlay::choiMotVan() {
    Hand player, banker;

    for (int i = 0; i < 2; i++) {
        player.themBai(shoe->rutBai());
        banker.themBai(shoe->rutBai());
    }

    int diemPlayer = player.tinhDiem();
    int diemBanker = banker.tinhDiem();

    // Natural 8/9: dung lai, khong rut them.
    if (diemPlayer >= 8 || diemBanker >= 8) {
        return timKetQua(diemPlayer, diemBanker);
    }

    int laThu3Player = -1;

    if (diemPlayer <= 5) {
        Card c = shoe->rutBai();
        player.themBai(c);
        laThu3Player = c.getValue();
        diemPlayer = player.tinhDiem();
    }

    if (bankerCanRutLa3(diemBanker, laThu3Player)) {
        banker.themBai(shoe->rutBai());
        diemBanker = banker.tinhDiem();
    }

    return timKetQua(diemPlayer, diemBanker);
}
