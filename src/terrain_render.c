#include "terrain.h"

void terrain_draw(Vector2 terrain[], int terrain_count)
{
    Color dirtColor = (Color){194, 155, 104, 255}; 
    Color grassColor = (Color){50, 168, 82, 255};  

    float bottom_y = 3000.0f;

    for (int i = 1; i < terrain_count; i++)
    {
        Vector2 point1 = terrain[i - 1];
        Vector2 point2 = terrain[i];

        Vector2 bottom_left = {point1.x, bottom_y};
        Vector2 bottom_right = {point2.x, bottom_y};

        DrawTriangle(point1, bottom_left, bottom_right, dirtColor);
        DrawTriangle(point1, bottom_right, point2, dirtColor);

        DrawLineEx(point1, point2, 15.0f, grassColor);
    }
}