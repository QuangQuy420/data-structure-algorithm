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


int _demDocGia(PTRDG root) {
    if (root == NULL) return 0;
    return 1 + _demDocGia(root->left) + _demDocGia(root->right);
}

void _loiDanhSachRong() {
	thongBao(0, "Danh Sach Doc Gia Rong!!!", 80, 24);
	Sleep(3000);
    clearTinhNang(80, 0);
}

void _clearVungDanhSachDocGia() {
	for (int y = 5; y <= 5 + ITEM_MOI_TRANG; y++) {
		gotoxy(0, y);
		cout << string(80, ' ');  // Xoá 80 ky tu
	}
}

// ========== Them doc gia ==========
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
    
    gotoxy(x, y + 2);
    cout<<"Ho  :"<<endl;
    gotoxy(x, y + 3);
    cout<<"Ten :"<<endl;
    gotoxy(x, y + 4);
    cout<<"Phai:		(0: Nam, 1: Nu)"<<endl;

    if (!nhapHoDocGia(dg.ho, x, y + 2)) return;
    if (!nhapTenDocGia(dg.ten, x, y + 3)) return;
    if (!nhapPhaiDocGia(dg.phai, x, y + 4)) return;
    
    dg.trangThai = 1;
    dg.ptrMT = NULL;

    insertDG(root, dg);

    thongBao(1, "Them Doc Gia Thanh Cong!", 80, 24);
    Sleep(3000);
    clearTinhNang(80, 0);
}
// ========== END Them doc gia ==========

// ========== In doc gia theo ten ==========
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

void _inDocGiaTheoTen(PTRDG root, int trang, int y) {
	int soLuongDG = _demDocGia(root);
	if (soLuongDG == 0) return;

	DocGia* nodeSapXep[soLuongDG];
	
	string trangThaiThe, phai;
	int index = 0;
	_saveDocGiaVaoMang(nodeSapXep, root, index);
	
	_sapXepDocGiaTheoTen(nodeSapXep, soLuongDG);
	
	for(int i = 0; i < soLuongDG; i++){
		trangThaiThe = nodeSapXep[i]->trangThai == 1 ? "Hoat Dong" : "Da Bi Khoa";
		phai = nodeSapXep[i]->phai == 0 ? "Nam" : "Nu";

		if(i >= (trang - 1)*ITEM_MOI_TRANG && i < trang*ITEM_MOI_TRANG) {
			gotoxy(0, y++);
			cout << left
				 << setw(6) << i + 1
		         << "| " << setw(6) << nodeSapXep[i]->maThe
		         << "| " << setw(30) << nodeSapXep[i]->ho +  " " + nodeSapXep[i]->ten
		         << "| " << setw(5)  << phai
		         << "| " << setw(10) << trangThaiThe << endl;
		}
	}
}

void _xuLyInDanhSachDocGiaTheoTen(PTRDG root, int trang, int soTrang) {
	_clearVungDanhSachDocGia();
	
	int y = 5; // Bat dau in tu dong thu 5
	
	_inDocGiaTheoTen(root, trang, y);
	
	gotoxy(55, 21);
	cout << "Trang: " << trang << "/" << soTrang;
}
// ========== END In doc gia theo ten ==========

int tinhSoTrang(PTRDG root) {
	if(root == NULL) return 0;

	int soDocGia = _demDocGia(root);

	return soDocGia/ITEM_MOI_TRANG + 1;
}

void _inTinhNangThaoTac() {
	cout << "-----------------------------------------------------------------" << endl;
	cout << left;
	cout << setw(20) << "F1: Them Doc Gia"
	     << setw(20) << "F2: Cap Nhat"
	     << setw(20) << "F3: Xoa Doc Gia" << endl;
	cout << setw(20) << "F4: In DG Theo Ten"
	     << setw(20) << "F5: In DG Theo Ma"
	     << setw(20) << "F6: Muon Sach" << endl;
	cout << setw(20) << "F7: Tra Sach" <<endl;
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

void _xuLyInDanhSachDocGiaTheoMa(PTRDG root, int trang, int soTrang) {
	_clearVungDanhSachDocGia();
	
	int index = 1;
	int y = 5; // Bat dau in tu dong thu 5
	
	_inDocGiaTheoMa(root, index, trang, y);
	
	gotoxy(55, 21);
	cout << "Trang: " << trang << "/" << soTrang;
}

// ========== Cap nhat doc gia ==========
DocGia* _timDocGiaTheoMa(PTRDG root, int maDG) {
    if (root == NULL) return NULL;

    if (root->dg.maThe == maDG) {
        return &(root->dg);  // Tra ve dia chi
    }

    if (maDG < root->dg.maThe) {
        return _timDocGiaTheoMa(root->left, maDG);
    } else {
        return _timDocGiaTheoMa(root->right, maDG);
    }
}

void xuLyCapNhatDocGia(PTRDG &root) {
	int x = 80, y = 3;
	int maDG;
	gotoxy(x, y);
	cout<<"-----CAP NHAT DOC GIA-----"<<endl;
	
	if(root == NULL) {
		_loiDanhSachRong();
	    return;
	}
    
    gotoxy(x, y+2);
    cout<<"Ma  :"<<endl;
    
    if (!nhapMaDocGia(maDG, x, y+2)) return;
    
    DocGia* dg = _timDocGiaTheoMa(root, maDG);
    
    if (dg != NULL) {
    	gotoxy(x, y+4);
	    cout<<"Ho  : "<< dg->ho <<endl;
	    gotoxy(x, y+5);
	    cout<<"Ten : "<< dg->ten <<endl;
	    gotoxy(x, y+6);
	    cout<<"Phai: " << dg->phai << "		(0: Nam, 1: Nu)" <<endl;
	    
		
	    if (!nhapHoDocGia(dg->ho, x, y+4)) return;
    	if (!nhapTenDocGia(dg->ten, x, y+5)) return;
    	if (!nhapPhaiDocGia(dg->phai, x, y+6)) return;
    	
    	thongBao(1, "Cap Nhat Doc Gia Thanh Cong!!!", x, 24);
	} else {
	    thongBao(0, "Khong tim thay Doc Gia!!!", x, 24);
	}
	
	Sleep(3000);
    clearTinhNang(x, 0);
    return;
}
// ========== END Cap nhat doc gia ==========

// ========== Xoa doc gia ==========
PTRDG _timMinCayPhai(PTRDG node) {
    while (node && node->left != NULL) {
        node = node->left;
    }
    return node;
}

void _xoaDocGia(PTRDG &root, int maThe) {
	if (root == NULL) return;

    if (maThe < root->dg.maThe) {
        _xoaDocGia(root->left, maThe);
    } else if (maThe > root->dg.maThe) {
        _xoaDocGia(root->right, maThe);
    } else {
		// Truong hop nut can xoa chi co 1 con or la nut la
        if (root->left == NULL) {
            PTRDG temp = root;
            root = root->right;
            delete temp;
        }
        else if (root->right == NULL) {
            PTRDG temp = root;
            root = root->left;
            delete temp;
        }
        else {
 			// Truong hop co 2 con
            PTRDG minNode = _timMinCayPhai(root->right);
            root->dg = minNode->dg;
            _xoaDocGia(root->right, minNode->dg.maThe);
        }
    }
}

void xuLyXoaDocGia(PTRDG &root) {
	int x = 80, y = 3;
	int maDG;
	gotoxy(x, y);
	cout<<"-----XOA DOC GIA-----"<<endl;
	
	if(root == NULL) {
		_loiDanhSachRong();
	    return;
	}
	
	gotoxy(x, y+2);
    cout<<"Ma  :"<<endl;
    
    if (!nhapMaDocGia(maDG, x, y+2)) return;
    
    DocGia* dg = _timDocGiaTheoMa(root, maDG);
    
    if (dg != NULL) {
    	string xacNhan;
		string phai = dg->phai == 0 ? "Nam" : "Nu";

    	gotoxy(x, y+4);
    	cout<<"Thong Tin Doc Gia Muon Xoa:"<<endl;
		gotoxy(x, y+5);
	    cout<<"Ho  : "<< dg->ho <<endl;
	    gotoxy(x, y+6);
	    cout<<"Ten : "<< dg->ten <<endl;
	    gotoxy(x, y+7);
	    cout<<"Phai: " << phai <<endl;
	    
	    gotoxy(x, y+9);
	    cout<<"Xac Nhan Xoa (Y/N): "<<endl;
	    if (!nhapXacNhan(xacNhan, x, y+9)) return;
	    
	    if(xacNhan == "Y") {
			_xoaDocGia(root, maDG);
			thongBao(1, "Da Xoa Doc Gia Thanh Cong!", x, 24);
		} else {
			thongBao(2, "Da Huy Thao Tac Xoa Doc Gia", x, 24);
		}
    		
	} else {
	    thongBao(0, "Khong tim thay Doc Gia!!!", x, 24);
	}
	
	Sleep(3000);
    clearTinhNang(x, 0);
    return;
}
// ========== END xoa doc gia ==========

void xuLyInDanhSachDocGia(PTRDG root, int trang, int soTrang, int typeInDG) {
	if (typeInDG == 0) {
		_xuLyInDanhSachDocGiaTheoTen(root, trang, soTrang);
	} else {
		_xuLyInDanhSachDocGiaTheoMa(root, trang, soTrang);
	}
}

// ========== Xu ly muon sach ==========

void _hienThiDocGia(DocGia* dg) {
	string trangThaiThe = dg->trangThai == 1 ? "Hoat Dong" : "Da Bi Khoa";
	string phai = dg->phai == 0 ? "Nam" : "Nu";
	
	gotoxy(0, 5);
	cout << left
         << setw(6) << 1
         << "| " << setw(6) << dg->maThe
         << "| " << setw(30) << dg->ho +  " " + dg->ten
         << "| " << setw(5)  << phai
         << "| " << setw(10) << trangThaiThe << endl;
}

void _hienThiSachDangMuon(DocGia* dg) {
	string trangThaiThe = dg->trangThai == 1 ? "Hoat Dong" : "Da Bi Khoa";
	string phai = dg->phai == 0 ? "Nam" : "Nu";
	
	gotoxy(0, 7);

	cout << left
	     << setw(6) << "STT"
         << "|" << setw(6) << "Ma Sach"
         << "| " << setw(10) << "Ngay Muon"
         << "| " << setw(10) << "Ngay Tra"
         << "| " << setw(15)  << "Vi Tri"
         << "| " << setw(10) << "Trang Thai" << endl;

    cout << setfill('-')
    	 << setw(6) << ""
         << "+-" << setw(6) << ""
         << "+-" << setw(10) << ""
         << "+-" << setw(10)  << ""
         << "+-" << setw(15)  << ""
         << "+-" << setw(10) << "" << endl;
    cout << setfill(' ');
    
    int index = 0;
    while(dg->ptrMT != NULL) {
	    cout << left
	         << setw(6) << ++index
	         << "| " << setw(6) << dg->ptrMT->mt.maSach
	         << "| " << setw(10) << dg->ptrMT->mt.viTri
	         << "| " << setw(10) << dg->ptrMT->mt.viTri
	         << "| " << setw(15)  << dg->ptrMT->mt.viTri
	         << "| " << setw(10) << trangThaiThe << endl;

		dg->ptrMT = dg->ptrMT->next;
	}
}

void xuLyMuonSach(PTRDG root) {
	int x = 80, y = 3;
	int maDG;
	gotoxy(x, y);
	cout<<"-----MUON SACH-----"<<endl;
	
	if(root == NULL) {
		_loiDanhSachRong();
	    return;
	}
	
	gotoxy(x, y+2);
    cout<<"Ma  :"<<endl;
    
    if (!nhapMaDocGia(maDG, x, y+2)) return;
    
    DocGia* dg = _timDocGiaTheoMa(root, maDG);
    
    if (dg != NULL) {
		_clearVungDanhSachDocGia();
		_hienThiDocGia(dg);
		_hienThiSachDangMuon(dg);
		
	} else {
	    thongBao(0, "Khong tim thay Doc Gia!!!", x, 24);
	}
	
	Sleep(300000);
    clearTinhNang(x, 0);
    return;
}

// ========== END xu ly muon sach ==========

// ========== Xu ly muon sach ==========

void xuLyTraSach(PTRDG root) {
	
}

// ========== END xu ly muon sach ==========




