#ifndef __NATE_CAMERA__
#define __NATE_CAMERA__

#include "raylib.h"
#include "core.h"


void updateCamera(thirdPersonCamera* camera){
    //Vector3 IdealOffset = >

    Vector3 targetPos = camera->target->position;
    camera->camera.position = Vector3Add(targetPos, camera->offset);
    camera->camera.target = targetPos;
}

void updateCamera2d(followingCamera* camera){
    camera->camera.target = (Vector2){camera->target->position.x, camera->target->position.y};
}

void initCamera(thirdPersonCamera* camera, entity* target){
    camera->camera.position = (Vector3){-3.0f, 2.5f,0.0f};
    camera->camera.up = (Vector3){0.0f,1.0f,0.0f};
    camera->camera.fovy = 65.0f;
    camera->camera.projection = CAMERA_PERSPECTIVE;
    camera->target = target;
    camera->offset = Vector3Subtract(camera->camera.position, target->position);
}

void initCamera2d(followingCamera* camera, entity* target){
    camera->camera.zoom = 1.0f;
    camera->camera.rotation = 0.0f;
    camera->camera.target = (Vector2){target->position.x, target->position.y};
    camera->target = target;
    camera->camera.offset = (Vector2){screenWidth/2.0f, screenHeight/ 2.0f};
}



#endif

