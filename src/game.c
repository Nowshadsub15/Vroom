#include "game.h"

GameState game_init(int window_width, int window_height)
{    
    GameState state = {0};

    Texture2D car_tex = LoadTexture("assets/car_body.png");
    Texture2D wheel_tex = LoadTexture("assets/wheel.png");

    Vector2 start_position = {1200, 300};
    state.car = car_init(start_position, 250, 100);

    state.car.texture = car_tex;
    state.car.back_wheel.texture = wheel_tex;
    state.car.front_wheel.texture = wheel_tex;
    

    terrain_generate(state.terrain, window_height, state.anchors);

    state.camera = camera_init(window_width, window_height);

    return state;
}

void game_update(GameState *state, float dt)
{
    Car *car = &state->car;

    camera_update(&state->camera, car->position, car->velocity.x, dt);

    int trigger_index = 850; 
    int anchor_shift_count = 30 ;
    int shift_count = anchor_shift_count*CONTROL_STEP; 

    if (state->car.position.x > state->terrain[trigger_index].x){
        float shift_x = shift_count * TERRAIN_LENGTH;

        terrain_shift(state->terrain, shift_count,state->anchors);

        state->car.position.x -= shift_x;
        state->car.back_wheel.position.x -= shift_x;
        state->car.front_wheel.position.x -= shift_x;
        state->camera.target.x -= shift_x;
    }

    car_control(car, dt);
    car_move(car, state->terrain, dt);
    car_rotate(car, dt);
    wheel_move(&car->back_wheel, state->terrain, dt);
    wheel_move(&car->front_wheel, state->terrain, dt);
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
