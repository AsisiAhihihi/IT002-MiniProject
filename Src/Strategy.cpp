#include "Strategy.h"
#include <algorithm>

ChienThuat::~ChienThuat() {}

ChienThuatCoDinh::ChienThuatCoDinh(CuaCuoc c, string t) {
    cua = c;
    ten = t;
}

string ChienThuatCoDinh::getTen() const {
    return ten;
}

CuaCuoc ChienThuatCoDinh::chonCua(const vector<KetQua>& lichSu) {
    return cua;
}

vector<KetQua> layKetQuaKhongHoa(const vector<KetQua>& lichSu, int soLuong) {
    vector<KetQua> kq;

    for (int i = (int)lichSu.size() - 1; i >= 0 && (int)kq.size() < soLuong; i--) {
        if (lichSu[i] != HOA) {
            kq.push_back(lichSu[i]);
        }
    }

    reverse(kq.begin(), kq.end());
    return kq;
}

KetQua layKetQuaGanNhat(const vector<KetQua>& lichSu) {
    for (int i = (int)lichSu.size() - 1; i >= 0; i--) {
        if (lichSu[i] != HOA) return lichSu[i];
    }
    return HOA;
}

int demChuoiGanNhat(const vector<KetQua>& lichSu) {
    KetQua ganNhat = layKetQuaGanNhat(lichSu);
    if (ganNhat == HOA) return 0;

    int dem = 0;
    for (int i = (int)lichSu.size() - 1; i >= 0; i--) {
        if (lichSu[i] == HOA) continue;
        if (lichSu[i] == ganNhat) dem++;
        else break;
    }
    return dem;
}

SoiCauBet::SoiCauBet(int n) {
    soVanToiThieu = n;
}

string SoiCauBet::getTen() const {
    return "Soi cau bet";
}

CuaCuoc SoiCauBet::chonCua(const vector<KetQua>& lichSu) {
    int chuoi = demChuoiGanNhat(lichSu);
    KetQua ganNhat = layKetQuaGanNhat(lichSu);

    if (chuoi >= soVanToiThieu) {
        if (ganNhat == BANKER_THANG) return CUOC_BANKER;
        return CUOC_PLAYER;
    }

    return CUOC_BANKER;
}

string SoiCau11::getTen() const {
    return "Soi cau 1-1";
}

CuaCuoc SoiCau11::chonCua(const vector<KetQua>& lichSu) {
    vector<KetQua> h = layKetQuaKhongHoa(lichSu, 4);
    if ((int)h.size() < 4) return CUOC_BANKER;

    bool luanPhien = true;
    for (int i = 1; i < (int)h.size(); i++) {
        if (h[i] == h[i - 1]) {
            luanPhien = false;
            break;
        }
    }

    if (luanPhien) {
        if (h.back() == BANKER_THANG) return CUOC_PLAYER;
        return CUOC_BANKER;
    }

    return CUOC_BANKER;
}

bool SoiCau12_13::khopMau(const vector<KetQua>& h, const vector<KetQua>& mau) const {
    int doDaiMau = (int)mau.size();
    int soOCanXet = doDaiMau * 2;

    if ((int)h.size() < soOCanXet) return false;

    int start = (int)h.size() - soOCanXet;
    for (int i = 0; i < soOCanXet; i++) {
        if (h[start + i] != mau[i % doDaiMau]) return false;
    }
    return true;
}

CuaCuoc SoiCau12_13::cuaTiepTheo(const vector<KetQua>& h, const vector<KetQua>& mau) const {
    KetQua tiepTheo = mau[h.size() % mau.size()];
    if (tiepTheo == BANKER_THANG) return CUOC_BANKER;
    return CUOC_PLAYER;
}

string SoiCau12_13::getTen() const {
    return "Soi cau 1-2/1-3";
}

CuaCuoc SoiCau12_13::chonCua(const vector<KetQua>& lichSu) {
    vector<KetQua> h = layKetQuaKhongHoa(lichSu, 8);
    if ((int)h.size() < 6) return CUOC_BANKER;

    vector<KetQua> mau1;
    mau1.push_back(PLAYER_THANG);
    mau1.push_back(BANKER_THANG);
    mau1.push_back(BANKER_THANG);

    vector<KetQua> mau2;
    mau2.push_back(BANKER_THANG);
    mau2.push_back(PLAYER_THANG);
    mau2.push_back(PLAYER_THANG);

    vector<KetQua> mau3;
    mau3.push_back(PLAYER_THANG);
    mau3.push_back(BANKER_THANG);
    mau3.push_back(BANKER_THANG);
    mau3.push_back(BANKER_THANG);

    vector<KetQua> mau4;
    mau4.push_back(BANKER_THANG);
    mau4.push_back(PLAYER_THANG);
    mau4.push_back(PLAYER_THANG);
    mau4.push_back(PLAYER_THANG);

    if (khopMau(h, mau1)) return cuaTiepTheo(h, mau1);
    if (khopMau(h, mau2)) return cuaTiepTheo(h, mau2);
    if (khopMau(h, mau3)) return cuaTiepTheo(h, mau3);
    if (khopMau(h, mau4)) return cuaTiepTheo(h, mau4);

    return CUOC_BANKER;
}

SoiCauNghieng::SoiCauNghieng(int soVan, int doLech) {
    soVanXet = soVan;
    doLechToiThieu = doLech;
}

string SoiCauNghieng::getTen() const {
    return "Soi cau nghieng";
}

CuaCuoc SoiCauNghieng::chonCua(const vector<KetQua>& lichSu) {
    vector<KetQua> h = layKetQuaKhongHoa(lichSu, soVanXet);
    if ((int)h.size() < soVanXet) return CUOC_BANKER;

    int player = 0;
    int banker = 0;

    for (int i = 0; i < (int)h.size(); i++) {
        if (h[i] == PLAYER_THANG) player++;
        if (h[i] == BANKER_THANG) banker++;
    }

    if (banker - player >= doLechToiThieu) return CUOC_BANKER;
    if (player - banker >= doLechToiThieu) return CUOC_PLAYER;
    return CUOC_BANKER;
}

TongHopSoiCau::TongHopSoiCau() : cauBet(3), cauNghieng(12, 3) {}

bool TongHopSoiCau::coCauBet(const vector<KetQua>& lichSu) const {
    return demChuoiGanNhat(lichSu) >= 3;
}

bool TongHopSoiCau::coCau11(const vector<KetQua>& lichSu) const {
    vector<KetQua> h = layKetQuaKhongHoa(lichSu, 4);
    if ((int)h.size() < 4) return false;

    for (int i = 1; i < (int)h.size(); i++) {
        if (h[i] == h[i - 1]) return false;
    }
    return true;
}

string TongHopSoiCau::getTen() const {
    return "Tong hop soi cau";
}

CuaCuoc TongHopSoiCau::chonCua(const vector<KetQua>& lichSu) {
    if (coCauBet(lichSu)) return cauBet.chonCua(lichSu);
    if (coCau11(lichSu)) return cau11.chonCua(lichSu);

    CuaCuoc theoMau = cau12.chonCua(lichSu);
    if (lichSu.size() >= 8 && theoMau != CUOC_BANKER) return theoMau;

    return cauNghieng.chonCua(lichSu);
}
