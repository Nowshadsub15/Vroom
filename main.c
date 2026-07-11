#include <raylib.h>
#include "src/game.h"

#define WINDOW_WIDTH 1500
#define WINDOW_HEIGHT 1000

int main(void)
{
    InitWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "Uphill Racer");
    SetTargetFPS(60);

    GameState state = game_init(WINDOW_WIDTH, WINDOW_HEIGHT);

    while (!WindowShouldClose())
    {
        float dt = GetFrameTime();

        game_update(&state, dt);

        BeginDrawing();
        ClearBackground(WHITE);
        game_draw(&state);
        EndDrawing();
    }

    CloseWindow();
    return 0;
}
