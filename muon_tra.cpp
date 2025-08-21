#include <iostream>
#include <iomanip>
#include <sstream>
#include "structs.h"
#include "mylib.h"
#include "globals.h"
#include "helpers.h"
#include "doc_gia.h"
#include "dau_sach.h"

using namespace std;

void _inTinhNangThaoTacMT() {
	cout << left;
	cout << setw(20) << "F1: Muon Sach"
	     << setw(20) << "F2: Tra Sach"
	     << setw(20) << "ESC: Thoat"<< endl;
//	cout << setw(40) << "< Trai | Phai > : Chuyen Trang"
}

void inKhungQuanLyMuonTra() {
	gotoxy(15, 1);
	cout << "----------QUAN LI MUON TRA----------";

	gotoxy(80, 1);
	_inTinhNangThaoTacMT();    // In dong chuc nang
}

void _inThongTinDocGia(DocGia* dg, int x, int y) {
	// Thong tin doc gia
	string trangThaiThe = dg->trangThai == 1 ? "Hoat Dong" : "Da Bi Khoa";
	string phai = dg->phai == 0 ? "Nam" : "Nu";
	
	gotoxy(x, y +8);
	cout << left
	     << setw(6) << "STT"
         << "| " << setw(6) << "Ma The"
         << "| " << setw(30) << "Ho Va Ten"
         << "| " << setw(5)  << "Phai"
         << "| " << setw(10) << "Trang Thai" << endl;

    cout << setfill('-')
    	 << setw(6) << ""
         << "+-" << setw(6) << ""
         << "+-" << setw(30) << ""
         << "+-" << setw(5)  << ""
         << "+-" << setw(10) << "" << endl;
    cout << setfill(' ');
    
    gotoxy(x, y+10);
	cout << left
         << setw(6) << 1
         << "| " << setw(6) << dg->maThe
         << "| " << setw(30) << dg->ho +  " " + dg->ten
         << "| " << setw(5)  << phai
         << "| " << setw(10) << trangThaiThe << endl;
    
    
    // Thong tin sach dang muon
    gotoxy(x, y + 12);
    cout<<"DANH SACH DANG MUON";
    
    gotoxy(x, y+13);
    cout << left
	     << setw(6) << "STT"
         << "| " << setw(9) << "Ma Sach"
         << "| " << setw(10) << "Ngay Muon"
         << "| " << setw(10) << "Ngay Tra"
         << "| " << setw(15)  << "Vi Tri"
         << "| " << setw(10) << "Trang Thai" << endl;

    cout << setfill('-')
    	 << setw(6) << ""
         << "+-" << setw(9) << ""
         << "+-" << setw(10) << ""
         << "+-" << setw(10)  << ""
         << "+-" << setw(15)  << ""
         << "+-" << setw(10) << "" << endl;
    cout << setfill(' ');
    
    gotoxy(x, y+15);
    int index = 0;
    string ngayMuon, ngayTra, trangThaiMuon;
    PTRMT first = dg->ptrMT;
    while(first != NULL) {
    	ngayMuon = to_string(first->mt.ngayMuon.ngay) + "/" + to_string(first->mt.ngayMuon.thang) + "/" + to_string(first->mt.ngayMuon.nam);
		ngayTra = "-";

		switch (first->mt.trangThai) {
			case 0: {
				trangThaiMuon = "Dang Muon";
				break;
			}
			case 1: {
				trangThaiMuon = "Da Tra";
				ngayTra = to_string(first->mt.ngayTra.ngay) + "/" + to_string(first->mt.ngayTra.thang) + "/" + to_string(first->mt.ngayTra.nam);
				break;
			}
			case 2: {
				trangThaiMuon = "Mat Sach";
				break;
			}
		}

		cout << left
	         << setw(6) << ++index
	         << "| " << setw(9) << first->mt.maSach
	         << "| " << setw(10) << ngayMuon
	         << "| " << setw(10) << ngayTra
	         << "| " << setw(15)  << first->mt.viTri
	         << "| " << setw(10) << trangThaiMuon << endl;

		first = first->next;
	}
}

void _inThongTinSach(ListDauSach &lds, int index, int x, int y) {
	// In thong tin Sach
	gotoxy(x, y +8);
	cout << left
	     << setw(4) << "STT"
         << "| " << setw(6) << "ISBN"
         << "| " << setw(10) << "The Loai"
         << "| " << setw(20)  << "Ten Sach"
         << "| " << setw(20)  << "Tac Gia"
		 << "| " << setw(5)  << "SLS" << endl;
	
	gotoxy(x, y +9);
    cout << setfill('-')
    	 << setw(4) << ""
         << "+-" << setw(6) << ""
         << "+-" << setw(10) << ""
         << "+-" << setw(20)  << ""
         << "+-" << setw(20)  << ""
         << "+-" << setw(5) << "" << endl;
    cout << setfill(' ');
    
    string theLoai = layTheLoai(lds.nodes[index].theLoai);
    gotoxy(x, y +10);
    cout << left
         << setw(4) << 1
         << "| " << setw(6) << lds.nodes[index].ISBN
         << "| " << setw(10) << theLoai
         << "| " << setw(20)  << lds.nodes[index].tenSach
         << "| " << setw(20)  << lds.nodes[index].tacGia
         << "| " << setw(5) << lds.nodes[index].soLuongSach << endl;
         
    // In Danh Sach Con
    gotoxy(x, y + 12);
    cout<<"DANH SACH CON";
    
    gotoxy(x, y+13);
    cout << left
	     << setw(6) << "STT"
         << "| " << setw(10) << "Ma Sach"
         << "| " << setw(15) << "Trang Thai"
         << "| " << setw(15)  << "Vi Tri" << endl;

	gotoxy(x, y+14);
    cout << setfill('-')
    	 << setw(6) << ""
         << "+-" << setw(10) << ""
         << "+-" << setw(15) << ""
         << "+-" << setw(15) << "" << endl;
    cout << setfill(' ');
    
    
    PTRSach first;
    first = lds.nodes[index].ptrSach;
    int stt = 0;
    string trangThaiSach;
    while (first != NULL) {
    	switch (first->sach.trangThai) {
			case 0: {
				trangThaiSach = "Cho Muon Duoc";
				break;
			}
			case 1: {
				trangThaiSach = "Da Cho Muon";
				break;
			}
			case 2: {
				trangThaiSach = "Da Thanh Ly";
				break;
			}
		}
    	
    	gotoxy(x, y + 15 + stt);
    	cout << left
	         << setw(6) << ++stt
	         << "| " << setw(10) << first->sach.maSach
	         << "| " << setw(15) << trangThaiSach
	         << "| " << setw(15)  << first->sach.viTri << endl;
    	
    	first = first->next;
	}
}

int _soNgayTrongThang(int thang, int nam) {
    int ngayTrongThang[] = {0,31,28,31,30,31,30,31,31,30,31,30,31};
    if ((nam%400==0) || (nam%4==0 && nam%100!=0)) ngayTrongThang[2] = 29;
    return ngayTrongThang[thang];
}

int _chuyenNgayThanhSo(Date date) {
    int days = date.nam * 365 + date.ngay;
    for(int i=1; i<date.thang; i++) {
        days += _soNgayTrongThang(i, date.nam);
    }
    
    // Cong Them So Nam Nhuan
    days += (date.nam/4 - date.nam/100 + date.nam/400);
    return days;
}

Date _layNgayHeThong() {
    time_t now = time(0);
    tm *ltm = localtime(&now);

    Date date;
    date.ngay  = ltm->tm_mday;
    date.thang = 1 + ltm->tm_mon;
    date.nam   = 1900 + ltm->tm_year;
    return date;
}

// return 1: Co The Muon Sach
// return 0: So Luong Muon > 3 Cuon
// return -1: Muon Sach Qua 7 Ngay
// return -2: Khong cho muon cung 1 quyen sach
int _kiemTraDocGiaCoTheMuonSach(DocGia* dg, string ISBN = "") {
	PTRMT first = dg->ptrMT;
	int SLMuon = 0;
	string maDauSach;
	Date ngayHeThong = _layNgayHeThong();
	int ngayHTInt = _chuyenNgayThanhSo(ngayHeThong), ngayMuonInt;
	
	
	while (first != NULL) {
		// Chi kiem tra sach voi trang thai == 0 (Dang muon)
        if (first->mt.trangThai == 0) {
            maDauSach = first->mt.maSach.substr(0, first->mt.maSach.find('-'));
            if (maDauSach == ISBN) return -2;

            ngayMuonInt = _chuyenNgayThanhSo(first->mt.ngayMuon);
            if (ngayHTInt - ngayMuonInt > 7) return -1;

            SLMuon++;
        }
        first = first->next;
    }
	
	if (SLMuon >= 3) return 0;
	
	return 1;
}

Sach* _layThongTinSach(ListDauSach &lds, int index, string maSachCon, int traSach = 0) {
	PTRSach first = lds.nodes[index].ptrSach;

	while (first != NULL) {
		// Lay thong tin sach muon
		if(first->sach.maSach == maSachCon && first->sach.trangThai == 0) return &first->sach;
		
		// Lay thong tin sach tra
		if(traSach == 1 && first->sach.maSach == maSachCon && first->sach.trangThai == 1) return &first->sach;
		
		first = first->next;
	}
	
	return NULL;
}

void _thucHienMuonSach(DauSach &dauSach, DocGia* dg, Sach* sachMuon) {
	if(dg == NULL || sachMuon == NULL) return;
	
	Date date = _layNgayHeThong();
	
	PTRMT mtNew = new nodeMT;
	mtNew->mt.maSach = sachMuon->maSach;
	
	mtNew->mt.ngayMuon.ngay = date.ngay;
	mtNew->mt.ngayMuon.thang = date.thang;
	mtNew->mt.ngayMuon.nam = date.nam;
	
	mtNew->mt.ngayTra.ngay = 0;
	mtNew->mt.ngayTra.thang = 0;
	mtNew->mt.ngayTra.nam = 0;
	
	mtNew->mt.trangThai = 0;
	mtNew->mt.viTri = sachMuon->viTri;
	
	// Them vao dau danh sach
	mtNew->next = dg->ptrMT;
    dg->ptrMT = mtNew;
	
	sachMuon->trangThai = 1;
	dauSach.soLuotMuon++;
}

void xuLyMuonSach(ListDauSach &lds, PTRDG &root) {
	int x = 0, y = 3;
	int maDG = -1, tonTaiISBN = -1, DGCoTheMuonSach = -1, canMS, maSachMuon = -1;
	string ISBN;
	
	gotoxy(x, y);
	cout<<"CHUC NANG MUON SACH";
	gotoxy(x, y+2);
	cout<<"Ma Doc Gia:";
    gotoxy(x, y+3);
    cout<<"ISBN      :";
    gotoxy(x + 30, y+2);
    cout<<"Ma Sach:";
	
	DocGia* dg;
	do {
		if (!nhapMaDG(maDG, x, y+2)) return;
	
		dg = timDocGiaTheoMa(root, maDG);
		
		if (!dg) {
			thongBao(0, "Khong tim thay Doc Gia!", 0, 35);
		} else {
			canMS = _kiemTraDocGiaCoTheMuonSach(dg);
		
			if (dg && canMS == 0) thongBao(0, "Doc Gia Da Muon Toi Da 3 Sach!", 0, 35);
			if (dg && canMS == -1) thongBao(0, "Doc Gia Da Muon Sach Qua 7 Ngay!", 0, 35);
		}
	} while (!dg || canMS != 1);
	
	clearBaoLoi(0, 35);
	_inThongTinDocGia(dg, x, y);
	
	do {
		DGCoTheMuonSach = -1;
		if (!nhapISBNMuonSach(ISBN, x, y+3)) return;
	
		tonTaiISBN = kiemTraTonTaiISBN(lds, ISBN);
		canMS = _kiemTraDocGiaCoTheMuonSach(dg, ISBN);
		
		if (tonTaiISBN == -1) thongBao(0, "Khong tim thay Sach!", 0, 35);
		if (tonTaiISBN > -1 && canMS == -2) thongBao(0, "Khong The Muon 2 Sach Giong Nhau!", 0, 35);
	} while (tonTaiISBN == -1 || canMS == -2);
	
		
	clearBaoLoi(0, 35);
	_inThongTinSach(lds, tonTaiISBN, x+80, y);
	
	Sach* sachMuon;
	do {
		if (!nhapMaSachCon(maSachMuon, x+39, y+2)) return;
		
		// Chuyen ma nhap vao sang ma sach: 1 -> ABCD-001
		ostringstream oss;
	    oss << lds.nodes[tonTaiISBN].ISBN << "-" << setw(3) << setfill('0') << maSachMuon;
	    string maSach = oss.str();
		
		sachMuon = _layThongTinSach(lds, tonTaiISBN, maSach);
		
		if (!sachMuon) thongBao(0, "Sach Da Cho Muon/Thanh Ly/Ko ton tai!", 0, 35);
	} while (!sachMuon);
	
	string xacNhan;
	do {
		gotoxy(0, 32);
		cout<<"Xac Nhan Muon(Y/N): "<<endl;
	    if (!nhapXacNhanMT(xacNhan, x, 32)) return;
	    if (xacNhan =="N") {
	    	thongBao(2, "Xac Nhan Huy Muon Sach!", 0, 35);
	    	Sleep(3000);
	    	clearTinhNang(0, 2, 38, 200);
	    	return;
		}
	} while (xacNhan != "Y" && xacNhan != "N");
	
	if (xacNhan == "Y") {
		_thucHienMuonSach(lds.nodes[tonTaiISBN], dg, sachMuon);
		
		thongBao(1, "Doc Gia Muon Sach Thanh Cong!", 0, 35);
		
		Sleep(3000);
	    clearTinhNang(0, 2, 38, 200);
	    return;
	}
}

// ====================== Tra sach ======================

// return 1: Ton tai sach co the tra.
// return -1: Khong ton tai Sach.
// return -2: Khong ton tai sach con trong Dau Sach.
// return -3: Sach ko ton tai or ko co trang thai dang muon trong Doc Gia.
int _kiemTraTonTaiSach(ListDauSach &lds, DocGia* dg, string maSachTra, Sach* &sachTra) {
	PTRMT first = dg->ptrMT;
	
	while (first != NULL) {
		if(first->mt.maSach == maSachTra && first->mt.trangThai == 0) break;
		
		first = first->next;
	}
	
	if(first == NULL) return -3;
	
	string maDauSach = maSachTra.substr(0, maSachTra.find('-'));
		
	int tonTaiISBN = kiemTraTonTaiISBN(lds, maDauSach);
	if (tonTaiISBN == -1) return tonTaiISBN;
	
	sachTra = _layThongTinSach(lds, tonTaiISBN, maSachTra, 1);
	
	if (!sachTra) return -2;
	
	return 1;
}

void _thucHienTraSach(DocGia* dg, Sach* sachTra) {
	if(dg == NULL || sachTra == NULL) return;
	
	Date date = _layNgayHeThong();
	
	PTRMT first = dg->ptrMT;
	
	while (first != NULL) {
		if(first->mt.maSach == sachTra->maSach && first->mt.trangThai == 0) break;
		
		first = first->next;
	}
	
	first->mt.ngayTra.ngay = date.ngay;
	first->mt.ngayTra.thang = date.thang;
	first->mt.ngayTra.nam = date.nam;
	first->mt.trangThai = 1;
	
	sachTra->trangThai = 0;
}

void xuLyTraSach(ListDauSach &lds, PTRDG &root) {
	int x = 0, y = 3;
	int maDG = -1, tonTaiSach = -1;
	string maSachTra;
	
	gotoxy(x, y);
	cout<<"CHUC NANG TRA SACH";
	gotoxy(x, y+2);
	cout<<"Ma Doc Gia:";
    gotoxy(x, y+3);
    cout<<"Ma Sach:";
    
    DocGia* dg;
	do {
		if (!nhapMaDG(maDG, x, y+2)) return;
	
		dg = timDocGiaTheoMa(root, maDG);
				
		if (!dg) thongBao(0, "Khong tim thay Doc Gia!", 0, 35);
	} while (!dg);
	_inThongTinDocGia(dg, x, y);
	
	clearBaoLoi(0, 35);
	
	Sach* sachTra;
	do {
		if (!nhapMaSachTra(maSachTra, x, y+3)) return;

		tonTaiSach = _kiemTraTonTaiSach(lds, dg, maSachTra, sachTra);

		if (tonTaiSach == -1) thongBao(0, "Khong tim thay Sach!", 0, 35);
		if (tonTaiSach == -2) thongBao(0, "Khong tim thay Sach con trong Dau Sach!", 0, 35);
		if (tonTaiSach == -3) thongBao(0, "Doc Gia da tra/ khong muon sach nay!", 0, 35);
	} while (tonTaiSach != 1);
	
	clearBaoLoi(0, 35);
	
	string xacNhan;
	do {
		gotoxy(0, 32);
		cout<<"Xac Nhan Tra (Y/N): "<<endl;
	    if (!nhapXacNhanMT(xacNhan, x, 32)) return;
	    if (xacNhan =="N") {
	    	thongBao(2, "Xac Nhan Huy Tra Sach!", 0, 35);
	    	Sleep(3000);
	    	clearTinhNang(0, 2, 38, 200);
	    	return;
		}
	} while (xacNhan != "Y" && xacNhan != "N");
	
	if (xacNhan == "Y") {
		_thucHienTraSach(dg, sachTra);
		
		thongBao(1, "Doc Gia Tra Sach Thanh Cong!", 0, 35);
		
		Sleep(3000);
	    clearTinhNang(0, 2, 38, 200);
	    return;
	}
}

int tinhSoNgayQuaHanMax(PTRMT first) {
    Date ngayHeThong = _layNgayHeThong();
    int ngayHTInt = _chuyenNgayThanhSo(ngayHeThong);
    int maxQuaHan = 0;

    while (first != NULL) {
        if (first->mt.trangThai == 0) {  
            int ngayMuonInt = _chuyenNgayThanhSo(first->mt.ngayMuon);
            int soNgayMuon = ngayHTInt - ngayMuonInt;
            int soNgayQuaHan = (soNgayMuon > 7) ? (soNgayMuon - 7) : 0;

            if (soNgayQuaHan > maxQuaHan) {
                maxQuaHan = soNgayQuaHan;
            }
        }
        first = first->next;
    }
    return maxQuaHan;
}


