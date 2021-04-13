#include "snake.h"
#include "global.h"
#include "graphic.h"
#include "analyses.h"
#include "parameter.h"

bool kollision(creature* mouse, creature* snake)
{
    if((snake->head.x == mouse->head.x+7)&&(snake->head.y == mouse->head.y+4))
        return true;
    else
        return false;
}

void game(program* programStatus)
{
    // if new game
    if (programStatus->gameNew == true)
    {
        initialize('\x06',outputColor);
        snakeInit(&snake);
        mouse.live=allive;
        mouse.step=-1;
        mouseNewPos(&mouse,&snake);
        programStatus->gameNew=false;
        snake.food=1;

        if (programStatus->demo==false)
      {
        // Grafik
        iW = W;
        iH = H;
        arrcpy(output,backgroundIntroText);
        initialize('\x04',outputColor);

        monitoring(outputColor,output);
        color('\x0F');

            // Abfrage des Namens
        info name;
        name.lenght = 18;
        name.INIT = true;
        name.C.y = 24;
        name.C.x = 25;
        name.tooLong = false;
        do
        {
            system("cls");
            monitoring(outputColor,output);
            coord(name.C.x,name.C.y);
            printf("whats your name?: %s%c",name.text,name.CURSOR);
            if(name.tooLong)
            {
                coord(name.C.x,name.C.y+2);
                printf("the name is too long!");
            }
            enterText(&name);
        }
        while(repeat);

        if (name.index == 0)
           strcpy(snake.name,"SNAKE");
        else
        strcpy(snake.name,name.text);
      }
      else
      strcpy(snake.name,"AI");
    }

    while(1)
    {
        iH=H;
        iW=W;
        arrcpy(output,forest);
        initialize('\x06',outputColor);

        mousePrint(outputColor,output,&mouse);
        // Die Schlange
        Snake(&snake,&mouse);
        if(programStatus->leave==false)
            return;

        for(int i=snake.step-8*snake.food; i<snake.step; i++)
        {
            outputColor[snake.body.yy[i]] [snake.body.xx[i]] = snake.skinColor [i];
            output[snake.body.yy[i]] [snake.body.xx[i]] = snake.skin [i];
        }

        // Abfrage ob es eine Kollision gab
        // Was passiert wenn es eine Kollision gab
        if(kollision(&mouse,&snake))
        {
            mouse.live = dead;
            snake.food++;
            mouse.step = 10;
        }

        if(mouse.step==0)
        {
            mouseNewPos(&mouse,&snake);
            mouse.live = allive;
            mouse.step = -1;
        }
        else
            mouse.step--;



        monitoring(outputColor,output);

        // Punkte anzeigen

        coord(5,2);
        printf("mice %i:",snake.food-1);



        if (snake.live == dead)
        {
            programStatus->gameNew = true;
            return;
        }
        snake.step++;
    }
    return;
}
