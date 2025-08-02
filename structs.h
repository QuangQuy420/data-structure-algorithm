#pragma once
#include <string>

#define MAXLIST 10000

using namespace std;

// =================================

struct Sach
{
    string maSach;
    int trangThai = -1; // 0: cho muon duoc, 1: da muon, 2: da thanh ly
    string viTri;
};

struct nodeSach
{
    Sach sach;
    nodeSach *next = NULL;
};

typedef nodeSach *PTRSach;

// =================================

struct DauSach
{
    string ISBN;
    string tenSach;
    int soTrang = -1;
    string tacGia;
    int namXuatBan = -1;
    string theLoai;
    int soLuotMuon = -1; // So luot muon cua sach
    int soLuongSach = 0;
    PTRSach ptrSach = NULL; // Con tro den danh sach cac sach cung dau sach nay
};

typedef struct
{
    int n = 0;
    DauSach nodes[MAXLIST];
} ListDauSach;

// =================================

struct Date {
    int ngay, thang, nam;
};

struct MuonTra
{
    string maSach;
    Date ngayMuon;
    Date ngayTra;
    int trangThai = -1;     // 0: sach dang muon (chua tra), 1: da tra, 2: mat sach
    string viTri; // ????
};

struct nodeMT
{
    MuonTra mt;
    nodeMT *next = NULL;
};

typedef nodeMT *PTRMT;

// =================================

struct DocGia
{
    int maThe = -1; // So nguyen ngau nhien tu dong
    string ho;
    string ten;
    int phai = -1;
    int trangThai = -1; // 0: da khoa, 1: dang hoat dong
    PTRMT ptrMT = NULL; // Con tro den danh sach muon tra cua doc gia
};

struct nodeDG
{
    DocGia dg;
    nodeDG *left = NULL; // Con tro den nut con ben trai
    nodeDG *right = NULL; // Con tro den nut con ben phai
};

typedef nodeDG *PTRDG;

