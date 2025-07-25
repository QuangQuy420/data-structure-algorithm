#include <iostream>
#include <conio.h>
#include "mylib.h"
#include "structs.h"
#include "doc_ghi_file.h"
#include "dau_sach.h"
#include "doc_gia.h"

#define MAXLIST 10000

using namespace std;

const char* dau_sach_file = "D:\\CTDLGT\\Do_An\\dau_sach.txt";
const char* doc_gia_file = "D:\\CTDLGT\\Do_An\\doc_gia.txt";


const int so_item = 5;
const int dong = 5;
const int cot = 20;
const int Up = 72;
const int Down = 80;
const int Enter = 13;

// Khai báo menu
char menu[5][50] = {
    "1. The Doc Gia       ",
    "2. Dau Sach          ",
    "3. Muon Sach         ",
    "4. Tra Sach          ",
    "5. Thoat Chuong Trinh",
};

char docgia[8][50] = {
    "1. Nhap danh sach doc gia           ",
    "2. Chinh sua doc gia theo ma        ",
    "3. Xoa doc gia theo ma              ",
    "4. Liet ke doc gia theo ten         ",
    "5. Liet ke doc gia theo ma          ",
    "6. Liet ke sach doc gia dang muon   ",
    "7. Liet ke doc gia muon sach qua han",
    "8. Tro lai                          "
};

char dausach[5][50] = {
    "1. Nhap thong tin dau sach        ",
    "2. Liet ke dau sach theo the loai ",
    "3. Tim kiem sach theo ten         ",
    "4. Liet ke 10 sach muon nhieu nhat",
    "5. Tro lai                        "
};

void Normal() {
    SetColor(15);
    SetBGColor(0);
}

void HighLight() {
    SetColor(15);
    SetBGColor(1);
}

int MenuDong(char td[][50], int so_item) {
    Normal();
    system("cls");
    int chon = 0;
    for (int i = 0; i < so_item; i++) {
        gotoxy(cot, dong + i);
        cout << td[i];
    }
    HighLight();
    gotoxy(cot, dong + chon);
    cout << td[chon];

    char kytu;
    do {
        kytu = getch();
        if (kytu == 0) kytu = getch();
        switch (kytu) {
            case Up:
                if (chon > 0) {
                    Normal();
                    gotoxy(cot, dong + chon);
                    cout << td[chon];
                    chon--;
                    HighLight();
                    gotoxy(cot, dong + chon);
                    cout << td[chon];
                }
                break;
            case Down:
                if (chon < so_item - 1) {
                    Normal();
                    gotoxy(cot, dong + chon);
                    cout << td[chon];
                    chon++;
                    HighLight();
                    gotoxy(cot, dong + chon);
                    cout << td[chon];
                }
                break;
            case Enter:
                return chon + 1;
        }
    } while (true);
}

int main() {
	ListDauSach lds;
	PTRDG root = NULL;
	
	loadDauSach(dau_sach_file, lds);
	loadDocGia(doc_gia_file, root);

    int chon;
    do {
        chon = MenuDong(menu, 5);
        Normal();
        system("cls");
        switch (chon) {
            case 1: { // The doc gia
                int chon_dg;
                do {
                    chon_dg = MenuDong(docgia, 8);
                    Normal();
                    system("cls");
                    if (chon_dg == 8) break;
                    if (chon_dg == 1) {
						nhapDocGia(root);
						getch();
					}
                    if (chon_dg == 5) {
                    	inTieuDeDocGiaTheoMa();
						inDocGiaTheoMa(root);
					}
                    cout << "Ban da chon muc: " << docgia[chon_dg - 1] << endl;
                    cout << "Nhan phim bat ky de tiep tuc...";
                    getch();
                } while (true);
                break;
            }

            case 2: { // Dau sach
                int chon_ds;
                do {
                    chon_ds = MenuDong(dausach, 5);
                    Normal();
                    system("cls");
                    if (chon_ds == 5) break;
                    if (chon_ds == 1) {
                    	nhapDauSach(lds);
                    	getch();
					}
                    if (chon_ds == 2) {
                    	// Khai bao mang con tro de sap xep
                    	DauSach* nodesSapXep[MAXLIST];

						inDauSachTheoTheLoai(lds, nodesSapXep);
                        cout << "Nhan phim bat ky de tiep tuc...";
                        getch();
					}
					if (chon_ds == 3) {
						timSach(lds);
                        cout << "Nhan phim bat ky de tiep tuc...";
                        getch();
					}
                } while (true);
                break;
            }

            case 3: {
                cout << "Dang phat trien chuc nang Muon Sach...\n";
                cout << "Nhan phim bat ky de tro ve menu chinh...";
                getch();
                break;
            }
            
            case 4: {
                cout << "Dang phat trien chuc nang Tra Sach...\n";
                cout << "Nhan phim bat ky de tro ve menu chinh...";
                getch();
                break;
            }
            case so_item : {
            	saveDauSach(dau_sach_file, lds);
            	saveDocGia(doc_gia_file, root);
    			return 0;
			}
        }
    } while (true);

    return 0;
}

	
	
	
