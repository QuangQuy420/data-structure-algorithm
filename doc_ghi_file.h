#pragma once
#include "structs.h"

void loadDauSach(const char* fileName, ListDauSach &lds);
void saveDauSach(const char* fileName, ListDauSach &lds);

void loadDocGia(const char* fileName, PTRDG &root);
void saveDocGia(const char* fileName, PTRDG root);
int layMaTheTuFile();
void saveMaTheFile();

