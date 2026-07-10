#include "car.h"
#include <raymath.h>

#define GRAVITY 12
#define ROTATION_SPEED 40
#define FRICTION 8
#define ROTATE_BACK_SPEED 15
#define CAR_SPEED 80

Car car_init(Vector2 start_position, int width, int height)
{
    Car car = {
        .position = start_position,
        .width = width,
        .height = height,
        .velocity = (Vector2){0, 0},
        .angle = 0,
    };

    car.back_wheel = (Wheel){
        .radius = 25,
        .padding = 10,
        .velocity = (Vector2){0, 0},
        .stiffness = 1.9,
        .damping = 1.2,
    };

    car.back_wheel.position = (Vector2){
        .x = car.position.x - car.width / 2 + car.back_wheel.radius + car.back_wheel.padding,
        .y = car.position.y + car.height / 2 + car.back_wheel.radius + car.back_wheel.padding,
    };

    car.front_wheel = (Wheel){
        .radius = 25,
        .padding = 10,
        .velocity = (Vector2){0, 0},
        .stiffness = 1.9,
        .damping = 1.2,
    };
    car.front_wheel.offset = car.width - car.back_wheel.radius - car.back_wheel.padding - car.front_wheel.padding - car.front_wheel.radius;
    car.front_wheel.position = (Vector2){
        .x = car.position.x + car.width / 2 - car.front_wheel.radius - car.front_wheel.padding,
        .y = car.position.y + car.height / 2 + car.front_wheel.radius + car.front_wheel.padding,
    };

    return car;
}

void car_control(Car *car, float dt)
{
    if (!car->back_wheel.on_ground && !car->front_wheel.on_ground)
    {
        if (IsKeyDown(KEY_LEFT))
        {
            car->angle += ROTATION_SPEED * dt;
        }
        else if (IsKeyDown(KEY_RIGHT))
        {
            car->angle -= ROTATION_SPEED * dt;
        }
    }
    if (IsKeyDown(KEY_RIGHT))
    {
        if (car->back_wheel.on_ground)
        {
            car->velocity.x += CAR_SPEED * dt;
        }
    }
    else if (IsKeyDown(KEY_LEFT))
    {
        if (car->front_wheel.on_ground)
        {
            car->velocity.x -= CAR_SPEED * dt;
        }
    }
}

void car_rotate(Car *car, float dt)
{
    if (car->back_wheel.on_ground && car->front_wheel.on_ground)
    {
        float angle = Vector2Angle(car->back_wheel.position, car->front_wheel.position);
        float diff = angle - car->angle;
        car->angle += diff * dt * ROTATE_BACK_SPEED;
    }
}

void car_move(Car *car, float dt)
{
    car->position.x += car->velocity.x;
    car->position.y += car->velocity.y;

    if (car->back_wheel.on_ground)
    {
        float friction = car->velocity.x * FRICTION;
        car->velocity.x -= friction * dt;
    }

    if (car->front_wheel.on_ground)
    {
        float friction = car->velocity.x * FRICTION;
        car->velocity.x -= friction * dt;
    }

    float max_y = GetScreenHeight() - car->height / 2;
    if (car->position.y >= max_y)
    {
        car->velocity.y = 0;
        car->position.y = max_y;
    }
    else
    {
        car->velocity.y += GRAVITY * dt;
    }
}

void car_apply_suspension(Car *car, Wheel *wheel, float dt)
{
    Vector2 bottom_direction = Vector2Rotate((Vector2){0, 1}, car->angle * DEG2RAD);
    Vector2 attachment_point = Vector2Rotate((Vector2){-car->width / 2 + wheel->padding + wheel->radius + wheel->offset, 0}, car->angle * DEG2RAD);
    attachment_point = Vector2Add(attachment_point, car->position);
    wheel->attachment_point = attachment_point; 

    float length = Vector2Distance(wheel->position, attachment_point);
    float resting_length = car->height / 2 + wheel->padding + wheel->radius;
    float strech = length - resting_length;
    wheel->position = Vector2Add(attachment_point, Vector2Scale(bottom_direction, length));

    float spring_force = strech * wheel->stiffness * dt;

    Vector2 relative_velocity = Vector2Subtract(car->velocity, wheel->velocity);
    Vector2 damping_force = Vector2Scale(relative_velocity, wheel->damping * dt);
    Vector2 force = Vector2Subtract(Vector2Scale(bottom_direction, spring_force), damping_force);
    car->velocity = Vector2Add(car->velocity, force);
    wheel->velocity = Vector2Subtract(wheel->velocity, Vector2Scale(force, 0.7));
}

void wheel_move(Wheel *wheel, float dt)
{
    wheel->position.x += wheel->velocity.x;
    wheel->position.y += wheel->velocity.y;
    float max_y = GetScreenHeight() - wheel->radius;

    if (wheel->position.y >= max_y)
    {
        wheel->velocity.y = 0;
        wheel->position.y = max_y;
        wheel->on_ground = true;
    }
    else
    {
        wheel->velocity.y += GRAVITY * dt;
        wheel->on_ground = false;
    }
}
