#include "raylib.h"
#include <cmath>
#include <string>

#define RAYGUI_IMPLEMENTATION
#define RAYGUI_SUPPORT_ICONS

using namespace std;

float Magnitude(Vector2 v)
{
    return (float)sqrt(v.x * v.x + v.y * v.y);
}

Vector2 Normalize(Vector2 v)
{
    float len = Magnitude(v);
    v.x /= len;  v.y /= len;
    return v;
}

int main(int argc, char* argv[])
{
    // Initialization
    //--------------------------------------------------------------------------------------
    int screenWidth = 800;
    int screenHeight = 450;

    InitWindow(screenWidth, screenHeight, "raylib [core] example - basic window");

    SetTargetFPS(60);
    //--------------------------------------------------------------------------------------
    float xdir = 0;
    float ydir = 0;
    
    float px = 700;
    float py = 225;

    float p2x = 100;
    float p2y = 225;
    Rectangle paddle = { px, py, 20, 80 };
    Rectangle paddle2 = { p2x, p2y, 20, 80 };

    int playerPoints = 0;
    int ComputerPoints = 0;

    Vector2 balldir = { 1, 0 };
    float x = 400;
    float y = 225;
    Color colour = BLACK;
    bool playing = true;
    string WinText = "";

    // Main game loop
    while (!WindowShouldClose())    // Detect window close button or ESC key
    {
        if (ComputerPoints > 4)
        {
            playing = false;
            WinText = "Computer Wins";
            
        }
        if (playerPoints > 4)
        {
            playing = false;
            WinText = "Player Wins";
        }

        if (playing)
        {


            paddle = { px, py, 20, 80 };
            paddle2 = { p2x, p2y, 20, 80 };

            // BALL COLLISION WITH WALLS
            if (y > 430)
            {
                balldir.y = -balldir.y;
            }
            if (y < 20)
            {
                balldir.y = -balldir.y;
            }

            // SCORING (LEFT AND RIGHT WALL COLLISION)
            if (x > 780)
            {
                ComputerPoints++;
                x = 400;
                y = 225;
                balldir.x = 0;
                balldir.y = 0;
            }
            if (x < 20)
            {
                playerPoints++;
                x = 400;
                y = 225;
                balldir.x = 0;
                balldir.y = 0;

            }



            // SERVE BALL
            if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT) && balldir.x == 0 && balldir.y == 0)
            {
                balldir.x = 1;
                balldir.y = 0;
            }


            // PLAYER PADDLE COLLISION
            if (CheckCollisionCircleRec({ x, y }, 20, paddle))
            {
                if (y > (py + 60))
                {
                    balldir.x = 0.75 * -copysignf(1.0, balldir.x);
                    balldir.y = 0.75;
                }
                else if (y < (py + 20))
                {

                    balldir.x = 0.75 * -copysignf(1.0, balldir.x);
                    balldir.y = -0.75;
                }
                else {
                    balldir.x = -balldir.x;
                    balldir.y *= 0.5;
                }
            }
            else {
                py = GetMousePosition().y;
            }

            // COMPUTER PADDLE COLLISION
            if (CheckCollisionCircleRec({ x, y }, 20, paddle2))
            {
                if (y > (p2y + 60))
                {
                    balldir.x = 0.75 * -copysignf(1.0, balldir.x);
                    balldir.y = 0.75;
                }
                else if (y < (p2y + 20))
                {

                    balldir.x = 0.75 * -copysignf(1.0, balldir.x);
                    balldir.y = -0.75;
                }
                else {
                    balldir.x = -balldir.x;
                    balldir.y *= 0.5;
                }
            }            
            else { 
                // MOVING TOWARDS BALL Y
                if (y > (p2y + 40))
                {
                    p2y += 6;
                }
                else  if (y < (p2y)) {
                    p2y -= 6;
                }

                // LOCKING COMPUTER PADDLE TO SCREEN
                if (p2y > 370)
                {
                    p2y = 370;
                }

                if (p2y < 0)
                {
                    p2y = 0;
                }
            }

            if (balldir.x != 0 && balldir.y != 0)
            {
                balldir = Normalize(balldir);
            }

            x += 10 * balldir.x;
            y += 10 * balldir.y;
        }
       

        BeginDrawing();


        DrawCircle(x, y, 20, RED);
        DrawRectanglePro(paddle, { 0, 0 }, 0, colour);
        DrawRectanglePro(paddle2, { 0, 0 }, 0, colour);

        
        DrawText(to_string(playerPoints).c_str(), 720, 20, 100, GREEN);
        DrawText(to_string(ComputerPoints).c_str(), 20, 20, 100, GREEN);

        if (!playing)
        {
            DrawText(WinText.c_str(), 150, 100, 50, BLUE);
        }

        ClearBackground(RAYWHITE);


        EndDrawing();
        //----------------------------------------------------------------------------------
    }

    // De-Initialization
    //--------------------------------------------------------------------------------------   
    CloseWindow();        // Close window and OpenGL context
    //--------------------------------------------------------------------------------------

    return 0;
}