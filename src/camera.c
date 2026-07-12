#include "camera.h"
#include <math.h>

Camera2D camera_init(int window_width, int window_height)
{
    Camera2D camera = {
        .offset = (Vector2) {window_width / 2, window_height / 2},
        .target = (Vector2) {0, 0},
        .rotation = 0,
        .zoom = 1,
    };

    return camera;
}

void camera_update(Camera2D *camera, Vector2 target, float velocity_x, float dt) 
{
    camera->target = target;

    float speed = fabsf(velocity_x);
    
    float target_zoom = 1.3f; 

    if (speed > 3.0f) 
    {
        target_zoom = 1.3f - ((speed - 3.0f) / 15.0f); 
    }

    if (target_zoom > 1.3f) target_zoom = 1.3f;
    if (target_zoom < -4.0f) target_zoom = -4.0f;
    float zoom_speed = 2.0f ; 

    camera->zoom += (target_zoom - camera->zoom) *zoom_speed*dt; 
}
