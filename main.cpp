#include "raylib.h"

int main()
{
    // window dimensions
    const int windowWidth{512};
    const int windowHeight{380};

    InitWindow(windowHeight, windowWidth, "Dasher Dapper Game");

    SetTargetFPS(60);
    while (!WindowShouldClose())
    {
        // Start Drawing
        BeginDrawing();
        ClearBackground(WHITE);

        

        // Stop Drawing
        EndDrawing();
    }
    
}