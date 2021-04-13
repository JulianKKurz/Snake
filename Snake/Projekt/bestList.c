#include "snake.h"
#include "global.h"
#include "graphic.h"
#include "analyses.h"
#include "parameter.h"
#include <time.h>

void newValue(creature* snake);
void frame(int a, int b);


void BestList(creature* snake, bool update)
{
    errorText = false;
    int limitArray = file("bestList.txt",bestList,"r");
    if(update == true)
    {
        newValue(snake);
        limitArray = file("bestList.txt",bestList,"r");
        // if array full
        if(limitArray>16)
        {
            // remove last value
            for(int j=0; j<16; j++)
                strcpy(bestList[j],bestList[j+1]);
            limit = 16;
            file("bestList.txt",bestList,"w");
        }
    }
    else
    {
        frame(20,3);
// load updated file
        // visualisation
        monitoring(outputColor,output);
            color('\x0F');
            cursor(false);
            centerStatic("BESTLIST",6);

            for(int j=0; j<limitArray; j++)
            {
                if (j==16)
                    break;
                coord(30,8+j);
                printf("%s",bestList[j]);
            }
        while(keyFlush(0)!='\x1B');
    }
    return;
}


void newValue(creature* snake)
{
    FILE* NEW;
    NEW = fopen("bestList.txt","a");

    // write the time
    time_t timer;
    char TIME[26];
    struct tm* tm_info;

    timer = time(NULL);
    tm_info = localtime(&timer);
    strftime(TIME, 26, "%d.%m.%Y %H:%M", tm_info);

    // aktueller Wert
    int mice = snake->food-1;
    if (mice == 0)
        fprintf(NEW,"%17s: no mouse! Looser! \t%s\n",snake->name,TIME);
    else if (mice == 1)
        fprintf(NEW,"%17s: one mouse! Disgusting! \t%s\n",snake->name,TIME);
    else if (mice < 10)
        fprintf(NEW,"%17s: %i mice! Disgusting! \t%s\n",snake->name,mice,TIME);
    else if (mice < 20)
        fprintf(NEW,"%17s: %i mice! Not bad! \t%s\n",snake->name,mice,TIME);
    else if (mice < 30)
        fprintf(NEW,"%17s: %i mice! Very good! \t%s\n",snake->name,mice,TIME);
    else if (mice < 40)
        fprintf(NEW,"%17s: %i mice! Genius! \t%s\n",snake->name,mice,TIME);

    fclose(NEW);

}


void frame(int a, int b)
{
    // Rahmen
    initialize('\x60',outputColor);
    iW = W;
    iH = H;
    arrcpy(output,forest);
    w = a;
    h = b;
    wd = a;
    hd = b;
    initialize('\xB1',output);
    w = a+1;
    h = b+1;
    wd = a+1;
    hd = b+1;
    initialize(' ',output);
    w = a+1;
    h = b+1;
    wd = a+1;
    hd = b+1;
    initialize('\x0F',outputColor);
    return;
}
