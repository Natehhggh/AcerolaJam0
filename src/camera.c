#ifndef __NATE_CAMERA__
#define __NATE_CAMERA__

#include "raylib.h"
#include "core.h"

//TODO: enum for other cameras like first person, just get any camera in here
typedef struct thirdPersonCamera{
    entity* target;
    Camera3D camera;
    Vector3 offset;
} thirdPersonCamera;

void updateCamera(thirdPersonCamera* camera){
    //Vector3 IdealOffset = >

    Vector3 targetPos = camera->target->position;
    camera->camera.position = Vector3Add(targetPos, camera->offset);
    camera->camera.target = targetPos;
}

void initCamera(thirdPersonCamera* camera, entity* target){
    camera->camera.position = (Vector3){-3.0f, 2.5f,0.0f};
    camera->camera.up = (Vector3){0.0f,1.0f,0.0f};
    camera->camera.fovy = 65.0f;
    camera->camera.projection = CAMERA_PERSPECTIVE;
    camera->target = target;
    camera->offset = Vector3Subtract(camera->camera.position, target->position);
}



#endif

