#include "Level.h"
#include "Constants.h"


void Player::update(Level* level)
{
    speed.x = cos(rotation * DEG2RAD) * PLAYER_SPEED;
    speed.y = sin(rotation * DEG2RAD) * PLAYER_SPEED;

    if (IsKeyDown(KEY_UP))
    {
        position.x += (speed.x * PLAYER_SPEED);
        position.y -= (speed.y * PLAYER_SPEED);
        PlaySoundMulti(level->thrust);
    }

    if (IsKeyDown(KEY_LEFT))
    {
        rotation += 5;
    }

    if (IsKeyDown(KEY_RIGHT))
    {
        rotation -= 5;
    }

    Vector2 direction = { cos(-rotation * DEG2RAD), sin(-rotation * DEG2RAD)};

    if (IsKeyPressed(KEY_SPACE)) { //FIX, not right rotation
        level->spawn_projectile(position, direction, rotation);
    }

    //Wall interaction
    int screenWidth = GetScreenWidth();
    int screenHeight = GetScreenWidth();

    if (position.x > screenWidth + ship_height) //Right Wall
    {
        position.x = -(ship_height);
    }
    else if (position.x < -(ship_height))   //Left Wall
    {
        position.x = screenWidth + ship_height;
    }
    if (position.y > (screenHeight + ship_height)) //Bottom Wall
    {
        position.y = -(ship_height);
    }
    else if (position.y < -(ship_height))  //Top Wall
    {
        position.y = screenHeight + ship_height;
    }

    Asteroid* target_asteroid = level->closest_asteroid(position, range);
    if (target_asteroid)
    {
        target_asteroid->dead = true;
        health = health - 1;
    }
}

void Player::render()
{
    /*
    Vector2 v1 = { position.x + cosf(rotation * DEG2RAD) * (ship_height), position.y - sinf(rotation * DEG2RAD) * (ship_height) };
    Vector2 v2 = { position.x - sinf(rotation * DEG2RAD) * (PLAYER_SIZE / 2), position.y - cosf(rotation * DEG2RAD) * (PLAYER_SIZE / 2) };
    Vector2 v3 = { position.x + sinf(rotation * DEG2RAD) * (PLAYER_SIZE / 2), position.y + cosf(rotation * DEG2RAD) * (PLAYER_SIZE / 2) };
    DrawTriangle(v1, v2, v3, MAROON);//*/
    
    
    Vector2 origin = { 0, 0 };
    Rectangle sourceRec = { 565.f, 58.f, 102.f, 83.f };
    Rectangle destRec = { position.x, position.y, 102.f, 83.f };
    DrawTexturePro(ship, sourceRec, destRec, origin, (float)rotation, WHITE);//*/
   
}


void Asteroid::update()
{
    if (position.y < radius || position.y > GetScreenHeight() - radius)
    {
        direction.y = -direction.y;
    }

    if (position.x < radius || position.x > GetScreenWidth() - radius)
    {
        direction.x = -direction.x;
    }

    position.x += direction.x * ASTEROIDS_SPEED * DELTA;
    position.y += direction.y * ASTEROIDS_SPEED * DELTA;
}


void Asteroid::render()
{
    Vector2 origin = { 213.f/2.f, 224.f/2.f };
    Rectangle sourceRec = { 1.f, 831.f, 213.f, 224.f };
    Rectangle destRec = { position.x, position.y, 213.f, 224.f };
    DrawTexturePro(rock, sourceRec, destRec, origin, (float)rotation, WHITE);
}

void Projectile::update(Level* level) {
    position.x += direction.x * PROJECTILE_SPEED * DELTA;
    position.y += direction.y * PROJECTILE_SPEED * DELTA;

    if (position.x <= 0 || position.x >= GetScreenWidth() || position.y >= GetScreenHeight() || position.y <= 0) {
        dead = true;
    }

    //if collision with astroid die
    Asteroid* target_asteroid = level->closest_asteroid(position, range);
    
    if (target_asteroid)
    {
        target_asteroid->dead = true;
        dead = true;
        level->points = level->points + 50;
        level->spawn_asteroids({ (float)GetRandomValue(100, GetScreenWidth()), (float)GetRandomValue(100, GetScreenHeight()) }, { (float)GetRandomValue(100, GetScreenWidth()), (float)GetRandomValue(100, GetScreenHeight()) });
    }
}

void Projectile::render() {
    Vector2 origin = { 0, 0 };
    Rectangle sourceRec = { 1093.f, 47.f, 23.f, 36.f };
    Rectangle destRec = { position.x, position.y, 23.f, 36.f };
    DrawTexturePro(missile, sourceRec, destRec, origin, (float)rotation, WHITE);
}


void Level::update() {

    player.update(this);

    if (IsKeyPressed(KEY_E)) {
        spawn_asteroids({ (float)GetRandomValue(100, 700), (float)GetRandomValue(100, 700) }, { (float)GetRandomValue(100, 700), (float)GetRandomValue(100, 700) });//1st should be random positon, random direction
    }

    if (IsKeyPressed(KEY_R)) { //FIX
        PlaySoundMulti(thrust);
    }

    for (Asteroid& a : asteroids) {
        a.update();
    }

    for (Projectile& p : projectiles) {
        p.update(this);
    }

    //erasing everything from the vector which is dead == true
    projectiles.erase(std::remove_if(projectiles.begin(), projectiles.end(), [](Projectile& p) { return p.dead; }), projectiles.end());
    asteroids.erase(std::remove_if(asteroids.begin(), asteroids.end(), [](Asteroid& a) { return a.dead; }), asteroids.end());

    if (player.health <= 0) { //if times change to win screen with score
        reset();
    }
}

void Level::render() {
    DrawText("Level", 30, 30, 50, RED);
    DrawText(TextFormat("Points: %4i", points), 30, 75, 32, RED);

    player.render();

    for (Projectile& p : projectiles) {
        p.render();
    }

    for (Asteroid& a : asteroids)
    {
        a.render();
    }
}

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

float distance_sq(Vector2 a, Vector2 b) { //add to my_math 
    float dx = a.x - b.x;
    float dy = a.y - b.y;

    return  dx * dx + dy * dy;
}

Asteroid* Level::closest_asteroid(Vector2 position, float range) {
    Asteroid* result = nullptr;
    float current_closest_distance_sq = range * range;

    for (Asteroid& a : asteroids) {
        float a_distance_sq = distance_sq(position, a.position);
        if (a_distance_sq <= current_closest_distance_sq) {
            current_closest_distance_sq = a_distance_sq;
            result = &a; 
        }
    }
    return result;
}

void Level::reset() {
    asteroids.clear();
    projectiles.clear();
    points = 0;

    player.position = { GetScreenWidth() / 2.f, GetScreenHeight() / 2.f };
    player.speed;
    player.acceleration;
    player.rotation = 0;
    player.health = 3;

    int numb_asteroid = 5;
    for (int i = 0; i < numb_asteroid; i++) { 
        spawn_asteroids({ (float)GetRandomValue(100, GetScreenWidth()), (float)GetRandomValue(100, GetScreenHeight()) }, { (float)GetRandomValue(100, GetScreenWidth()), (float)GetRandomValue(100, GetScreenHeight()) });
    }
}