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

#include <vector>
#include <stack>


//Entity code
class Player 
{

};

class Asteroid
{

};

class Projectile
{
    Vector2 position;
    Vector2 direction;

    int health;
    bool isdead = false;

    void kill() {

    }

    void update() {

    }

};


//Level code
class Level
{
    std::vector<Asteroid> asteroids;
    std::vector<Projectile> projectiles;
    Player player;

    void update() {

    }

    void render() {

    }


};







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
    int title_font = 32;
    int title_x = (GetScreenWidth() / 2) - 32;
    int title_y = (GetScreenHeight() * 0.25);
    DrawText("ASTEROID CLONE", title_x, title_y, title_font, RED);

    //Button
    int pos_x = GetScreenWidth() / 2;
    int pos_y = (GetScreenHeight() / 2) - 124;
    DrawRectangle(pos_x, pos_y, 124, 64, GREEN);

    Rectangle btnbounds(pos_x, pos_y, 124, 64);
    
    bool btn_action = false;

    if (CheckCollisionPointRec(mouse_pos, btnbounds))
    {
        if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
            states.push(State::GAME);
        }
    }
}




//------------------------------------------------------------------------------------
// Program main entry point
//------------------------------------------------------------------------------------
int main(void)
{
    // Initialization
    //--------------------------------------------------------------------------------------
    const int screenWidth = 800;
    const int screenHeight = 800;

    InitWindow(screenWidth, screenHeight, "raylib [core] example - basic window");

    SetTargetFPS(60);               // Set our game to run at 60 frames-per-second
    //--------------------------------------------------------------------------------------


    states.push(State::MAIN_MENU);


    // Main game loop
    while (!WindowShouldClose())    // Detect window close button or ESC key
    {
        // Update
        //----------------------------------------------------------------------------------
        // TODO: Update your variables here
        //----------------------------------------------------------------------------------
        
        State current_state = states.top();
        
        switch (current_state)
        {
        case State::MAIN_MENU:
            do_main_menu();
            break;
        case State::GAME:
            //do_game(level)
            break;
        }






        // Draw
        //----------------------------------------------------------------------------------
        BeginDrawing();

        ClearBackground(DARKGRAY);
        

        //DrawText("Congrats! You created your first window!", 190, 200, 20, LIGHTGRAY);

        EndDrawing();
        //----------------------------------------------------------------------------------
    }

    // De-Initialization
    //--------------------------------------------------------------------------------------
    CloseWindow();        // Close window and OpenGL context
    //--------------------------------------------------------------------------------------

    return 0;
}




