#pragma once
#include "structs.h"

void insertLastMT(PTRMT &first, MuonTra mt);
void insertDG(PTRDG &root, DocGia dg);
void inKhungQuanLyDocGia();
//int tinhSoTrang(PTRDG root);
DocGia* timDocGiaTheoMa(PTRDG root, int maDG);

// Them doc gia
void xuLyNhapDocGia(PTRDG &root, int listMaThe[], int &soLuongMaThe);

// Cap nhat doc gia
void xuLyCapNhatDocGia(PTRDG &root);

// Xoa doc gia
void xuLyXoaDocGia(PTRDG &root);

// In doc gia theo ten or theo ma
void xuLyInDanhSachDocGia(PTRDG root, int trang, int soTrang, int typeInDG);
int demDocGia(PTRDG root);

