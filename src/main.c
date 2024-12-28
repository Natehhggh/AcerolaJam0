#include <stdint.h>
#include <unistd.h>
#include "raylib.h"
#include "core.h"
#include "camera.c"
#include "rlights.h"
#include "player.c"
#include "scene.c"

//FPS Notes:
//white screen, ~14-15kfps
//Initial ECS , ~13kfps
//flag ~8kfps

//TODO: Fix name convention, not sure what im doing here, it's all over the place

void setup(){
    InitWindow(screenWidth,screenHeight,"Jam Game");
    //SetTargetFPS(60);
    initScene();
}


//TODO: move to some rendering file, dont want to look at rendering logic here
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

//TODO: move to some rendering file, dont want to look at rendering logic here
void drawSprites(){
    for(int8_t i = 0; i < MAX_ENTITIES; ++i){
        if(entities[i].flags | Active && entities[i].flags | SpriteRendered){
            DrawTextureRec(entities[i].spritesheet, entities[i].frameRec, (Vector2){entities[i].position.x, entities[i].position.y} , WHITE);
        }
    }
}

//TODO: rework from frames/frame to delta time
void updateSprites(){
    for(int8_t i = 0; i < MAX_ENTITIES; ++i){
        if(entities[i].flags | Active && entities[i].flags | SpriteRendered){
            entities[i].frameCounter++;
            if(entities[i].frameCounter >= entities[i].frameRate){
                entities[i].frameCounter = 0;
                //Why is this not working?
                //entities[i].currentFrame = (entities[i].currentFrame + 1) % entities[i].spriteFrames;
                entities[i].currentFrame++;
                if(entities[i].currentFrame >= entities[i].spriteFrames) entities[i].currentFrame = 0;

                entities[i].frameRec.x = (float)entities[i].currentFrame * (float)entities[i].spritesheet.width/entities[i].spriteFrames;
            }
        }
    }
}

void DrawScene(){
    BeginDrawing();
    {
        ClearBackground(RAYWHITE);
        
        if(rendering == _2d){
            BeginMode2D(camera2d.camera);
            {
                drawSprites();
            }

            EndMode2D();
        }else{
            BeginMode3D(camera.camera);
            {
                //TODO: Render struct 
                drawPrimativeShapes();
                DrawGrid(10,1.0f);

            }
            EndMode3D();
        }

        entity* target = camera.target;
        DrawFPS(10,10);
        DrawText(TextFormat("Frame time: %02.04f ms", GetFrameTime()* 1000), 10, 30, 20, GREEN);
        DrawText(TextFormat("Target x: %02.02f y: %02.02f z: %02.02f", target->position.x, target->position.y, target->position.z), 800, 50, 12, RED);
        //DrawText(TextFormat("frame: %02i count: %02i frames: %02i rate: %02i", target->currentFrame, target->frameCounter, target->spriteFrames, target->frameRate), 800, 70, 12, RED);
    }
    EndDrawing();
}



void GameLoop(){
    while(!WindowShouldClose())
    {
        HandleInput();
        updateSprites();
        updateCamera(&camera);
        //updateCamera2d(&camera2d);
        DrawScene();
    }
}

int main()
{
    setup();
    GameLoop();
    return 0;
}


