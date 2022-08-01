#include "raylib.h"

struct AnimData 
{
    Rectangle rec;
    Vector2 pos;
    int frame;
    float updateTime;
    float runningTime;
};

bool isOnGround (AnimData data, int windowHeight)
{
    return data.pos.y >= windowHeight - data.rec.height;
};



int main()
{
    // array with window dimensions
    int windowDimensions[2];
    windowDimensions[0] = 512;
    windowDimensions[1] = 380;

    // Initialize the window
    InitWindow(windowDimensions[0], windowDimensions[1], "Dasher Dapper Game");

    // acceleration due to gravity (pixels/sec) / sec
    const int gravity{1'000};

    // nebula varibales
    Texture2D nebula = LoadTexture("textures/12_nebula_spritesheet.png");

    const int sizeOfNebulae{10};
    AnimData nebulae[sizeOfNebulae]{};

    for (int i = 0; i < sizeOfNebulae; i++)
    {
        nebulae[i].rec.x = 0.0;
        nebulae[i].rec.y = 0.0;
        nebulae[i].rec.width = int(nebula.width/8);
        nebulae[i].rec.height = int(nebula.height/8);
        nebulae[i].pos.y = windowDimensions[1] - nebula.height/8;
        nebulae[i].frame = 0;
        nebulae[i].runningTime = 0.0;
        nebulae[i].updateTime = 0.0;

        nebulae[i].pos.x = windowDimensions[0] + i*300;
    }

    // nebula x velocity
    int nebVel{-200};

    // Scarfy variables 
    Texture2D scarfy = LoadTexture("textures/scarfy.png");
    AnimData scarfyData;
    scarfyData.rec.width = scarfy.width/6;
    scarfyData.rec.height = scarfy.height;
    scarfyData.rec.x = 0;
    scarfyData.rec.y = 0;
    scarfyData.pos.x = windowDimensions[0]/2 - scarfyData.rec.width/2;
    scarfyData.pos.y = windowDimensions[1] - scarfyData.rec.height;
    scarfyData.frame = 0;
    scarfyData.updateTime = 1.0/12.0;
    scarfyData.runningTime = 0.0;

    // Defining Velocity
    int velocity{0};

    // Defining jupm velocity
    const int jupmVel{-600};

    // creating variable to check if object is in air
    bool isInAir{};

    SetTargetFPS(60);
    while (!WindowShouldClose())
    {
        // delta time (time since last frame)
        float dT{GetFrameTime()};
        
        // Start Drawing
        BeginDrawing();
        ClearBackground(WHITE);

        // ENVIRONMENT: performing ground check and applying gravity
        if (isOnGround(scarfyData, windowDimensions[1]))
        {
            // rectangle is on the ground - do not apply gravity
            velocity = 0;
            isInAir = false;
        }
        else {
            //apply gravity
            velocity += gravity * dT;
            isInAir = true;
        }

        // ENVIRONMENT: Jump Check
        if (IsKeyPressed(KEY_SPACE) && !isInAir)
        {
            velocity += jupmVel;
        }

        // update nebula position
        for (int i = 0; i < sizeOfNebulae; i++)
        {
            // update the position of each nebula
            nebulae[i].pos.x += nebVel * dT;
        }


        // update scarfy position
        scarfyData.pos.y += velocity * dT;

        // update scarfy animation frame
        if (!isInAir) 
        {
            scarfyData.runningTime += dT;
            if (scarfyData.runningTime >= scarfyData.updateTime)
            {
                scarfyData.runningTime = 0;
                // Update animation frame
                scarfyData.rec.x = scarfyData.frame * scarfyData.rec.width;
                scarfyData.frame++;
                if (scarfyData.frame > 5)
                {
                    scarfyData.frame = 0;
                }
            }
        }

        for (int i = 0; i < sizeOfNebulae; i++)
        {
            // update nebula animation frame
            nebulae[i].runningTime += dT;
            if (nebulae[i].runningTime >= nebulae[i].updateTime)
            {
                nebulae[i].runningTime = 0.0;
                nebulae[i].rec.x = nebulae[i].frame * nebulae[i].rec.width;
                nebulae[i].frame++;
                if (nebulae[i].frame > 7)
                { 
                    nebulae[i].frame = 0;
                }
            }
        }

        for (int i = 0; i < sizeOfNebulae; i++)
        {
            // draw nebula
            DrawTextureRec(nebula, nebulae[i].rec, nebulae[i].pos, WHITE);
        }

        // Draw Scarfy
        DrawTextureRec(scarfy, scarfyData.rec, scarfyData.pos, WHITE);

        // Stop Drawing
        EndDrawing();
    }

    // Unload texture before closing the program
    UnloadTexture(scarfy);
    UnloadTexture(nebula);
    CloseWindow();
}