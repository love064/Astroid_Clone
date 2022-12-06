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


const float PLAYER_SIZE = 50.0f;
const float PLAYER_SPEED = 2.5f;
const int PLAYER_MAX_SHOTS = 5;
float ship_height = 60.0f;

const float ASTEROIDS_SPEED = 0.2f;
//const int MAX_BIG_ASTEROIDS = 4;
//const int MAX_ASTEROIDS = 8;
//const int MAX_MINI_ASTEROIDS = 16;
//const int shipHeight = (PLAYER_SIZE / 2) / tanf(20 * DEG2RAD);

class Level;

//Entity code
class Player
{
public:
    Vector2 position = { GetScreenWidth()/2.f, GetScreenHeight() / 2.f };
    Vector2 speed;
    Vector2 direction;
    int acceleration;
    int rotation;
    int health = 1;
    //Texture2D ship;

    bool destroyed = false;
    //virtual void update(Level* level) = 0;

    void update(Level* level);

    void render()
    {
        //DrawRectangle(position.x, position.y, PLAYER_SIZE, PLAYER_SIZE, BLUE);

        Vector2 v1 = { position.x + sinf(rotation * DEG2RAD) * (ship_height), position.y - cosf(rotation * DEG2RAD) * (ship_height) };
        Vector2 v2 = { position.x - cosf(rotation * DEG2RAD) * (PLAYER_SIZE / 2), position.y - sinf(rotation * DEG2RAD) * (PLAYER_SIZE / 2) };
        Vector2 v3 = { position.x + cosf(rotation * DEG2RAD) * (PLAYER_SIZE / 2), position.y + sinf(rotation * DEG2RAD) * (PLAYER_SIZE / 2) };
        DrawTriangle(v1, v2, v3, MAROON);
        /*
        Vector2 origin = { 0, 0 };
        Rectangle sourceRec = { 565.f, 58.f, 102.f, 83.f };
        Rectangle destRec = { position.x, position.y, 102.f, 83.f };
        DrawTexturePro(ship, sourceRec, destRec, origin, (float)rotation, WHITE);
        */
    }
};

class Asteroid
{
public:
    Vector2 position = {};
    Vector2 speed;
    Vector2 direction;
    float radius = 40; //can be upgrade to other shapes later
    bool dead = false;

  


    void update()
    {
       if (position.y < radius || position.y > GetScreenHeight()-radius)
        {
            direction.y = -direction.y;
        }

        if (position.x < radius || position.x > GetScreenWidth()-radius)
        {
            direction.x = -direction.x;
        }

        position.x += direction.x * ASTEROIDS_SPEED * DELTA;
        position.y += direction.y * ASTEROIDS_SPEED * DELTA;

    }

    Texture2D rock;
    int rotation = 0;

    void render()
    {
        Vector2 origin = { 0, 0 };
        Rectangle sourceRec = {1.f, 831.f, 213.f, 224.f};
        Rectangle destRec = { position.x, position.y, 213.f, 224.f};
        DrawTexturePro(rock, sourceRec, destRec, origin, (float)rotation, WHITE);
        //DrawCircle(position.x, position.y, radius, WHITE);   
        
    }
};

class Projectile
{
public:
    Vector2 position = {};
    Vector2 direction;
    //Vector2 size = { 12, 12 }; //doesnt use
    float range = 12.f;
    

    int health = 1; //doesnt use
    bool dead = false;

    void update() {
        position.x += direction.x * PROJECTILE_SPEED * DELTA;
        position.y += direction.y * PROJECTILE_SPEED * DELTA;

        if (position.x <= 0 || position.x >= GetScreenWidth() || position.y >= GetScreenHeight() || position.y <= 0 ) {
            dead = true;
        }

        //if collision with astroid die
        //Asteroid* target_asteroid = Level::closest_asteroid(position, range); //ask how to link this to the level vector of asteroids
        /*
        if (target_asteroid)
        {
            target_asteroid->dead = true;
            dead = true;
        }//*/

    }

    //Texture
    Texture2D missile;
    int rotation = 0;

    void render() {
        Vector2 origin = { 0, 0 };
        Rectangle sourceRec = { 1093.f, 47.f, 23.f, 36.f };           
        Rectangle destRec = { position.x, position.y, 23.f, 36.f };   
        DrawTexturePro(missile, sourceRec, destRec, origin, (float)rotation, WHITE);
        //DrawRectangle(position.x, position.y, size.x, size.y, RED);
    }
};

//Level code
class Level
{
    std::vector<Asteroid> asteroids = {};
    std::vector<Projectile> projectiles = {};
    Player player;

public: 
    Texture2D projectile_texture;

    void spawn_projectile(Vector2 positon, Vector2 direction, int rotation); //parameters should be vector2 position, and vector2 direction
    void spawn_asteroids(Vector2 positon, Vector2 direction);
    
    Asteroid* closest_asteroid(Vector2 position, float range); //ASK Where to put this
    
    //virtual void update(Level* level) = 0;
    
    void update() {

        player.update(this);
        
        if (IsKeyPressed(KEY_E)) {
            spawn_asteroids({ (float)GetRandomValue(100, 700), (float)GetRandomValue(100, 700) }, { (float)GetRandomValue(100, 700), (float)GetRandomValue(100, 700) });//1st should be random positon, random direction
        }
 
        
       

        for (Asteroid& a : asteroids) {
            a.update();
        }

        for (Projectile& p : projectiles) { 
            p.update();
        }

       // if (IsKeyPressed(KEY_SPACE)) { //doesnt work properly they do not move
         //   spawn_projectile(player.position, player.direction, player.rotation);
       // }

        //erasing everything from the vector which is dead == true
        projectiles.erase(std::remove_if(projectiles.begin(), projectiles.end(), [](Projectile& p) { return p.dead; }), projectiles.end());
        asteroids.erase(std::remove_if(asteroids.begin(), asteroids.end(), [](Asteroid& a) { return a.dead; }), asteroids.end());
    }

    void render() {
        DrawText("Level", 50, 50, 50, RED);

        player.render();
        
        for (Projectile& p : projectiles) {
            p.render();
        }

        for (Asteroid& a : asteroids)
        {
            a.render();
        }
    }

};

void Level::spawn_asteroids(Vector2 position, Vector2 direction) {
    Asteroid asteroid{};

    asteroid.position = position;
    asteroid.direction = direction;
    asteroid.rock = projectile_texture;
    asteroids.push_back(asteroid);


}


void Level::spawn_projectile(Vector2 position, Vector2 direction, int rotation) {
    Projectile projectile{};

    projectile.position = position;
    projectile.direction = direction;
    projectile.missile = projectile_texture;
    projectile.rotation = rotation;
    projectiles.push_back(projectile);
}

float distance_sq(Vector2 a, Vector2 b) {
    float dx = a.x - b.x;
    float dy = a.y - b.y;

    return  dx * dx + dy * dy ;
}

Asteroid* Level::closest_asteroid(Vector2 position, float range) {
    Asteroid* result = nullptr;
    float current_closest_distance_sq = range * range;

    for (Asteroid& a : asteroids) {
        float a_distance_sq = distance_sq(position, a.position);
        if (a_distance_sq <= current_closest_distance_sq) {
            current_closest_distance_sq = a_distance_sq;
            result = &a;    //fix
        }
    }
    return result;

}

void Player::update(Level* level) //override
{


    speed.x = sin(rotation * DEG2RAD) * PLAYER_SPEED;
    speed.y = cos(rotation * DEG2RAD) * PLAYER_SPEED;

    if (IsKeyDown(KEY_UP))
    {
        position.x += (speed.x * PLAYER_SPEED);
        position.y -= (speed.y * PLAYER_SPEED);
    }

    if (IsKeyDown(KEY_LEFT))
    {
        rotation -= 5;
    }

    if (IsKeyDown(KEY_RIGHT))
    {
        rotation += 5;
    }

    if (IsKeyDown(KEY_SPACE)) { //FIX, need to make update virtual void, override
        level->spawn_projectile(position, direction, rotation);
    }

    //Wall interaction
    int screenWidth = GetScreenWidth();
    int screenHeight = GetScreenWidth();


    if (position.x > screenWidth + PLAYER_SIZE) //Rght Wall
    {
        position.x = -(PLAYER_SIZE);
    }
    else if (position.x < -(PLAYER_SIZE))   //Left Wall
    {
        position.x = screenWidth + PLAYER_SIZE;
    }
    if (position.y > (screenHeight + PLAYER_SIZE)) //Bottom Wall
    {
        position.y = -(PLAYER_SIZE);
    }
    else if (position.y < -(PLAYER_SIZE))  //Top Wall
    {
        position.y = screenHeight + PLAYER_SIZE;
    }


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
    const int screenWidth = 1800;
    const int screenHeight = 1000;

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




