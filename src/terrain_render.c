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
        
        DrawCircleV(point1, 8, grassColor) ;
        DrawCircleV(point2, 8, grassColor) ;

        DrawLineEx(point1, point2, 16.0, grassColor);
    }
    //DrawSplineCatmullRom(terrain, TERRAIN_COUNT, 15.0, grassColor);
}
void terrain_draw_anchors(float anchors[], int num_anchors)
{
    Color anchorColor = (Color){255, 0, 0, 255}; // red, easy to spot

    for (int i = 0; i < num_anchors; i++)
    {
        float x = i * CONTROL_STEP * TERRAIN_LENGTH;
        float y = anchors[i];

        DrawCircleV((Vector2){x, y}, 12, anchorColor);
        DrawText(TextFormat("%d", i), x - 8, y - 30, 16, BLACK); // optional index label
    }
}