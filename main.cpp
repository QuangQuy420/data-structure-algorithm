#include <iostream>
#include <conio.h>
#include "mylib.h"
#include "structs.h"
#include "doc_ghi_file.h"
#include "dau_sach.h"
#include "doc_gia.h"
#include "helpers.h"
#include "globals.h"

#define MAXLIST 10000

using namespace std;

// Khai báo menu
char menu[3][50] = {
    "1. Quan Ly The Doc Gia       ",
    "2. Quan Ly Dau Sach          ",
    "3. Thoat Chuong Trinh        ",
};

int main() {
	ListDauSach lds;
	PTRDG root = NULL;
	
    int listMaThe[MAX_DG];
    int soLuongMaThe = 0;
	
	loadDauSach(dau_sach_file, lds);
	loadDocGia(doc_gia_file, root);
	loadMaThe(ma_the_file, listMaThe, soLuongMaThe);

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
			            	xuLyNhapDocGia(root, listMaThe, soLuongMaThe);
			            	canReprint = true;
			                break;
			            case KEY_F2:
			            	xuLyCapNhatDocGia(root);
			            	canReprint = true;
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
            	saveMaThe(ma_the_file, listMaThe ,soLuongMaThe);
    			return 0;
			}
        }
    } while (true);

    return 0;
}

	
	
	
