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

// return -1: Khong duoc de trong
// return 0: ESC, Huy nhap
// return 1: Nhap chuoi thanh cong
int nhapChuoi(string &s, int maxLen) {
    s.clear();
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
    string s;
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

//int kiemTraTonTaiISBN(ListDauSach &lds, string ISBN) {
//	for (int i = 0; i < lds.n; i++) {
//		if (lds.nodes[i].ISBN == ISBN) {
//			return i;
//		}
//	}
//	return -1;
//}

//bool nhapMaISBN(ListDauSach &lds, string &s, int maxLen) {
//    s.clear();
//    char ch;
//
//    while (true) {
//        ch = getch();
//
//        if (ch == 27) return false; // ESC -> h?y
//        if (ch == 13) { // Enter
//            if (s.length() != maxLen) {
//                cout << "\nMa ISBN phai co dung " << maxLen << " ky tu. Nhap lai: ";
//                s.clear();
//                continue;
//            }
//
//            if (kiemTraTonTaiISBN(lds, s) != -1) {
//                cout << "\nMa ISBN da ton tai. Nhap lai: ";
//                s.clear();
//                continue;
//            }
//
//            cout << endl;
//            return true;
//        }
//
//        // Backspace
//        if (ch == 8) {
//            if (!s.empty()) {
//                cout << "\b \b";
//                s.pop_back();
//            }
//        }
//
//        else if (isalpha(ch) && s.length() < maxLen) {
//            ch = toupper(ch);
//            cout << ch;
//            s += ch;
//        }
//    }
//}

//bool chonTheLoai(string &theLoai) {
//    int luaChon;
//
//    cout << "Cac the loai duoc chon:\n";
//    cout << "1. Khoa hoc\n";
//    cout << "2. Van hoc\n";
//    cout << "3. Lich su\n";
//    cout << "4. Thieu nhi\n";
//    cout << "5. Ky nang\n";
//    cout << "Nhap the loai (tu 1 den 5):";
//
//    if (!nhapSo(luaChon, 1, 5, 1)) {
//        return false;
//    }
//
//    switch (luaChon) {
//        case 1: theLoai = "Khoa hoc"; break;
//        case 2: theLoai = "Van hoc"; break;
//        case 3: theLoai = "Lich su"; break;
//        case 4: theLoai = "Thieu nhi"; break;
//        case 5: theLoai = "Ky nang"; break;
//    }
//    
//    return true;
//}

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

// type 1: Success
// type 0: Error
void thongBao(int type, string message, int x, int y) {
	string typeTB = type == 0 ? "- Error -" : " Success ";
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

bool nhapHoDocGia(string &ho) {
    const int x = 80, y = 5;
    int ketQuaNhap = 0;
    
    gotoxy(x, 22);
    cout << "ESC: Huy Tinh Nang Nhap";
    
    do {
        gotoxy(x + 6, y);
        cout << string(20, ' '); // Xoá dòng nhap cu
        gotoxy(x + 6, y);

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

bool nhapTenDocGia(string &ten) {
    const int x = 80, y = 6;
    int ketQuaNhap = 0;

    gotoxy(x, 22);
    cout << "ESC: Huy Tinh Nang Nhap";
    
    do {
        gotoxy(x + 6, y);
        cout << string(20, ' '); // Xoá dòng nhap cu
        gotoxy(x + 6, y);

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

bool nhapPhaiDocGia(int &phai) {
    const int x = 80, y = 7;
    int ketQuaNhap = 0;

    gotoxy(x, 22);
    cout << "ESC: Huy Tinh Nang Nhap";

    do {
        gotoxy(x + 6, y);
        cout << string(5, ' '); // Xoá dòng nhap cu
        gotoxy(x + 6, y);

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

bool nhapMaDocGia(int &maDG) {
    const int x = 80, y = 5;
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

