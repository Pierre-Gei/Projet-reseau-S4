#include <stdio.h>
#include <stdlib.h>
#include "structure.h"


Matrix initMatrix(Matrix m)
{
    m.width = 0;
    m.height = 0;
    m.pixel_min = 0;
    return m;
}