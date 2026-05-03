#ifndef STRATEGY_H
#define STRATEGY_H

#include <string>
#include <vector>
#include "Common.h"
using namespace std;

class ChienThuat {
public:
    virtual ~ChienThuat();
    virtual string getTen() const = 0;
    virtual CuaCuoc chonCua(const vector<KetQua>& lichSu) = 0;
};

class ChienThuatCoDinh : public ChienThuat {
private:
    CuaCuoc cua;
    string ten;

public:
    ChienThuatCoDinh(CuaCuoc c, string t);
    string getTen() const;
    CuaCuoc chonCua(const vector<KetQua>& lichSu);
};

vector<KetQua> layKetQuaKhongHoa(const vector<KetQua>& lichSu, int soLuong);
KetQua layKetQuaGanNhat(const vector<KetQua>& lichSu);
int demChuoiGanNhat(const vector<KetQua>& lichSu);

class SoiCauBet : public ChienThuat {
private:
    int soVanToiThieu;

public:
    SoiCauBet(int n = 3);
    string getTen() const;
    CuaCuoc chonCua(const vector<KetQua>& lichSu);
};

class SoiCau11 : public ChienThuat {
public:
    string getTen() const;
    CuaCuoc chonCua(const vector<KetQua>& lichSu);
};

class SoiCau12_13 : public ChienThuat {
private:
    bool khopMau(const vector<KetQua>& h, const vector<KetQua>& mau) const;
    CuaCuoc cuaTiepTheo(const vector<KetQua>& h, const vector<KetQua>& mau) const;

public:
    string getTen() const;
    CuaCuoc chonCua(const vector<KetQua>& lichSu);
};

class SoiCauNghieng : public ChienThuat {
private:
    int soVanXet;
    int doLechToiThieu;

public:
    SoiCauNghieng(int soVan = 12, int doLech = 3);
    string getTen() const;
    CuaCuoc chonCua(const vector<KetQua>& lichSu);
};

class TongHopSoiCau : public ChienThuat {
private:
    SoiCauBet cauBet;
    SoiCau11 cau11;
    SoiCau12_13 cau12;
    SoiCauNghieng cauNghieng;

    bool coCauBet(const vector<KetQua>& lichSu) const;
    bool coCau11(const vector<KetQua>& lichSu) const;

public:
    TongHopSoiCau();
    string getTen() const;
    CuaCuoc chonCua(const vector<KetQua>& lichSu);
};

#endif
