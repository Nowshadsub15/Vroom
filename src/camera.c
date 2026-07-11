#include "camera.h"

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

void camera_update(Camera2D *camera, Vector2 target, float velocity_x)
{
    camera->target = target;
    camera->zoom = 1.3 - velocity_x / 10;
    if( camera->zoom > 1.3 ) {
        camera->zoom = 1.3;
    }
    if( camera->zoom < 1 ) {
        camera->zoom = 1;
    }
}
