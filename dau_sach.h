#pragma once
#include "structs.h"

int isDauSachEmpty(ListDauSach &lds);
int isDauSachFull(ListDauSach &lds);
void insertFirst(PTRSach &first, Sach sach);
void insertLastSach(PTRSach &first, Sach sach);
void nhapDauSach(ListDauSach &lds);
void timSach(ListDauSach &lds);
void inDauSachTheoTheLoai(ListDauSach &lds, DauSach* nodesSapXep[]);

