#ifndef __NATE_ENTITY__
#define __NATE_ENTITY__

#include <stdint.h>
#include <string.h>
#include <unistd.h>
#include "raylib.h"
#include "core.h"
#include "camera.c"



#define MAX_ENTITIES 100
//TODO: get component by Id methods for camera and controllers
//TODO: sort entities by active/alive


//-- Objects --
entity entities[MAX_ENTITIES];
thirdPersonCamera camera = {0};
entityInput input = {0};

int8_t newEntity(char name[10], Vector3 position, Vector3 rotation, Vector3 scale, int char* shapeStr, bool isActive){
    int8_t i = 0;
    while(!(entities[i].id < 0)){
        ++i;
    }
    entities[i].id = i;
    strcpy(entities[i].debugName, name);
    transforms[i].position = position;
    transforms[i].rotation = rotation;
    transforms[i].scale = scale;
    shapeType shape;
    if(strcmp(shapeStr,"cube")){
        shape = Cube;
    }
    else if(strcmp(shapeStr,"cylinder")){
        shape = Cylinder;
    }

    else if(strcmp(shapeStr,"capsule")){
        shape = Capsule;
    }
    else if(strcmp(shapeStr,"plane")){
        shape = Plane;
    }

    primativeRenderers[i].shape = shape;
    primativeRenderers[i].isActive = isActive;
    return i;
}

void releaseEntity(int8_t entityId){
    entities[entityId].id = -128;
    for(int i = 0; i < MAX_ENTITIES; ++i){
        if(transforms[i].entityId == entityId){
        transforms[i].entityId = -127;
        }
        if(primativeRenderers[i].entityId == entityId){
            primativeRenderers[i].isActive = false;
        }
    }
}
void setDefaultData(){
    //Set useful data to unlinked negative values;
    for(int i = 0; i < MAX_ENTITIES; ++i){
        entities[i].id = -128;
    }
}

void initPlayer(){
    int8_t entityId = newEntity("Player");
    int8_t transformId = newTransform(entityId, (Vector3){0.0f,0.0f,0.0f}, (Vector3){0.0f,0.0f,0.0f}, (Vector3){2.5f,1.0f,1.0f});
    int8_t shapeId = newPrimativeRenderer(entityId, transformId, "cube", true);
    
    input.transformId = transformId;
    input.entityId = transforms[input.transformId].entityId;
    initCamera(&camera, transformId, transforms[transformId]);
}

void initEntities(){

    setDefaultData();
    initPlayer();

}


#endif
