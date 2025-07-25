#include <iostream>
#include <string>
#include <cstring>
#include <cctype>
#include <algorithm>
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

void nhapChuoi(string &s, int maxLen) {
    do {
        getline(cin, s);
        s = chuanHoaChuoi(s);

        if ((int)s.length() > maxLen) {
            cout << "Chi duoc nhap toi da " << maxLen << " ky tu. Vui long nhap lai: ";
        }
    } while ((int)s.length() > maxLen);
}

void nhapSo(int &so, int minVal = INT_MIN, int maxVal = INT_MAX) {
    string input;
    bool valid = false;

    do {
        getline(cin, input);

        // Trim d?u và cu?i
        while (!input.empty() && input.front() == ' ') input.erase(input.begin());
        while (!input.empty() && input.back() == ' ') input.pop_back();

        // Kiem tra chuoi khong rong va chi co cac ky tu hop le
        if (!input.empty()) {
            // D?u '-' ch? du?c phép d?ng d?u
            size_t startIdx = 0;
            if (input[0] == '-') {
                startIdx = 1;
            }

            // Ki?m tra t? startIdx tr? di ph?i toàn s?
            bool allDigits = true;
            for (size_t i = startIdx; i < input.length(); i++) {
                if (!isdigit(input[i])) {
                    allDigits = false;
                    break;
                }
            }

            if (allDigits) {
                so = stoi(input);
                if (so < minVal || so > maxVal) {
                    cout << "So phai nam trong [" << minVal << ", " << maxVal << "]. Nhap lai: ";
                    valid = false;
                } else {
                    valid = true;
                }
            } else {
                cout << "Chi duoc nhap so nguyen. Nhap lai: ";
            }
        } else {
            cout << "Khong duoc de trong. Nhap lai: ";
        }

    } while (!valid);
}

int kiemTraTonTaiISBN(ListDauSach &lds, string ISBN) {
	for (int i = 0; i < lds.n; i++) {
		if (lds.nodes[i].ISBN == ISBN) {
			return i;
		}
	}
	return -1;
}

void nhapMaISBN(ListDauSach &lds, string &s, int maxLen) {
	int existISBN = -1;
    do {
        getline(cin, s);

        // Xóa khoang trang
        s.erase(remove(s.begin(), s.end(), ' '), s.end());

        // Chuyen thanh chu hoa
        for (char &c : s) {
            c = toupper(c);
        }

        // Kiem tra do dai va chi chua chu cai
        bool valid = true;
        if ((int)s.length() != maxLen) {
            valid = false;
        } else {
            for (char c : s) {
                if (!isalpha(c)) {
                    valid = false;
                    break;
                }
            }
        }
        
        existISBN = kiemTraTonTaiISBN(lds, s);

        if (!valid) {
            cout << "Chi duoc nhap dung " << maxLen << " ky tu, khong khoang trang, chi chua chu cai. Vui long nhap lai: ";
        } else if (existISBN != -1) {
			cout << "Ma ISBN da ton tai, Vui long nhap lai: ";
		}
    } while ((int)s.length() != maxLen || !all_of(s.begin(), s.end(), ::isalpha) || existISBN != -1);
}

void chonTheLoai(string &theLoai) {
    int luaChon;

    cout << "Cac the loai duoc chon:\n";
    cout << "1. Khoa hoc\n";
    cout << "2. Van hoc\n";
    cout << "3. Lich su\n";
    cout << "4. Thieu nhi\n";
    cout << "5. Ky nang\n";
    cout << "Nhap the loai (tu 1 den 5):";

    nhapSo(luaChon, 1, 5);

    switch (luaChon) {
        case 1: theLoai = "Khoa hoc"; break;
        case 2: theLoai = "Van hoc"; break;
        case 3: theLoai = "Lich su"; break;
        case 4: theLoai = "Thieu nhi"; break;
        case 5: theLoai = "Ky nang"; break;
    }
}

void chonPhai(string &phai) {
    int luaChon;

    cout << "Cac phai co the chon:\n";
    cout << "1. Nam\n";
    cout << "2. Nu\n";
    cout << "Nhap phai (1 hoac 2):";

    nhapSo(luaChon, 1, 2);

    switch (luaChon) {
        case 1: phai = "Nam"; break;
        case 2: phai = "Nu"; break;
    }
}

string chuanHoaInHoa(string s) {
    transform(s.begin(), s.end(), s.begin(), ::toupper);
    return s;
}




