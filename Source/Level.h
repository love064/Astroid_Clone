#pragma once
#include "raylib.h"
#include <vector>
#include "Constants.h"

class Level;

class Player
{
public:
    Vector2 position = { GetScreenWidth() / 2.f, GetScreenHeight() / 2.f };
    Vector2 speed;
    float range = PLAYER_SIZE * 3.5;
    int acceleration = 0;
    int rotation = 0;
    int health = 0; //set to zero to trigger level(reset) at the begining, which spawns in the asteroids and set health to 3
    Texture2D shp;
    
    void update(Level* level);
    void render(Level* level);
};

class Asteroid
{
public:
    Vector2 position = {};
    Vector2 direction;
    float radius = 100;
    int rotation = 0;
    bool dead = false;
    Texture2D rock;

    void update();
    void render();
};

class Projectile
{
public:
    Vector2 position = {};
    Vector2 direction;
    float range = 150.f;
    int rotation = 0;
    bool dead = false;
    Texture2D missile;
    
    void update(Level* level);
    void render();
};


class Level
{
    std::vector<Asteroid> asteroids = {};
    std::vector<Projectile> projectiles = {};
    Player player;

public:
    Texture2D texture_sheet;
    Sound thrust;
    Sound explosion;
    Sound pew;
    int points = 0;

    void spawn_projectile(Vector2 positon, Vector2 direction, int rotation);
    void spawn_asteroid(Vector2 positon, Vector2 direction);

    Asteroid* closest_asteroid(Vector2 position, float range);

    void update();
    void render();
    void reset();
};
