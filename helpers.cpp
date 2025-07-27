#include <iostream>
#include <string>
#include <cstring>
#include <cctype>
#include <algorithm>
#include <conio.h>
#include <thread>
#include <chrono>
#include "structs.h"

using namespace std;


string chuanHoaChuoi(const string &str) {
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

bool nhapChuoi(string &s, int maxLen) {
    s.clear();

    char ch;
    while (true) {
        ch = getch();

        if (ch == 13) break;            // Enter ket thuc nhap
        if (ch == 27) return false;		// ESC huy

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
    s = chuanHoaChuoi(s);
    return true;
}

bool nhapSo(int &so, int minVal, int maxVal, int maxLen) {
    string s;
    char ch;

    while (true) {
        ch = getch();

        if (ch == 13) { // Enter
            if (!s.empty()) {
                so = stoi(s);
                if (so >= minVal && so <= maxVal) {
                    cout << endl;
                    return true;
                } else {
                    cout << "\nSo phai nam trong [" << minVal << ", " << maxVal << "]. Nhap lai: ";
                    s.clear();
                }
            } else {
                cout << "\nKhong duoc de trong. Nhap lai: ";
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

int kiemTraTonTaiISBN(ListDauSach &lds, string ISBN) {
	for (int i = 0; i < lds.n; i++) {
		if (lds.nodes[i].ISBN == ISBN) {
			return i;
		}
	}
	return -1;
}

bool nhapMaISBN(ListDauSach &lds, string &s, int maxLen) {
    s.clear();
    char ch;

    while (true) {
        ch = getch();

        if (ch == 27) return false; // ESC -> h?y
        if (ch == 13) { // Enter
            if (s.length() != maxLen) {
                cout << "\nMa ISBN phai co dung " << maxLen << " ky tu. Nhap lai: ";
                s.clear();
                continue;
            }

            if (kiemTraTonTaiISBN(lds, s) != -1) {
                cout << "\nMa ISBN da ton tai. Nhap lai: ";
                s.clear();
                continue;
            }

            cout << endl;
            return true;
        }

        // Backspace
        if (ch == 8) {
            if (!s.empty()) {
                cout << "\b \b";
                s.pop_back();
            }
        }

        else if (isalpha(ch) && s.length() < maxLen) {
            ch = toupper(ch);
            cout << ch;
            s += ch;
        }
    }
}

bool chonTheLoai(string &theLoai) {
    int luaChon;

    cout << "Cac the loai duoc chon:\n";
    cout << "1. Khoa hoc\n";
    cout << "2. Van hoc\n";
    cout << "3. Lich su\n";
    cout << "4. Thieu nhi\n";
    cout << "5. Ky nang\n";
    cout << "Nhap the loai (tu 1 den 5):";

    if (!nhapSo(luaChon, 1, 5, 1)) {
        return false;
    }

    switch (luaChon) {
        case 1: theLoai = "Khoa hoc"; break;
        case 2: theLoai = "Van hoc"; break;
        case 3: theLoai = "Lich su"; break;
        case 4: theLoai = "Thieu nhi"; break;
        case 5: theLoai = "Ky nang"; break;
    }
    
    return true;
}

bool chonPhai(string &phai) {
    int luaChon;

    cout << "Cac phai co the chon:\n";
    cout << "1. Nam\n";
    cout << "2. Nu\n";
    cout << "Nhap phai (1 hoac 2):";

    if (!nhapSo(luaChon, 1, 2, 1)) {
        return false;
    }

    switch (luaChon) {
        case 1: phai = "Nam"; break;
        case 2: phai = "Nu"; break;
    }
    
    return true;
}

string chuanHoaInHoa(string s) {
    transform(s.begin(), s.end(), s.begin(), ::toupper);
    return s;
}

void showTitleChucNang(string chucNang, int esc) {
	cout<<"Ban Dang Chon Chuc Nang "<<chucNang<<endl;
	
	if(esc)
		cout<<"Nhan Phim ESC De Dung Thao Tac."<<endl;

	cout<<endl;
}

void nhanPhimBatKyDeQuayLai() {
	cout<<endl;
	cout<<"Nhan Phim Bat Ky De Quay Lai Menu..."<<endl;
	getch();
}

void thongBaoHuyThaoTac(string thaoTac) {
	cout<<"\n\nDa Huy Thao Tac "<<thaoTac<<endl;
}



