#ifndef PARAMETER_H
#define PARAMETER_H



char keyFlush(int ms);
bool intervall(float input,float min, float max);
float parameter(char type, float min, float max, char* error);
char Xparameter(char* Array, char* error, bool line, int Cy, int ty);
void keyTimer(int ms,int multiplier,char key);

typedef struct
{
    short x;
    short y;
} textCoord;

typedef struct {
char text [W];
int lenght;
bool tooLong;
bool INIT;
char CURSOR;
int index;
textCoord C;
} info;
void enterText(info* Text);

float generator(float y, float start, float end,char *sprache);
char compare(char* Array, char sample);

#endif // PARAMETER_H

