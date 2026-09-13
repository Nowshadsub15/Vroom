#ifndef FUEL_H
#define FUEL_H

#include<raylib.h>
#include "car.h"
#include "terrain.h"

#define FUEL_MAX 100.0
#define FUEL_DRAIN_RATE 5.0
#define FUEL_PICKUP_AMOUNT 35.0
#define FUEL_PICKUP_SPACING 3000.0
#define FUEL_PICKUP_RADIUS 28.0
#define FUEL_PICKUP_AHEAD 2000.0
#define FUEL_SPACING_INCREAMENT 1000.0
#define FUEL_SPACING_MAX 150000.0


typedef struct FuelSystem
{
    float amount;
    float distance_since_pickup;
    bool pickup_active;
    Vector2 pickup_position;
    Texture2D tex ; 
    Font temp ;
    float current_spacing;
}FuelSystem;

FuelSystem fuel_init(void);
void fuel_update(FuelSystem *fuel, Car *car, Vector2 terrain[], float dt);
void fuel_shift(FuelSystem *fuel, float shift_x);
bool fuel_is_empty(FuelSystem *fuel);

void fuel_draw_pickup(FuelSystem *fuel);
void fuel_draw_bar(FuelSystem *fuel, int window_width, Font temp);

#endif


