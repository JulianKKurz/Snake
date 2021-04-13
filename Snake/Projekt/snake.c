#include "snake.h"
#include "global.h"
#include "graphic.h"
#include "analyses.h"
#include "parameter.h"
#include <time.h>

char SKIN [H*W];
char snakeHead [0][W];

void snakeInit(creature* s)
{
    srand(time(NULL));
    file("images\\snakeHead.txt",snakeHead,"r");
    asciiConvert(snakeHead);

    s->head.x=60;
    s->head.y=15;
    s->xFaktor=1;
    s->yFaktor=0;
    s->step=0;
    s->live=allive;
    s->food=1;

    for(int i=0; i<H*W; i++)
    {
        if(rand()%11==0)
            SKIN [i] = '\xB0';
        else if (rand()%7==0)
            SKIN [i] = '\xB1';
        else if(rand()%3==0)
            SKIN [i] = '\xB2';
        else if(rand()%2==0)
            SKIN [i] = ' ';
        else
            SKIN [i] = '\xDB';
    }
}

void Snake(creature* s, creature* m)
{
    static char key;
    static int speed;

    if(programStatus.demo==false)
        key = keyFlush(0);
    else
        key=AI(s,m,rand()%5);

    if (speed == 0)
        speed = 1;
// die Position des Wurms
// in welche Richtung will er laufen
// er kann nicht gegen sich laufen

    if (programStatus.demo==false)
    {
        if (key == 32)
            speed = 0.5;
        else
            speed = 1;
    }

    switch(key)
    {
    case '\x1B':        // esc
        programStatus.counter = 50;
        programStatus.trigger = '\x1B';
        menuBackground();
        break;
    //L
    case 75:
        if (s->xFaktor == 1)
            break;
        s->xFaktor = -1;
        s->yFaktor = 0;
        break;
    //UP
    case 72:
        if (s->yFaktor == 1)
            break;
        s->xFaktor = 0;
        s->yFaktor = -1;
        break;
    //R
    case 77:
        if (s->xFaktor == -1)
            break;
        s->xFaktor = 1;
        s->yFaktor = 0;
        break;
    //DOWN
    case 80:
        if (s->yFaktor == -1)
            break;
        s->xFaktor = 0;
        s->yFaktor = 1;
        break;
    default:
        break;
    }


    if ((keyFlush(0) ==  '\x1B')&&(programStatus.demo==true)) //esc
    {
        programStatus.counter = 50;
        programStatus.trigger = '\x1B';
        menuBackground();
    }



    // wohin will er laufen
    s->head.x += s->xFaktor;
    s->head.y += s->yFaktor;

    // wo kommt er an
    if (s->head.y == -1)
        s->head.y = H-1;
    else if (s->head.y == H)
        s->head.y = 0;

    if (s->head.x == -1)
        s->head.x = W-1;
    else if (s->head.x == W)
        s->head.x = 0;

    // Abfrage ob es eine Kollision gab
    for(int i=s->step-8*s->food; i<s->step; i++)
    {
        if((s->head.x == s->body.xx[i]))
            if((s->head.y == s->body.yy[i]))
            {
                s->live = dead;
                if(programStatus.demo==false)
                printf("\a");
            }
    }


    s->body.xx[s->step]=s->head.x;
    s->body.yy[s->step]=s->head.y;

    // Wie ist seine Gesundheit und wie sieht er aus
    if(s->live==dead)
    {
        for(int i=0; i<s->step; i++)
        {
            s->skinColor[i]='\x40';
            s->skin[i]=' ';
        }
    }
    else
    {
        for(int i=0; i<s->step; i++)
        {
            s->skinColor[i]='\xF0';
        }

        int STRLEN = strlen(SKIN);

        for(int j=s->step; j>s->step-STRLEN; j--)
        {
            if(j > 0)
                s->skin[j]=SKIN[s->step-j];
        }
        STRLEN = strlen(snakeHead[0]);


        for(int j=s->step; j>s->step-STRLEN; j--)
        {
            if(j > 0)
                s->skin[j]=snakeHead[0][s->step-j];
        }

    }

    if(s->xFaktor!=0)
        timer(speed*50);
    else
        timer(speed*100);
    return;
}


// shur, you can make it better ;)
char AI (creature* s, creature* m,int random)
{
    int key;
    switch (random)
    {
    case 1:
        if (s->head.x-7 > m->head.x)
            key = 75; // left;
        break;
    case 2:
        if (s->head.y-4 > m->head.y)
            key = 72; // up;
        break;
    case 3:
        if (s->head.x-7 < m->head.x)
            key = 77; // right;
        break;
    case 4:
        if(s->head.y-4 < m->head.y)
            key = 80; // down;
        break;
    default:
        break;
    }
    return key;
}
