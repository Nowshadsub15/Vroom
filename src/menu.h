#ifndef MENU_H
#define MENU_H

#include <raylib.h>
#include<stdbool.h>

typedef struct Menu
{
    Font font;
    
} Menu;

Menu menu_init(void);
bool menu_update_and_draw(Menu *menu, int window_width, int window_height);
// bool menu_update_draw -- handles user interaction
#endif