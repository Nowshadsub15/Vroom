#include "camera.h"
#include <math.h>

#define CAMERA_ZOOM_MAX 1.3
#define CAMERA_ZOOM_MIN 0.5
#define CAMERA_ZOOM_SPEED 1.0

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
    
    float target_zoom = CAMERA_ZOOM_MAX; 

    if (speed > 3.0f) 
    {
        target_zoom = CAMERA_ZOOM_MAX - ((speed - 3.0) / 15.0); 
    }

    if (target_zoom > CAMERA_ZOOM_MAX) target_zoom = CAMERA_ZOOM_MAX;
    if (target_zoom < CAMERA_ZOOM_MIN) target_zoom = CAMERA_ZOOM_MIN;

    camera->zoom += (target_zoom - camera->zoom) *CAMERA_ZOOM_SPEED*dt; 
    
}
