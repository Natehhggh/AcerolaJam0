#include "raylib.h"
#include <stdint.h>

#ifndef __NATE_THIRDPERSONCAMERA__
#define __NATE_THIRDPERSONCAMERA__

//TODO: enum for other cameras like first person, just get any camera in here
struct thirdPersonCamera{
    int8_t transformId;
    Camera3D camera;
    Vector3 offset;
};

#endif

