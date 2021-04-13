#include "global.h"
#include "graphic.h"

void zebra(int step,char (*output)[W])
{
    step = step%24;
    char string [120];
    // Rahmen wird eingeblendet
    // obere Zeile
    h = 1;
    w = 1;
    hd = 22;
    wd = 1;
    do
    {
        graphic1(-600-h+step,6,120,string,'\xDB','\xB0');
        replace('$',string[w],output,'i');
    }
    while(repeat);
    // untere Zeile
    h = 22;
    w = 1;
    hd = 1;
    wd = 1;
    do
    {
        graphic1(-h-step,6,120,string,'\xDB','\xB0');
        replace('$',string[w],output,'i');
    }
    while(repeat);
    // zweite Zeile
    h = 9;
    w = 1;
    hd = 20;
    wd = 1;
    do
    {
        graphic1(-9-step,12,120,string,'\xDB','\xB1');
        replace('$',string[w],output,'i');
    }
    while(repeat);
    // Vorletzte Zeile
    h = 20;
    w = 1;
    hd = 9;
    wd = 1;
    do
    {
        graphic1(-600-18+step,12,120,string,'\xDB','\xB1');
        replace('$',string[w],output,'i');
    }
    while(repeat);
    return;
}
