#include<stdio.h>
#include "car.h"
#include "terrain.h"
#include <raymath.h>

#define GRAVITY 5
#define FRICTION 2
#define ROTATION_SPEED 25
#define ROTATE_BACK_SPEED 3
#define CAR_SPEED 30
#define HILL_SPEED -0.9
#define WHEEL_ROTATION_SPEED 1000


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
        .padding = 0,
        .stiffness = 0.8,
        .damping = 2.3,
    };

    car.back_wheel.position = (Vector2){
        .x = car.position.x - 60,
        .y = car.position.y + 50,
    };

    car.front_wheel = (Wheel){
        .radius = 25,
        .padding = 0,
        .stiffness = 0.8,
        .damping = 2.3,
    };

    car.back_wheel.offset = 41 ;
    car.front_wheel.offset = 186;

    car.front_wheel.position = (Vector2){
        .x = car.position.x + 61.3,
        .y = car.position.y + 50,
    };

    return car;
}

void car_control(Car *car, float dt)
{
    if (IsKeyDown(KEY_RIGHT))
    {
          car->back_wheel.angle += WHEEL_ROTATION_SPEED * dt;
    car->front_wheel.angle += WHEEL_ROTATION_SPEED * dt;
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
            car->back_wheel.angle -= WHEEL_ROTATION_SPEED * dt;
    car->front_wheel.angle -= WHEEL_ROTATION_SPEED * dt;
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
    car->angle = angle;
}

void car_move(Car *car, Vector2 terrain[], float dt)
{
    car->position.x += car->velocity.x;
    car->position.y += car->velocity.y;

    if (car->back_wheel.on_ground)
    {
        int terrain_index = floor(car->back_wheel.position.x / TERRAIN_LENGTH);

        Vector2 point1 = terrain[terrain_index];
        Vector2 point2 = terrain[terrain_index + 1];

        float angle = Vector2LineAngle(point1, point2) * RAD2DEG;
        car->velocity.x += angle * HILL_SPEED * dt;
        float friction = car->velocity.x * FRICTION;
        car->velocity.x -= friction * dt;
    }

    if (car->front_wheel.on_ground)
    {
        int terrain_index = floor(car->front_wheel.position.x / TERRAIN_LENGTH);

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
    Vector2 temp = {
        .x = car->position.x,
        .y = car->position.y-19,
    };
    attachment_point = Vector2Add(attachment_point, temp);
    
    float length = Vector2Distance(wheel->position, attachment_point);
    float resting_length = car->height / 2 + wheel->padding + wheel->radius;
    float strech = length - resting_length;
    
    wheel->position = Vector2Add(attachment_point, Vector2Scale(bottom_direction, length));

    float spring_force = strech * wheel->stiffness ;
    
    Vector2 relative_velocity = Vector2Subtract(car->velocity, wheel->velocity);
    Vector2 damping_force = Vector2Scale(relative_velocity, wheel->damping);
    
    Vector2 force = Vector2Subtract(Vector2Scale(bottom_direction, spring_force), damping_force);
    force = Vector2Scale(force,dt) ;
    car->velocity = Vector2Add(car->velocity, force);
    wheel->velocity = Vector2Subtract(wheel->velocity, Vector2Scale(force, 0.7));
}

void wheel_move(Wheel *wheel, Vector2 terrain[], float dt)
{
    //wheel->position.x += wheel->velocity.x;
    wheel->position.y += wheel->velocity.y;

    wheel->on_ground = false;

    for (int i = 1; i < TERRAIN_COUNT; i++)
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
    wheel->velocity.y += GRAVITY * dt;
    wheel->angle += wheel->velocity.x * WHEEL_ROTATION_SPEED/20 * dt;
}
