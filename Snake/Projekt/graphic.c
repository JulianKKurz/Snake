#include "global.h"
#include "graphic.h"

// Deklariert in "global.h"
int mW = 0;
int mH = 0;
int wp = 0;
int hp = 0;
int h = 0;
int w = 0;
int hd = 0;
int wd = 0;
bool repeat = 0;
int marker = -1;


void ascii()
{
    for(int i=0; i<255; i++)
    {
        printf("char: %c int: %i hex: %X",i,i,i);
        getchar();
    }
    return;
}



void graphic1(int start, int max, int length, char string [], char A, char B)
{
    char dummy [length];
    int compare;
    int i = start;
    if (i <= 0)
    {
        // initialize
        for (; i < length;)
        {
            // parts
            compare = i;
            for (; (i < length) && (i < (compare+max)); i++)
                // part A
                dummy[i]=A;
            compare = i;
            for (; (i < length) && (i < (compare+max)); i++)     //
                // part B
                dummy[i]=B;
        }
        dummy[i]='\0';
    }
    strcpy(string,dummy);
    return;
}



void replace(char replace, char input, char (*output)[W], char task)
{


    if (marker == -1)
    {
        marker = w;
        repeat = 1;
    }
    if  ((w >= W-wd)&&(h >= H-hd-1))
    {
        h = 0;
        w = 0;
        hd = 0;
        wd = 0;
        marker = -1;
        repeat = 0;
        return;
    }
    if (input == 0)
        switch(task)
        {
        case 'i':   // i = invert  0 TRUE
            if (output[h][w] != replace)     // invert replace}
                output[h][w] = REPLACE[h][w];
            break;
        case 'r':  //   r = replace    0 = TRUE
            if (output[h][w] == replace)     // replace replace}
                output[h][w] = REPLACE[h][w];
            break;
        default:
            printf("task missing");
            getchar();
            break;
        }
    else
        switch(task)
        {
        case 'i':   // i = invert  0 TRUE
            if (output[h][w] != replace)     // invert replace}
                output[h][w] = input;
            break;
        case 'r':  //   r = replace    0 = TRUE
            if (output[h][w] == replace)     // replace replace}
                output[h][w] = input;
            break;
        default:
            printf("task missing");
            getchar();
            break;
        }
    if (w <= W-wd)
        w++;
    if ((w == W-wd)&&(h != H-hd-1))
    {
        w = marker;
        h++;
    }
}



void initialize (char input, char (*output)[W])
{
    for (int i = h; i < H-hd; i++)
        for (int j = w; j < W-wd; j++)
            if (output[i][j] != input)
                output[i][j] = input;
    w = 0;
    h = 0;
    wd = 0;
    hd = 0;
    return;
}

char* strGen(char Char,int j)
{

    char *string = calloc(j,sizeof(char)+1);
    for(int k = 0; k < j; k++)
        string [k] = Char;
    return string;
}


void monitoring (char COLOR [H][W], char CHAR[H][W])
{
    cursor(false);
    // Zellendaten: Farbe + Zeichen
    CHAR_INFO gridbuffer[H][W];
    // Rahmen: {X Anfang, Y Anfang, X Ende Y Ende}
    COORD zerozero= {0,0},gridsz= {W,H};
    // Verschiebung Textur:  zerozero= {X Anfang,Y Ende}, gridsz= {X Ende,Y Ende};
    SMALL_RECT gridrect= {0,0,W,H};
    HANDLE out;
    out=GetStdHandle(STD_OUTPUT_HANDLE);
    for(int i=0; i<H; i++)
        for(int j=0; j<W; j++)
        {
            gridbuffer[i][j].Char.AsciiChar=CHAR[i][j];
            gridbuffer[i][j].Attributes=(unsigned char)COLOR[i][j];
        }
    WriteConsoleOutput(out,*gridbuffer,gridsz,zerozero,&gridrect);
    return;
}




void cut(char (*mask)[mW], char attribute, char (*texture)[mW], char (*output)[W])
{
    if((mH == 0)||(mW == 0))
    {
        printf("mask size missing:\n\nmH =;\nmW =;");
        getch();
    }

    for (int i = h; i < mH-hd; i++)
    {
        for (int j = w; j < mW-wd; j++)
        {
            if (mask[i][j]==attribute)
                output[i+hp][j+wp]=texture[i][j];
        }
    }
    mW = 0;
    mH = 0;
    wp = 0;
    hp = 0;
    w = 0;
    h = 0;
    wd = 0;
    hd = 0;
    return;
}

char* ArrToStr(char (*Array)[W], int i)
{
    char* string = calloc(W,sizeof(char)+1);
    for(int k = 0; k < W; k++)
        string [k] = Array[i][k];
    return string;
}

int iW = 0;
int iH = 0;
int oW = 120;
int oH = 30;
void arrcpy(char output [oH][oW],char input [iH][iW])
{
    // error
    if ((iW <= 0)||(iH <= 0))
    {
        printf("definitions missing; \ndefine: \niW = sizeof(input[0]);\niH = sizeof(input)/sizeof(input[0]);");
        getchar();
    }
    // error
    for (int i = h; (i < (iH-hd))&(i < oH-hp); i++)
        for (int j = w; (j < (iW-wd))&(j < oW-wp); j++)
            if ((j+hp >= 0)&(i+wp >= 0))
                output [i+hp][j+wp] = input[i][j];
    hp = 0;
    wp = 0;
    iW = 0;
    iH = 0;
    oW = 120;
    oH = 30;
    w = 0;
    h = 0;
    wd = 0;
    hd = 0;
    return;
}

int edge (char* string, int j)
{
    for (; j <= strlen(string); j++)
        if ((string[j] != string[j+1])||(string[j] == strlen(string)-1))
            return j;
    return -1;
}

void windowsize(int Y,int X,char task)
{
    COORD c;

    HANDLE wHnd;    // Handle to write to the console.

    if (task == 'w')
        system("mode 1000");
    if (task == 's')
    {
        c.X = X;
        c.Y = Y;
        SetConsoleScreenBufferSize( GetStdHandle( STD_OUTPUT_HANDLE ), c );
    }
    if ((task == 'w')||(task == 's'))
    {
        // Set up the handles for reading/writing:
        wHnd = GetStdHandle(STD_OUTPUT_HANDLE);
        // Set up the required window size:
        SMALL_RECT windowSize = {0, 0, X-1, Y-1};
        SetConsoleWindowInfo(wHnd, 1, &windowSize);
    }
    if ((task == 'w')||(task == 's')||(task == 'b'))
    {
        // Change the console window size:
        // Create a COORD to hold the buffer size:
        COORD bufferSize = {Y,X};
        SetConsoleScreenBufferSize(wHnd, bufferSize);
        // Exit

        c.X = X;
        c.Y = Y;
        SetConsoleScreenBufferSize( GetStdHandle( STD_OUTPUT_HANDLE ), c );
    }
    else
        printf("task missing");
}

void sign (int art, int k)
{
    switch (art)
    {
    case 1:
    {
        if (k == 1)
            printf("\xC9");
        if (k == 2)
            printf("\xDA");
    }
    break;
    case 2:
    {
        if (k == 1)
            printf("\xCD");
        if (k == 2)
            printf("\xC4");
    }
    break;
    case 3:
    {
        if (k == 1)
            printf("\xBB");
        if (k == 2)
            printf("\xBF");
    }
    break;
    case 4:
    {
        if (k == 1)
            printf("\xBA");
        if (k == 2)
            printf("\xB3");
    }
    break;
    case 5:
    {
        if (k == 1)
            printf("\xCE");
        if (k == 2)
            printf("\xC5");
    }
    break;
    case 6:
    {
        if (k == 1)
            printf("\xBA");
        if (k == 2)
            printf("\xB3");
    }
    break;
    case 7:
    {
        if (k == 1)
            printf("\xC8");
        if (k == 2)
            printf("\xC0");
    }
    break;
    case 8:
    {
        if (k == 1)
            printf("\xCD");
        if (k == 2)
            printf("\xC4");
    }
    break;
    case 9:
    {
        if (k == 1)
            printf("\xBC");
        if (k == 2)
            printf("\xD9");
    }
    break;
    case 88:
    {
        if (k == 1)
            printf("\xCA");
        if (k == 2)
            printf("\xC1");
    }
    break;
    case 44:
    {
        if (k == 1)
            printf("\xCC");
        if (k == 2)
            printf("\xC3");
    }
    break;
    case 22:
    {
        if (k == 1)
            printf("\xCB");
        if (k == 2)
            printf("\xC2");
    }
    break;
    case 66:
    {
        if (k == 1)
            printf("\xB9");
        if (k == 2)
            printf("\xB4");
    }
    break;
    default:
        break;
    }
}

void cursor (bool cursor)
{
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO info;
    info.dwSize = 100;
    info.bVisible = cursor;
    SetConsoleCursorInfo(hConsole, &info);
}

void color (unsigned char color)
{
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO info;
    info.dwSize = 100;
    SetConsoleCursorInfo(hConsole, &info);
    SetConsoleTextAttribute(hConsole, color);
}

int string = 0;
int width = 0;
int hight = 0;
unsigned char class = '\xDB';
void table (char dataArray [hight][width][string])
{
    if ((hight==0)||(width==0)||(string==0))
        printf("parameters missing:\n\nstring = sizeof(dataArray[0][0]);\nwidth = sizeof(dataArray[0])/string;\nhight = sizeof(dataArray)/(string*width);\n\n");
    if (class < 33)
    {
        printf("class missing:\n\nclass '1' \xCE\n\nclass '2' \xC5\n\n");
        class = '\xDB';
    }
    char above,left,middle,aboveCorner,belowCorner,leftCorner,rightCorner,aboveLeftCorner,aboveRightCorner,belowLeftCorner,belowRightCorner;

    switch(class)
    {
    case '1':
        above = '\xCD';
        left = '\xBA';
        middle = '\xCE';

        aboveCorner = '\xCB';
        belowCorner = '\xCA';
        leftCorner = '\xCC';
        rightCorner = '\xB9';

        aboveLeftCorner = '\xC9';
        aboveRightCorner = '\xBB';
        belowLeftCorner = '\xC8';
        belowRightCorner = '\xBC';
        break;
    case '2':
        above = '\xC4';
        left = '\xB3';
        middle = '\xC5';

        aboveCorner = '\xC2';
        belowCorner = '\xC1';
        leftCorner = '\xC3';
        rightCorner = '\xB4';

        aboveLeftCorner = '\xDA';
        aboveRightCorner = '\xBF';
        belowLeftCorner = '\xC0';
        belowRightCorner = '\xD9';
        break;
    default:
        above = class;
        left = class;
        middle = class;

        aboveCorner = class;
        belowCorner = class;
        leftCorner = class;
        rightCorner = class;

        aboveLeftCorner = class;
        aboveRightCorner = class;
        belowLeftCorner = class;
        belowRightCorner = class;
        break;
    }

    printf("%c",aboveLeftCorner);
    for(int j=0; j<width; j++)
    {
        for(int j=0; j<string; j++)
            printf("%c",above);
        if(j<width-1)
            printf("%c",aboveCorner);
    }
    printf("%c\n",aboveRightCorner);
// |data|data|data|data|
// |----|----|----|----|
    for(int i=0; i<hight; i++)
    {
        for(int j=0; j<width; j++)
        {
            // |data|data|data|data|
            printf("%c",left);
            for(int c=0; c<string; c++)
                printf("%c",dataArray[i][j][c]);
            if (j == width-1)
                printf("%c\n",left);
        }
        // |----|----|----|----|
        if(i <hight-1)
        {
            printf("%c",leftCorner);
            for(int j=0; j<width; j++)
            {
                for(int j=0; j<string; j++)
                    printf("%c",above);     //-
                if (j < width-1)
                    printf("%c",middle);     //+
            }
            if(i < hight-1)
                printf("%c\n",rightCorner);
        }
    }
    // |____|____|____|____|
    printf("%c",belowLeftCorner);
    for(int j=0; j<width; j++)
    {
        for(int j=0; j<string; j++)
            printf("%c",above);
        if(j<width-1)
            printf("%c",belowCorner);
    }
    printf("\%c\n",belowRightCorner);
    //reset
    string = 0;
    width = 0;
    hight = 0;
    return;
}

void line (int l)
{
    for(; l > 0 ; l--)
        printf("\n");
}

void space (int s)
{
    for(; s > 0 ; s--)
        printf(" ");
}

void center(char*text,int string)
{
    if (strlen(text) > W)
    {
        for(int i=0; i <= strlen(text)/W; i++)
            center(stringSelect(text,W,i),1);
    }
    else
    {
        for (; string > 0; string--)
            printf("\n");
        for (int space = (W-strlen(text))/2; space > 0; space--)
            printf(" ");
        printf("%s",text);
    }
    return;
}

void arraySprintf(char *text, char *output,char task)
{
    int d;

    switch(task)
    {
    case 'c':
        d = (W-strlen(text))/2;
        break;
    case 'r':
        d = 0;
        break;
    case 'l':
        d =     W-strlen(text);
        break;
    default:
        printf("task missing:   l   c   r");
        getch();
        break;
    }
    for (int i = 0; i < strlen(text)-wd; i++)
        output[i+w+d] = text [i];
    w = 0;
    return;
}

void centerStatic(char*text, int y)
{
    coord((W-strlen(text))/2,y);
    printf("%s",text);
    return;
}

void numberArray (char* text, float* Numbers, int elements, char* delimiter)
{
    text [0] = '\0';
    char* copy = calloc(elements*10, sizeof(char));        //          //char copy [elements];
    for(int i=0; i<elements; i++)
    {
        gcvt(Numbers[i],3, copy);
        strcat(text,copy);
        strcat(text,delimiter);
    }
    return;
}

void coord(int x,int y)
{
    COORD position= {0,0};
    HANDLE console;
    console=GetStdHandle(STD_OUTPUT_HANDLE);
    position.X=x;
    position.Y=y;
    SetConsoleCursorPosition(console,position);

    return;
}

char* stringSelect(char* text, int length, int index)
{
    char StringArray [1000][length];
    for (int i=0; i<strlen(text); i++)
        for (int j=0; j<W; j++)
        {
            StringArray[i][j] = text[(i*W)+j];
            if ((i)*(j+1)==strlen(text))
                return ArrToStr(StringArray,index);
        }
    return "index overflow";
}
//int C(char v)
//{
//    COORD position;
//    HANDLE console;
//    console=GetStdHandle(STD_OUTPUT_HANDLE);
//    if ((v - 'x' == 0)||(v - 'X' == 0))
//        return position.X;
//    if ((v - 'y' == 0)||(v - 'Y' == 0))
//        return position.Y;
//    else
//        return -1;
//}
int limit = 0;
bool errorText = true;
int file(char* directory, char (*Array)[W],char* mode)
{
    FILE* file;
    file = fopen(directory,mode);

    int i=0;
    char buffer[W+2];
    switch (mode[0])
    {
    case 'r':
        while (fgets(buffer,W+2,file) != NULL)
        {
            strcpy(Array[i],buffer);
            i++;
        }
        if (i < 1)
        {
            if(errorText)
            {
                printf("wrong directory or file missing: \"%s\"\nor file is empty",directory);
            getch();
            }
        }
        fclose(file);
        limit=0;
        return i;
        break;
    case 'a':
        //write
        for(int i=0; i<limit; i++)
            fprintf(file,Array[i]);
        break;
    case 'w':
        //write
        for(int i=0; i<limit; i++)
            fprintf(file,Array[i]);
        // fputs(Array[i],file);
        break;
    default:
        printf("wrong mode");
        getch();
        break;
    }
    fclose(file);
    limit=0;
    errorText = true;
    return -1;
}

// (1234 )
void asciiConvert(char (*output)[W])
{
    /*
            ( ) = 0 = 0   = 0
            (░) = 1 = 176 = \xB0
            (▒) = 2 = 177 = \xB1
            (▓) = 3 = 178 = \xB2
            (█) = 4 = 219 = \xDB
    */

    do
        replace('0',' ',output,'r');
    while(repeat);
    do
        replace('1','\xB0',output,'r');
    while(repeat);
    do
        replace('2','\xB1',output,'r');
    while(repeat);
    do
        replace('3','\xB2',output,'r');
    while(repeat);
    do
        replace('4','\xDB',output,'r');
    while(repeat);

    return;
}
