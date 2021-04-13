#include "global.h"
#include "graphic.h"
#include "analyses.h"
#include "debugging.h"
#include "parameter.h"
#include "snake.h"

void menuBackground()
{

    programStatus.demoCounter = 0;
    while(programStatus.leave)
    {
        if ((programStatus.demoCounter==5)&&(snake.live==dead))
        {
            programStatus.demo=true;
            game(&programStatus);
            programStatus.demoCounter = 0;
        }
        // for for zebra frame
        for(volatile int i = 0; i < 24; i++)
        {
            if(programStatus.counter<50)
            {
                do
                    replace('X','\xB2',MenuBackground,'r');
                while(repeat);
            }
            iW = W;
            iH = H;
            arrcpy(output,MenuBackground);
            initialize('\x06',outputColor);
            zebra(i,output);

            int CASE;
            if (programStatus.counter < 50)
                CASE = 0;
            else
                CASE = 1;

            switch(CASE)
            {
            case 0:
                // Tasten werden erklärt

                // Weiße Schrift
                w=3;
                wd=3;
                h=10;
                hd=10;
                initialize('\x0F',outputColor);

                if(keyFlush(0)=='\x1B')
                    programStatus.counter = 50;
                iW = W;
                iH = H;
                w = 1;
                h = 10;
                wd = 1;
                hd = 10;
                arrcpy(output,MenuSymbolText);
                break;
            case 1:
                switch(menu(&programStatus))
                {
                case 1:
                    // continue
                    if((programStatus.gameNew==true)||(programStatus.trigger == '\x1B'))
                        break;
                    game(&programStatus);
                    if(programStatus.leave == false)
                        return;
                    BestList(&snake,true);
                    break;
                case 2:
                    // new game
                    programStatus.demo=false;
                    programStatus.gameNew=true;
                    game(&programStatus);
                    if(programStatus.leave == false)
                        return;
                    BestList(&snake,true);
                    BestList(&snake,false);
                    break;
                case 3:
                    // best list
                    BestList(&snake,false);
                    break;
                case 4:
                    programStatus.counter=0;
                    // symbols
                    break;
                case 5:
                    // exit game
                    programStatus.leave = false;
                    return;
                default:
                    break;

                }
            default:
                break;

            }
            monitoring(outputColor,output);
            programStatus.counter++;
            timer(50);
        }
        if(snake.live==dead);
        programStatus.demoCounter++;
    }
    return;
}
