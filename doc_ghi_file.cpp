#include <iostream>
#include <fstream>
#include <cstring>
#include <sstream>
#include <string>
#include "structs.h"
#include "doc_ghi_file.h"
#include "dau_sach.h"
#include "doc_gia.h"

using namespace std;

const char* ma_the_file = "D:\\CTDLGT\\Do_An\\ma_the.txt";
int currentMaThe = -1;

void saveDauSach(const char* fileName, ListDauSach &lds) {
    ofstream file(fileName);
    if (!file.is_open()) {
        cout << "Khong mo duoc file de ghi!" << endl;
        return;
    }

    // Ghi s? lu?ng d?u sách ? dòng d?u
    file << lds.n << endl;

    for (int i = 0; i < lds.n; i++) {
        DauSach &ds = lds.nodes[i];

        // Ghi dòng thông tin d?u sách
        file << ds.ISBN << "|"
             << ds.tenSach << "|"
             << ds.soTrang << "|"
             << ds.tacGia << "|"
             << ds.namXuatBan << "|"
             << ds.theLoai << "|"
             << ds.soLuotMuon << "|"
             << ds.soLuongSach << endl;

        // Ghi danh sách sách con
        PTRSach p = ds.ptrSach;
        while (p != NULL) {
            file << p->sach.maSach << ","
                 << p->sach.trangThai << ","
                 << p->sach.viTri << endl;
            p = p->next;
        }

        // Ghi ký hi?u k?t thúc
        file << "#END_SACH" << endl;
    }

    cout << "Da ghi Dau Sach vao file!" << endl;
    file.close();
}

void loadDauSach(const char* fileName, ListDauSach &lds) {
    ifstream file(fileName);
    if (!file.is_open()) {
        cout << "Khong mo duoc file!" << endl;
        return;
    }

    string line;

    // Doc dong dau tien chua so luong dau sach
    if (!getline(file, line)) {
        cout << "File rong hoac loi dinh dang!" << endl;
        return;
    }

    while (getline(file, line)) {
        if (line.empty() || line == "#END_SACH")
            continue;

        DauSach ds;

        stringstream ss(line);
        string token;

        getline(ss, ds.ISBN, '|');
        getline(ss, ds.tenSach, '|');

        getline(ss, token, '|');
        ds.soTrang = token.empty() ? 0 : stoi(token);

        getline(ss, ds.tacGia, '|');

        getline(ss, token, '|');
        ds.namXuatBan = token.empty() ? 0 : stoi(token);

        getline(ss, ds.theLoai, '|');

        getline(ss, token, '|');
        ds.soLuotMuon = token.empty() ? 0 : stoi(token);
        
        getline(ss, token, '|');
        ds.soLuongSach = token.empty() ? 0 : stoi(token);

        ds.ptrSach = NULL;

        // Ð?c danh sách sách con
        while (getline(file, line)) {
            if (line.empty() || line == "#END_SACH")
                break;

            stringstream ssSach(line);
            string ma, ttStr, vt;

            getline(ssSach, ma, ',');
            getline(ssSach, ttStr, ',');
            getline(ssSach, vt);

            if (ma.empty() || ttStr.empty() || vt.empty()) {
                cout << "Dong sach bi thieu truong: " << line << endl;
                continue;
            }

            Sach sach;
            sach.maSach = ma;
            sach.trangThai = stoi(ttStr);
            sach.viTri = vt;

            insertLastSach(ds.ptrSach, sach);
        }

        // Thêm dau sách vào danh sách
        if (isDauSachFull(lds)) {
			cout << "Danh sach dau sach da day!" << endl;
            break;
		} else {
			lds.nodes[lds.n++] = ds;
		}
    }

    cout << "Da doc Dau Sach tu file!" << endl;
    file.close();
}

void _ghiDocGia(ofstream &file, PTRDG p) {
    if (p == NULL) return;

    // Ghi thông tin DocGia
    file << p->dg.maThe << "|"
         << p->dg.ho << "|"
         << p->dg.ten << "|"
         << p->dg.phai << "|"
         << p->dg.trangThai << endl;

    // Ghi danh sach muon tra
    PTRMT mt = p->dg.ptrMT;
    while (mt != NULL) {
        file << mt->mt.maSach << ","
             << mt->mt.ngayMuon.ngay << ","
             << mt->mt.ngayMuon.thang << ","
             << mt->mt.ngayMuon.nam << ","
             << mt->mt.ngayTra.ngay << ","
             << mt->mt.ngayTra.thang << ","
             << mt->mt.ngayTra.nam << ","
             << mt->mt.trangThai << ","
             << mt->mt.viTri << endl;
        mt = mt->next;
    }

    // Ket thuc danh sach muon tra
    file << "#END_MT" << endl;

    // De quy sang trai va phai
	_ghiDocGia(file, p->left);
    _ghiDocGia(file, p->right);
}

void saveDocGia(const char* fileName, PTRDG root) {
    ofstream file(fileName);
    if (!file.is_open()) {
        cout << "Khong mo duoc file de ghi!" << endl;
        return;
    }

    _ghiDocGia(file, root);

    cout << "Da ghi Doc Gia vao file!" << endl;
    file.close();
}

void loadDocGia(const char* fileName, PTRDG &root) {
    ifstream file(fileName);
    if (!file.is_open()) {
        cout << "Khong mo duoc file!" << endl;
        return;
    }

    string line;
    while (getline(file, line)) {
        if (line.empty() || line == "#END_MT")
			continue;

        stringstream ss(line);
        string token;

        DocGia dg;

        getline(ss, token, '|');
        dg.maThe = stoi(token);

        getline(ss, dg.ho, '|');
        getline(ss, dg.ten, '|');
        
        getline(ss, token, '|');
        dg.phai = stoi(token);

        getline(ss, token, '|');
        dg.trangThai = token.empty() ? 0 : stoi(token);

        dg.ptrMT = NULL;

        // Doc danh sach muon tra
        while (getline(file, line)) {
            if (line == "#END_MT") break;

            stringstream ssMT(line);
            MuonTra mt;
            string nmuonNgay, nmuonThang, nmuonNam;
            string ntraNgay, ntraThang, ntraNam;
            string ttStr, viTri;

            getline(ssMT, mt.maSach, ',');
            getline(ssMT, nmuonNgay, ',');
            getline(ssMT, nmuonThang, ',');
            getline(ssMT, nmuonNam, ',');
            getline(ssMT, ntraNgay, ',');
            getline(ssMT, ntraThang, ',');
            getline(ssMT, ntraNam, ',');
            getline(ssMT, ttStr, ',');
            getline(ssMT, viTri);

            mt.ngayMuon.ngay = stoi(nmuonNgay);
            mt.ngayMuon.thang = stoi(nmuonThang);
            mt.ngayMuon.nam = stoi(nmuonNam);

            mt.ngayTra.ngay = stoi(ntraNgay);
            mt.ngayTra.thang = stoi(ntraThang);
            mt.ngayTra.nam = stoi(ntraNam);

            mt.trangThai = stoi(ttStr);
            mt.viTri = viTri;

            insertLastMT(dg.ptrMT, mt);
        }

        insertDG(root, dg);
    }

    cout << "Da doc Doc Gia tu file!" << endl;
    file.close();
}

int layMaTheTuFile() {
    ifstream file(ma_the_file);
    if (!file.is_open()) {
        cout << "Khong mo duoc file maThe.txt!" << endl;
        return -1;
    }

    string line;
    if (getline(file, line)) {
        if (!line.empty()) {
            currentMaThe = stoi(line); // Luu vao bien toan cuc.
            file.close();
            return currentMaThe;
        }
    }

    file.close();
    cout << "File maThe.txt rong hoac loi!" << endl;
    return -1;
}

void saveMaTheFile() {
    ifstream file(ma_the_file);
    if (!file.is_open()) {
        cout << "Khong mo duoc file maThe.txt de cap nhat!" << endl;
        return;
    }

    const int MAX = 1024;
    int arr[MAX];
    int count = 0;
    string line;

    while (getline(file, line)) {
        if (!line.empty()) {
            arr[count++] = stoi(line);
        }
    }
    file.close();

    if (count > 0 && arr[0] == currentMaThe) {
        for (int i = 1; i < count; i++) {
            arr[i - 1] = arr[i];
        }
        count--;
    }

    ofstream outFile(ma_the_file);
    for (int i = 0; i < count; i++) {
        outFile << arr[i] << endl;
    }
    outFile.close();

    currentMaThe = -1;
}
