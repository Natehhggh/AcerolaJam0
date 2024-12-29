#ifndef __NATE_PLAYER__
#define __NATE_PLAYER__ 

#include "raylib.h"
#include "raymath.h"
#include "core.h"
#include <stdint.h>

//TODO: return input state, move logic to another spot
void HandleInput(float deltaTime){
    
        float playerSpeed = 10.0f * deltaTime; 
        Vector3 playerInputDir = {0.0f,0.0f,0.0f};
        float deltaScale = 0.0f;

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


        if(IsKeyDown(KEY_KP_0)){
            SetTargetFPS(10000000);
        }
        if(IsKeyDown(KEY_KP_1)){
            SetTargetFPS(15);
        }
        if(IsKeyDown(KEY_KP_2)){
            SetTargetFPS(30);
        }
        if(IsKeyDown(KEY_KP_3)){
            SetTargetFPS(60);
        }
        if(IsKeyDown(KEY_KP_4)){
            SetTargetFPS(120);
        }
        if(IsKeyDown(KEY_KP_ADD)){
            deltaScale = 1.0f * deltaTime;
        }
        if(IsKeyDown(KEY_KP_SUBTRACT)){
            deltaScale = -1.0f * deltaTime;
        }


        playerInputDir = Vector3Normalize(playerInputDir);
        playerInputDir = Vector3Scale(playerInputDir, playerSpeed);

        for(int i = 0; i < MAX_ENTITIES; i++){
            if(entities[i].flags & Active && entities[i].flags & PlayerControlled){
                entities[i].position = Vector3Add(playerInputDir, entities[i].position);
                entities[i].scale = Vector3AddValue(entities[i].scale, deltaScale);
            }
        }
        //transforms[playerInput.transformId].position = Vector3Add(transforms[playerInput.transformId].position, playerInputDir);

}


#endif
