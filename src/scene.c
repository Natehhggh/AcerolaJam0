#ifndef __NATE_SCENE__
#define __NATE_SCENE__ 

#include "raylib.h"
#include "raymath.h"
#include "core.h"
#include "entity.c"
#include "camera.c"

void initPlayer(){
    entity* playerEntity = newEntity();
    playerEntity->position = (Vector3){0.0f,0.0f,0.0f};
    playerEntity->rotation = (Vector3){0.0f,0.0f,0.0f};
    playerEntity->scale = (Vector3){2.5f,1.0f,1.0f};
    playerEntity->shape = Cube;
    playerEntity->flags = playerEntity->flags | ShapeRendered;
    playerEntity->flags = playerEntity->flags | Active;
    playerEntity->flags = playerEntity->flags | PlayerControlled;
    playerEntity->flags = playerEntity->flags | SpriteRendered;
    playerEntity->spritesheet = LoadTexture("../assets/2d/knight/Idle_KG_1.png");
    playerEntity->spriteFrames = 4;
    playerEntity->frameRec = (Rectangle){0.0f, 0.0f, (float)playerEntity->spritesheet.width / playerEntity->spriteFrames, (float)playerEntity->spritesheet.height };
    playerEntity->currentFrame = 0;
    playerEntity->frameCounter = 0;
    playerEntity->frameRate = 8;

    initCamera(&camera, playerEntity);
    initCamera2d(&camera2d, playerEntity);
}

void initScene(){

    setDefaultData();
    initPlayer();
}

#endif
