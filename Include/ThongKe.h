#ifndef THONGKE_H
#define THONGKE_H

#include <string>
#include <vector>
#include "Common.h"
#include "Strategy.h"
using namespace std;

struct KetQuaChienThuat {
    string ten;
    long long soVan;
    long long soCuoc;
    double loiLo;
    double evMoiCuoc;
    double maxDrawdown;
};

double tinhLoiLo(CuaCuoc cuoc, KetQua ketQua, double donVi);
KetQuaChienThuat danhGiaChienThuat(ChienThuat& chienThuat, const vector<KetQua>& danhSachKetQua, double donVi);

#endif
