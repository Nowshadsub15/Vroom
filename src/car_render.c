// #include "car.h"

// // #define TRANSPARENT_BLACK (Color){0,0,0,100}

// void car_draw(Car *car)
// {
//     //     DrawRectanglePro((Rectangle){
//     //                          .width = car->width,
//     //                          .height = car->height,
//     //                          .x = car->position.x,
//     //                          .y = car->position.y,
//     //                      },
//     //                      (Vector2){car->width / 2, car->height / 2}, car->angle, TRANSPARENT_BLACK);
//     //     DrawCircle(car->back_wheel.position.x, car->back_wheel.position.y, car->back_wheel.radius, TRANSPARENT_BLACK);
//     //     DrawCircle(car->front_wheel.position.x, car->front_wheel.position.y, car->front_wheel.radius, TRANSPARENT_BLACK);

//     Rectangle sourceBack = {0.0f, 0.0f, (float)car->back_wheel.texture.width, (float)car->back_wheel.texture.height};
//     Rectangle destBack = {car->back_wheel.position.x, car->back_wheel.position.y, car->back_wheel.radius * 2, car->back_wheel.radius * 2};
//     Vector2 originWheel = {car->back_wheel.radius, car->back_wheel.radius};
//     DrawTexturePro(car->back_wheel.texture, sourceBack, destBack, originWheel, car->back_wheel.rotation, WHITE);

//     Rectangle sourceFront = {0.0f, 0.0f, (float)car->front_wheel.texture.width, (float)car->front_wheel.texture.height};
//     Rectangle destFront = {car->front_wheel.position.x, car->front_wheel.position.y, car->front_wheel.radius * 2, car->front_wheel.radius * 2};
//     DrawTexturePro(car->front_wheel.texture, sourceFront, destFront, originWheel, car->front_wheel.rotation, WHITE);

//     Rectangle sourceBody = {0.0f, 0.0f, (float)car->textture.width, (float)car->textture.height};
//     Rectangle destBody = {car->front_wheel.position.x, car->front_wheel.position.y, (float)car->width, (float)car->height};
//     Vector2 originBody = {(float)car->width / 2.0f, (float)car->height / 2.0f};
//     DrawTexturePro(car->textture, sourceBody, destBody, originBody, car->angle, WHITE);
// }

#include "car.h"

void car_draw(Car *car)
{
    Rectangle sourceBody = { 0.0f, 0.0f, (float)car->texture.width, (float)car->texture.height };
    Rectangle destBody = { car->position.x, car->position.y+40, (float)car->width, (float)car->height }; 
    Vector2 originBody = { (float)car->width / 2.0f, (float)car->height / 2.0f };
    
    DrawTexturePro(car->texture, sourceBody, destBody, originBody, car->angle, WHITE);

    float back_diameter = car->back_wheel.radius * 2.0f;
    Rectangle sourceBack = { 0.0f, 0.0f, (float)car->back_wheel.texture.width, (float)car->back_wheel.texture.height };
    Rectangle destBack = { car->back_wheel.position.x+25, car->back_wheel.position.y, back_diameter, back_diameter }; 
    Vector2 originBack = { car->back_wheel.radius, car->back_wheel.radius };
    
    DrawTexturePro(car->back_wheel.texture, sourceBack, destBack, originBack, 0, WHITE);

    float front_diameter = car->front_wheel.radius * 2.0f;
    Rectangle sourceFront = { 0.0f, 0.0f, (float)car->front_wheel.texture.width, (float)car->front_wheel.texture.height };
    Rectangle destFront = { car->front_wheel.position.x -20, car->front_wheel.position.y, front_diameter, front_diameter };
    Vector2 originFront = { car->front_wheel.radius, car->front_wheel.radius };
    
    DrawTexturePro(car->front_wheel.texture, sourceFront, destFront, originFront, 0, WHITE);
}