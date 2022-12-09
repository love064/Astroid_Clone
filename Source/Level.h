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
    float range = PLAYER_SIZE * 3.5;
    int acceleration;
    int rotation = 50;
    int health = 0; 
    Texture2D ship;
    
    void update(Level* level);
    void render(Level* level);
};

class Asteroid
{
public:
    Vector2 position = {};
    Vector2 speed;
    Vector2 direction;
    float radius = 100;
    bool dead = false;
    int numb_asteroid = 0;
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
    float range = 150.f;
    bool dead = false;
   
    //Texture
    Texture2D missile;
    int rotation = 0;

    void update(Level* level);
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
    Sound thrust;
    Sound explosion;
    Sound shoot;
    int points = 0;

    void spawn_projectile(Vector2 positon, Vector2 direction, int rotation);
    void spawn_asteroids(Vector2 positon, Vector2 direction);

    Asteroid* closest_asteroid(Vector2 position, float range);

    void update();
    void render();
    void reset();
};
