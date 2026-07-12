#ifndef CAMERA_H
#define CAMERA_H

#include <raylib.h>

Camera2D camera_init(int window_width, int window_height);
void camera_update(Camera2D *camera, Vector2 target, float velocity_x, float dt);

#endif
