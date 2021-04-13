#include "analyses.h"
#include "global.h"
#include "graphic.h"

void db(int ms, char* error)
{
    printf("<%i ms - text: %s>",ms, error);
    timer(ms);
    return;
}

void keytest()
{
    int i;
    while(1)
    {
    i = getch();
    printf("int: %i   hex: %X   char: %c\n",i,i,i);
    }
    return;
}

void colortest()
{
    color(240);
    while(1)
    {
        printf("press any key");
        for (int i = 0; i <= 256; i++)
        {
            color(i);
            printf("%i   %X   \n",i,i);
            getch();
        }
    }
    return;
}
