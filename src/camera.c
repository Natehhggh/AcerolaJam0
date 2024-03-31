#ifndef __NATE_CAMERA__
#define __NATE_CAMERA__

#include "raylib.h"
#include <stdint.h>
#include "core.h"

//TODO: enum for other cameras like first person, just get any camera in here
typedef struct thirdPersonCamera{
    int8_t transformId;
    Camera3D camera;
    Vector3 offset;
} thirdPersonCamera;

void updateCamera(thirdPersonCamera* camera, transform targetTransform){
    //Vector3 IdealOffset = 
    camera->camera.position = Vector3Add(targetTransform.position, camera->offset);
    camera->camera.target = targetTransform.position;
}

//TODO: refactor, moving here to clean up main
//Good Enough, just assuming I have 1 camera for now, and it's what it is
void initCamera(thirdPersonCamera* camera, int8_t transformId, transform targetTransform){
    camera->camera.position = (Vector3){-3.0f, 2.5f,0.0f};
    camera->camera.up = (Vector3){0.0f,1.0f,0.0f};
    camera->camera.fovy = 65.0f;
    camera->camera.projection = CAMERA_PERSPECTIVE;
    camera->transformId = transformId;
    camera->offset = Vector3Subtract(camera->camera.position, targetTransform.position);
}



#endif

