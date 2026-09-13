#ifndef GAMEOVER_H
#define GAMEOVER_H

#include <raylib.h>

typedef enum
{
    GAMEOVER_NONE,
    GAMEOVER_RESTART,
    GAMEOVER_HOME
} GameOverChoice;

GameOverChoice gameover_update_and_draw(Font font, int window_width, int window_height);

#endif