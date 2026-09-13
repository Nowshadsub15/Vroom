#include "menu.h"

Menu menu_init(void)
{

    Menu menu = {0};
    menu.font = LoadFont("assets/ANTEORS.ttf");
    return menu;
}

bool menu_update_and_draw(Menu *menu, int window_width, int window_height)
{
    const char *title = "VROOM";
    float title_font_size = 120.0f;
    Vector2 title_size = MeasureTextEx(menu->font, title, title_font_size, 0);
    // returns textsize x and y

    Rectangle button = {window_width / 2.0f - 200, window_height / 2.0f - 5, 390, 150};

    Vector2 mouse = GetMousePosition();
    bool hovered = CheckCollisionPointRec(mouse, button);
    // if mouse is in button's region

    bool clicked = hovered && IsMouseButtonPressed(MOUSE_LEFT_BUTTON);
    bool key_pressed = IsKeyPressed(KEY_ENTER) || IsKeyPressed(KEY_SPACE);

    ClearBackground(SKYBLUE);

    DrawTextEx(menu->font, title, (Vector2){window_width / 2.0f - title_size.x+80, window_height / 3.5f}, title_font_size, 0, DARKBLUE); // co ordinates using ai

    Color button_color = hovered ? (Color){50, 160, 60, 225} : (Color){40, 130, 50, 255};
    DrawRectangleRounded(button, 0.3f, 8, button_color);
    DrawRectangleRoundedLines(button, 0.3f, 8, (Color){20, 80, 25, 255});

    const char *label = "PLAY";
    float label_font_size = 80;
    Vector2 label_size = MeasureTextEx(menu->font, label, label_font_size, 0);
    DrawTextEx(menu->font, label, (Vector2){button.x + button.width / 2.0f - label_size.x / 2.0f, button.y + button.height / 2.0f - label_size.y / 2.0f}, label_font_size, 0, WHITE);
    // co ordinates using ai

    const char *hint = "Press ENTER or Click PLAY";
    float hint_font_size = 50;
    Vector2 hint_size = MeasureTextEx(menu->font, hint, hint_font_size, 0);
    DrawTextEx(menu->font, hint, (Vector2){window_width / 2.0f - hint_size.x / 2.0f-8, button.y + button.height + 30}, hint_font_size, 0, DARKGRAY);

    return clicked || key_pressed;
}