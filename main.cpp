#include "raylib.h"


int main()
{
    // window dimensions
    const int windowWidth{512};
    const int windowHeight{380};
    // Initialize the window
    InitWindow(windowWidth, windowHeight, "Dasher Dapper Game");

    // acceleration due to gravity (pixels/sec) / sec
    const int gravity{1'000};

    // nebula varibales
    Texture2D nebula = LoadTexture("textures/12_nebula_spritesheet.png");
    // Rectangle nebRec{0.0, 0.0, nebula.width/8, nebula.height/8};
    Rectangle nebRec;
    nebRec.height = int(nebula.height/8);
    nebRec.width = int(nebula.width/8);
    nebRec.x = 0;
    nebRec.y = 0;
    Vector2 nebPos{windowWidth, windowHeight - nebRec.height};

    // nebula animation variables
    int nebFrame{};
    const float nebUpdateTime{1.0/12.0};
    float nebRunningTime{};

    // nebula x velocity
    int nebVel{-200};

    // Scarfy variables 
    Texture2D scarfy = LoadTexture("textures/scarfy.png");
    Rectangle scarfyRec;
    scarfyRec.width = scarfy.width/6;
    scarfyRec.height = scarfy.height;
    scarfyRec.x = 0;
    scarfyRec.y = 0;
    Vector2 scarfyPos;
    scarfyPos.x = windowWidth/2 - scarfyRec.width/2;
    scarfyPos.y = windowHeight - scarfyRec.height;

    // animation frame
    int frame{};

    // assigning updateTime for animation to update
    const float updateTime{1.0/12.0};
    float runningTime{};


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
        if (scarfyPos.y >= windowHeight - scarfyRec.height)
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
        nebPos.x += nebVel * dT;

        // update scarfy position
        scarfyPos.y += velocity * dT;

        // update scarfy animation frame
        if (!isInAir) 
        {
            runningTime += dT;
            if (runningTime >= updateTime)
            {
                runningTime = 0;
                // Update animation frame
                scarfyRec.x = frame * scarfyRec.width;
                frame++;
                if (frame > 5)
                {
                    frame = 0;
                }
            }
        }

        // update nebula animation frame
        nebRunningTime += dT;
        if (nebRunningTime >= nebUpdateTime)
        {
            nebRunningTime = 0.0;
            nebRec.x = nebFrame * nebRec.width;
            nebFrame++;
            if (nebFrame > 7)
            {
                nebFrame = 0;
            }
        }
        
        // Draw Nebula
        DrawTextureRec(nebula, nebRec, nebPos, BLACK);

        // Draw Scarfy
        DrawTextureRec(scarfy, scarfyRec, scarfyPos, WHITE);

        // Stop Drawing
        EndDrawing();
    }

    // Unload texture before closing the program
    UnloadTexture(scarfy);
    UnloadTexture(nebula);
    CloseWindow();
}