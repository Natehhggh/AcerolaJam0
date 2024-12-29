#ifndef __NATE_CORE__
#define __NATE_CORE__

#include "raylib.h"
#include "raymath.h"

#define WORLD_HEIGHT = 20;
#define WORLD_WIDTH = 20;


typedef enum {
    Free = 1 << 0,
    Active = 1 << 1,
    PlayerControlled = 1 << 2,
    ShapeRendered = 1 << 3,
    SpriteRendered = 1 << 4,
    ModelRendered= 1 << 5,
    Unused003 = 1 << 6,
    Unused004 = 1 << 7,
    Unused005 = 1 << 8,
    Unused006 = 1 << 9,
    Unused007 = 1 << 10,
    Unused008 = 1 << 11,
    Unused009 = 1 << 12,
    Unused010 = 1 << 13,
    Unused011 = 1 << 14,
    Unused012 = 1 << 15,
    Unused013 = 1 << 16,
    Unused014 = 1 << 17,
    Unused015 = 1 << 18,
    Unused016 = 1 << 19,
    Unused017 = 1 << 20,
    Unused018 = 1 << 21,
    Unused019 = 1 << 22,
    Unused020 = 1 << 23,
    Unused021 = 1 << 24,
    Unused022 = 1 << 25,
    Unused023 = 1 << 26,
    Unused024 = 1 << 27,
    Unused025 = 1 << 28,
    Unused026 = 1 << 29,
} entityFlags;

typedef enum shapeType {
    Cube,
    Sphere,
    Cylinder,
    Capsule,
    Plane
} shapeType;

typedef enum renderMode {
    _2d,
    _3d
} renderMode;

typedef struct {
    int flags;
    Vector3 position;
    Vector3 rotation;
    Vector3 scale;
    enum shapeType shape;
    //TOOD: refactor sprite system
    Texture2D spritesheet;
    Rectangle sourceRec;
    Rectangle spriteRec;
    int spriteFrames;
    int currentFrame;
    float frameTime;
    float frameTimeAcc;
    float spriteWidth;
    float spriteHeight;
} entity;


//Why does this struct complain wihtout the world2d name at the start?
//typedef struct world2d{
//    int tileSize;
//    int tiles[];

//} world2d;

//TODO: enum for other cameras like first person, just get any camera in here
typedef struct thirdPersonCamera{
    entity* target;
    Camera3D camera;
    Vector3 offset;
} thirdPersonCamera;

typedef struct followingCamera{
    entity* target;
    Camera2D camera;
} followingCamera;

#define MAX_ENTITIES 100
//TODO: do I put this in a game state struct
entity entities[MAX_ENTITIES];
thirdPersonCamera camera = {0};
followingCamera camera2d = {0};
enum renderMode rendering = _3d;
int screenHeight = 720;
int screenWidth = 1280;


#endif
