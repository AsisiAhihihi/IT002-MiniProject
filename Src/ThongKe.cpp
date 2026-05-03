#include "ThongKe.h"

double tinhLoiLo(CuaCuoc cuoc, KetQua ketQua, double donVi) {
    if (cuoc == BO_QUA) return 0;

    if (cuoc == CUOC_TIE) {
        if (ketQua == HOA) return 8.0 * donVi;
        return -1.0 * donVi;
    }

    if (ketQua == HOA) {
        return 0; // Dat Player/Banker gap hoa thi tra lai tien cuoc.
    }

    if (cuoc == CUOC_PLAYER) {
        if (ketQua == PLAYER_THANG) return 1.0 * donVi;
        return -1.0 * donVi;
    }

    if (cuoc == CUOC_BANKER) {
        if (ketQua == BANKER_THANG) return 0.95 * donVi; // Tru 5% hoa hong.
        return -1.0 * donVi;
    }

    return 0;
}

KetQuaChienThuat danhGiaChienThuat(ChienThuat& chienThuat, const vector<KetQua>& danhSachKetQua, double donVi) {
    KetQuaChienThuat kq;
    kq.ten = chienThuat.getTen();
    kq.soVan = (long long)danhSachKetQua.size();
    kq.soCuoc = 0;
    kq.loiLo = 0;
    kq.evMoiCuoc = 0;
    kq.maxDrawdown = 0;

    vector<KetQua> lichSu;
    double vonHienTai = 0;
    double dinhVon = 0;

    for (int i = 0; i < (int)danhSachKetQua.size(); i++) {
        CuaCuoc cuoc = chienThuat.chonCua(lichSu);

        if (cuoc != BO_QUA) {
            kq.soCuoc++;
            vonHienTai += tinhLoiLo(cuoc, danhSachKetQua[i], donVi);

            if (vonHienTai > dinhVon) dinhVon = vonHienTai;

            double drawdown = dinhVon - vonHienTai;
            if (drawdown > kq.maxDrawdown) kq.maxDrawdown = drawdown;
        }

        lichSu.push_back(danhSachKetQua[i]);
    }

    kq.loiLo = vonHienTai;
    if (kq.soCuoc > 0) kq.evMoiCuoc = kq.loiLo / kq.soCuoc;

    return kq;
}
