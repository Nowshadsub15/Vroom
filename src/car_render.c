#include "car.h"

void car_draw(Car *car)
{
    Rectangle sourceBody = { 0.0, 0.0, (float)car->texture.width, (float)car->texture.height };
    Rectangle destBody = { car->position.x, car->position.y+40, (float)car->width, (float)car->height }; 
    Vector2 originBody = { (float)car->width / 2.0, (float)car->height / 2.0 };
    
    DrawTexturePro(car->texture, sourceBody, destBody, originBody, car->angle, WHITE);

    float back_diameter = car->back_wheel.radius * 2.0;
    Rectangle sourceBack = { 0.0, 0.0, (float)car->back_wheel.texture.width, (float)car->back_wheel.texture.height };
    Rectangle destBack = { car->back_wheel.position.x+25, car->back_wheel.position.y, back_diameter, back_diameter }; 
    Vector2 originBack = { car->back_wheel.radius, car->back_wheel.radius };
    
    DrawTexturePro(car->back_wheel.texture, sourceBack, destBack, originBack, 0, WHITE);

    float front_diameter = car->front_wheel.radius * 2.0;
    Rectangle sourceFront = { 0.0, 0.0, (float)car->front_wheel.texture.width, (float)car->front_wheel.texture.height };
    Rectangle destFront = { car->front_wheel.position.x -20, car->front_wheel.position.y, front_diameter, front_diameter };
    Vector2 originFront = { car->front_wheel.radius, car->front_wheel.radius };
    
    DrawTexturePro(car->front_wheel.texture, sourceFront, destFront, originFront, 0, WHITE);
}