#ifndef GLOBAL_STYLE_H
#define GLOBAL_STYLE_H

#include <raygui.h>
#include <raylib.h>

#define BACK_GROUND_COLOR \
    (Color) { 165, 215, 232, 255 }
#define NORMAL_TEXT_COLOR \
    (Color) { 11, 24, 47, 255 }
#define ERROR_TEXT_COLOR \
    (Color) { 255, 0, 0, 255 }
#define SCREEN_WIDTH 1600
#define SCREEN_HEIGHT 900
#define DEFAULT_TITLE_SIZE 48
#define DEFAULT_TEXT_SIZE 24
#define DEFAULT_ITEM_HEIGHT 60.0f
#define DEFAULT_PADDING \
    (Vector2) { 20.0f, 20.0f }
#define DEFAULT_TEXT_MARGIN \
    (Vector2) { 6.0f, 6.0f }
#define DEFAULT_ITEM_MARGIN \
    (Vector2) { 20.0f, 20.0f }
#define MAX_INPUT_CHAR 256
#define SPACING 1.0f
#define DEFAULT_AVATAR_SIZE \
    (Vector2) { 50.f, 50.f }
#define DEFAULT_MENU_BUTTON_WIDTH 180

extern Font titleFont, textFont;

#endif
