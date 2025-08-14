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
    int canReprint = 1;
    do {
        chon = MenuDong(menu, 3);
        Normal();
        system("cls");
        switch (chon) {
        	case 2: { // Dau sach
        		trang = 1;
        		string tenTimKiem;
        		int soTrang = tinhSoTrang(lds.n);
        		inKhungQuanLyDauSach();
        		
        		do {
        			if (canReprint == 1) {
        				soTrang = tinhSoTrang(lds.n);
						xuLyInDanhSachDauSach(lds, trang, soTrang);
						canReprint = 0;
					}

        			key = getch();
			        switch (key) {
						case KEY_F1:
							xuLyNhapDauSach(lds);
							canReprint = 1;
							break;
						case KEY_F4:
							xuLyTimSach(lds);
							canReprint = 1;
							break;
						case KEY_LEFT:
			            	if(trang > 1) {
								trang--;
			            		canReprint = 1;
							}
			            	break;
			            case KEY_RIGHT:
			            	if(trang < soTrang) {
								trang++;
			            		canReprint = 1;
							}
			            	break;
			            case KEY_ESC:
			            	canReprint = 1;
					}
				} while (key != KEY_ESC);
                break;
            }
            case 1: { // The doc gia
            	trang = 1;
            	int soTrang = tinhSoTrang(root);
            	int typeInDG = 0; // 0: In theo ten; 1: In theo ma
            	inKhungQuanLyDocGia();

            	do {
            		if (canReprint == 1) {
            			soTrang = tinhSoTrang(root);
            			if(trang > soTrang) trang = soTrang;
            			xuLyInDanhSachDocGia(root, trang, soTrang, typeInDG);
						canReprint = 0;
					}

	            	key = getch();
			        switch (key) {
			            case KEY_F1: // Them Doc Gia
			            	xuLyNhapDocGia(root, listMaThe, soLuongMaThe);
			            	canReprint = 1;
			                break;
			            case KEY_F2: // Update Doc Gia
			            	xuLyCapNhatDocGia(root);
			            	canReprint = 1;
			                break;
			            case KEY_F3: // Delete Doc Gia
			            	xuLyXoaDocGia(root);
			            	canReprint = 1;
			                break;
			            case KEY_F4: // In Theo Ten
			            	trang = 1;
							typeInDG = 0;
							canReprint = 1;
			                break;
			            case KEY_F5: // In Theo Ma
			            	trang = 1;
			            	typeInDG = 1;
			            	canReprint = 1;
			                break;
			            case KEY_F6: // Muon Sach
			            	xuLyMuonSach(root);
			            	canReprint = 1;
			                break;
			            case KEY_F7: // Tra Sach
			            	xuLyTraSach(root);
			            	canReprint = 1;
			                break;
			            case KEY_LEFT:
			            	if(trang > 1) {
								trang--;
			            		canReprint = 1;
							}
			            	break;
			            case KEY_RIGHT:
			            	if(trang < soTrang) {
								trang++;
			            		canReprint = 1;
							}
			            	break;
			            case KEY_ESC:
			            	canReprint = 1;
			        }
				} while (key != KEY_ESC);
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

	
	
	
