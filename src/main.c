#include <stdint.h>
#include <string.h>
#include <unistd.h>
#include "raylib.h"
#include "raymath.h"
#include "core.h"
#include "camera.c"

//FPS Notes:
//white screen, ~14-15kfps
//Initial ECS , ~13kfps


#define MAX_ENTITIES 100

//TODO: get component by Id methods for camera and controllers
//TODO: sort entities by active/alive


//-- Objects --
entity entities[MAX_ENTITIES];
transform transforms[MAX_ENTITIES];
primativeRenderer primativeRenderers[MAX_ENTITIES];
thirdPersonCamera camera = {0};
entityInput input = {0};
Model model = {0};
float modelSize = 1.0f;

int8_t newEntity(char name[10]){
    int8_t i = 0;
    while(!(entities[i].id < 0)){
        ++i;
    }
    entities[i].id = i;
    strcpy(entities[i].debugName, name);
    return i;
}

int8_t newTransform(int8_t entityID, Vector3 position, Vector3 rotation, Vector3 scale){
    int8_t i = 0;
    while(!(transforms[i].entityId < 0)){
        ++i;
    }
    transforms[i].entityId = entityID;
    transforms[i].position = position;
    transforms[i].rotation = rotation;
    transforms[i].scale = scale;

    return i;
}

int8_t newPrimativeRenderer(int8_t entityId, int8_t transformId, shapeType shape, bool isActive){
    int8_t i = 0;
    while(!(primativeRenderers[i].transformId < 0)){
        ++i;
    }
    primativeRenderers[i].entityId = entityId;
    primativeRenderers[i].transformId = transformId;
    primativeRenderers[i].shape = shape;
    primativeRenderers[i].isActive = isActive;
    return i;
}


void releaseEntity(int8_t entityId){
    entities[entityId].id = -128;
    for(int i = 0; i < MAX_ENTITIES; ++i){
        if(transforms[i].entityId == entityId){
        transforms[i].entityId = -127;
        }
        if(primativeRenderers[i].entityId == entityId){
            primativeRenderers[i].entityId = -126;
            primativeRenderers[i].transformId = -126;
            primativeRenderers[i].isActive = false;
        }
    }
}


void setDefaultData(){
    //Set useful data to unlinked negative values;
    for(int i = 0; i < MAX_ENTITIES; ++i){
        entities[i].id = -128;
        transforms[i].entityId = -127;
        primativeRenderers[i].entityId = -126;
        primativeRenderers[i].transformId = -126;
    }
}

void initPlayer(){
    int8_t entityId = newEntity("Player");
    int8_t transformId = newTransform(entityId, (Vector3){0.0f,0.0f,0.0f}, (Vector3){0.0f,0.0f,0.0f}, (Vector3){2.5f,1.0f,1.0f});
    int8_t shapeId = newPrimativeRenderer(entityId, transformId, Cube, true);
    
    input.transformId = transformId;
    input.entityId = transforms[input.transformId].entityId;
    initCamera(&camera, transformId, transforms[transformId]);
}

void initEntities(){

    setDefaultData();
    initPlayer();

}

void InitScene(){
    InitWindow(1200,800,"Jam Game");
//    SetTargetFPS(60);
    initEntities();
    //ChangeDirectory("../assets/Models/OBJ format/");
    chdir("../assets/Models/glTF format/");
    Model playerModel = LoadModel("ship_light.gltf");
    model = playerModel;
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
            DrawModel(model, (Vector3){0.0f,0.0f,0.0f},modelSize, WHITE);
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
        if(IsKeyDown(KEY_KP_ADD)){
            modelSize += 0.1f * GetFrameTime();
        }
        if(IsKeyDown(KEY_KP_SUBTRACT)){
            modelSize -= 0.1f * GetFrameTime();
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


