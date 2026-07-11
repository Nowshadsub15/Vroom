#ifndef TERRAIN_H
#define TERRAIN_H

#include <raylib.h>

#define TERRAIN_LENGTH 100
#define TERRAIN_COUNT 255

bool IsPointBelowLine(Vector2 a, Vector2 b, Vector2 point, Vector2 *collisionPoint);
void terrain_generate(Vector2 terrain[], int terrain_count, int terrain_length, int window_height);
void terrain_draw(Vector2 terrain[], int terrain_count);

#endif
