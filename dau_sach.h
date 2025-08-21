#pragma once
#include "structs.h"

int isDauSachEmpty(ListDauSach &lds);
int isDauSachFull(ListDauSach &lds);
void insertFirst(PTRSach &first, Sach sach);
void insertLastSach(PTRSach &first, Sach sach);

// ========== Them Dau Sach ==========
void xuLyNhapDauSach(ListDauSach &lds);

// ========== Xu Ly In Danh Sach Dau Sach ==========
void inKhungQuanLyDauSach();
void xuLyInDanhSachDauSach(ListDauSach &lds, int trang, int soTrang);

// ========== Tim Sach ==========
void xuLyTimSach(ListDauSach &lds);
string layTheLoai(int theLoai);
