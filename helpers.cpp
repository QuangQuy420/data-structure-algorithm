#include <iostream>
#include <string>
#include <cstring>
#include <cctype>
#include <algorithm>
#include <conio.h>
#include <thread>
#include <chrono>
#include <iomanip>
#include "structs.h"
#include "mylib.h"
#include "globals.h"

using namespace std;


string chuanHoaChuoi(string str) {
    string res;
    int i = 0;

    // Bo khoang trang dau
    while (i < str.length() && str[i] == ' ') i++;
	
	// Bo khoang trang giua
    bool spaceFlag = false;

    for (; i < str.length(); i++) {
        if (str[i] != ' ') {
            res += str[i]; // Neu ko phai khoang trang thi them vao
            spaceFlag = false; // flag chua gap khoang trang
        } else if (!spaceFlag) {
            res += ' '; // them 1 dau cach neu gap khoang trang
            spaceFlag = true; //flag da gap khoang trang
        }
        // neu gap khoang trang, flag = true => bo qua
    }

    // Bo khoang trang cuoi
    if (!res.empty() && res.back() == ' ')
        res.pop_back();

    return res;
}


// return 0: ESC, Huy nhap
// return 1: Nhap chuoi thanh cong, Hien thi chi tiet sach
int nhapChuoiTimKiem(string &s, int &trang, int soTrang, int maxLen) {
	char ch;
	
	while (true) {
        ch = getch();
        
        if (ch == 13) {
			if(s.empty()) {
				trang = 1;
				return -1;
			}
			else {
				break;
			}
		};
        if (ch == 27) return 0;		// ESC huy

        if (ch == 8) { // Backspace
            if (!s.empty()) {
                cout << "\b \b"; // Dat lai con tro sau khi xoa
                s.pop_back();
            }
        }
        
        if (ch == KEY_RIGHT && trang < soTrang) {
        	trang++;
        	if (s.empty()) {
        		return -1;
			} else {
				return 1;
			}
		}
		
		if (ch == KEY_LEFT && trang > 1) {
			trang--;
			if (s.empty()) {
        		return -1;
			} else {
				return 1;
			}
		}
        
        else if (isprint(ch) && s.length() < maxLen && ch != KEY_RIGHT && ch != KEY_LEFT) {
            cout << ch;
            s += ch;
        }
    }

    cout << endl;
    trang = 1;
    return 1;
}

// return -1: Khong duoc de trong
// return 0: ESC, Huy nhap
// return 1: Nhap chuoi thanh cong
int nhapChuoi(string &s, int maxLen, bool isUpper = false) {
//    s.clear();
    char ch;

    while (true) {
        ch = getch();
        
        if (ch == 13) {
        	s = chuanHoaChuoi(s);
			if(s.empty()) {
				return -1;
			}
			else {
				break;
			}
		};
        if (ch == 27) return 0;		// ESC huy

        if (ch == 8) { // Backspace
            if (!s.empty()) {
                cout << "\b \b"; // Dat lai con tro sau khi xoa
                s.pop_back();
            }
        }
        else if (isprint(ch) && s.length() < maxLen) {
        	if(isUpper) 
				ch = toupper(ch);

            cout << ch;
            s += ch;
        }
    }

    cout << endl;
    return 1;
}

// return -2: So ko nam trong mang gia tri [min, max]
// return -1: Khong duoc de trong
// return 0: ESC, Huy nhap
// return 1: Nhap chuoi thanh cong
int nhapSo(int &so, int min, int max, int maxLen) {
    string s = (so >= 0) ? to_string(so) : "";
    char ch;

    while (true) {
        ch = getch();

        if (ch == 13) { // Enter
            if (!s.empty()) {
                so = stoi(s);
                if (so >= min && so <= max) {
                    cout << endl;
                    return 1;
                } else {
                    return -2;
                }
            } else {
                return -1;
            }
        }
        else if (ch == 27) return false;
        else if (ch == 8) { // Backspace
            if (!s.empty()) {
                cout << "\b \b";
                s.pop_back();
            }
        }
        else if (ch >= '0' && ch <= '9') {
            if (s.length() < maxLen) {
                cout << ch;
                s += ch;
            }
        }
    }
}

string chuanHoaInHoa(string s) {
    transform(s.begin(), s.end(), s.begin(), ::toupper);
    return s;
}

void clearTinhNang(int x, int y) {
	for (int i = 0; i < 30; i++) {
        gotoxy(x, y + i);
        cout << string(45, ' ');
    }
}

// type 2: Info
// type 1: Success
// type 0: Error
void thongBao(int type, string message, int x, int y) {
	string typeTB;
	switch(type) {
		case 0: typeTB = "- Error -"; break;
		case 1: typeTB = " Success "; break;
		case 2: typeTB = "- Info --"; break;
	}

    gotoxy(x, y);
    cout << "--"<< typeTB <<"--------------------------------";
    gotoxy(x, y + 1);
    cout << "+" << string(41, ' ') << "+";
    gotoxy(x, y + 2);
    cout << "+ " << setw(40) << left << message << "+";
    gotoxy(x, y + 3);
    cout << "-------------------------------------------";
}

void clearBaoLoi(int x, int y) {
    for (int i = 0; i < 4; i++) {
        gotoxy(x, y + i);
        cout << string(45, ' ');
    }
}

// ===== DOC GIA =====

bool nhapHoDocGia(string &ho, int x, int y) {
    int ketQuaNhap = 0;
    int lenHo;
    
    gotoxy(x, 22);
    cout << "ESC: Huy Tinh Nang Nhap";

    do {
    	lenHo = ho.length();
        gotoxy(x + 6 + lenHo, y);

        ketQuaNhap = nhapChuoi(ho, 20);

        if (ketQuaNhap == -1) {
            thongBao(0, "Khong duoc de trong!!!", x, 24);
        } else {
			clearBaoLoi(x, 24);
		}

        if (ketQuaNhap == 0) {
        	clearTinhNang(x, 0);
            return false;
        }

    } while (ketQuaNhap != 1);

    return true;
}

bool nhapTenDocGia(string &ten, int x, int y) {
    int ketQuaNhap = 0;
    int lenTen;

    gotoxy(x, 22);
    cout << "ESC: Huy Tinh Nang Nhap";
    
    do {
    	lenTen = ten.length();
        gotoxy(x + 6 + lenTen, y);

        ketQuaNhap = nhapChuoi(ten, 20);

        if (ketQuaNhap == -1) {
            thongBao(0, "Khong duoc de trong!!!", x, 24);
        } else {
			clearBaoLoi(x, 24);
		}

        if (ketQuaNhap == 0) {
        	clearTinhNang(x, 0);
            return false;
        }

    } while (ketQuaNhap != 1);

    return true;
}

bool nhapPhaiDocGia(int &phai, int x, int y) {
    int ketQuaNhap = 0;
    int lenPhai;

    gotoxy(x, 22);
    cout << "ESC: Huy Tinh Nang Nhap";

    do {
    	lenPhai = (phai >= 0) ? to_string(phai).length() : 0;
    	
        gotoxy(x + 6 + lenPhai, y);

        ketQuaNhap = nhapSo(phai, 0, 1, 1);

        if (ketQuaNhap == -1) {
            thongBao(0, "Khong duoc de trong!!!", x, 24);
		} else if (ketQuaNhap == -2) {
			thongBao(0, "So ko nam trong mang gia tri [0, 1]", x, 24);
        } else {
			clearBaoLoi(x, 24);
		}

        if (ketQuaNhap == 0) {
        	clearTinhNang(x, 0);
            return false;
        }

    } while (ketQuaNhap != 1);

    return true;
}

bool nhapMaDocGia(int &maDG, int x, int y) {
    int ketQuaNhap = 0;

    gotoxy(x, 22);
    cout << "ESC: Huy Tinh Nang Nhap";

    do {
        gotoxy(x + 6, y);
        cout << string(8, ' '); // Xoá dòng nhap cu
        gotoxy(x + 6, y);

        ketQuaNhap = nhapSo(maDG, 1, MAX_DG , 4);

        if (ketQuaNhap == -1) {
            thongBao(0, "Khong duoc de trong!!!", x, 24);
		} else if (ketQuaNhap == -2) {
			thongBao(0, "So ko nam trong mang gia tri [1, 1024]", x, 24);
        } else {
			clearBaoLoi(x, 24);
		}

        if (ketQuaNhap == 0) {
        	clearTinhNang(x, 0);
            return false;
        }

    } while (ketQuaNhap != 1);

    return true;
}

// ===== END DOC GIA =====

// ===== DAU SACH =====

int _kiemTraTonTaiISBN(ListDauSach &lds, string ISBN) {
	for (int i = 0; i < lds.n; i++) {
		if (lds.nodes[i].ISBN == ISBN) {
			return i;
		}
	}
	return -1;
}

bool nhapISBN(ListDauSach &lds, string &ISBN, int x, int y) {
    int ketQuaNhap = 0;
    int len;
    int checkISBN = -1;
    
    gotoxy(x, 22);
    cout << "ESC: Huy Tinh Nang Nhap";

    do {
    	len = ISBN.length();
        gotoxy(x + 15 + len, y);

        ketQuaNhap = nhapChuoi(ISBN, 4, true);
        
        checkISBN = _kiemTraTonTaiISBN(lds, ISBN);
		
        if (ketQuaNhap == -1) {
            thongBao(0, "Khong duoc de trong!!!", x, 24);
        } else {
			clearBaoLoi(x, 24);
		}
		
		if (checkISBN > -1) {
			thongBao(0, "Ma ISBN da duoc su dung!!!", x, 24);
		}

        if (ketQuaNhap == 0) {
        	clearTinhNang(x, 0);
            return false;
        }

    } while (ketQuaNhap != 1 || checkISBN > -1);

    return true;
}

bool nhapTheLoaiDS(int &theLoai, int x, int y) {
    int ketQuaNhap = 0;
    int len;

    gotoxy(x, 22);
    cout << "ESC: Huy Tinh Nang Nhap";

    do {
    	len = (theLoai >= 0) ? to_string(theLoai).length() : 0;
    	
        gotoxy(x + 15 + len, y);

        ketQuaNhap = nhapSo(theLoai, 1, 4, 1);

        if (ketQuaNhap == -1) {
            thongBao(0, "Khong duoc de trong!!!", x, 24);
		} else if (ketQuaNhap == -2) {
			thongBao(0, "So ko nam trong mang gia tri [1, 4]", x, 24);
        } else {
			clearBaoLoi(x, 24);
		}

        if (ketQuaNhap == 0) {
        	clearTinhNang(x, 0);
            return false;
        }

    } while (ketQuaNhap != 1);

    return true;
}

bool nhapTenSach(string &tenSach, int x, int y) {
    int ketQuaNhap = 0;
    int len;
    
    gotoxy(x, 22);
    cout << "ESC: Huy Tinh Nang Nhap";

    do {
    	len = tenSach.length();
        gotoxy(x + 15 + len, y);

        ketQuaNhap = nhapChuoi(tenSach, 20);

        if (ketQuaNhap == -1) {
            thongBao(0, "Khong duoc de trong!!!", x, 24);
        } else {
			clearBaoLoi(x, 24);
		}

        if (ketQuaNhap == 0) {
        	clearTinhNang(x, 0);
            return false;
        }

    } while (ketQuaNhap != 1);

    return true;
}

bool nhapTenTacGia(string &tacGia, int x, int y) {
    int ketQuaNhap = 0;
    int len;
    
    gotoxy(x, 22);
    cout << "ESC: Huy Tinh Nang Nhap";

    do {
    	len = tacGia.length();
        gotoxy(x + 15 + len, y);

        ketQuaNhap = nhapChuoi(tacGia, 20);

        if (ketQuaNhap == -1) {
            thongBao(0, "Khong duoc de trong!!!", x, 24);
        } else {
			clearBaoLoi(x, 24);
		}

        if (ketQuaNhap == 0) {
        	clearTinhNang(x, 0);
            return false;
        }

    } while (ketQuaNhap != 1);

    return true;
}

bool nhapSoTrang(int &soTrang, int x, int y) {
    int ketQuaNhap = 0;
    int len;

    gotoxy(x, 22);
    cout << "ESC: Huy Tinh Nang Nhap";

    do {
    	len = (soTrang >= 0) ? to_string(soTrang).length() : 0;
    	
        gotoxy(x + 15 + len, y);

        ketQuaNhap = nhapSo(soTrang, 1, 10000, 5);

        if (ketQuaNhap == -1) {
            thongBao(0, "Khong duoc de trong!!!", x, 24);
		} else if (ketQuaNhap == -2) {
			thongBao(0, "So ko nam trong mang gia tri [1, 10000]", x, 24);
        } else {
			clearBaoLoi(x, 24);
		}

        if (ketQuaNhap == 0) {
        	clearTinhNang(x, 0);
            return false;
        }

    } while (ketQuaNhap != 1);

    return true;
}

bool nhapNamXuatBan(int &namXuatBan, int x, int y) {
    int ketQuaNhap = 0;
    int len;

    gotoxy(x, 22);
    cout << "ESC: Huy Tinh Nang Nhap";

    do {
    	len = (namXuatBan >= 0) ? to_string(namXuatBan).length() : 0;
    	
        gotoxy(x + 15 + len, y);

        ketQuaNhap = nhapSo(namXuatBan, 1000, 2025, 4);

        if (ketQuaNhap == -1) {
            thongBao(0, "Khong duoc de trong!!!", x, 24);
		} else if (ketQuaNhap == -2) {
			thongBao(0, "So ko nam trong mang gia tri [1000, 2025]", x, 24);
        } else {
			clearBaoLoi(x, 24);
		}

        if (ketQuaNhap == 0) {
        	clearTinhNang(x, 0);
            return false;
        }

    } while (ketQuaNhap != 1);

    return true;
}

bool nhapSoLuongSach(int &soLuongSach, int x, int y) {
    int ketQuaNhap = 0;
    int len;

    gotoxy(x, 22);
    cout << "ESC: Huy Tinh Nang Nhap";

    do {
    	len = (soLuongSach >= 0) ? to_string(soLuongSach).length() : 0;
    	
        gotoxy(x + 15 + len, y);

        ketQuaNhap = nhapSo(soLuongSach, 0, 30, 2);

        if (ketQuaNhap == -1) {
            thongBao(0, "Khong duoc de trong!!!", x, 24);
		} else if (ketQuaNhap == -2) {
			thongBao(0, "So ko nam trong mang gia tri [0, 30]", x, 24);
        } else {
			clearBaoLoi(x, 24);
		}

        if (ketQuaNhap == 0) {
        	clearTinhNang(x, 0);
            return false;
        }

    } while (ketQuaNhap != 1);

    return true;
}

bool nhapViTri(string &viTri, int x, int y) {
    int ketQuaNhap = 0;
    int len;
    
    gotoxy(x, 22);
    cout << "ESC: Huy Tinh Nang Nhap";

    do {
    	len = viTri.length();
        gotoxy(x + 15 + len, y);

        ketQuaNhap = nhapChuoi(viTri, 20);

        if (ketQuaNhap == -1) {
            thongBao(0, "Khong duoc de trong!!!", x, 24);
        } else {
			clearBaoLoi(x, 24);
		}

        if (ketQuaNhap == 0) {
        	clearTinhNang(x, 0);
            return false;
        }

    } while (ketQuaNhap != 1);

    return true;
}

// ===== END DAU SACH =====

bool nhapXacNhan(string &xacNhan, int x, int y) {
	int ketQuaNhap = 0;
	int lenXacNhan;
	bool isHopLe;

    gotoxy(x, 22);
    cout << "ESC: Huy Tinh Nang Nhap";
    
    do {
    	lenXacNhan = xacNhan.length();
        gotoxy(x + 20 + lenXacNhan, y);

        ketQuaNhap = nhapChuoi(xacNhan, 1);
        isHopLe = (xacNhan == "Y" || xacNhan == "N");

        if (ketQuaNhap == -1) {
            thongBao(0, "Khong duoc de trong!!!", x, 24);
        } else {
			clearBaoLoi(x, 24);
		}

        if (ketQuaNhap == 0) {
        	clearTinhNang(x, 0);
            return false;
        }

        if (ketQuaNhap == 1 && !isHopLe) {
			thongBao(0, "Chi cho phep nhap 'Y' or 'N'", x, 24);
		}

    } while (ketQuaNhap != 1 || !isHopLe);

    return true;
}

// ========== Nhap Ten Sach Tim Kiem ==========

int nhapTenSachTimKiem(string &tenSach, int &trang, int soTrang, int x, int y) {
	int ketQuaNhap = 0;
    int len;

    gotoxy(x, 22);
    cout << "ESC: Huy Tinh Nang Nhap";

    do {
    	len = tenSach.length();
        gotoxy(x + 10 + len, y);

        ketQuaNhap = nhapChuoiTimKiem(tenSach, trang, soTrang, 20);

        if (ketQuaNhap == -1) return -1;

        if (ketQuaNhap == 0) {
        	clearTinhNang(x, 0);
            return ketQuaNhap;
        }

    } while (ketQuaNhap != 1);

    return 1;
}

int tinhSoTrang(int soItem) {
	return soItem/ITEM_MOI_TRANG + (soItem % ITEM_MOI_TRANG != 0 ? 1 : 0);
}

