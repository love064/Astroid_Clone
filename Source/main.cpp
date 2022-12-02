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

#include <vector>
#include <stack>

const float PLAYER_SIZE = 20.0f;
const float PLAYER_SPEED = 6.0f;
const int PLAYER_MAX_SHOTS = 5;

const int ASTEROIDS_SPEED = 2;
const int MAX_BIG_ASTEROIDS = 4;
const int MAX_MID_ASTEROIDS = 8;
const int MAX_MINI_ASTEROOIDS = 16;


//Entity code
class Player 
{
public:
    Vector2 position;
    Vector2 speed;
    Vector2 direction;
    int acceleration;
    int rotation;
    int health = 1;

    bool destroyed = false;

    void update()
    {
        position.x += (speed.x * acceleration);
        position.y -= (speed.y * acceleration);

        speed.x = sin(rotation * DEG2RAD) * PLAYER_SPEED;
        speed.y = cos(rotation * DEG2RAD) * PLAYER_SPEED;
    }
    void render()
    {

    }

};

class Asteroid
{

};

class Projectile
{
public:
    Vector2 position = {};
    Vector2 direction;
    Vector2 size = { 12, 12 };

    int health = 1;
    bool dead = false;

    void update() {
        position.x += direction.x * PROJECTILE_SPEED * DELTA;
        position.y += direction.y * PROJECTILE_SPEED * DELTA;

        if (position.x <= 0 || position.x >= GetScreenWidth() || position.y >= GetScreenHeight() || position.y <= 0 ) {
            dead = true;
        }

        //if collision with astroid die
    }

    //texture
    Texture2D missile;

    int rotation = 0;

    void render() {//x1 1094, y1 47  , x2 1112, y2 81
        Vector2 origin = { 0, 0 };
        Rectangle sourceRec = { 1094.f, 47.f, 22.f, 35.f };              //chnage, go into paint a select the area using the mouse position to find which part of the thing is the missile
        Rectangle destRec = { position.x, position.y, 22.f, 35.f };    //chnage
        DrawTexturePro(missile, sourceRec, destRec, origin, (float)rotation, WHITE);
        //DrawRectangle(position.x, position.y, size.x, size.y, RED);
    }
};

//Level code
class Level
{
    std::vector<Asteroid> asteroids;
    std::vector<Projectile> projectiles = {};
    Player player;

public: 
    Texture2D projectile_texture;

    void spawn_projectile(Vector2 positon, Vector2 direction); //parameters should be vector2 position, and vector2 direction
    
    void update() {

        if (IsMouseButtonPressed(0)) { //done to test if the spawning works
            spawn_projectile(GetMousePosition(), {1,1});
        }

        for (Projectile& p : projectiles) { 
            p.update();
        }

        //erasing everything from the vector which is dead == true
        projectiles.erase(std::remove_if(projectiles.begin(), projectiles.end(), [](Projectile& p) { return p.dead; }), projectiles.end()); //ASK
        
    }

    void render() {
        DrawText("Level", 50, 50, 50, RED);

        for (Projectile& p : projectiles) {
            p.render();
        }
    }

};

void Level::spawn_projectile(Vector2 position, Vector2 direction) {
    Projectile projectile{};

    projectile.position = position;
    projectile.direction = direction;
    projectile.missile = projectile_texture;
    projectiles.push_back(projectile);
}





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
    int title_x = (GetScreenWidth() / 4) - 50;
    int title_y = (GetScreenHeight() * 0.25);
    DrawText("ASTEROID CLONE", title_x, title_y, title_font, RED);

    //Button
    int pos_x = (GetScreenWidth() / 2) - 25;
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
    const int screenWidth = 800;
    const int screenHeight = 800;

    InitWindow(screenWidth, screenHeight, "raylib [core] example - basic window");

    SetTargetFPS(60);               // Set our game to run at 60 frames-per-second
    //--------------------------------------------------------------------------------------

    Level level;

    level.projectile_texture = LoadTexture("Spritesheet/spaceShooter2_spritesheet.png");
    
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




