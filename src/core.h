#include "raylib.h"
#include "raymath.h"
#include <stdint.h>

#ifndef __NATE_CORE__
#define __NATE_CORE__

//TODO: swap bools to mask flags
enum shapeType {
    Cube,
    Sphere,
    Cylinder,
    Capsule,
    Plane
};


struct entity{
    int8_t id;
    char debugName[10];
};

//-- Components --
struct transform {
    int8_t entityId;
    Vector3 position;
    Vector3 rotation;
    Vector3 scale;
};


struct entityInput{
    int8_t entityId;
    int8_t transformId;
};


struct shapeRender{
    int8_t entityId;
    int8_t transformId;
    enum shapeType shape;
    bool isActive;
};



#endif
