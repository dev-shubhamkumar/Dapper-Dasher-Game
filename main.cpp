#include "raylib.h"

int main()
{
    // window dimensions
    const int windowWidth{512};
    const int windowHeight{380};
    // Initialize the window
    InitWindow(windowWidth, windowHeight, "Dasher Dapper Game");

    // acceleration due to gravity (pixels/frame) / frame
    const int gravity{1};

    // Loading Scarfy Sprites
    Texture2D scarfy = LoadTexture("textures/scarfy.png");
    Rectangle scarfyRec;
    Vector2 scarfyPos;

    // rectangle dimensions
    const int width{50};
    const int height{80};

    int posY{windowHeight - height};
    int velocity{0};

    // Defining jupm velocity
    const int jupmVel{-22};

    // creating variable to check if object is in air
    bool isInAir{};

    SetTargetFPS(60);
    while (!WindowShouldClose())
    {
        // Start Drawing
        BeginDrawing();
        ClearBackground(WHITE);

        // ENVIRONMENT: performing ground check and applying gravity
        if (posY >= windowHeight - height)
        {
            // rectangle is on the ground - do not apply gravity
            velocity = 0;
            isInAir = false;
        }
        else {
            //apply gravity
            velocity += gravity;
            isInAir = true;
        }

        // ENVIRONMENT: Defining Velocity
        if (IsKeyPressed(KEY_SPACE) && !isInAir)
        {
            velocity += jupmVel;
        }

        // update the position
        posY += velocity;


        

        DrawRectangle(windowHeight/2, posY, width, height, BLUE);

        // Stop Drawing
        EndDrawing();
    }
    CloseWindow();
    
}