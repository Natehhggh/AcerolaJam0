#ifndef __NATE_ENTITY__
#define __NATE_ENTITY__

#include <stdio.h>
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

entity* newEntity(){

    entity* newEntity = NULL;  
    for(int i = 0; i < MAX_ENTITIES; i++){
        if(entities[i].flags & Free){
            entities[i].flags |= Free;
            newEntity = &entities[i];
            break;
        }
    }
    return newEntity;
}

void freeEntity(entity* entity){
    entity->flags = 0;
}
void setDefaultData(){
    for(int i = 0; i < MAX_ENTITIES; ++i){
        entities[i].flags = Free;
    }
}

//TODO: Move to player file
void initPlayer(){
    entity* playerEntity = newEntity();
    playerEntity->position = (Vector3){0.0f,0.0f,0.0f};
    playerEntity->rotation = (Vector3){0.0f,0.0f,0.0f};
    playerEntity->scale = (Vector3){2.5f,1.0f,1.0f};
    playerEntity->shape = Cube;
    playerEntity->flags = playerEntity->flags | ShapeRendered;
    playerEntity->flags = playerEntity->flags | Active;
    playerEntity->flags = playerEntity->flags | PlayerControlled;
    
    
    initCamera(&camera, playerEntity);
}

void initEntities(){

    setDefaultData();
    printf("Defaults set\n");
    initPlayer();
    printf("Player Init\n");
}


#endif
