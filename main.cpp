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

    // Loading Scarfy Sprites
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

        // ENVIRONMENT: Defining Velocity
        if (IsKeyPressed(KEY_SPACE) && !isInAir)
        {
            velocity += jupmVel;
        }


        // update the position
        scarfyPos.y += velocity * dT;


        // update running time
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
        
        DrawTextureRec(scarfy, scarfyRec, scarfyPos, WHITE);

        // Stop Drawing
        EndDrawing();
    }

    // Unload texture before closing the program
    UnloadTexture(scarfy);
    CloseWindow();
}