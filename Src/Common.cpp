#include "Common.h"

string tenKetQua(KetQua kq) {
    if (kq == PLAYER_THANG) return "Player";
    if (kq == BANKER_THANG) return "Banker";
    return "Tie";
}

string tenCuaCuoc(CuaCuoc cuoc) {
    if (cuoc == CUOC_PLAYER) return "Player";
    if (cuoc == CUOC_BANKER) return "Banker";
    if (cuoc == CUOC_TIE) return "Tie";
    return "Bo qua";
}
