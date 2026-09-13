#include <raylib.h>
#include "src/game.h"
#include <math.h>
#include "src/menu.h"
#include "src/gameover.h"

#define WINDOW_WIDTH 1500
#define WINDOW_HEIGHT 1000
#define STOPPED_SPEED_THRESHOLD 5.0f

typedef enum
{
    SCREEN_MENU,
    SCREEN_GAMEPLAY,
    SCREEN_GAMEOVER

} AppScreen;

int main(void)
{
    InitWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "Vroom");
    SetTargetFPS(60);

    AppScreen screen = SCREEN_MENU;
    Menu menu = menu_init();
    GameState state = game_init(WINDOW_WIDTH, WINDOW_HEIGHT);

    while (!WindowShouldClose())
    {
        float dt = GetFrameTime();

        BeginDrawing();

        if (screen == SCREEN_MENU)
        {
            bool start_pressed = menu_update_and_draw(&menu, WINDOW_WIDTH, WINDOW_HEIGHT);
            if (start_pressed)
            {
                state = game_init(WINDOW_WIDTH, WINDOW_HEIGHT);
                screen = SCREEN_GAMEPLAY;
            }
        }

        else if (screen == SCREEN_GAMEPLAY)
        {
        game_update(&state, dt);


        ClearBackground(BLUE);
        game_draw(&state);

        bool out_of_fuel = fuel_is_empty(&state.fuel);
        bool car_stopped = fabsf(state.car.velocity.x) < STOPPED_SPEED_THRESHOLD;

        if (out_of_fuel && car_stopped)
        {
            screen = SCREEN_GAMEOVER;
        }
        
        }

        else
        {
            GameOverChoice choice = gameover_update_and_draw(menu.font, WINDOW_WIDTH,WINDOW_HEIGHT);
            if (choice == GAMEOVER_RESTART)
            {
                state = game_init(WINDOW_WIDTH,WINDOW_HEIGHT);
                screen = SCREEN_GAMEPLAY;
            }
            else if(choice == GAMEOVER_HOME)
            {
                screen = SCREEN_MENU;
            }
        }
        
        EndDrawing();
    }

    CloseWindow();
    return 0;
}
