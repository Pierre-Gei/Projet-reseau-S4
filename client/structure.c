#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <SDL2/SDL.h>

#include "structure.h"

CASE initColorRect( CASE c)
{
    c.color.a = 0;
    c.color.b = 0;
    c.color.g = 0;
    c.color.r = 0;
    c.rect.h = 0;
    c.rect.w = 0;
    c.rect.x = 0;
    c.rect.y = 0;
    return c;
}