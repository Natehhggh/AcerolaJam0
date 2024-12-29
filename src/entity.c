#ifndef __NATE_ENTITY__
#define __NATE_ENTITY__

#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include "core.h"


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
    entity->flags = Free;
}
void setDefaultData(){
    for(int i = 0; i < MAX_ENTITIES; ++i){
        entities[i].flags = Free;
    }
}




#endif
