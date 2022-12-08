#pragma once
#include "raylib.h"
#include <vector>
#include "Constants.h"

class Level;

//Entity code
class Player
{
public:
    Vector2 position = { GetScreenWidth() / 2.f, GetScreenHeight() / 2.f };
    Vector2 speed;
    Vector2 direction;
    int acceleration;
    int rotation;
    bool dead = false;
    int health = 1; //doesnt use
    //Texture2D ship;
    
   
    void update(Level* level);
    void render();
};

class Asteroid
{
public:
    Vector2 position = {};
    Vector2 speed;
    Vector2 direction;
    float radius = 40; //chnage to fit new specs
    bool dead = false;
    Texture2D rock;
    int rotation = 0;

    void update();
    void render();
};

class Projectile
{
public:
    Vector2 position = {};
    Vector2 direction;
    //Vector2 size = { 12, 12 }; //doesnt use
    float range = 12.f;
    bool dead = false;
    int health = 1; //doesnt use
    
    //Texture
    Texture2D missile;
    int rotation = 0;

    void update();    
    void render();
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

    void update();
    void render();
};
