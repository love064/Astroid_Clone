#include "raylib.h"
#include "Level.h"
#include <stack>

enum class State
{
    MAIN_MENU,
    GAME
};

std::stack<State> states;

void do_main_menu()
{
    int title_font = 50;
    int title_x = (GetScreenWidth() / 2) - 200;
    int title_y = (GetScreenHeight() * 0.25);
    DrawText("ASTEROID CLONE", title_x, title_y, title_font, RED);

    int btn_x = (GetScreenWidth() / 2) - 25;
    int btn_y = (GetScreenHeight() / 2) - 124;
    int start_font = 32;
    bool btn_action = false;
    DrawRectangle(btn_x, btn_y, 124, 64, GREEN);
    DrawText("START", btn_x + 8, btn_y + 16, start_font, WHITE);
    Rectangle btnbounds(btn_x, btn_y, 124, 64);
    
    if (CheckCollisionPointRec(GetMousePosition(), btnbounds))
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
    const int screenWidth = 1200;
    const int screenHeight = 1000;

    InitWindow(screenWidth, screenHeight, "raylib [core] example - basic window");
    InitAudioDevice();

    SetTargetFPS(60);               // Set our game to run at 60 frames-per-second
    
    Level level;

    level.texture_sheet    = LoadTexture("Spritesheet/spaceShooter2_spritesheet.png");
   
    level.thrust    = LoadSound("sounds/space_ship_thurst.wav");
    level.explosion = LoadSound("sounds/explosion.wav");
    level.pew       = LoadSound("sounds/pew.wav");

    SetSoundVolume(level.thrust, 0.3f);
    SetSoundVolume(level.explosion, 0.3f);
    SetSoundVolume(level.pew, 0.3f);

    states.push(State::MAIN_MENU);
    //--------------------------------------------------------------------------------------

    // Main game loop
    while (!WindowShouldClose())    // Detect window close button or ESC key
    {
        // Update
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




