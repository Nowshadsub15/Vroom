#include "car.h"

#define TRANSPARENT_BLACK (Color){0,0,0,100}

void car_draw(Car *car)
{
    DrawRectanglePro((Rectangle){
                         .width = car->width,
                         .height = car->height,
                         .x = car->position.x,
                         .y = car->position.y,
                     },
                     (Vector2){car->width / 2, car->height / 2}, car->angle, TRANSPARENT_BLACK);
    DrawCircle(car->back_wheel.position.x, car->back_wheel.position.y, car->back_wheel.radius, TRANSPARENT_BLACK);
    DrawCircle(car->front_wheel.position.x, car->front_wheel.position.y, car->front_wheel.radius, TRANSPARENT_BLACK);
}
