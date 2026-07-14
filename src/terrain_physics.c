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
    int pos = GetRandomValue(window_height * 0.35,
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
    int pos = last.y ;
    int max_height = window_height * 0.35 ;
    int min_hight = window_height * 0.95 ;
    int drag = 15 ;
    for (int i = keep_count; i < terrain_count; i++)
    {
        
        pos += GetRandomValue(-20,20);
        if(pos < max_height)
            pos = max_height;
        if(pos > min_hight)
            pos = min_hight;
        if(pos == max_height && terrain[i-1].y == max_height){
            pos += drag ;
        }    
        if(pos == min_hight && terrain[i-1].y == min_hight){
            pos -= drag ;
        }
        terrain[i].y = pos;
    }
}