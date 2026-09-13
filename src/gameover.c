#include "gameover.h"

GameOverChoice gameover_update_and_draw(Font font, int window_width, int window_height)
{
    const char *title = "GAME OVER";
    float title_font_size = 100.0f;

    Vector2 title_size = MeasureTextEx(font, title, title_font_size, 0);

    Rectangle restart_button = {window_width / 2.0f - 230, window_height / 2.0f + 20, 200, 70};

    Rectangle home_button = {window_width / 2.0f + 30, window_height / 2.0f + 20, 200, 70};

    Vector2 mouse = GetMousePosition();

    bool restart_hovered = CheckCollisionPointRec(mouse, restart_button);
    bool home_hovered = CheckCollisionPointRec(mouse, home_button);

    bool restart_clicked = restart_hovered && IsMouseButtonPressed(MOUSE_LEFT_BUTTON);
    bool home_clicked = home_hovered && IsMouseButtonPressed(MOUSE_LEFT_BUTTON);

    ClearBackground((Color){30, 30, 30, 255});

    DrawTextEx(font, title, (Vector2){window_width / 2.0f - title_size.x / 2.0f, window_height / 3.0f}, title_font_size, 0, RED);

    Color restart_color = restart_hovered ? (Color){50, 160, 60, 255} : (Color){40, 130, 50, 255};
    DrawRectangleRounded(restart_button, 0.3f, 8, restart_color);
    DrawRectangleRoundedLines(restart_button, 0.3f, 8, (Color){20, 80, 25, 255});

    Color home_color = home_hovered ? (Color){70, 120, 200, 255} : (Color){50, 100, 180, 255};
    DrawRectangleRounded(home_button, 0.3f, 8, home_color);
    DrawRectangleRoundedLines(home_button, 0.3f, 8, (Color){20, 50, 100, 255});

    const char *restart_label = "RESTART";
    float label_font_size = 30.0f;
    Vector2 restart_label_size = MeasureTextEx(font, restart_label, label_font_size, 0);
    DrawTextEx(font, restart_label, (Vector2){restart_button.x + restart_button.width / 2.0f - restart_label_size.x / 2.0f, restart_button.y + restart_button.height / 2.0f - restart_label_size.y / 2.0f}, label_font_size, 0, WHITE);

    const char *home_label = "HOME";
    Vector2 home_label_size = MeasureTextEx(font, home_label, label_font_size, 0);
    DrawTextEx(font, home_label, (Vector2){home_button.x + home_button.width / 2.0f - home_label_size.x / 2.0f, home_button.y + home_button.height / 2.0f - home_label_size.y / 2.0f}, label_font_size, 0, WHITE);

    if (restart_clicked)
    {
        return GAMEOVER_RESTART;
    }
    if (home_clicked)
    {
        return GAMEOVER_HOME;
    }

    return GAMEOVER_NONE;
}