#include "terrain.h"
#include <math.h>
#include <string.h>

bool IsPointBelowLine(Vector2 a, Vector2 b, Vector2 point, Vector2 *collisionPoint) {
    if (fabs(b.x - a.x) > 1e-6) {
        float t = (point.x - a.x) / (b.x - a.x);
        if (t < 0.0f || t > 1.0f)
            return false;
        collisionPoint->x = point.x;
        collisionPoint->y = a.y + t * (b.y - a.y);
        return (point.y > collisionPoint->y);
    } else {
        if (fabs(point.x - a.x) > 1e-6)
            return false;
        collisionPoint->x = a.x;
        collisionPoint->y = fmax(a.y, b.y);
        return (point.y > collisionPoint->y);
    }
}

void terrain_generate(Vector2 terrain[],
                      int terrain_count,
                      int terrain_length,
                      int window_height)
{
    int pos = GetRandomValue(window_height * 0.7,
                             window_height * 0.95);

    for (int i = 0; i < terrain_count; i++)
    {
        terrain[i].x = i * terrain_length;
        terrain[i].y = pos;

        pos += GetRandomValue(-20,20);

        if(pos < window_height * 0.35)
            pos = window_height * 0.35;

        if(pos > window_height * 0.95)
            pos = window_height * 0.95;
    }
}




void terrain_shift(Vector2 terrain[], int terrain_count, int terrain_length, int shift_count)
{
    int keep_count = terrain_count - shift_count;

    memmove(terrain, terrain + shift_count, sizeof(Vector2) * keep_count);

    for(int i = 0; i < terrain_count; i++)
    {
        terrain[i].x = i * terrain_length;
    }

    Vector2 last = terrain[keep_count - 1];
    int window_height = GetScreenHeight() ;
    int base_y = GetScreenHeight()*0.7f; 

    for(int i = keep_count; i < terrain_count; i++)
    {
        int slope = GetRandomValue(-20, 20);

        if (last.y < base_y - 150) slope += 15;
        if (last.y > base_y + 150) slope -= 15; 

        last.y += slope;
        if (last.y < window_height * 0.35f) last.y = window_height * 0.35f;
        if (last.y > window_height * 0.95f) last.y = window_height * 0.95f;
        terrain[i].y = last.y;
        last = terrain[i];
    }
}