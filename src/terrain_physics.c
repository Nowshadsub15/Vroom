#include "terrain.h"
#include <math.h>
#include <string.h>

bool IsPointBelowLine(Vector2 a, Vector2 b, Vector2 point, Vector2 *collisionPoint) {
    // Handle non-vertical segments.
    if (fabs(b.x - a.x) > 1e-6) {
        // Compute the parameter t from a to b using the x coordinate.
        float t = (point.x - a.x) / (b.x - a.x);
        // If t is not between 0 and 1, the vertical line does not intersect the segment.
        if (t < 0.0f || t > 1.0f)
            return false;
        // Compute the y-coordinate of the intersection on the segment.
        collisionPoint->x = point.x;
        collisionPoint->y = a.y + t * (b.y - a.y);
        // In raylib, a larger y means further down the screen.
        return (point.y > collisionPoint->y);
    } else {
        // For a vertical segment, the point must align with the segment's x value (within a tolerance).
        if (fabs(point.x - a.x) > 1e-6)
            return false;
        collisionPoint->x = a.x;
        // Use the lower end (largest y value) of the segment as the collision point.
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
    
    int base_y = 500; 

    for(int i = keep_count; i < terrain_count; i++)
    {
        int slope = GetRandomValue(-20, 20);

        if (last.y < base_y - 150) slope += 15;
        if (last.y > base_y + 150) slope -= 15; 

        last.y += slope;
        terrain[i].y = last.y;
        last = terrain[i];
    }
}