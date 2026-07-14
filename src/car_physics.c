#include<stdio.h>
#include "car.h"
#include "terrain.h"
#include <raymath.h>

#define GRAVITY 5
#define FRICTION 2
#define ROTATION_SPEED 25
#define ROTATE_BACK_SPEED 3
#define CAR_SPEED 20
#define HILL_SPEED -0.9

Car car_init(Vector2 start_position, int width, int height)
{
    Car car = {
        .position = start_position,
        .width = width,
        .height = height,
        .angle = 0,
    };

    car.back_wheel = (Wheel){
        .radius = 25,
        .padding = 10,
        .stiffness = 0.8,
        .damping = 2.3,
    };

    car.back_wheel.position = (Vector2){
        .x = car.position.x - car.width / 2 + car.back_wheel.radius + car.back_wheel.padding,
        .y = car.position.y + car.height / 2 + car.back_wheel.radius + car.back_wheel.padding,
    };

    car.front_wheel = (Wheel){
        .radius = 25,
        .padding = 10,
        .stiffness = 0.8,
        .damping = 2.3,
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
    // if (!car->back_wheel.on_ground && !car->front_wheel.on_ground)
    // {
    //     if (IsKeyDown(KEY_LEFT))
    //     {
    //         car->angle += ROTATION_SPEED * dt;
    //     }
    //     else if (IsKeyDown(KEY_RIGHT))
    //     {
    //         car->angle -= ROTATION_SPEED * dt;
    //     }
    // } //as rotation not considered ... 

    if (IsKeyDown(KEY_RIGHT))
    {
        if (car->back_wheel.on_ground)
        {
            car->velocity.x += CAR_SPEED * dt;
        }

        if (car->front_wheel.on_ground)
        {
            car->velocity.x += CAR_SPEED * dt;
        }
    }
    else if (IsKeyDown(KEY_LEFT))
    {
        if (car->back_wheel.on_ground)
        {
            car->velocity.x -= CAR_SPEED * dt;
        }

        if (car->front_wheel.on_ground)
        {
            car->velocity.x -= CAR_SPEED * dt;
        }
    }
}
void car_rotate(Car *car, float dt)
{
    float angle = -Vector2LineAngle(car->back_wheel.position, car->front_wheel.position) * RAD2DEG;
    float diff = angle - car->angle;
    car->angle += diff * ROTATE_BACK_SPEED * dt;
}

void car_move(Car *car, Vector2 terrain[], int terrain_length, float dt)
{
    car->position.x += car->velocity.x;
    car->position.y += car->velocity.y;

    if (car->back_wheel.on_ground)
    {
        int terrain_index = floor(car->back_wheel.position.x / terrain_length);

        Vector2 point1 = terrain[terrain_index];
        Vector2 point2 = terrain[terrain_index + 1];

        float angle = Vector2LineAngle(point1, point2) * RAD2DEG;
        car->velocity.x += angle * HILL_SPEED * dt;
        float friction = car->velocity.x * FRICTION;
        car->velocity.x -= friction * dt;
    }

    if (car->front_wheel.on_ground)
    {
        int terrain_index = floor(car->front_wheel.position.x / terrain_length);

        Vector2 point1 = terrain[terrain_index];
        Vector2 point2 = terrain[terrain_index + 1];

        float angle = Vector2LineAngle(point1, point2) * RAD2DEG;
        car->velocity.x += angle * HILL_SPEED * dt;
        float friction = car->velocity.x * FRICTION;
        car->velocity.x -= friction * dt;
    }

    
    car->velocity.y += GRAVITY * dt;

    if (car->position.x < terrain[0].x + (car->width) * 3)
    {
        car->position.x = terrain[0].x + (car->width) * 3;

        if (car->velocity.x < 0)
        {
            car->velocity.x = 0;
        }
    }
}

void car_apply_suspension(Car *car, Wheel *wheel, float dt)
{
    Vector2 bottom_direction = Vector2Rotate((Vector2){0, 1}, car->angle * DEG2RAD);
    Vector2 attachment_point = Vector2Rotate((Vector2){-car->width / 2 + wheel->padding + wheel->radius + wheel->offset, 0}, car->angle * DEG2RAD);
    attachment_point = Vector2Add(attachment_point, car->position);
    
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

void wheel_move(Wheel *wheel, Vector2 terrain[], int terrain_count, float dt)
{
    wheel->position.x += wheel->velocity.x;
    wheel->position.y += wheel->velocity.y;

    wheel->on_ground = false;

    for (int i = 1; i < terrain_count; i++)
    {
        Vector2 point1 = terrain[i - 1];
        Vector2 point2 = terrain[i];

        Vector2 collision_point = {0};
        Vector2 bottom_of_wheel = {wheel->position.x, wheel->position.y + wheel->radius};
        if (IsPointBelowLine(point1, point2, bottom_of_wheel, &collision_point))
        {
            wheel->velocity.y = 0;
            wheel->position.y = collision_point.y - wheel->radius + 1;

            wheel->on_ground = true;
        }
    }

    if (!wheel->on_ground)
    {
        wheel->velocity.y += GRAVITY * dt;
    }



}
