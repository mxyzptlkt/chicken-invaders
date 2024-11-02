#pragma once

#include <iostream>
#include <cmath>
#include <vector>
#include <cstdlib>
#include "random.h"

constexpr float PI = 3.14159;

inline float difficulty;
inline int playerScore;
enum GameState {
    MENU,
    PLAYING,
    GAME_OVER
};

GameState currentState = GameState::MENU;

// Window dimensions
constexpr int WIDTH = 600;
constexpr int HEIGHT = 800;

// Viewport scale
constexpr float SCALE_MAX = 1.0f;
constexpr float SCALE_MIN = -1.0f;

// Player attributes
inline float playerX;
inline float playerY;
inline float playerImmortal;
constexpr float playerImmortalTime = 20.0f;
constexpr float playerRadius = 0.1f;
constexpr float playerSpeed = 0.01f;

// Enemy attributes
struct Enemy {
    float x, y, radius;
    int hp;
    bool movingRight = true;
    bool movingDown = true;
};
constexpr float enemyRadius = playerRadius;
inline float enemySpeed;
inline int enemyCount;
std::vector<Enemy> enemies;

// Power attributes
struct Power {
    float x, y, radius;
};
constexpr float powerRadius = 0.4f * playerRadius;
constexpr float powerSpeed = 0.5f * playerSpeed;
constexpr float powerRate = 0.02f;
std::vector<Power> powersBullet;
std::vector<Power> powersImmortal;

// Bullet attributes
struct Bullet {
    float x, y;
};
constexpr float bulletPlayerRadius = 0.05f * playerRadius;
constexpr float bulletEnemyRadius = 0.3f * enemyRadius;
constexpr float bulletPlayerSpeed = 2.0f * playerSpeed;
inline float bulletEnemySpeed;
constexpr float bulletPlayerRate = 20.0f;
constexpr float bulletPlayerCooldown = 1.0f / bulletPlayerRate;
inline float bulletEnemyChance;
inline int bulletCount;
constexpr int maxBulletCount = 5;
std::vector<std::vector<Bullet>> playerBullets;
std::vector<Bullet> enemyBullets;
