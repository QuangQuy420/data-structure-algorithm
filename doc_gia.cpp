#include <iostream>
#include <cstring>
#include <sstream>
#include <iomanip>
#include "structs.h"
#include "doc_gia.h"
#include "helpers.h"
#include "doc_ghi_file.h"
#include "mylib.h"
#include "globals.h"

using namespace std;


void insertLastMT(PTRMT &first, MuonTra mt) {
	PTRMT newMT = new nodeMT;
	newMT->mt = mt;
	newMT->next = NULL;
	
	if(first == NULL) {
		first = newMT;
	}
	else {
		PTRMT p = first;
		while(p->next != NULL)
			p = p->next;
			
		p->next = newMT;
	}
}


void insertDG(PTRDG &root, DocGia dg) {
	// Insert vao nut la
    if (root == NULL) {
        root = new nodeDG;
        root->dg = dg;
        root->left = root->right = NULL;
    } else if (dg.maThe < root->dg.maThe) {
        insertDG(root->left, dg);
    } else {
        insertDG(root->right, dg);
    }
}

void xuLyNhapDocGia(PTRDG &root, int listMaThe[], int &soLuongMaThe) {
	DocGia dg;
	int x = 80, y = 3;
	gotoxy(x, y);
	cout<<"-----THEM DOC GIA-----"<<endl;
	
	dg.maThe = layMaThe(listMaThe, soLuongMaThe);
	if (dg.maThe == -1) {
        thongBao(0, "Khong the lay ma the!", 80, 24);
        Sleep(3000);
        clearTinhNang(80, 0);
        return;
    }
    
    gotoxy(80, 5);
    cout<<"Ho  :"<<endl;
    gotoxy(80, 6);
    cout<<"Ten :"<<endl;
    gotoxy(80, 7);
    cout<<"Phai:		(0: Nam, 1: Nu)"<<endl;

    if (!nhapHoDocGia(dg.ho)) return;
    if (!nhapTenDocGia(dg.ten)) return;
    if (!nhapPhaiDocGia(dg.phai)) return;
    
    dg.trangThai = 1;
    dg.ptrMT = NULL;

    insertDG(root, dg);

    thongBao(1, "Them Doc Gia Thanh Cong!", 80, 24);
    Sleep(3000);
    clearTinhNang(80, 0);
}

int DemDocGia(PTRDG root) {
    if (root == NULL) return 0;
    return 1 + DemDocGia(root->left) + DemDocGia(root->right);
}

void _saveDocGiaVaoMang(DocGia* nodeSapXep[], PTRDG root, int &index) {
	if(root != NULL) {
		_saveDocGiaVaoMang(nodeSapXep, root->left, index);
		nodeSapXep[index++] = &root->dg;
		_saveDocGiaVaoMang(nodeSapXep, root->right, index);
	}
}

int _soSanhDocGiaTheoTen(DocGia* a, DocGia* b) {
	string tenA = a->ten + a->ho;
	string tenB = b->ten + b->ho;
	
	return tenA < tenB;
}

void _sapXepDocGiaTheoTen(DocGia* nodeSapXep[], int n) {
	DocGia* min;
	int i, j, viTriMin;

	for(i = 0; i < n-1; i++){
		min = nodeSapXep[i];
		viTriMin=i;

	    for (j = i+1; j < n; j++) {
	    	if (_soSanhDocGiaTheoTen(nodeSapXep[j], min)) {
		    	min = nodeSapXep[j];
				viTriMin=j;
	        }	
		}

		nodeSapXep[viTriMin] = nodeSapXep[i];
		nodeSapXep[i] = min;
	}
}

void xuLyInDocGiaTheoTen(PTRDG root) {
	int soLuongDG = DemDocGia(root);
	if (soLuongDG == 0) return;

	DocGia* nodeSapXep[soLuongDG];
	
	int index = 0;
	_saveDocGiaVaoMang(nodeSapXep, root, index);
	
	_sapXepDocGiaTheoTen(nodeSapXep, soLuongDG);
	
	for(int i = 0; i < soLuongDG; i++){
		cout << left
			 << setw(8) << i + 1
	         << "| " << setw(10) << nodeSapXep[i]->maThe
	         << "| " << setw(15) << nodeSapXep[i]->ho
	         << "| " << setw(10) << nodeSapXep[i]->ten
	         << "| " << setw(5)  << nodeSapXep[i]->phai
	         << "| " << setw(10) << nodeSapXep[i]->trangThai << endl;
	}
}

int tinhSoTrang(PTRDG root) {
	if(root == NULL) return 0;

	int soDocGia = DemDocGia(root);
	return (soDocGia + ITEM_MOI_TRANG - 1) / ITEM_MOI_TRANG;
}

void _inTinhNangThaoTac() {
	cout << "-----------------------------------------------------------------------" << endl;
	cout << left;
	cout << setw(20) << "F1: Them Doc Gia"
	     << setw(20) << "F2: Cap Nhat"
	     << setw(20) << "F3: Xoa Doc Gia" << endl;
	cout << setw(20) << "F4: Tim Kiem"
	     << setw(20) << "F5: Muon Sach"
	     << setw(20) << "F6: Tra Sach" << endl;
	cout << setw(40) << "< Trai | Phai > : Chuyen Trang"
		 << setw(20) << "ESC: Thoat"<< endl;
}

void _inTieuDeLietKeDocGia() {
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
}

void _inDocGiaTheoMa(PTRDG root, int &index, int trang, int &y) {
	if(root != NULL) {
		_inDocGiaTheoMa(root->left, index, trang, y);

		if(index > (trang - 1)*ITEM_MOI_TRANG && index <= trang*ITEM_MOI_TRANG) {
			gotoxy(0, y++);
			string trangThaiThe = root->dg.trangThai == 1 ? "Hoat Dong" : "Da Bi Khoa";
			string phai = root->dg.phai == 0 ? "Nam" : "Nu";
			cout << left
	         << setw(6) << index
	         << "| " << setw(6) << root->dg.maThe
	         << "| " << setw(30) << root->dg.ho +  " " + root->dg.ten
	         << "| " << setw(5)  << phai
	         << "| " << setw(10) << trangThaiThe << endl;
		}
		index++;
	
	    _inDocGiaTheoMa(root->right, index, trang, y);
	}
}

void inKhungQuanLyDocGia() {
	gotoxy(15, 1);
	cout << "----------QUAN LI THE DOC GIA----------";

	gotoxy(0, 3);
	_inTieuDeLietKeDocGia(); // In dong tieu de

	gotoxy(0, 24);
	_inTinhNangThaoTac();    // In dong chuc nang
}

void _clearVungDanhSachDocGia() {
	for (int y = 5; y <= 5 + ITEM_MOI_TRANG; y++) {
		gotoxy(0, y);
		cout << string(80, ' ');  // Xoá 80 ky tu
	}
}

void xuLyInDanhSachDocGia(PTRDG root, int trang, int soTrang) {
	_clearVungDanhSachDocGia();
	
	int index = 1;
	int y = 5; // Bat dau in tu dong thu 5
	
	_inDocGiaTheoMa(root, index, trang, y);
	
	gotoxy(55, 21);
	cout << "Trang: " << trang << "/" << soTrang;
}

// Cap nhat doc gia
void xuLyCapNhatDocGia(PTRDG &root) {
//	DocGia dg;
	int x = 80, y = 3;
	int maDG;
	gotoxy(x, y);
	cout<<"-----CAP NHAT DOC GIA-----"<<endl;
    
    gotoxy(80, 5);
    cout<<"Ma  :"<<endl;
    
    if (!nhapMaDocGia(maDG)) return;
    
//    timDocGiaTheoMa(root, maDG);
    
//    updateDocGia();
//    gotoxy(80, 6);
//    cout<<"Ten :"<<endl;
//    gotoxy(80, 7);
//    cout<<"Phai:		(0: Nam, 1: Nu)"<<endl;

//    if (!nhapHoDocGia(dg.ho)) return;
//    if (!nhapTenDocGia(dg.ten)) return;
//    if (!nhapPhaiDocGia(dg.phai)) return;
    
//    dg.trangThai = 1;
//    dg.ptrMT = NULL;
//
//    insertDG(root, dg);

    thongBao(1, "Cap Nhat Doc Gia Thanh Cong!", 80, 24);
    Sleep(3000);
    clearTinhNang(80, 0);
}

