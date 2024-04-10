#include <stdint.h>
#include <unistd.h>
#include "raylib.h"
#include "raymath.h"
#include "core.h"
#include "camera.c"
#include "rlights.h"
#include "entity.c"

//FPS Notes:
//white screen, ~14-15kfps
//Initial ECS , ~13kfps





void InitScene(){
    InitWindow(1200,800,"Jam Game");
//    SetTargetFPS(60);
    initEntities();
}


//Might be good for debugging uses, figure it out later
//TODO: if I care to, make these more consistant in what values map to what
void drawPrimativeShapes(){
    for(int8_t i = 0; i < MAX_ENTITIES; ++i){
        if(primativeRenderers[i].isActive){
            switch(primativeRenderers[i].shape){
                case Cube:
                    DrawCubeV(transforms[primativeRenderers[i].transformId].position, transforms[primativeRenderers[i].transformId].scale, BLUE);
                    break;
                case Sphere:
                    DrawSphere(transforms[primativeRenderers[i].transformId].position, transforms[primativeRenderers[i].transformId].scale.x, RED);
                    break;
                case Cylinder:
                    DrawCubeV(transforms[primativeRenderers[i].transformId].position, transforms[primativeRenderers[i].transformId].scale, RED);
                    break;
                case Capsule:
                    DrawCubeV(transforms[primativeRenderers[i].transformId].position, transforms[primativeRenderers[i].transformId].scale, RED);
                    break;
                case Plane:
                    DrawPlane(transforms[primativeRenderers[i].transformId].position,
                            (Vector2){transforms[primativeRenderers[i].transformId].scale.x,transforms[primativeRenderers[i].transformId].scale.z}, RED);
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
        transform target = transforms[camera.transformId];
        DrawFPS(10,10);
        DrawText(TextFormat("Frame time: %02.04f ms", GetFrameTime()* 1000), 10, 30, 20, GREEN);
        DrawText(TextFormat("CameraTargetID: %02i", camera.transformId), 800, 30, 12, RED);
        DrawText(TextFormat("Target x: %02.02f y: %02.02f z: %02.02f", target.position.x, target.position.y, target.position.z), 800, 50, 12, RED);
    }
    EndDrawing();
}


void HandleInput(entityInput playerInput){
    
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
        transforms[playerInput.transformId].position = Vector3Add(playerInputDir, transforms[playerInput.transformId].position);
        //transforms[playerInput.transformId].position = Vector3Add(transforms[playerInput.transformId].position, playerInputDir);

}

void GameLoop(){
    while(!WindowShouldClose())
    {
        HandleInput(input);
        transform cameraTarget = transforms[camera.transformId];
        updateCamera(&camera, cameraTarget);
        DrawScene();
    }
}

int main()
{
    InitScene();
    GameLoop();
    return 0;
}


