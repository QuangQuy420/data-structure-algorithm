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

void inTieuDeDocGiaTheoMa() {
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

void inDocGiaTheoMa(PTRDG root) {
	if(root != NULL) {
		inDocGiaTheoMa(root->left);

	    cout << left
	         << setw(10) << root->dg.maThe
	         << "| " << setw(15) << root->dg.ho
	         << "| " << setw(10) << root->dg.ten
	         << "| " << setw(5)  << root->dg.phai
	         << "| " << setw(10) << root->dg.trangThai << endl;
	
	    inDocGiaTheoMa(root->right);
	}
}

void nhapDocGia(PTRDG &root) {
	DocGia dg;
	
	dg.maThe = layMaTheTuFile();
	if (dg.maThe == -1) {
        cout << "Khong the lay ma the! Huy thao tac nhap doc gia." << endl;
        return;
    }
	
	cout << "Nhap ho doc gia (toi da 10 ki tu): ";
    nhapChuoi(dg.ho, 10);
    
    cout << "Nhap ten doc gia (toi da 10 ki tu): ";
    nhapChuoi(dg.ten, 10);
    
    cout << "Nhap phai doc gia (toi da 10 ki tu): ";
    chonPhai(dg.phai);
    
    dg.trangThai = 0;
    dg.ptrMT = NULL;
    
    insertDG(root, dg);
    saveMaTheFile();
    
    cout << "Them doc gia thanh cong!" << endl;
}


