#include <stdio.h>
#include "raylib.h"

int main() {
    InitWindow(800,800,"Jam Game");

    SetTargetFPS(60);

    while (!WindowShouldClose())
    {

        BeginDrawing();

            ClearBackground(RAYWHITE);

            DrawText("Congrats! You created your first window!", 190, 200, 20, LIGHTGRAY);

        EndDrawing();
    }


    return 0;
}
