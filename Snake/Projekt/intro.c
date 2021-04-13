#include "snake.h"
#include "global.h"
#include "graphic.h"
#include "analyses.h"
#include "parameter.h"

char output [H][W];
char outputColor [H][W];
void intro()
{
    creature mouse1;

    // Hintergrund Schlange
    file("images\\backgroundIntro.txt",backgroundIntro,"r");
    asciiConvert(backgroundIntro);
    // Hintergrundfarbe
    file("images\\backgroundIntroColor.txt",backgroundIntroColor,"r");

    do
        replace('0',15,backgroundIntroColor,'i');
    while(repeat);
    do
        replace('0','\x06',backgroundIntroColor,'r');
    while(repeat);
    // Darstellung
    iW = W;
    iH = H;
    arrcpy(output,backgroundIntro);





    iW = W;
    iH = H;
    arrcpy(REPLACE,forest);
    do
        replace(' ',0,output,'r');
    while(repeat);







    iW = W;
    iH = H;
    arrcpy(outputColor,backgroundIntroColor);
    monitoring(outputColor,output);
    // Verzögerung

    // 1000 ms / Escape
    keyTimer(50,20,'\x1B');

    mousePrint(outputColor,output,&mouse1);
    monitoring(outputColor,output);

    // 200 ms / Escape
    keyTimer(50,4,'\x1B');

    // Hintergrundtext
    file("images\\backgroundIntroText.txt",backgroundIntroText,"r");
    file("images\\backgroundIntroTextMask.txt",backgroundIntroTextMask,"r");
    asciiConvert(backgroundIntroText);
    mH = 30;
    mW = 120;
    cut(backgroundIntroTextMask,'0',backgroundIntroText,output);
    mH = 30;
    mW = 120;
    cut(backgroundIntroTextMask,'0',backgroundIntroTextMask,outputColor);
    do
        replace('0','\x4',outputColor,'r');
    while(repeat);

    // Darstellung
    monitoring(outputColor,output);
    // Verzögerung

    // 500 ms / Escape
    keyTimer(50,10,'\x1B');

    // Hintergrundtext 2
    // Darstellung
    iW = W;
    iH = H;
    arrcpy(output,backgroundIntroText);
    initialize('\x04',outputColor);
    monitoring(outputColor,output);

    // 1000 ms / Escape
    keyTimer(50,20,'\x1B');

    return;
}

