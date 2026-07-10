#ifndef CAR_H
#define CAR_H

#include <raylib.h>

typedef struct Wheel
{
    Vector2 position;
    Vector2 velocity;
    float radius;
    float padding;
    float stiffness;
    float damping;
    float offset;
    Vector2 attachment_point; 
    bool on_ground;
} Wheel;

typedef struct Car
{
    Vector2 position;
    Vector2 velocity;
    int width;
    int height;
    Wheel back_wheel;
    Wheel front_wheel;
    float angle;
} Car;


Car car_init(Vector2 start_position, int width, int height);

void car_control(Car *car, float dt);
void car_rotate(Car *car, float dt);
void car_move(Car *car, float dt);
void car_apply_suspension(Car *car, Wheel *wheel, float dt);
void wheel_move(Wheel *wheel, float dt);

void car_draw(Car *car);

#endif
