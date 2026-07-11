#include "terrain.h"

void terrain_draw(Vector2 terrain[], int terrain_count)
{
    for( int i = 1; i < terrain_count; i++ ) {
        Vector2 point1 = terrain[i-1];
        Vector2 point2 = terrain[i];

        DrawLineEx( point1, point2, 5, BLACK );
    }
}
