#ifndef __NATE_CORE__
#define __NATE_CORE__

#include "raylib.h"
#include "raymath.h"
#include <stdint.h>

//TODO: swap bools to mask flags
typedef enum shapeType {
    Cube,
    Sphere,
    Cylinder,
    Capsule,
    Plane
} shapeType;

typedef enum {
    Free = 1 << 0,
    Active = 1 << 1,
    PlayerControlled = 1 << 2,
    ShapeRendered = 1 << 3,
    Unused001 = 1 << 4,
    Unused002 = 1 << 5,
    Unused003 = 1 << 6,
    Unused004 = 1 << 7,
    Unused005 = 1 << 8,
    Unused006 = 1 << 9,
    Unused007 = 1 << 10,


} entityFlags;


typedef struct entity{
    int flags;
    Vector3 position;
    Vector3 rotation;
    Vector3 scale;
    enum shapeType shape;
} entity;




#endif
