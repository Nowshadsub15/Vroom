#include "game.h"

GameState game_init(int window_width, int window_height)
{
    GameState state = {0};
    Vector2 start_position = {300, 300};
    state.car = car_init(start_position, 250, 100);
    return state;
}

void game_update(GameState *state, float dt)
{
    Car *car = &state->car;

    car_control(car, dt);
    car_move(car, dt);
    car_rotate(car, dt);
    wheel_move(&car->back_wheel, dt);
    wheel_move(&car->front_wheel, dt);
    car_apply_suspension(car, &car->back_wheel, dt);
    car_apply_suspension(car, &car->front_wheel, dt);
}

void game_draw(GameState *state)
{
    car_draw(&state->car);
}
