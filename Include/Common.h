#ifndef COMMON_H
#define COMMON_H

#include <string>
using namespace std;

enum KetQua {
    PLAYER_THANG = 1,
    HOA = 2,
    BANKER_THANG = 3
};

enum CuaCuoc {
    CUOC_PLAYER,
    CUOC_BANKER,
    CUOC_TIE,
    BO_QUA
};

string tenKetQua(KetQua kq);
string tenCuaCuoc(CuaCuoc cuoc);

#endif
