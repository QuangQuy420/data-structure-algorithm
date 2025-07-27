#pragma once
#include "structs.h"

int isDauSachEmpty(ListDauSach &lds);
int isDauSachFull(ListDauSach &lds);
void insertFirst(PTRSach &first, Sach sach);
void insertLastSach(PTRSach &first, Sach sach);
void xuLyNhapDauSach(ListDauSach &lds);
void timSach(ListDauSach &lds);
void xuLyInDauSachTheoTheLoai(ListDauSach &lds, DauSach* nodesSapXep[]);

