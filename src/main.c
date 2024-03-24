#include "raylib.h"
#include "raymath.h"
#include <stdint.h>
#include <string.h>
#include "core.h"


//FPS Notes:
//white screen, ~14-15kfps
//Initial ECS , ~13kfps



#define MAX_ENTITIES 100

//TODO: get component by Id methods for camera and controllers
//TODO: sort entities by active/alive


//-- Objects --
struct entity entities[MAX_ENTITIES];
struct transform transforms[MAX_ENTITIES];
struct shapeRender shapeRenders[MAX_ENTITIES];
struct trackingCamera camera = {0};
struct entityInput input = {0};


//Good Enough, just assuming I have 1 camera for now, and it's what it is
void initCamera(int8_t transformId){
    camera.camera.position = (Vector3){-3.0f, 2.5f,0.0f};
    camera.camera.up = (Vector3){0.0f,1.0f,0.0f};
    camera.camera.fovy = 65.0f;
    camera.camera.projection = CAMERA_PERSPECTIVE;
    camera.transformId = transformId;
    camera.offset = Vector3Subtract(camera.camera.position, transforms[camera.transformId].position);
}


struct trackingCamera updateTrackingCamera(struct trackingCamera camera){
    camera.camera.position = Vector3Add(transforms[camera.transformId].position, camera.offset);
    camera.camera.target = transforms[camera.transformId].position;
    return camera;
}

int8_t newEntity(char name[10]){
    int8_t i = 0;
    while(entities[i].id < 0){
        ++i;
    }
    entities[i].id = i;
    strcpy(entities[i].debugName, name);
    return i;
}

int8_t newTransform(int8_t entityID, Vector3 position, Vector3 rotation, Vector3 scale){
    int8_t i = 0;
    while(transforms[i].entityId < 0){
        ++i;
    }
    transforms[i].entityId = entityID;
    transforms[i].position = position;
    transforms[i].rotation = rotation;
    transforms[i].scale = scale;

    return i;
}

int8_t newShapeRender(int8_t entityId, int8_t transformId, enum shapeType shape, bool isActive){
    int8_t i = 0;
    while(shapeRenders[i].transformId < 0){
        ++i;
    }
    shapeRenders[i].entityId = entityId;
    shapeRenders[i].transformId = transformId;
    shapeRenders[i].shape = shape;
    shapeRenders[i].isActive = isActive;
    return i;
}


void releaseEntity(int8_t entityId){
    entities[entityId].id = -128;
    for(int i = 0; i < MAX_ENTITIES; ++i){
        if(transforms[i].entityId == entityId){
        transforms[i].entityId = -127;
        }
        if(shapeRenders[i].entityId == entityId){
            shapeRenders[i].entityId = -126;
            shapeRenders[i].transformId = -126;
            shapeRenders[i].isActive = false;
        }
    }
}


void setDefaultData(){
    //Set useful data to unlinked negative values;
    for(int i = 0; i < MAX_ENTITIES; ++i){
        entities[i].id = -128;
        transforms[i].entityId = -127;
        shapeRenders[i].entityId = -126;
        shapeRenders[i].transformId = -126;
    }
}

void initPlayer(){
    int8_t entityId = newEntity("Player");
    int8_t transformId = newTransform(entityId, (Vector3){0.0f,0.0f,0.0f}, (Vector3){0.0f,0.0f,0.0f}, (Vector3){2.5f,1.0f,1.0f});
    int8_t shapeId = newShapeRender(entityId, transformId, Cube, true);
    
    input.transformId = transformId;
    input.entityId = transforms[input.transformId].entityId;
    initCamera(transformId);
}

void initEntities(){

    setDefaultData();
    initPlayer();

}

void InitScene(){
    InitWindow(800,800,"Jam Game");
//    SetTargetFPS(60);
    initEntities();
}



void DrawShapes(){
    for(int8_t i = 0; i < MAX_ENTITIES; ++i){
        if(shapeRenders[i].isActive){
            switch(shapeRenders[i].shape){
                case Cube:
                    DrawCubeV(transforms[shapeRenders[i].transformId].position, transforms[shapeRenders[i].transformId].scale, BLUE);
                    break;
                case Sphere:
                    DrawSphere(transforms[shapeRenders[i].transformId].position, transforms[shapeRenders[i].transformId].scale.x, RED);
                    break;
                case Cylinder:
                    break;
                case Capsule:
                    break;
                case Plane:
                    DrawPlane(transforms[shapeRenders[i].transformId].position,
                            (Vector2){transforms[shapeRenders[i].transformId].scale.x,transforms[shapeRenders[i].transformId].scale.z}, RED);
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
            DrawShapes();
            DrawGrid(10,1.0f);
        }
        EndMode3D();
        DrawFPS(10,10);
    }
    EndDrawing();

}

void DrawBlankScene(){
    BeginDrawing();
    {
        ClearBackground(RAYWHITE);
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
        if(IsKeyDown(KEY_S)){
            playerInputDir.x = -1.0f;
        }
        if(IsKeyDown(KEY_D)){
            playerInputDir.z = 1.0f;
        }
        playerInputDir = Vector3Normalize(playerInputDir);
        playerInputDir = Vector3Scale(playerInputDir, playerSpeed);
        transforms[playerInput.transformId].position = Vector3Add(playerInputDir, transforms[playerInput.transformId].position);

}



void GameLoop(){
    while(!WindowShouldClose())
    {
        HandleInput(input);
        camera = updateTrackingCamera(camera);
        DrawScene();
    }
}

void EmptyGameLoop(){
    while(!WindowShouldClose())
    {
        DrawBlankScene();
    }
}
int main()
{
    InitScene();
    GameLoop();
    return 0;
}


