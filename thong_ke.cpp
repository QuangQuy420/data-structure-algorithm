#include <iostream>
#include <conio.h>
#include <iomanip>
#include "structs.h"
#include "mylib.h"
#include "globals.h"
#include "helpers.h"
#include "doc_gia.h"
#include "muon_tra.h"
#include "dau_sach.h"

void _inTinhNangThaoTacTK() {
	cout << left;
	cout << setw(35) << "F1: Liet Ke Doc Gia Qua Han"
	     << setw(35) << "F2: Liet Ke 10 Sach Pho Bien"
	     << setw(20) << "ESC: Thoat"<< endl;
}

void inKhungThongKe() {
	gotoxy(15, 1);
	cout << "----------THONG KE THU VIEN----------";

	gotoxy(60, 1);
	_inTinhNangThaoTacTK();    // In dong chuc nang
}

// Liet ke doc gia qua han theo thu tu thoi gian giam dan.
void _inTieuDeLietKeDocGiaQuaHan() {
	gotoxy(0, 3);
	cout << "DANH SACH DOC GIA MUON SACH QUA HAN" <<endl;
	gotoxy(0, 5);
	cout << left
	     << setw(6) << "STT"
         << "| " << setw(6) << "Ma The"
         << "| " << setw(30) << "Ho Va Ten"
         << "| " << setw(5)  << "Phai"
         << "| " << setw(10) << "Trang Thai"
         << "| " << setw(15) << "So Ngay Qua Han" << endl;

    cout << setfill('-')
    	 << setw(6) << "" 
         << "+-" << setw(6) << ""
         << "+-" << setw(30) << ""
         << "+-" << setw(5)  << ""
         << "+-" << setw(10) << ""
         << "+-" << setw(15) << "" << endl;
    cout << setfill(' ');
}

void _saveDocGiaVaoMangQuaHan(DGQuaHan* dgqh[], PTRDG root, int &index) {
	if (root != NULL) {
        _saveDocGiaVaoMangQuaHan(dgqh, root->left, index);

		dgqh[index] = new DGQuaHan;
        dgqh[index]->dg = &root->dg;
        dgqh[index]->soNgayQuaHan = tinhSoNgayQuaHanMax(root->dg.ptrMT);

        index++;
        _saveDocGiaVaoMangQuaHan(dgqh, root->right, index);
    }
}

void _sapXepDocGiaQuaHan(DGQuaHan* dgqh[], int n) {
	DGQuaHan* DGQHMax;
	int i, j, viTriMax;
	
	for (i = 0; i < n - 1; i++) {
		DGQHMax = dgqh[i];
		viTriMax = i;
		
        for (j = i + 1; j < n; j++) {
            if (DGQHMax->soNgayQuaHan < dgqh[j]->soNgayQuaHan) {
            	DGQHMax = dgqh[j];
                viTriMax = j;
            }
        }
        
        dgqh[viTriMax] = dgqh[i];
        dgqh[i] = DGQHMax;
    }
}

void _inDanhSachDocGiaQuaHan(PTRDG root) {
	int soLuongDG = demDocGia(root);
	if (soLuongDG == 0) return;

	DGQuaHan* dgqh[soLuongDG];
	
	string trangThaiThe, phai;
	int index = 0;
	_saveDocGiaVaoMangQuaHan(dgqh, root, index);
	
	_sapXepDocGiaQuaHan(dgqh, soLuongDG);
	
	// In Danh Sach
	int soTrang = tinhSoTrang(soLuongDG);
    int trang = 1, x = 0, y;
    char key;
	do {
		int viTriBatDauLoop = (trang - 1) * ITEM_MOI_TRANG;
        int viTriKetThucLoop = min(viTriBatDauLoop + ITEM_MOI_TRANG, soLuongDG);
        clearTinhNang(0, 7, 15, 90);
        y = 7;

        for (int i = viTriBatDauLoop; i < viTriKetThucLoop; i++) {
            string trangThaiThe = dgqh[i]->dg->trangThai == 1 ? "Hoat Dong" : "Da Bi Khoa";
            string phai = dgqh[i]->dg->phai == 0 ? "Nam" : "Nu";

            gotoxy(x, y++);
            cout << left
                 << setw(6) << i + 1
                 << "| " << setw(6) << dgqh[i]->dg->maThe
                 << "| " << setw(30) << dgqh[i]->dg->ho + " " + dgqh[i]->dg->ten
                 << "| " << setw(5) << phai
                 << "| " << setw(10) << trangThaiThe
                 << "| " << setw(15) << dgqh[i]->soNgayQuaHan << endl;
        }

        gotoxy(72, 25);
        cout << "Trang: " << trang << "/" << soTrang;
        gotoxy(0, 26);
        cout << "ESC: Thoat Chuc Nang";

        key = getch();

        if ((key == KEY_RIGHT) && trang < soTrang) {
            trang++;
        }
        if ((key == KEY_LEFT) && trang > 1) {
            trang--;
        }
        if (key == KEY_ESC) clearTinhNang(0, 3, 26, 90);

    } while (key != KEY_ESC);

	for (int i = 0; i < soLuongDG; i++) {
	        delete dgqh[i];
	    }
}

void xuLyLietKeDocGiaQuaHan(PTRDG &root) {
	_inTieuDeLietKeDocGiaQuaHan();

	_inDanhSachDocGiaQuaHan(root);
}

// In 10 sach co so luot muon nhieu nhat.
void _inTieuDeSachPhoBien() {
	gotoxy(0, 3);
	cout << "TOP 10 SACH CO LUOT MUON NHIEU NHAT" <<endl;
	gotoxy(0, 5);
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

void _saveSachVaoDauSach(ListDauSach lds, DauSach* ds[]) {
	for(int i = 0; i < lds.n; i++) {
		ds[i] = &lds.nodes[i];
	}
}

void _sapXepSachTheoLuotMuon(DauSach* ds[], int n) {
	DauSach* dsMax;
	int i, j, viTriMax;
	
	for(i = 0; i < n - 1; i++) {
		dsMax = ds[i];
		viTriMax = i;
		
		for (j = i+1; j < n; j++) {
			if (ds[j]->soLuotMuon > dsMax->soLuotMuon) {
				dsMax = ds[j];
				viTriMax = j;
			}
		}
		
		ds[viTriMax] = ds[i];
		ds[i] = dsMax;
	}
}

void _inTop10SachMuonNhieuNhat(ListDauSach lds) {
	DauSach* ds[lds.n];
	
	_saveSachVaoDauSach(lds, ds);
	
	_sapXepSachTheoLuotMuon(ds, lds.n);
	
	int x = 0, y;
    char key;
	do {
		y = 7;
        clearTinhNang(0, 7, 15, 100);
		string theLoai;
        for (int i = 0; i < 10; i++) {
        	theLoai = layTheLoai(ds[i]->theLoai);
            gotoxy(0, y++);
	        cout << left
	             << setw(6) << i+1
	             << "| " << setw(6) << ds[i]->ISBN
	             << "| " << setw(10) << theLoai
	             << "| " << setw(20) << ds[i]->tenSach
	             << "| " << setw(20) << ds[i]->tacGia
	             << "| " << setw(5)  << ds[i]->soTrang
	             << "| " << setw(5)  << ds[i]->namXuatBan
	             << "| " << setw(5)  << ds[i]->soLuotMuon
	             << "| " << setw(5)  << ds[i]->soLuongSach
	             << endl;
        }
        gotoxy(0, 26);
        cout << "ESC: Thoat Chuc Nang";

        key = getch();

        if (key == KEY_ESC) clearTinhNang(0, 3, 26, 100);

    } while (key != KEY_ESC);
}

void xuLyLietKeSachPhoBien(ListDauSach &lds) {
	_inTieuDeSachPhoBien();
	
	_inTop10SachMuonNhieuNhat(lds);
}
