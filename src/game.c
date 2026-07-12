#include "game.h"

GameState game_init(int window_width, int window_height)
{
    GameState state = {0};

    Vector2 start_position = {1200, 300};
    state.car = car_init(start_position, 250, 100);

    terrain_generate(state.terrain, TERRAIN_COUNT, TERRAIN_LENGTH, window_height);

    state.camera = camera_init(window_width, window_height);

    return state;
}

void game_update(GameState *state, float dt)
{
    Car *car = &state->car;

    camera_update(&state->camera, car->position, car->velocity.x, dt);

    int trigger_index = 200;
    int shift_count = 100;

    if(state->car.position.x > state->terrain[trigger_index].x)
    {
        float shift_x = shift_count * TERRAIN_LENGTH;

        terrain_shift(state->terrain, TERRAIN_COUNT, TERRAIN_LENGTH, shift_count);

        state->car.position.x -= shift_x;
        state->car.back_wheel.position.x -= shift_x;
        state->car.front_wheel.position.x -= shift_x;
        state->camera.target.x -= shift_x;

    }

    car_control(car, dt);
    car_move(car, state->terrain, TERRAIN_LENGTH, dt);
    car_rotate(car, dt);
    wheel_move(&car->back_wheel, state->terrain, TERRAIN_COUNT, dt);
    wheel_move(&car->front_wheel, state->terrain, TERRAIN_COUNT, dt);
    car_apply_suspension(car, &car->back_wheel, dt);
    car_apply_suspension(car, &car->front_wheel, dt);
}

void game_draw(GameState *state)
{
    BeginMode2D(state->camera);

    terrain_draw(state->terrain, TERRAIN_COUNT);
    car_draw(&state->car);

    EndMode2D();
}
