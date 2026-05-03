#include <iomanip>
#include <iostream>
#include <vector>

#include "Common.h"
#include "GamePlay.h"
#include "Strategy.h"
#include "ThongKe.h"

using namespace std;

int main() {
    const int SO_BO_BAI = 8;
    const int GIOI_HAN_TRON_LAI = 50;
    const double DON_VI_CUOC = 1.0;

    int soVan;
    cout << "Nhap so van mo phong: ";
    cin >> soVan;

    if (soVan <= 0) {
        cout << "So van khong hop le!" << endl;
        return 0;
    }

    Shoe shoe(SO_BO_BAI);
    GamePlay game(&shoe);

    vector<KetQua> danhSachKetQua;
    danhSachKetQua.reserve(soVan);

    long long playerThang = 0;
    long long bankerThang = 0;
    long long hoa = 0;

    for (int i = 0; i < soVan; i++) {
        if (shoe.soLaConLai() < GIOI_HAN_TRON_LAI) {
            shoe.taoMoi(SO_BO_BAI);
        }

        KetQua kq = game.choiMotVan();
        danhSachKetQua.push_back(kq);

        if (kq == PLAYER_THANG) playerThang++;
        else if (kq == BANKER_THANG) bankerThang++;
        else hoa++;
    }

    cout << fixed << setprecision(4);
    cout << "\nTONG KET TAN SUAT KET QUA" << endl;
    cout << "Tong so van: " << soVan << endl;
    cout << "Player thang: " << playerThang * 100.0 / soVan << "%" << endl;
    cout << "Banker thang: " << bankerThang * 100.0 / soVan << "%" << endl;
    cout << "Hoa Tie:      " << hoa * 100.0 / soVan << "%" << endl;

    ChienThuatCoDinh luonBanker(CUOC_BANKER, "Luon dat Banker");
    ChienThuatCoDinh luonPlayer(CUOC_PLAYER, "Luon dat Player");
    ChienThuatCoDinh luonTie(CUOC_TIE, "Luon dat Tie");
    SoiCauBet cauBet(3);
    SoiCau11 cau11;
    SoiCau12_13 cau12;
    SoiCauNghieng cauNghieng(12, 3);
    TongHopSoiCau tongHop;

    vector<ChienThuat*> dsChienThuat;
    dsChienThuat.push_back(&luonBanker);
    dsChienThuat.push_back(&luonPlayer);
    dsChienThuat.push_back(&luonTie);
    dsChienThuat.push_back(&cauBet);
    dsChienThuat.push_back(&cau11);
    dsChienThuat.push_back(&cau12);
    dsChienThuat.push_back(&cauNghieng);
    dsChienThuat.push_back(&tongHop);

    cout << "\nCHIEN THUAT CHOI, " << DON_VI_CUOC << " don vi/van" << endl;
    cout << left << setw(22) << "Chien thuat"
         << right << setw(12) << "So cuoc"
         << setw(14) << "Loi/Lo"
         << setw(14) << "EV/cuoc"
         << setw(16) << "MaxDrawdown" << endl;

    for (int i = 0; i < (int)dsChienThuat.size(); i++) {
        KetQuaChienThuat kq = danhGiaChienThuat(*dsChienThuat[i], danhSachKetQua, DON_VI_CUOC);
        cout << left << setw(22) << kq.ten
             << right << setw(12) << kq.soCuoc
             << setw(14) << kq.loiLo
             << setw(14) << kq.evMoiCuoc
             << setw(16) << kq.maxDrawdown << endl;
    }

    cout << "\nGIAI THICH NHANH" << endl;
    cout << "EV/cuoc: loi hoac lo trung binh tren moi 1 don vi tien cuoc." << endl;
    cout << "MaxDrawdown: muc tut von lon nhat tu dinh xuong day trong qua trinh choi." << endl;
    cout << "Neu EV am, ve dai han nguoi choi dang bat loi va chu co loi the." << endl;

    return 0;
}
