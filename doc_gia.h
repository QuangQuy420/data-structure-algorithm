#pragma once
#include "structs.h"

void insertLastMT(PTRMT &first, MuonTra mt);
void insertDG(PTRDG &root, DocGia dg);
void xuLyInDocGiaTheoTen(PTRDG root);
void inKhungQuanLyDocGia();
int tinhSoTrang(PTRDG root);
void xuLyInDanhSachDocGia(PTRDG root, int trang, int soTrang);

// Them doc gia
void xuLyNhapDocGia(PTRDG &root, int listMaThe[], int &soLuongMaThe);

// Cap nhat doc gia
void xuLyCapNhatDocGia(PTRDG &root);
