#include "terrain.h"
#include <math.h>

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

void terrain_generate(Vector2 terrain[], int terrain_count, int terrain_length, int window_height)
{
    int pos = GetRandomValue( window_height * 0.7, window_height * 0.95 );
    for( int i = 0; i < terrain_count; i++ ) {
        int movement = GetRandomValue( -20, 20 );

        Vector2 point = {i * terrain_length, pos};
        terrain[i] = point;

        pos = pos + movement;
    }
}
