#ifndef SNAKE_H
#define SNAKE_H
#include "global.h"

#define dead 0
#define allive 1

char forest [H][W];
char output [H][W];
char outputColor [H][W];
char MenuBackground [H][W];
char MenuSymbolText [H][W];
char MenuText [H][W];
char Mouse [H][W];
char MouseMask [H][W];
char bestList [6][W];
char backgroundIntro [H][W];
char backgroundIntroColor [H][W];
char backgroundIntroText [H][W];
char backgroundIntroTextMask [H][W];

typedef struct
{
    short x;
    short y;
    short xx [H*W];
    short yy [H*W];
} Coord;

typedef struct
{
    int counter;
    bool leave;
    bool gameNew;
    bool demo;
    int demoCounter;
    char trigger;
} program;

program programStatus;

typedef struct
{
    Coord head;
    Coord body;
    int xFaktor;
    int yFaktor;
    int step;
    bool live;
    char skin [H*W];
    char skinColor [H*W];
    int food;
    char name [20];
} creature;

creature snake;
creature mouse;

void intro();
void menuBackground();
char menu(program* programStatus);
void game(program* programStatus);
void snakeInit(creature* s);
void Snake(creature* s,creature* m);
void mouseInit();
void mousePrint(char (*outputColor)[W], char (*output)[W], creature* mouse);
void mouseNewPos(creature* mouse,creature* snake);
void zebra(int step,char (*output)[W]);
void init();
bool kollision(creature* mouse, creature* snake);
void BestList(creature* snake, bool update);
char AI (creature* s, creature* m,int random);

#endif // SNAKE_H
