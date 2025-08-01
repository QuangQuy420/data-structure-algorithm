#include <iostream>
#include <windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <string.h>
#include "mylib.h"
#include "globals.h"

using namespace std;

void gotoxy(short x, short y)
{
    HANDLE hConsoleOutput;
    COORD Cursor_an_Pos = { x, y };
    hConsoleOutput = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleCursorPosition(hConsoleOutput, Cursor_an_Pos);
}

int wherex(void)
{
    HANDLE hConsoleOutput;
    hConsoleOutput = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFO info;
    GetConsoleScreenBufferInfo(hConsoleOutput, &info);
    return info.dwCursorPosition.X;
}

int wherey(void)
{
    HANDLE hConsoleOutput;
    hConsoleOutput = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFO info;
    GetConsoleScreenBufferInfo(hConsoleOutput, &info);
    return info.dwCursorPosition.Y;
}

void clreol(void)
{
    COORD coord;
    DWORD written;
    CONSOLE_SCREEN_BUFFER_INFO info;
    GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &info);
    coord.X = info.dwCursorPosition.X;
    coord.Y = info.dwCursorPosition.Y;
    FillConsoleOutputCharacter(GetStdHandle(STD_OUTPUT_HANDLE), ' ',
        info.dwSize.X - coord.X, coord, &written);
    gotoxy(coord.X, coord.Y);
}

void SetColor(WORD color)
{
    HANDLE hConsoleOutput = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFO info;
    GetConsoleScreenBufferInfo(hConsoleOutput, &info);
    WORD attributes = info.wAttributes;
    attributes &= 0xFFF0;
    attributes |= (color & 0x000F);
    SetConsoleTextAttribute(hConsoleOutput, attributes);
}

void SetBGColor(WORD color)
{
    HANDLE hConsoleOutput = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFO info;
    GetConsoleScreenBufferInfo(hConsoleOutput, &info);
    WORD attributes = info.wAttributes;
    attributes &= 0xFF0F;
    attributes |= ((color & 0x000F) << 4);
    SetConsoleTextAttribute(hConsoleOutput, attributes);
}

void clrscr()
{
    system("cls");
}

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

