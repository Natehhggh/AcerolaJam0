#include <stdio.h>
#include "raylib.h"

Camera3D camera = {0};
Vector3 playerPosition = {0,0,0};

void initCamera(){
    camera.position = (Vector3){2.5f, 2.5f,3.0f};
    camera.target = (Vector3){0.0f, 0.0f, 0.7f};
    camera.up = (Vector3){0.0f,1.0f,0.0f};
    camera.fovy = 65.0f;
    camera.projection = CAMERA_PERSPECTIVE;
}




int main() {
    InitWindow(800,800,"Jam Game");

    SetTargetFPS(60);
    initCamera();

    while (!WindowShouldClose())
    {

        BeginDrawing();

        ClearBackground(RAYWHITE);

        BeginMode3D(camera);

        DrawCube(playerPosition, 1.0f,1.0f,1.0f, BLUE);

        DrawGrid(10,1.0f);
        EndMode3D();

        DrawFPS(10,10);
        EndDrawing();

    }


    return 0;
}


