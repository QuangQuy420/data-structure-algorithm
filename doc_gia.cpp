#include <iostream>
#include <cstring>
#include <sstream>
#include <iomanip>
#include "structs.h"
#include "doc_gia.h"
#include "helpers.h"
#include "doc_ghi_file.h"

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

void inTieuDeLietKeDocGia() {
	cout << left
         << setw(10) << "Ma The"
         << "| " << setw(15) << "Ho"
         << "| " << setw(10) << "Ten"
         << "| " << setw(5)  << "Phai"
         << "| " << setw(10) << "Trang Thai" << endl;

    cout << setfill('-')
         << setw(10) << ""
         << "+-" << setw(15) << ""
         << "+-" << setw(10) << ""
         << "+-" << setw(5)  << ""
         << "+-" << setw(10) << "" << endl;
    cout << setfill(' ');
}

void xuLyInDocGiaTheoMa(PTRDG root) {
	if(root != NULL) {
		xuLyInDocGiaTheoMa(root->left);

	    cout << left
	         << setw(10) << root->dg.maThe
	         << "| " << setw(15) << root->dg.ho
	         << "| " << setw(10) << root->dg.ten
	         << "| " << setw(5)  << root->dg.phai
	         << "| " << setw(10) << root->dg.trangThai << endl;
	
	    xuLyInDocGiaTheoMa(root->right);
	}
}

void xuLyNhapDocGia(PTRDG &root) {
	DocGia dg;
	
	dg.maThe = layMaTheTuFile();
	if (dg.maThe == -1) {
        cout << "Khong the lay ma the!"<< endl;
        thongBaoHuyThaoTac("Them Doc Gia");
        return;
    }
	
    cout << "Nhap ho doc gia (toi da 10 ki tu): ";
    if (!nhapChuoi(dg.ho, 10)) {
        thongBaoHuyThaoTac("Them Doc Gia");
        return;
    }

    cout << "Nhap ten doc gia (toi da 10 ki tu): ";
    if (!nhapChuoi(dg.ten, 10)) {
        thongBaoHuyThaoTac("Them Doc Gia");
        return;
    }

    cout << "Nhap phai doc gia: ";
    if (!chonPhai(dg.phai)) {
        thongBaoHuyThaoTac("Them Doc Gia");
        return;
    }
    
    dg.trangThai = 0;
    dg.ptrMT = NULL;

    insertDG(root, dg);
    saveMaTheFile();

    cout << "\nThem doc gia thanh cong!" << endl;
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
	         << setw(10) << nodeSapXep[i]->maThe
	         << "| " << setw(15) << nodeSapXep[i]->ho
	         << "| " << setw(10) << nodeSapXep[i]->ten
	         << "| " << setw(5)  << nodeSapXep[i]->phai
	         << "| " << setw(10) << nodeSapXep[i]->trangThai << endl;
	}
}


