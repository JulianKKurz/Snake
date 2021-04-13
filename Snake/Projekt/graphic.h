
#ifndef GRAPHIC_H
#define GRAPHIC_H
#include "global.h"

int mW;
int mH;
int wp;
int hp;
int h;
int w;
int hd;
int wd;
int iW;
int iH;
int oW;
int oH;
bool repeat;
int marker;
int limit;
bool errorText;

int string;
int width;
int hight;
unsigned char class;

void ascii();
void graphic1(int start, int max, int length, char string [], char A, char B);
char REPLACE [H][W];
void replace(char replace, char input, char (*output)[W], char task);
void initialize (char input, char (*output)[W]);
void monitoring (char Cmonitor [H][W], char monitor [H][W]);
void color (unsigned char color);
void cursor (bool cursor);
void cut(char (*mask)[mW], char attribute, char (*texture)[mW], char (*output)[W]);
char* ArrToStr(char (*Array)[W], int i);
void arrcpy(char output [oH][oW],char input [iH][iW]);
int edge (char* string, int j);
char* strGen(char Char,int j);
void windowsize(int Y,int X,char task);
void sign (int art, int k);
void table (char dataArray [hight][width][string]);
void line (int l);
void space (int s);
void center(char*text,int string);
void arraySprintf(char *text, char *output,char task);
void centerStatic(char*text, int y);
void coord(int x,int y);
char* stringSelect(char* text, int length, int index);
//int C(char v);
void numberArray (char* text, float* Numbers, int elements, char* delimiter);
int file(char* directory, char (*Array)[W],char* mode);
void asciiConvert(char (*output)[W]);

/*
Pixels
        ( ) = 0 = 0   = 0
        (░) = 1 = 176 = \xB0
        (▒) = 2 = 177 = \xB1
        (▓) = 3 = 178 = \xB2
        (█) = 4 = 219 = \xDB
*/
#endif // GRAPHIC_H
