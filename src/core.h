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
    char debugName[10];
} entity;

//-- Components --
typedef struct transform {
    int8_t entityId;
    Vector3 position;
    Vector3 rotation;
    Vector3 scale;
} transform;


typedef struct entityInput{
    int8_t entityId;
    int8_t transformId;
} entityInput;


typedef struct shapeRender{
    int8_t entityId;
    int8_t transformId;
    enum shapeType shape;
    bool isActive;
} shapeRender;



#endif
