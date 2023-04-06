#include "GetCenterPosition.h"

#include "../GlobalStyle.h"

float getCenterX(float width) { return (SCREEN_WIDTH - width) / 2; }

float getCenterY(float height) { return (SCREEN_HEIGHT - height) / 2; }

Vector2 getCenterPosition(Vector2 size) {
    return {getCenterX(size.x), getCenterY(size.y)};
}
