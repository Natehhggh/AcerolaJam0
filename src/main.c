#include "raylib.h"
#include "raymath.h"

Camera3D camera = {0};


struct Player {
    Vector3 position;
    Vector3 rotation;
    Vector3 scale;
};

void initCamera(){
    camera.position = (Vector3){-3.0f, 2.5f,0.0f};
    camera.up = (Vector3){0.0f,1.0f,0.0f};
    camera.fovy = 65.0f;
    camera.projection = CAMERA_PERSPECTIVE;
}

Vector3 cameraOffset = {0};

struct Player player = {
    .position = {0.0f,0.0f,0.0f},
    .rotation = {0.0f,0.0f,0.0f},
    .scale = {1.5f,1.0f,1.0f}
};


void InitScene(){
    InitWindow(800,800,"Jam Game");
    SetTargetFPS(60);
    initCamera();
    cameraOffset = Vector3Subtract(camera.position,player.position);
}

void DrawScene(){
    BeginDrawing();
    {

        ClearBackground(RAYWHITE);

        BeginMode3D(camera);
        {
            DrawCubeV(player.position, player.scale, BLUE);

            DrawGrid(10,1.0f);
        }
        EndMode3D();
        DrawFPS(10,10);
    }
    EndDrawing();

}
            

int main()
{
    InitScene();

    while(!WindowShouldClose())
    {
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



        float playerSpeed = 10.0f * GetFrameTime(); 
        playerInputDir = Vector3Normalize(playerInputDir);
        playerInputDir = Vector3Scale(playerInputDir, playerSpeed);
        player.position = Vector3Add(playerInputDir, player.position);
        camera.position = Vector3Add(player.position, cameraOffset);

        camera.target = player.position;
        DrawScene();
    }


    return 0;
}


