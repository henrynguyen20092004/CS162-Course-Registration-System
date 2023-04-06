#ifndef GLOBAL_STYLE_H
#define GLOBAL_STYLE_H

#include <raygui.h>
#include <raylib.h>

#define BACK_GROUND_COLOR \
    (Color) { 165, 215, 232, 255 }
#define TEXT_COLOR \
    (Color) { 11, 24, 47, 255 }
#define SCREEN_WIDTH 1600
#define SCREEN_HEIGHT 900
#define DEFAULT_TITLE_SIZE 48
#define DEFAULT_TEXT_SIZE 24
#define DEFAULT_TITLE_PATH "Font\\tahoma.ttf"
#define DEFAULT_TEXT_PATH "Font\\cambria.ttf"
#define MAX_INPUT_CHAR 256
#define SPACING 1.0f

extern Font titleFont, textFont;

#endif
