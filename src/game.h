#ifndef GAME_H
#define GAME_H

#include "car.h"
typedef struct GameState
{
    Car car;
} GameState;

GameState game_init(int window_width, int window_height);
void game_update(GameState *state, float dt);
void game_draw(GameState *state);

#endif
