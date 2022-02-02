#include "engine/2d_util.h"

#include <algorithm>

bool isInBounds(int x, int y, int x1, int y1, int x2, int y2)
{
    if (x2 < x1) std::swap(x1, x2);
    if (y2 < y1) std::swap(y1, y2);

    return x >= x1 && y >= y1 && x <= x2 && y <= y2;
}