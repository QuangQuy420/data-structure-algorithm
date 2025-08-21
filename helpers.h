#pragma once

string chuanHoaChuoi(string str);
int nhapChuoi(string &s, int maxLen, bool isUpper = false);
int nhapSo(int &so, int min, int max, int maxLen);
int tinhSoTrang(int soItem);

// Dau Sach
bool nhapISBN(ListDauSach &lds, string &ISBN, int x, int y);
bool nhapTheLoaiDS(int &theLoai, int x, int y);
bool nhapTenSach(string &tenSach, int x, int y);
bool nhapTenTacGia(string &tacGia, int x, int y);
bool nhapSoTrang(int &soTrang, int x, int y);
bool nhapNamXuatBan(int &namXuatBan, int x, int y);
bool nhapSoLuongSach(int &soLuongSach, int x, int y);
bool nhapViTri(string &viTri, int x, int y);

// Tim Sach
int nhapTenSachTimKiem(string &tenSach, int &trang, int soTrang, int x, int y);
int nhapChuoiTimKiem(string &s, int &trang, int soTrang, int maxLen);
int kiemTraTonTaiISBN(ListDauSach &lds, string ISBN);

// Doc Gia
void thongBao(int type, string message, int x, int y);
void clearBaoLoi(int x, int y);
bool nhapHoDocGia(string &ho, int x, int y);
bool nhapTenDocGia(string &ten, int x, int y);
bool nhapPhaiDocGia(int &phai, int x, int y);
bool nhapMaDocGia(int &maDG, int x, int y);
bool nhapXacNhan(string &xacNhan, int x, int y);

void clearTinhNang(int x, int y, int dong = 30, int khoangTrang = 45);

//Muon Tra
bool nhapMaDG(int &maDG, int x, int y);
bool nhapISBNMuonSach(string &ISBN, int x, int y);
bool nhapMaSachCon(int &maSachMuon, int x, int y);
bool nhapXacNhanMT(string &xacNhan, int x, int y);

bool nhapMaSachTra(string &maSachTra, int x, int y);

