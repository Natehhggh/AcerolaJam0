#include <stdint.h>
#include <unistd.h>
#include "raylib.h"
#include "raymath.h"
#include "core.h"
#include "camera.c"
#include "rlights.h"
#include "entity.c"
#include <stdio.h>

//FPS Notes:
//white screen, ~14-15kfps
//Initial ECS , ~13kfps
//flag ~8kfps



void InitScene(){
    InitWindow(1200,800,"Jam Game");
//    SetTargetFPS(60);
    printf("Init Scene\n");
    initEntities();
    printf("Setup complete\n");
}


//Might be good for debugging uses, figure it out later
//TODO: if I care to, make these more consistant in what values map to what
void drawPrimativeShapes(){
    for(int8_t i = 0; i < MAX_ENTITIES; ++i){
        if(entities[i].flags | Active && entities[i].flags | ShapeRendered){
            switch(entities[i].shape){
                case Cube:
                    DrawCubeV(entities[i].position, entities[i].scale, BLUE);
                    break;
                case Sphere:
                    DrawSphere(entities[i].position, entities[i].scale.x, RED);
                    break;
                case Cylinder:
                    DrawCubeV(entities[i].position, entities[i].scale, RED);
                    break;
                case Capsule:
                    DrawCubeV(entities[i].position, entities[i].scale, RED);
                    break;
                case Plane:
                    DrawPlane(entities[i].position,
                            (Vector2){entities[i].scale.x, entities[i].scale.z}, RED);
                    break;
            }
        }
    }
}

void DrawScene(){
    BeginDrawing();
    {
        ClearBackground(RAYWHITE);

        BeginMode3D(camera.camera);
        {
            //TODO: Render struct 
            drawPrimativeShapes();
            DrawGrid(10,1.0f);

        }
        EndMode3D();
        entity* target = camera.target;
        DrawFPS(10,10);
        DrawText(TextFormat("Frame time: %02.04f ms", GetFrameTime()* 1000), 10, 30, 20, GREEN);
        DrawText(TextFormat("Target x: %02.02f y: %02.02f z: %02.02f", target->position.x, target->position.y, target->position.z), 800, 50, 12, RED);
    }
    EndDrawing();
}


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
        //playerInputDir = Vector3Normalize(playerInputDir);
        playerInputDir = Vector3Scale(playerInputDir, playerSpeed);
        for(int i = 0; i < MAX_ENTITIES; i++){
            if(entities[i].flags & Active && entities[i].flags & PlayerControlled){
                entities[i].position = Vector3Add(playerInputDir, entities[i].position);
            }
        }
        //transforms[playerInput.transformId].position = Vector3Add(transforms[playerInput.transformId].position, playerInputDir);

}

void GameLoop(){
    printf("Starting Game Loop\n");
    while(!WindowShouldClose())
    {
        HandleInput();
        updateCamera(&camera);
        DrawScene();
    }
}

int main()
{
    InitScene();
    GameLoop();
    return 0;
}


