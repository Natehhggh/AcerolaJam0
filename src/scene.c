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
    playerEntity->scale = (Vector3){1.0f,1.0f,1.0f};

    playerEntity->flags = playerEntity->flags | Active;
    playerEntity->flags = playerEntity->flags | PlayerControlled;

    playerEntity->flags = playerEntity->flags | ShapeRendered;
    playerEntity->shape = Cube;

    playerEntity->flags = playerEntity->flags | SpriteRendered;
    playerEntity->currentFrame = 0;
    playerEntity->spriteFrames = 4;
    playerEntity->spritesheet = LoadTexture("../assets/2d/knight/Idle_KG_1.png");
    playerEntity->sourceRec = (Rectangle){0.0f, 0.0f, (float)playerEntity->spritesheet.width / playerEntity->spriteFrames, (float)playerEntity->spritesheet.height };
    playerEntity->frameTime = 1 / (float)15;
    playerEntity->frameTimeAcc = 0.0f;
    playerEntity->spriteHeight = 32.0f;
    playerEntity->spriteWidth = 50.0f;


    initCamera(&camera, playerEntity);
    initCamera2d(&camera2d, playerEntity);
}

void initScene(){

    setDefaultData();
    initPlayer();
}

#endif
