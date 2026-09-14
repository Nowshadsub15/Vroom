#include "fuel.h"
#include <math.h>
#include <raymath.h>
#include <stdio.h>
FuelSystem fuel_init(void)
{
    FuelSystem fuel = {0};
    fuel.amount = FUEL_MAX;
    fuel.distance_since_pickup = FUEL_PICKUP_SPACING;
    fuel.pickup_active = false;
    fuel.current_spacing = FUEL_PICKUP_SPACING;

    return fuel;
}

static float terrain_height_at(Vector2 terrain[], float x)
{
    int index = (int)floorf(x / TERRAIN_LENGTH);
    Vector2 p1 = terrain[index];
    Vector2 p2 = terrain[index + 1];

    float t = (x - p1.x) / (p2.x - p1.x); // perc of the distance i have covered between pos1 and pos2

    return p1.y + t * (p2.y - p1.y); // using the perc to find the height -- using linear interpolation
}

void fuel_update(FuelSystem *fuel, Car *car, Vector2 terrain[], float dt)
{
    if (fuel->amount > 0)
    {
        fuel->amount -= FUEL_DRAIN_RATE * dt * 0.8;
        if (IsKeyDown(KEY_RIGHT) || IsKeyDown(KEY_LEFT))
        {
            if (car->back_wheel.on_ground)
                fuel->amount -= fabs(car->velocity.x) * 0.002 * dt;
            if (car->front_wheel.on_ground)
                fuel->amount -= fabs(car->velocity.x) * 0.002 * dt;
            fuel->amount -= fabs(car->velocity.x) * 0.02 * dt;
        }
        if (fuel->amount < 0)
        {
            fuel->amount = 0;
        }
    }

    // distance tracking
    fuel->distance_since_pickup += fabsf(car->velocity.x);

    // adding new fuel icon
    if (fuel->pickup_active == false && fuel->distance_since_pickup >= fuel->current_spacing)
    {
        float spawn_x = car->position.x + FUEL_PICKUP_AHEAD;

        float spawn_y = terrain_height_at(terrain, spawn_x) - FUEL_PICKUP_RADIUS - 45;

        fuel->current_spacing += FUEL_SPACING_INCREAMENT;

        if (fuel->current_spacing >= FUEL_SPACING_MAX)
        {
            fuel->current_spacing = FUEL_SPACING_MAX;
        }

        fuel->pickup_position = (Vector2){spawn_x, spawn_y};
        fuel->pickup_active = true;
    }

    // fuel collect
    if (fuel->pickup_active)
    {
        float dist = Vector2Distance(car->position, fuel->pickup_position);

        if (dist < (FUEL_PICKUP_RADIUS + car->width / 2.0f))
        {
            fuel->amount += FUEL_PICKUP_AMOUNT;
            if (fuel->amount > FUEL_MAX)
            {
                fuel->amount = FUEL_MAX;
            }
            fuel->pickup_active = false;
            fuel->distance_since_pickup = 0;
        }
    }
}

void fuel_shift(FuelSystem *fuel, float shift_x)
{
    if (fuel->pickup_active)
    {
        fuel->pickup_position.x -= shift_x;
    }
}

bool fuel_is_empty(FuelSystem *fuel)
{
    return fuel->amount <= 0.0f;
}

// fuel icon draw
void fuel_draw_pickup(FuelSystem *fuel)
{
    if (fuel->pickup_active == false)
    {
        return;
    }

    Vector2 pos = fuel->pickup_position;
    Rectangle source = {0, 0, fuel->tex.width, fuel->tex.height};
    Rectangle dest = {pos.x, pos.y, 56, 70};
    Vector2 origin = {28, 35};
    DrawTexturePro(fuel->tex, source, dest, origin, 0, WHITE);

    //     Color body = (Color){235, 190, 40, 255};
    //     Color outline = (Color){120, 90, 10, 255};

    //     Rectangle can = {pos.x - 26, pos.y - 35, 56, 70};                    // can
    //     DrawRectangleRounded(can, 0.3f, 6, body);                            // adds color in can and rounded edge
    //     DrawRectangleRoundedLines(can, 0.3f, 6, outline);                    // outline
    //     DrawRectangle((int)(pos.x - 6), (int)(pos.y - 26), 12, 10, outline); // another rectangle
    //     DrawText("F", (int)(pos.x - 5), (int)(pos.y - 9), 20, outline);
}

// fuel bar draw
void fuel_draw_bar(FuelSystem *fuel, int window_width, Font temp)
{
    int bar_w = 300;
    int bar_h = 40;
    int bar_x = window_width - bar_w - 40;
    int bar_y = 80;

    float ratio = fuel->amount / FUEL_MAX;
    if (ratio < 0)
    {
        ratio = 0;
    }

    Color fill_color = (Color){60, 200, 90, 255};
    if (ratio < 0.5f)
    {
        fill_color = (Color){240, 190, 40, 255};
    }
    if (ratio < 0.2f)
    {
        fill_color = (Color){220, 60, 50, 255};
    }

    DrawRectangle(bar_x, bar_y, bar_w, bar_h, (Color){30, 30, 30, 180});
    DrawRectangle(bar_x + 3, bar_y + 3, (int)((bar_w - 6) * ratio), bar_h - 6, fill_color);
    DrawRectangleLines(bar_x, bar_y, bar_w, bar_h, WHITE);
    DrawTextEx(temp, "FUEL", (Vector2){bar_x, bar_y - 60}, 70, 0, WHITE);

    if (fuel_is_empty(fuel))
    {
        DrawTextEx(temp, "OUT OF FUEL", (Vector2){bar_x - 30, bar_y + bar_h + 30}, 60, 0, RED);
    }
}
