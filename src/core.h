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


typedef struct entity{
    int8_t id;
    Vector3 position;
    Vector3 rotation;
    Vector3 scale;
    enum shapeType shape;
    bool isActive;
} entity;


typedef struct entityInput{
    int8_t entityId;
} entityInput;

#endif
