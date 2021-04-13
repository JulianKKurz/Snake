#include "snake.h"
#include "global.h"
#include "graphic.h"
#include "analyses.h"
#include "parameter.h"
#include "debugging.h"
#include <windows.h>

int main(void)
{

    printf("\a");

    programStatus.counter = false;
    programStatus.leave = true;
    programStatus.gameNew = true;
    programStatus.demo = false;
    snake.live = dead;

    init();
    do
    {
        SetConsoleTitle("Snake");
        windowsize(H,W,'w');

        intro();
        menuBackground();
    }
    while(programStatus.leave);
    return 0;
}
