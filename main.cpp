#include <iostream>
#include <conio.h>
#include "mylib.h"
#include "structs.h"
#include "doc_ghi_file.h"
#include "dau_sach.h"
#include "doc_gia.h"
#include "helpers.h"

#define MAXLIST 10000

using namespace std;

const char* dau_sach_file = "D:\\CTDLGT\\Do_An\\dau_sach.txt";
const char* doc_gia_file = "D:\\CTDLGT\\Do_An\\doc_gia.txt";


const int so_item = 3;
const int dong = 5;
const int cot = 20;
const int KEY_UP = 72;
const int KEY_DOWN = 80;
const int KEY_LEFT = 75;
const int KEY_RIGHT = 77;
const int KEY_ENTER = 13;

const int KEY_F1 = 59;
const int KEY_F2 = 60;
const int KEY_F3 = 61;
const int KEY_F4 = 62;
const int KEY_F5 = 63;
const int KEY_ESC = 27;

// Khai báo menu
char menu[3][50] = {
    "1. Quan Ly The Doc Gia       ",
    "2. Quan Ly Dau Sach          ",
    "3. Thoat Chuong Trinh        ",
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
            case KEY_UP:
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
            case KEY_DOWN:
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
            case KEY_ENTER:
                return chon + 1;
        }
    } while (true);
}

int main() {
	ListDauSach lds;
	PTRDG root = NULL;
	
	loadDauSach(dau_sach_file, lds);
	loadDocGia(doc_gia_file, root);

    int chon, key, trang;
    bool canReprint = true;
    do {
        chon = MenuDong(menu, 3);
        Normal();
        system("cls");
        switch (chon) {
            case 1: { // The doc gia
            	trang = 1;
            	int soTrang = tinhSoTrang(root);
            	inKhungQuanLyDocGia();

            	do {
            		if (canReprint) {
            			soTrang = tinhSoTrang(root);
						xuLyInDanhSachDocGia(root, trang, soTrang);
						canReprint = false;
					}

	            	key = getch();
			        switch (key) {
			            case KEY_F1:
			            	xuLyNhapDocGia(root);
			            	canReprint = true;
			                break;
			            case KEY_F2:
			                break;
			            case KEY_F3:
			                break;
			            case KEY_F4:
			                break;
			            case KEY_F5:
			                break;
			            case KEY_LEFT:
			            	if(trang > 1) {
								trang--;
			            		canReprint = true;
							}
			            	break;
			            case KEY_RIGHT:
			            	if(trang < soTrang) {
								trang++;
			            		canReprint = true;
							}
			            	break;
			            case KEY_ESC:
			            	canReprint = true;
			        }
				} while (key != KEY_ESC);
            	break;
            }

            case 2: { // Dau sach
                break;
            }
            case so_item: {
            	saveDauSach(dau_sach_file, lds);
            	saveDocGia(doc_gia_file, root);
    			return 0;
			}
        }
    } while (true);

    return 0;
}

	
	
	
