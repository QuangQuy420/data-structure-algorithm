#include <iostream>
#include <cstring>
#include <sstream>
#include <iomanip>
#include <string>
#include <algorithm>
#include "structs.h"
#include "dau_sach.h"
#include "helpers.h"
#include "globals.h"
#include "mylib.h"

using namespace std;

// ========== Xu Ly In Danh Sach Dau Sach ==========

void _inTieuDeLietKeDauSach(){
	cout << left
	     << setw(6) << "STT"
         << "| " << setw(6) << "ISBN"
         << "| " << setw(10) << "The Loai"
         << "| " << setw(20)  << "Ten Sach"
         << "| " << setw(20)  << "Tac Gia"
         << "| " << setw(5)  << "SoTr"
         << "| " << setw(5)  << "NXB"
		 << "| " << setw(5)  << "SLM"
		 << "| " << setw(5)  << "SLS" << endl;

    cout << setfill('-')
    	 << setw(6) << ""
         << "+-" << setw(6) << ""
         << "+-" << setw(10) << ""
         << "+-" << setw(20)  << ""
         << "+-" << setw(20)  << ""
         << "+-" << setw(5)  << ""
         << "+-" << setw(5)  << ""
         << "+-" << setw(5)  << ""
         << "+-" << setw(5) << "" << endl;
    cout << setfill(' ');
}

void _inTinhNangThaoTacDS() {
	cout << "-----------------------------------------------------------------" << endl;
	cout << left;
	cout << setw(40) << "F1: Them Dau Sach"
	     << setw(20) << "F4: Tim Sach" << endl;
	cout << setw(40) << "< Trai | Phai > : Chuyen Trang"
		 << setw(20) << "ESC: Thoat"<< endl;
}

void inKhungQuanLyDauSach() {
	gotoxy(15, 1);
	cout << "----------QUAN LI DANH SACH DAU SACH----------";

	gotoxy(0, 3);
	_inTieuDeLietKeDauSach(); // In dong tieu de

	gotoxy(0, 24);
	_inTinhNangThaoTacDS();    // In dong chuc nang
}

void _clearVungDanhSachDauSach() {
	for (int y = 5; y <= 5 + ITEM_MOI_TRANG; y++) {
		gotoxy(0, y);
		cout << string(100, ' ');  // Xoá 100 ky tu
	}
}

string layTheLoai(int theLoai) {
	switch (theLoai) {
		case 1: return "Khoa Hoc";
		case 2: return "Ky Nang";
		case 3: return "Lich Su";
		case 4: return "Truyen";
	}
}

void _inDauSachTheoTheLoai(ListDauSach &lds, int trang, int y) {
    string theLoai;

	for (int i = 0; i < lds.n; i++) {
		theLoai = layTheLoai(lds.nodes[i].theLoai);

		if(i >= (trang - 1)*ITEM_MOI_TRANG && i < trang*ITEM_MOI_TRANG) {
			gotoxy(0, y);
			y++;
			cout << left
		         << setw(6) << i + 1
		         << "| " << setw(6) << lds.nodes[i].ISBN
		         << "| " << setw(10) << theLoai
		         << "| " << setw(20)  << lds.nodes[i].tenSach
		         << "| " << setw(20)  << lds.nodes[i].tacGia
		         << "| " << setw(5)  << lds.nodes[i].soTrang
		         << "| " << setw(5)  << lds.nodes[i].namXuatBan
		         << "| " << setw(5)  << lds.nodes[i].soLuotMuon
		         << "| " << setw(5) << lds.nodes[i].soLuongSach << endl;
		}
	}
}

void xuLyInDanhSachDauSach(ListDauSach &lds, int trang, int soTrang) {
	_clearVungDanhSachDauSach();

	int y = 5; // Bat dau in tu dong thu 5
	
	_inDauSachTheoTheLoai(lds, trang, y);
	
	gotoxy(87, 21);
	cout << "Trang: " << trang << "/" << soTrang;
}

// ========== END Xu Ly In Danh Sach Dau Sach ==========


// ========== Xu Ly Nhap Danh Sach Dau Sach ==========
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

int _timViTriTheoTheLoaiVaTen(ListDauSach &lds, int theLoai, string ten) {
	if(isDauSachEmpty(lds)) return 0;

	for (int i = 0; i < lds.n; i++) {
		if ((lds.nodes[i].theLoai == theLoai && lds.nodes[i].tenSach >= ten) || lds.nodes[i].theLoai > theLoai) return i;
	}
	return lds.n;
}

void _insertAfterDS(ListDauSach &lds, DauSach ds) {
	int viTri = _timViTriTheoTheLoaiVaTen(lds, ds.theLoai, ds.tenSach);
	
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

void xuLyNhapDauSach(ListDauSach &lds) {
    if (isDauSachFull(lds)) {
        thongBao(0, "Danh Sach Day, Khong The Them!", 100, 24);
        Sleep(3000);
        clearTinhNang(100, 0);
        return;
    }
    
    int x = 110, y = 3, soLuongSach = -1;
    DauSach ds;
    Sach sach;

    gotoxy(x, y);
	cout<<"-----THEM DAU SACH-----";
	gotoxy(x, y + 2);
    cout<<"ISBN         :";
    gotoxy(x, y + 3);
    cout<<"The Loai     :   (1: Khoa Hoc, 2: Ky Nang,";
    gotoxy(x, y + 4);
    cout<<"                  3: Lich Su,  4: Truyen)";
    gotoxy(x, y + 5);
    cout<<"Ten Sach     :";
    gotoxy(x, y + 6);
    cout<<"Tac Gia      :";
    gotoxy(x, y + 7);
    cout<<"So Trang     :";
    gotoxy(x, y + 8);
    cout<<"Nam Xuat Ban :";
    gotoxy(x, y + 9);
    cout<<"So Luong Sach:";
    gotoxy(x, y + 10);
    cout<<"Vi Tri       :";
    
    if (!nhapISBN(lds, ds.ISBN, x, y + 2)) return;
    if (!nhapTheLoaiDS(ds.theLoai, x, y + 3)) return;
    if (!nhapTenSach(ds.tenSach, x, y + 5)) return;
    if (!nhapTenTacGia(ds.tacGia, x, y + 6)) return;
    if (!nhapSoTrang(ds.soTrang, x, y + 7)) return;
    if (!nhapNamXuatBan(ds.namXuatBan, x, y + 8)) return;
    if (!nhapSoLuongSach(soLuongSach, x, y + 9)) return;
    if (!nhapViTri(sach.viTri, x, y + 10)) return;
    
    ds.soLuotMuon = 0;
    ds.soLuongSach = 0;
    ds.ptrSach = NULL;
    sach.trangThai = 0;
    
    for (int i = 0; i < soLuongSach; i++) {
    	sach.maSach = _danhMaSachTuDong(ds);
    	insertLastSach(ds.ptrSach, sach);
	}
	
	_insertAfterDS(lds, ds);
	
	thongBao(1, "Them Dau Sach Thanh Cong!", 110, 24);
    Sleep(3000);
    clearTinhNang(110, 0);
}

// ========== END Xu Ly Nhap Danh Sach Dau Sach ==========


// ========== Xu Ly Tim Sach ==========

string _toLowerCase(string str) {
    transform(str.begin(), str.end(), str.begin(), ::tolower);
    return str;
}

void _timSachTheoTen(ListDauSach &lds, string ten, int arr[], int &count) {
    string tenTimKiemLower = _toLowerCase(ten);
    count = 0;
    for (int i = 0; i < lds.n; i++) {
        string tenSachLower = _toLowerCase(lds.nodes[i].tenSach);
        
        if (tenSachLower.find(tenTimKiemLower) != string::npos) { // Tim thay chuoi con trong ten sach
            arr[count++] = i;
        }
    }
}

void _inDanhSachTimThay(ListDauSach &lds, int arr[], int trang, int count, int y) {
	_clearVungDanhSachDauSach();
	
    for (int i = 0; i < count; i++) {
        string theLoai = layTheLoai(lds.nodes[arr[i]].theLoai);

        if (i >= (trang - 1) * ITEM_MOI_TRANG && i < trang * ITEM_MOI_TRANG) {
            gotoxy(0, y);
            y++;
            cout << left
                 << setw(6) << i + 1
                 << "| " << setw(6) << lds.nodes[arr[i]].ISBN
                 << "| " << setw(10) << theLoai
                 << "| " << setw(20) << lds.nodes[arr[i]].tenSach
                 << "| " << setw(20) << lds.nodes[arr[i]].tacGia
                 << "| " << setw(5) << lds.nodes[arr[i]].soTrang
                 << "| " << setw(5) << lds.nodes[arr[i]].namXuatBan
                 << "| " << setw(5) << lds.nodes[arr[i]].soLuotMuon
                 << "| " << setw(5) << lds.nodes[arr[i]].soLuongSach << endl;
        }
    }
    
    int soTrang = tinhSoTrang(count);
    
    gotoxy(87, 21);
    cout << string(15, ' ');
    gotoxy(87, 21);
	cout << "Trang: " << trang << "/" << soTrang;
}

void xuLyTimSach(ListDauSach &lds) {
	int x = 110, y = 3;
	string ten;
	int arr[MAXLIST];
    int count = 0;

    gotoxy(x, y);
	cout<<"-----TIM SACH-----";
    gotoxy(x, y + 2);
    cout<<"Ten Sach:";
    
    int trang = 1;
    int soTrang = tinhSoTrang(lds.n);

    while (true) {
    	int ketQua = nhapTenSachTimKiem(ten, trang, soTrang, x, y + 2);
        if (ketQua == 0) return;
        
        // De trong enter, in toan bo danh sach
        if (ketQua == -1) {
        	soTrang = tinhSoTrang(lds.n);
        	xuLyInDanhSachDauSach(lds, trang, soTrang);
		}

		if (ketQua == 1) {
			_timSachTheoTen(lds, ten, arr, count);
			soTrang = tinhSoTrang(count);
			_inDanhSachTimThay(lds, arr, trang, count, y + 2);
		}

        gotoxy(x + 10 + ten.length(), y + 2);
    }
}

// ========== END Xu Ly Tim Sach ==========

