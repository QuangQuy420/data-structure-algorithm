#pragma once
#include "structs.h"

void loadDauSach(const char* fileName, ListDauSach &lds);
void saveDauSach(const char* fileName, ListDauSach &lds);

void loadDocGia(const char* fileName, PTRDG &root);
void saveDocGia(const char* fileName, PTRDG root);

void loadMaThe(const char* fileName, int arr[], int &n);
void saveMaThe(const char* fileName, int arr[], int n);
int layMaThe(int arr[], int &n);

