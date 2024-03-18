#include "raylib.h"
#include "raymath.h"
#include <stdint.h>
#include <string.h>
//#include "player.c"


//TODO: Move structs to header
struct transform {
    int8_t entityId;
    Vector3 position;
    Vector3 rotation;
    Vector3 scale;
};

struct trackingCamera{
    int8_t transformId;
    Camera3D camera;
    Vector3 offset;
};


struct entity{
    int8_t id;
    char debugName[10];
};

struct entityInput{
    int8_t entityId;
    int8_t transformId;
};


//-- Objects --
struct entity entities[100];
struct transform transforms[100];
struct trackingCamera camera = {0};
struct entityInput input = {0};


//Good Enough, just assuming I have 1 camera for now, and it's what it is
void initCamera(){
    camera.camera.position = (Vector3){-3.0f, 2.5f,0.0f};
    camera.camera.up = (Vector3){0.0f,1.0f,0.0f};
    camera.camera.fovy = 65.0f;
    camera.camera.projection = CAMERA_PERSPECTIVE;
    camera.transformId = 0;
    camera.offset = Vector3Subtract(camera.camera.position, transforms[camera.transformId].position);
}


struct trackingCamera updateTrackingCamera(struct trackingCamera camera){
    camera.camera.position = Vector3Add(transforms[camera.transformId].position, camera.offset);
    camera.camera.target = transforms[camera.transformId].position;
    return camera;
}



void initEntities(){

    entities[0].id = 0;
    strcpy(entities[0].debugName, "Player");
    
    transforms[0].position = (Vector3){0.0f,0.0f,0.0f};
    transforms[0].rotation = (Vector3){0.0f,0.0f,0.0f};
    transforms[0].scale = (Vector3){2.5f,1.0f,1.0f};
    transforms[0].entityId = 0;
    
    input.transformId = 0;
    input.entityId = transforms[input.transformId].entityId;

}

void InitScene(){
    InitWindow(800,800,"Jam Game");
    SetTargetFPS(60);
    initEntities();
    initCamera();
}



void DrawScene(){
    BeginDrawing();
    {

        ClearBackground(RAYWHITE);

        BeginMode3D(camera.camera);
        {
            //TODO: Render struct 
            DrawCubeV(transforms[0].position, transforms[0].scale, BLUE);

            DrawGrid(10,1.0f);
        }
        EndMode3D();
        DrawFPS(10,10);
    }
    EndDrawing();

}

void HandleInput(struct entityInput playerInput){
    
        float playerSpeed = 10.0f * GetFrameTime(); 
        Vector3 playerInputDir = {0.0f,0.0f,0.0f};

        if(IsKeyDown(KEY_W)){
            playerInputDir.x = 1.0f;
        }
        if(IsKeyDown(KEY_A)){
            playerInputDir.z = -1.0f;
        }
        //camera.position = Vector3Add(camera.position, playerInputDir);
        if(IsKeyDown(KEY_S)){
            playerInputDir.x = -1.0f;
        }
        if(IsKeyDown(KEY_D)){
            playerInputDir.z = 1.0f;
        }

        playerInputDir = Vector3Normalize(playerInputDir);
        playerInputDir = Vector3Scale(playerInputDir, playerSpeed);
        transforms[playerInput.transformId].position = Vector3Add(
                playerInputDir, transforms[playerInput.transformId].position);

}


int main()
{

    InitScene();

    while(!WindowShouldClose())
    {
        HandleInput(input);
        camera = updateTrackingCamera(camera);
        DrawScene();
    }


    return 0;
}


