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

    // rectangle dimensions
    const int width{50};
    const int height{80};

    int posY{windowHeight - height};
    int velocity{0};

    SetTargetFPS(60);
    while (!WindowShouldClose())
    {
        // Start Drawing
        BeginDrawing();
        ClearBackground(WHITE);

        // performing ground check
        if (posY >= windowHeight - height)
        {
            // rectangle is on the ground - do not apply gravity
            velocity = 0;
        }
        else {
            //apply gravity
            velocity += gravity;
        }

        if (IsKeyPressed(KEY_SPACE))
        {
            velocity -= 10;
        }

        // update the position
        posY += velocity;

        DrawRectangle(windowHeight/2, posY, width, height, BLUE);

        // Stop Drawing
        EndDrawing();
    }
    CloseWindow();
    
}