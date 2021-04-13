#include "global.h"
#include "graphic.h"
#include "analyses.h"
#include "parameter.h"
#include <math.h>

char keyFlush(int ms)
{
    char k = -1;
    if (ms > 0)
        timer(ms);
    while(kbhit()!=0)
    {
        k = getch();
    }
    return k;
}

char text [120] = {0};
bool intervall(float input,float min, float max)
{
    bool output;

    if (((input >= min)&&(input <= max))||((input <= min)&&(input >= max)))
        output = true;
    else
        output = false;

    return output;
}

float parameter(char type, float min, float max, char* error)
{
    float p;
    bool typeTest = 0;
    cursor(true);
    color(240);
    do
    {
        p = 0;
        fflush(stdin);
        center("> ",1);
        switch(type)
        {
        case 'c':
        {
            char dummy = (char)p;
            typeTest = scanf("%c",&dummy);
            p = (float)dummy;
        }
        break;
        case 'i':
        {
            int dummy = (int)p;
            typeTest = scanf("%i",&dummy);
            p = (float)dummy;
        }
        break;
        case 'f':
        {
            typeTest = scanf("%f",&p);

        }
        break;
        default:
            printf("type missing\n");
            getchar();
            return 0;
        }
        if((intervall(p,min,max)&&typeTest)==true)
            break;
        else
        {
            cursor(true);
            color(252);
            sprintf(text,"%s",error);
            center(text,1);
        }
    }
    while(1);
    cursor(true);
    color(240);
    return p;
}

char compare(char* Array, char sample)
{
    for(int i = 0; i <= strlen(Array); i++)
        if(Array[i] == sample)
            return sample;
    return -1;
}

char Xparameter(char* Array, char* error, bool line, int Cy, int ty)
{
    char p;
    cursor(true);
    color(240);
    do
    {
        keyFlush(0);
        p = 0;
        if (line == true)
        {
            if (Cy<0)
                center("> ",1);
            else
                centerStatic("> ",Cy);
        }
        else
            centerStatic("",Cy);

        keyFlush(100);
        p = getch();
        printf("%c",p);

        if (compare(Array,p) == p)
            break;
        else
        {
            cursor(true);
            color(252);
            if (Cy<0)
                center(error,1);
            else if (Cy>=0)
                centerStatic(error,ty);
        }
    }
    while(1);
    cursor(true);
    color(240);
    return p;
}





void enterText(info* Text)
{
    cursor(false);
    static bool counter;
    static int index;
    char CHAR = -1;
    repeat = true;

    // initialisierung
    if(Text->INIT==true)
    {
        for(int k=0; k<Text->lenght; k++)
            Text->text[k]=0;
        Text->INIT = false;
    }
    else
        for(int i=0; i<10; i++) // cursor blink
        {
            CHAR = keyFlush(0);
            timer(50);

            if((CHAR != -1)&&!((CHAR == '\x08')&&(index==0)))
                break;
        }

    if (CHAR == '\x08')     // backspace
    {
        if (index>0)
        {
            index--;
            Text->text [index] = 0;
            counter = true;
        }
    }
    else if (CHAR == '\x0D')       // Eingabe
    {
        repeat=false;
    }
    else if((index<Text->lenght-1)&&(CHAR != -1))        // wenn nicht zu lang       und      eine legale Eingabe
    {
        Text->text[index] = CHAR;
        index++;
        counter = true;
    }

    if (repeat==true)
    {
        // cursor blink
        if (counter == true)
        {
            Text->CURSOR = ' ';
            counter = false;
        }
        else
        {
            Text->CURSOR = '\xDB';
            counter = true;
        }
    }
    else
        Text->text[index] = 0;
    Text->text[index+1] = 0;

    if (index>Text->lenght-2)
    {
        Text->tooLong = true;
    }
    else
        Text->tooLong = false;
    Text->index = index;
    if (CHAR == '\x0D')       // Eingabe
        index = 0;
    return;
}














float x = 0;
float min = 0;
float max = 0;
int reset = 0;

float generator(float y, float start, float end,char *sprache)
{
    char errorStart [120] = {0};
    char errorEnd [120] = {0};

    sprintf(errorStart,"Der Startwert muss grosser als %f.2 und kleiner als %f.2 sein. Bitte nochmal eingeben: ",start,end);
    sprintf(errorEnd,"Der Endwert muss grosser als %f.2 und kleiner als %f.2 sein. Bitte nochmal eingeben: ",start,end);

    if (reset != 0)
    {
        if (!intervall(y, -10000,10000)||!intervall(x,min,max))
        {
            if(!intervall(y, -10000,10000))
                printf("\t%10.5f     error\n",x);
            {
                reset = 0;
                return 0;
            }
        }
        else
        {
            printf("%10.5f   %10.5f\n",x,y);

            if(min>=max)
                x--;
            else
                x++;
        }
    }
    if (reset == 0)
    {
        system("cls");
        printf("Bitte gebe den Startwert ein: ");
        min = parameter('f', start,end,errorStart);
        printf("Bitte gebe den Endwert ein: ");
        max = parameter('f', start, end,errorEnd);
        x = min;
        reset = 1;
    }
    return x;
}

void keyTimer(int ms,int multiplier,char key)
{
    for(int i=0; i<multiplier; i++)
    {
        if(keyFlush(0)==key)
            return;
        timer(ms);
    }
    return;
}
