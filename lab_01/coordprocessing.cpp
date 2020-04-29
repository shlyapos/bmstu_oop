#include "coordprocessing.h"
#include "figureallocate.h"

float into_2d(float coord, float z, float screen, int mode)
{
    float sc;

    sc = (screen / 2) + (((coord * DISTANCE) / (z + DISTANCE)) * mode);
    return sc;
}
