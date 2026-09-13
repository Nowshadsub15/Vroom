#ifndef TERRAIN_H
#define TERRAIN_H

#include <raylib.h>

#define TERRAIN_LENGTH 15
#define TERRAIN_COUNT 1012
#define CONTROL_STEP 23

float catmull_rom(float p0, float p1, float p2, float p3, float t) ;
bool IsPointBelowLine(Vector2 a, Vector2 b, Vector2 point, Vector2 *collisionPoint);
void terrain_generate(Vector2 terrain[], int window_height, float anchors[]);
void terrain_draw(Vector2 terrain[], int terrain_count);
void terrain_shift(Vector2 terrain[], int shift_count, float anchors[]);
#endif
