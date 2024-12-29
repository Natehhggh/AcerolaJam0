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
//Initial ECS , ~13kfps flag ~8kfps

//TODO: Fix name convention, not sure what im doing here, it's all over the place
//TODO: Add Screenshot system
//TODO: Check Flags Raylib, named vsync

void setup(){
    InitWindow(screenWidth,screenHeight,"Jam Game");
    SetTargetFPS(60);
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
            Rectangle dest = {
                entities[i].position.x,
                entities[i].position.y,
                entities[i].spriteWidth * entities[i].scale.x,
                entities[i].spriteHeight * entities[i].scale.y
            };
            DrawTexturePro(entities[i].spritesheet, entities[i].sourceRec, dest, (Vector2){dest.width / 2.0f, dest.height / 2.0f}, 0.0f, WHITE);
        }
    }
}

//TODO: rework from frames/frame to delta time
void updateSprites(float dt){
    for(int8_t i = 0; i < MAX_ENTITIES; ++i){
        if(entities[i].flags | Active && entities[i].flags | SpriteRendered){
            entities[i].frameTimeAcc+= dt;

            if(entities[i].frameTimeAcc >= entities[i].frameTime){
                entities[i].frameTimeAcc = 0.0f;
                //Why is this not working?
                //entities[i].currentFrame = (entities[i].currentFrame + 1) % entities[i].spriteFrames;
                entities[i].currentFrame++;
                if(entities[i].currentFrame >= entities[i].spriteFrames) entities[i].currentFrame = 0;

                entities[i].sourceRec.x = (float)entities[i].currentFrame * (float)entities[i].spritesheet.width/entities[i].spriteFrames;
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
                DrawLine((int)camera2d.camera.target.x, -screenHeight*10, (int)camera2d.camera.target.x, screenHeight*10, GREEN);
                DrawLine(-screenWidth*10, (int)camera2d.camera.target.y, screenWidth*10, (int)camera2d.camera.target.y, GREEN);
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



//TODO: draw scene only on a delta time?
void GameLoop(){
    while(!WindowShouldClose())
    {
        float dt = GetFrameTime();
        HandleInput(dt);
        updateSprites(dt);
        updateCamera(&camera);
        //updateCamera2d(&camera2d);
        DrawScene();
    }
}
//TODO: Do this
//come back to it, going to pass dt into updates and use that for now
//https://gafferongames.com/post/fix_your_timestep/
void GameLoop2(){
    //clock_t clockOld, timeNew;
     
    //double timeOld = time(NULL);
    double t = 0.0f;
    double dt = 0.01f;
    double accumulator = 0.0f;
    while(!WindowShouldClose())
    {

        //double timeNew = time(NULL);
        //double timeSince = timeNew - timeOld;
        //timeOld = timeNew;
        //if(timeSince > 0.25){
         //   timeSince = 0.25;
        //}

        

        //HandleInput();
        
        //updateSprites();
        //updateCamera(&camera);
        //updateCamera2d(&camera2d);
        //DrawScene();
    }

}

int main()
{
    setup();
    GameLoop();
    return 0;
}


