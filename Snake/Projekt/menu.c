#include "snake.h"
#include "global.h"
#include "graphic.h"
#include "analyses.h"
#include "parameter.h"
char MenuText [H][W];
char output [H][W];
char outputColor [H][W];
char menu(program* programStatus)
{

    // sagt Programm soll bisschen warten nach counter Ringabe
    static int counter;
    static char key;
    static int positionMenu;
    iW = W;
    iH = H;
    w = 1;
    h = 12;
    wd = 1;
    hd = 12;
    arrcpy(output,MenuText);

    w = 12;
    h = 14;
    wd = 12;
    hd = 15;
    initialize('\x6F',outputColor);

    // Wurde eine Taste gedrückt?
    // default
    if (counter == 0)
    {
        if(positionMenu == 0)
            positionMenu = 2;

        key = keyFlush(0);

        // continue ausblenden
        if(programStatus->gameNew==true)
        {
            w = 12;
            wd = 88;
            h = 14;
            hd = 15;
            initialize(' ',output);
        }

        switch(key)
        {
        case '\x1B':    // Escape
            if(programStatus->trigger == '\x1B')
                break;
            return 1;
        case 75:
            positionMenu--;
            break;
        case 77:
            positionMenu++;
            break;
        default:
            programStatus->trigger = 0;
            break;
        }
        if(positionMenu == 0)
            positionMenu = 5;
        if(positionMenu == 6)
            positionMenu = 1;
    }

    switch(positionMenu)
    {
    // Continue
    case 1:
        w = 12;
        wd = 88;
        break;
    // new game
    case 2:
        w = 12+19;
        wd = 88-19;
        break;
    // best list
    case 3:
        w = 12+19*2;
        wd = 88-19*2;
        break;
    // Symbols
    case 4:
        w = 12+19*3;
        wd = 88-19*3;
        break;
    // Exit Game
    case 5:
        w = 12+19*4;
        wd = 88-19*4;
        break;
    default:
        break;
    }
    h = 14;
    hd = 15;

    // Bedingung mit counter
    if (key == '\x0D')
        counter++;


    // Vor Enter: Abfrage nach Enter
    if (counter == 0)
    {
        initialize('\xF6',outputColor);
        return -1;
    }

    // Verhalten vor Weiterleitung
    if (counter < 5)
    {
        initialize('\xC7',outputColor);
        counter++;
        return -1;
    }
    counter = 0;

    key = 0;
    w = 0;
    h = 0;
    wd = 0;
    hd = 0;

    programStatus->demoCounter = 0;
    return positionMenu;
}
