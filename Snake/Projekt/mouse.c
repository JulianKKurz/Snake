#include "snake.h"
#include "global.h"
#include "graphic.h"
#include "analyses.h"
#include "parameter.h"
#include <time.h>

void mouseInit()
{
    file("images\\mouse.txt",Mouse,"r");
    file("images\\mouseMask.txt",MouseMask,"r");
    asciiConvert(Mouse);
}

void mousePrint(char (*outputColor)[W], char (*output)[W],creature* mouse)
{
    int X = mouse->head.x + rand()%2;
    int Y = mouse->head.y + rand()%2;

    wp = X;
    hp = Y;
    mH=30;
    mW=120;
    cut(MouseMask,'x',Mouse,output);


    wp = X;
    hp = Y;

    mH=30;
    mW=120;
    cut(MouseMask,'x',MouseMask,outputColor);

    do
        if(mouse->live == allive)
            replace('x','\xF0',outputColor,'r');
        else
            replace('x','\x40',outputColor,'r');
    while(repeat);


    // das Herz
    output[mouse->head.y+4][mouse->head.x+7] = ' ';
    outputColor[mouse->head.y+4][mouse->head.x+7] = '\x40';
    return;
}

void mouseNewPos(creature* mouse,creature* snake)
{
    srand(time(NULL));
    do
    {
    mouse->head.x=rand()%80+20;
    mouse->head.y=rand()%20+5;
    }
    while(kollision(mouse,snake));

    return;
}
