/*******************************************************************************************
*
*   raylib [core] example - Basic window
*
*   Welcome to raylib!
*
*   To test examples, just press F6 and execute raylib_compile_execute script
*   Note that compiled executable is placed in the same folder as .c file
*
*   You can find all basic examples on C:\raylib\raylib\examples folder or
*   raylib official webpage: www.raylib.com
*
*   Enjoy using raylib. :)
*
*   Example originally created with raylib 1.0, last time updated with raylib 1.0
*
*   Example licensed under an unmodified zlib/libpng license, which is an OSI-certified,
*   BSD-like license that allows static linking with closed source software
*
*   Copyright (c) 2013-2022 Ramon Santamaria (@raysan5)
*
********************************************************************************************/

#include "raylib.h"
#include "Constants.h"
#include "Level.h"
#include <stack>


//Menu code
enum class State
{
    MAIN_MENU,
    GAME
};

std::stack<State> states;

void do_main_menu() //Main Menu 
{
    Vector2 mouse_pos = GetMousePosition();
    
    //Title
    int title_font = 50;
    int title_x = (GetScreenWidth() / 2) - 192;
    int title_y = (GetScreenHeight() * 0.25);
    DrawText("ASTEROID CLONE", title_x, title_y, title_font, RED);

    //Button
    int pos_x = (GetScreenWidth() / 2) - 25;
    int pos_y = (GetScreenHeight() / 2) - 124;
    int start_font = 32;
    DrawRectangle(pos_x, pos_y, 124, 64, GREEN);
    DrawText("START", pos_x + 8, pos_y + 16, start_font, WHITE);

    Rectangle btnbounds(pos_x, pos_y, 124, 64);
    
    bool btn_action = false;

    if (CheckCollisionPointRec(mouse_pos, btnbounds))
    {
        if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
            states.push(State::GAME);
        }
    }
}

void do_level(Level* level) {
   
    level->update();
    level->render();
}


//------------------------------------------------------------------------------------
// Program main entry point
//------------------------------------------------------------------------------------
int main(void)
{
    // Initialization
    //--------------------------------------------------------------------------------------
    const int screenWidth = 1800;
    const int screenHeight = 1000;

    InitWindow(screenWidth, screenHeight, "raylib [core] example - basic window");
    InitAudioDevice();

    SetTargetFPS(60);               // Set our game to run at 60 frames-per-second
    //--------------------------------------------------------------------------------------

    Level level;

    level.projectile_texture    = LoadTexture("Spritesheet/spaceShooter2_spritesheet.png");
   
    level.thrust = LoadSound("sounds/space_ship_thurst.wav");
    level.explosion = LoadSound("sounds/explosion.wav");
    level.pew = LoadSound("sounds/pew.wav");

    SetSoundVolume(level.thrust, 0.5f);
    SetSoundVolume(level.explosion, 0.5f);
    SetSoundVolume(level.pew, 0.5f);

    states.push(State::MAIN_MENU);

    // Main game loop
    while (!WindowShouldClose())    // Detect window close button or ESC key
    {
        // Update
        //----------------------------------------------------------------------------------
        // TODO: Update your variables here
        //----------------------------------------------------------------------------------
        
        State current_state = states.top();

        // Draw
        //----------------------------------------------------------------------------------
        BeginDrawing();

        ClearBackground(BLACK);

        switch (current_state)
        {
        case State::MAIN_MENU:
            do_main_menu();
            break;
        case State::GAME:
            do_level(&level);
            break;
        }

        EndDrawing();
        //----------------------------------------------------------------------------------
    }

    // De-Initialization
    //--------------------------------------------------------------------------------------
    StopSoundMulti();
    UnloadSound(level.thrust);
    UnloadSound(level.explosion);
    UnloadSound(level.pew);
    CloseAudioDevice();

    CloseWindow();        // Close window and OpenGL context
    //--------------------------------------------------------------------------------------

    return 0;
}




