#include "snake.h"
#include "global.h"
#include "graphic.h"

void init()
   {
    mouseInit();
    file("images\\forest.txt",forest,"r");
    asciiConvert(forest);
    file("images\\MenuBackground.txt",MenuBackground,"r");
    file("images\\MenuSymbolText.txt",MenuSymbolText,"r");
    file("images\\MenuText.txt",MenuText,"r");
   }
