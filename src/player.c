#ifndef __NATE_PLAYER__
#define __NATE_PLAYER__ 

#include "raylib.h"
#include "raymath.h"
#include "core.h"

void HandleInput(){
    
        float playerSpeed = 10.0f * GetFrameTime(); 
        Vector3 playerInputDir = {0.0f,0.0f,0.0f};

        if(IsKeyDown(KEY_W)){
            playerInputDir.x = 1.0f;
        }
        if(IsKeyDown(KEY_A)){
            playerInputDir.z = -1.0f;
        }
        if(IsKeyDown(KEY_S)){
            playerInputDir.x = -1.0f;
        }
        if(IsKeyDown(KEY_D)){
            playerInputDir.z = 1.0f;
        }
        if(IsKeyDown(KEY_LEFT_CONTROL)){
            playerInputDir.y = -1.0f;
        }
        if(IsKeyDown(KEY_SPACE)){
            playerInputDir.y = 1.0f;
        }

        if(IsKeyDown(KEY_F2)){
            rendering = _2d;
        }
        if(IsKeyDown(KEY_F3)){
            rendering = _3d;
        }

        playerInputDir = Vector3Normalize(playerInputDir);
        playerInputDir = Vector3Scale(playerInputDir, playerSpeed);

        for(int i = 0; i < MAX_ENTITIES; i++){
            if(entities[i].flags & Active && entities[i].flags & PlayerControlled){
                entities[i].position = Vector3Add(playerInputDir, entities[i].position);
            }
        }
        //transforms[playerInput.transformId].position = Vector3Add(transforms[playerInput.transformId].position, playerInputDir);

}


#endif
