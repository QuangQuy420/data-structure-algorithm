#include <iostream>
#include <cstring>
#include <sstream>
#include <iomanip>
#include "structs.h"
#include "dau_sach.h"
#include "helpers.h"

using namespace std;

int isDauSachEmpty(ListDauSach &lds) {
	return lds.n == 0;
}

int isDauSachFull(ListDauSach &lds) {
	return lds.n >= MAXLIST;
}

void insertFirst(PTRSach &first, Sach sach) {
    PTRSach newSach = new nodeSach;
    newSach->sach = sach;
    newSach->next = NULL;
    if (first == NULL) {
        first = newSach;
    } else {
    	newSach->next = first;
    	first = newSach;
    }
}

void insertLastSach(PTRSach &first, Sach sach) {
	PTRSach newSach = new nodeSach;
	newSach->sach = sach;
	newSach->next = NULL;
	
	if(first == NULL) {
		first = newSach;
	} else {
		PTRSach p = first;
		while(p->next != NULL) {
			p = p->next;
		}
		
		p->next = newSach;
	}
}

int _timViTriTheoTen(ListDauSach &lds, string ten) {
	if(isDauSachEmpty(lds)) return 0;

	for (int i = 0; i < lds.n; i++) {
		if (chuanHoaInHoa(lds.nodes[i].tenSach) > chuanHoaInHoa(ten)) {
			return i;
		}
	}
	return lds.n;
}

void insertAfterDS(ListDauSach &lds, DauSach ds) {
	int viTri = _timViTriTheoTen(lds, ds.tenSach);
	
	for(int i = lds.n - 1; i >= viTri; i--){
		lds.nodes[i+1] = lds.nodes[i];
	}
	lds.nodes[viTri] = ds;
	lds.n++;
}

string _danhMaSachTuDong(DauSach &ds) {
    ds.soLuongSach++;
    stringstream ss;
    ss << ds.ISBN << "-" << setfill('0') << setw(3) << ds.soLuongSach;
    return ss.str();
}

void nhapDauSach(ListDauSach &lds) {
    if (isDauSachFull(lds)) {
        cout << "Danh sach dau sach da day!" << endl;
        return;
    }

    DauSach ds;
    
    cout << "Nhap ma ISBN (toi da 4 ki tu): ";
    nhapMaISBN(lds, ds.ISBN, 4);

    cout << "Nhap ten sach (toi da 50 ki tu): ";
    nhapChuoi(ds.tenSach, 50);

    cout << "Nhap so trang (tu 1 den 100000):";
    nhapSo(ds.soTrang, 1, 100000);

    cout << "Nhap tac gia (toi da 50 ki tu): ";
    nhapChuoi(ds.tacGia, 50);

    cout << "Nhap nam xuat ban (tu 1000 toi 2025): ";
    nhapSo(ds.namXuatBan, 1000, 2025);

    chonTheLoai(ds.theLoai);

    ds.soLuotMuon = 0;
    ds.ptrSach = NULL;

    // Nhap danh sach cac cuon sach con
    int soCuon;
    cout << "Nhap so cuon sach con (tu 1 toi 10000): ";
    nhapSo(soCuon, 1, 10000);

    string viTriSachCon;
    cout << "Nhap vi tri cho tat ca sach con (toi da 20 ki tu): ";
    nhapChuoi(viTriSachCon, 20);

    for (int i = 0; i < soCuon; i++) {
        Sach sach;
        sach.maSach = _danhMaSachTuDong(ds);
		sach.trangThai = 0;
		sach.viTri = viTriSachCon;

        insertLastSach(ds.ptrSach, sach);
    }

    // Them dau sach vao danh sach
    insertAfterDS(lds, ds);

    cout << "Nhap dau sach thanh cong!" << endl;
}

void _swapDauSach(DauSach* &x, DauSach* &y) {
	DauSach* temp = x;
	x = y;
	y = temp;
}

void _sapXepDauSachTheoTheLoai(ListDauSach &lds, DauSach* nodesSapXep[]) {
	
	for (int i = 0; i < lds.n; i++) {
		// Gan dia chi vao nodesSapXep
		nodesSapXep[i] = &lds.nodes[i];
	}

	// Su dung selection sort 
	for (int i = 0; i < lds.n; i++) {
		for (int j = i + 1; j < lds.n; j++) {
			if(nodesSapXep[j]->theLoai < nodesSapXep[i]->theLoai) {
				_swapDauSach(nodesSapXep[j], nodesSapXep[i]);
			}
			else if (nodesSapXep[j]->theLoai == nodesSapXep[i]->theLoai) {
				if(chuanHoaInHoa(nodesSapXep[j]->tenSach) < chuanHoaInHoa(nodesSapXep[i]->tenSach)) {
					_swapDauSach(nodesSapXep[j], nodesSapXep[i]);
				}
			}
		}
	}
}

void inDauSachTheoTheLoai(ListDauSach &lds, DauSach* nodesSapXep[]) {
    _sapXepDauSachTheoTheLoai(lds, nodesSapXep);

    cout << left
         << setw(10) << "ISBN"
         << "| " << setw(15) << "The Loai"
         << "| " << setw(30) << "Ten Sach" << endl;

    // In dong ke ngang
    cout << setfill('-')
         << setw(10) << ""
         << "+-" << setw(15) << ""
         << "+-" << setw(30) << "" << endl;
    cout << setfill(' ');

    for (int i = 0; i < lds.n; i++) {
        cout << left
             << setw(10) << nodesSapXep[i]->ISBN 
             << "| " << setw(15) << nodesSapXep[i]->theLoai
             << "| " << setw(30) << nodesSapXep[i]->tenSach << endl;
    }
}

void timSach(ListDauSach &lds) {

}








