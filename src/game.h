#ifndef GAME_H
#define GAME_H

#include "car.h"
#include "terrain.h"
#include "camera.h"

typedef struct GameState
{
    Car car;
    Vector2 terrain[TERRAIN_COUNT];
    Camera2D camera;
    Texture2D background;
} GameState;

GameState game_init(int window_width, int window_height);
void game_update(GameState *state, float dt);
void game_draw(GameState *state);

#endif
