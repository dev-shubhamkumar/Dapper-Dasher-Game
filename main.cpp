#include "raylib.h"

int main()
{
    // window dimensions
    const int windowWidth{512};
    const int windowHeight{380};
    // Initialize the window
    InitWindow(windowWidth, windowHeight, "Dasher Dapper Game");

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

        if (IsKeyPressed(KEY_SPACE))
        {
            velocity -= 10;
        }

        posY += velocity;

        DrawRectangle(windowHeight/2, posY, width, height, BLUE);

        // Stop Drawing
        EndDrawing();
    }
    CloseWindow();
    
}