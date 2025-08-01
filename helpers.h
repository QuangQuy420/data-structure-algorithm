#pragma once

string chuanHoaChuoi(string str);
int nhapChuoi(string &s, int maxLen);
int nhapSo(int &so, int min, int max, int maxLen);
//bool nhapMaISBN(ListDauSach &lds, string &s, int maxLen);
//bool chonTheLoai(string &theLoai);
string chuanHoaInHoa(string s);

// Dau Sach

// Doc Gia
void thongBao(int type, string message, int x, int y);
void clearBaoLoi(int x, int y);
bool nhapHoDocGia(string &ho);
bool nhapTenDocGia(string &ten);
bool nhapPhaiDocGia(int &phai);
bool nhapMaDocGia(int &maDG);

void clearTinhNang(int x, int y);
