#include "Level.h"
#include "Constants.h"



void Player::update(Level* level)
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

    if (IsKeyDown(KEY_SPACE)) { //FIX, after it spawns the projectiles dont move
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

void Player::render()
{

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
    Vector2 origin = { 0, 0 };
    Rectangle sourceRec = { 1.f, 831.f, 213.f, 224.f };
    Rectangle destRec = { position.x, position.y, 213.f, 224.f };
    DrawTexturePro(rock, sourceRec, destRec, origin, (float)rotation, WHITE);
    //DrawCircle(position.x, position.y, radius, WHITE);   
}

void Projectile::update() {
    position.x += direction.x * PROJECTILE_SPEED * DELTA;
    position.y += direction.y * PROJECTILE_SPEED * DELTA;

    if (position.x <= 0 || position.x >= GetScreenWidth() || position.y >= GetScreenHeight() || position.y <= 0) {
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

void Projectile::render() {
    Vector2 origin = { 0, 0 };
    Rectangle sourceRec = { 1093.f, 47.f, 23.f, 36.f };
    Rectangle destRec = { position.x, position.y, 23.f, 36.f };
    DrawTexturePro(missile, sourceRec, destRec, origin, (float)rotation, WHITE);
    //DrawRectangle(position.x, position.y, size.x, size.y, RED);
}


void Level::update() {

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

    //erasing everything from the vector which is dead == true
    projectiles.erase(std::remove_if(projectiles.begin(), projectiles.end(), [](Projectile& p) { return p.dead; }), projectiles.end());
    asteroids.erase(std::remove_if(asteroids.begin(), asteroids.end(), [](Asteroid& a) { return a.dead; }), asteroids.end());
}

void Level::render() {
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
            result = &a;    //fix
        }
    }
    return result;
}