#pragma once

#define STB_IMAGE_IMPLEMENTATION

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <fstream>
#include <string>
#include <cmath>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <chrono>
#include "stb_image.h"
#include "config.h"
#include "random.h"

auto lastTimeImmortal = std::chrono::high_resolution_clock::now();
auto lastTimeBullet = std::chrono::high_resolution_clock::now();
float immortalTime = 0.0f;
float bulletTime = 0.0f;

inline void scoreToFile(const std::string& filename);
inline void drawPlayer(float x, float y, float radius);
inline void drawEnemy(float x, float y, float radius, bool movingDown);
inline void drawCircle(float cx, float cy, float radius, int segments = 30);
inline void drawTriangle(float x, float y, float radius);
inline bool isPlanePowerCollision(float tx, float ty, float r1, float sx, float sy, float r2);
inline bool isPlaneBulletCollision(float cx, float cy, float r1, float rx, float ry, float r2);
inline void enemyInit(int enemyCount);
inline void enemyMove();
inline void enemyFire();
inline void powerBulletInit();
inline void powerBulletUp();
void powerImmortalInit();
void powerImmortalUp();
inline void playerMove(GLFWwindow* window);
inline void render();
inline void checkCollision();
inline void InitializeGame();
inline void setDifficulty(float difficulty);
inline GLFWwindow* createWindow(int width, int height, const char* title);

void scoreToFile(const std::string& filename) {
    std::time_t now = std::time(nullptr);
    std::tm localTime;
    localtime_s(&localTime, &now);

    char buf[100];
    std::strftime(buf, sizeof(buf), "%Y-%m-%d %H:%M:%S", &localTime);

    std::ofstream outFile(filename, std::ios::app);
    if (outFile.is_open()) {
        outFile << buf << (difficulty == 1.0f ? "\tEasy: " :
            difficulty == 1.5f ? "\tMedium: " :
            "\tSuper Mega Ultra Hard: ") << "You scored " << playerScore << "!\n";
        outFile.close();
        std::cout << "Results written to " << filename << "\n";
    }
    else {
        std::cerr << "Unable to open file: " << filename << "\n";
    }
}
void drawPlayer(float x, float y, float radius) {
    glBegin(GL_LINE_LOOP);
    glVertex2f(x, y + radius / 2);
    glVertex2f(x - radius / 6, y + radius / 3);
    glVertex2f(x - radius / 6, y + radius / 6);
    glVertex2f(x - radius / 2, y - radius / 6);
    glVertex2f(x - radius / 2, y - radius / 3);
    glVertex2f(x - radius / 6, y - radius / 6);
    glVertex2f(x - radius / 6, y - radius / 3);
    glVertex2f(x - radius / 4, y - radius / 2);
    glVertex2f(x + radius / 4, y - radius / 2);
    glVertex2f(x + radius / 6, y - radius / 3);
    glVertex2f(x + radius / 6, y - radius / 6);
    glVertex2f(x + radius / 2, y - radius / 3);
    glVertex2f(x + radius / 2, y - radius / 6);
    glVertex2f(x + radius / 6, y + radius / 6);
    glVertex2f(x + radius / 6, y + radius / 3);
    glEnd();
}
void drawEnemy(float x, float y, float radius, bool movingDown) {
    glBegin(GL_LINE_LOOP);

    if (movingDown) {
        glVertex2f(x, y + radius / 2);
        glVertex2f(x - radius / 6, y - radius / 3);
        glVertex2f(x - radius / 6, y - radius / 6);
        glVertex2f(x - radius / 2, y + radius / 6);
        glVertex2f(x - radius / 2, y + radius / 3);
        glVertex2f(x - radius / 6, y + radius / 6);
        glVertex2f(x - radius / 6, y + radius / 3);
        glVertex2f(x - radius / 4, y + radius / 2);
        glVertex2f(x + radius / 4, y + radius / 2);
        glVertex2f(x + radius / 6, y + radius / 3);
        glVertex2f(x + radius / 6, y + radius / 6);
        glVertex2f(x + radius / 2, y + radius / 3);
        glVertex2f(x + radius / 2, y + radius / 6);
        glVertex2f(x + radius / 6, y - radius / 6);
        glVertex2f(x + radius / 6, y - radius / 3);
    }
    else {
        glVertex2f(x, y - radius / 2);
        glVertex2f(x - radius / 6, y + radius / 3);
        glVertex2f(x - radius / 6, y + radius / 6);
        glVertex2f(x - radius / 2, y - radius / 6);
        glVertex2f(x - radius / 2, y - radius / 3);
        glVertex2f(x - radius / 6, y - radius / 6);
        glVertex2f(x - radius / 6, y - radius / 3);
        glVertex2f(x - radius / 4, y - radius / 2);
        glVertex2f(x + radius / 4, y - radius / 2);
        glVertex2f(x + radius / 6, y - radius / 3);
        glVertex2f(x + radius / 6, y - radius / 6);
        glVertex2f(x + radius / 2, y - radius / 3);
        glVertex2f(x + radius / 2, y - radius / 6);
        glVertex2f(x + radius / 6, y + radius / 6);
        glVertex2f(x + radius / 6, y + radius / 3);
    }

    glEnd();
}
void drawCircle(float cx, float cy, float radius, int segments) {
    glBegin(GL_LINE_LOOP);
    glVertex2f(cx, cy);
    for (int i = 0; i <= segments; ++i) {
        float theta = 2.0f * PI * float(i) / float(segments);
        float x = radius * cosf(theta);
        float y = radius * sinf(theta);
        glVertex2f(cx + x, cy + y);
    }
    glEnd();
}
void drawTriangle(float x, float y, float radius) {
    float height = (std::sqrt(3) / 2) * radius;

    glBegin(GL_TRIANGLE_FAN);
    glVertex2f(x, y + height * 2.0f / 3.0f);
    glVertex2f(x - radius / 2, y - height * 1.0f / 3.0f);
    glVertex2f(x + radius / 2, y - height * 1.0f / 3.0f);
    glEnd();
}
bool isPlanePowerCollision(float tx, float ty, float r1, float sx, float sy, float r2) {
    float halfSideTriangle = r1 / 2.0;
    float halfSideSquare = r2 / 2.0;
    float triangleHeight = (std::sqrt(3) / 2) * r1;
    float halfHeightTriangle = triangleHeight / 2.0;

    bool xOverlap = std::abs(sx - tx) <= (halfSideSquare + halfSideTriangle);
    bool yOverlap = std::abs(sy - ty) <= (halfSideSquare + halfHeightTriangle);

    return xOverlap && yOverlap;
}
bool isPlaneBulletCollision(float cx, float cy, float r1, float sx, float sy, float r2) {
    float closestX = std::max(sx - r2, std::min(cx, sx + r2));
    float closestY = std::max(sy - r2, std::min(cy, sy + r2));

    float distanceX = cx - closestX;
    float distanceY = cy - closestY;

    return (distanceX * distanceX + distanceY * distanceY) <= (r1 * r1);
}
void enemyInit(int enemyCount) {
    for (int i = 0; i < enemyCount; ++i) {
        enemies.push_back({ getRandomFloat(SCALE_MIN, SCALE_MAX), getRandomFloat(0, SCALE_MAX), enemyRadius, getRandomInt(1, 10) });
    }
}
void enemyMove() {
    for (auto& enemy : enemies) {
        if (enemy.movingRight) {
            enemy.x += enemySpeed;
            if (enemy.x > SCALE_MAX - enemyRadius) enemy.movingRight = false;
        }
        else {
            enemy.x -= enemySpeed;
            if (enemy.x < SCALE_MIN + enemyRadius) enemy.movingRight = true;
        }
        if (enemy.movingDown) {
            enemy.y -= enemySpeed;
            if (enemy.y < enemyRadius) enemy.movingDown = false;
        }
        else {
            enemy.y += enemySpeed;
            if (enemy.y > SCALE_MAX) enemy.movingDown = true;
        }
    }
}
void enemyFire() {
    for (auto& enemy : enemies) {
        if (getRandomFloat(0.0f, 100.0f) < (enemy.x > 0.0f ? bulletEnemyChance : bulletEnemyChance * 2.0f) && !enemy.movingDown) {
            enemyBullets.push_back({ enemy.x, enemy.y - enemy.radius});
        }
    }
}
void powerBulletInit() {
    if (getRandomFloat(0.0f, 100.0f) < powerRate) {
        powersBullet.push_back({ getRandomFloat(SCALE_MIN, SCALE_MAX), SCALE_MAX, powerRadius });
    }
}
void powerBulletUp() {
    bulletCount += bulletCount >= maxBulletCount ? 0 : 1;
    playerBullets.resize(bulletCount);
}
void powerImmortalInit() {
    if (getRandomFloat(0.0f, 100.0f) < powerRate) {
        powersImmortal.push_back({ getRandomFloat(SCALE_MIN, SCALE_MAX), SCALE_MAX, powerRadius });
    }
}
void powerImmortalUp() {
    playerImmortal = true;
}
void playerMove(GLFWwindow* window) {
    if ((glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS || glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) && playerX > SCALE_MIN + playerRadius)
        playerX -= playerSpeed;
    if ((glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS || glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) && playerX < SCALE_MAX - playerRadius)
        playerX += playerSpeed;
    if ((glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS || glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) && playerY < playerRadius)
        playerY += playerSpeed;
    if ((glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS || glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) && playerY > SCALE_MIN + playerRadius)
        playerY -= playerSpeed;

    auto currentTime = std::chrono::high_resolution_clock::now();
    float deltaTime = std::chrono::duration<float>(currentTime - lastTimeBullet).count();
    lastTimeBullet = currentTime;
    bulletTime += deltaTime;

    if (bulletTime >= bulletPlayerCooldown) {
        if (bulletCount == 1) {
            playerBullets[0].push_back(Bullet{ playerX, playerY + playerRadius / 2 });
        }
        else {
            for (size_t i = 0; i < bulletCount; ++i) {
                playerBullets[i].push_back(Bullet{ playerX - playerRadius / 2 + i * playerRadius / (bulletCount - 1), playerY + playerRadius / 2 });
            }
        }
        bulletTime = 0.0f;
    }

    currentTime = std::chrono::high_resolution_clock::now();
    deltaTime = std::chrono::duration<float>(currentTime - lastTimeImmortal).count();
    lastTimeImmortal = currentTime;
    immortalTime += deltaTime;
    if (immortalTime > playerImmortalTime) {
        playerImmortal = false;
        immortalTime = 0.0f;
    }
}
void render() {
    glClear(GL_COLOR_BUFFER_BIT);

    // Draw the player
    if (!playerImmortal) { 
        glColor3f(0.0f, 1.0f, 1.0f); // Cyan
    } 
    else { 
        if (playerImmortalTime - immortalTime < 5.0f) {
            if (getRandomFloat(0.0f, 100.f) < 50.0f) {
                glColor3f(1.0f, 1.0f, 1.0f); // White
            }
            else {
                glColor3f(0.0f, 0.0f, 0.0f);
            }
        }
        else {
            glColor3f(1.0f, 1.0f, 1.0f); // White
        }
    }
    drawPlayer(playerX, playerY, playerRadius);

    // Draw power Bullet
    if (getRandomFloat(0.0f, 100.f) < 50.0f) {
        glColor3f(0.0f, 1.0f, 1.0f); // Cyan
    }
    else {
        glColor3f(0.0f, 0.0f, 0.0f);
    }
    for (auto power = powersBullet.begin(); power != powersBullet.end();) {
        if (power->y < SCALE_MIN) {
            power = powersBullet.erase(power);
        }
        else {
            drawTriangle(power->x, power->y, powerRadius);
            power->y -= powerSpeed;
            ++power;
        }
    }

    // Draw power Immortal
    if (getRandomFloat(0.0f, 100.f) < 50.0f) {
        glColor3f(1.0f, 1.0f, 1.0f); // White
    }
    else {
        glColor3f(0.0f, 0.0f, 0.0f);
    }
    for (auto power = powersImmortal.begin(); power != powersImmortal.end();) {
        if (power->y < SCALE_MIN) {
            power = powersImmortal.erase(power);
        }
        else {
            drawTriangle(power->x, power->y, powerRadius);
            power->y -= powerSpeed;
            ++power;
        }
    }

    // Draw player bullets
    glColor3f(1.0f, 1.0f, 1.0f); // White
    for (size_t i = 0; i < bulletCount; ++i) {
        for (auto bullet = playerBullets[i].begin(); bullet != playerBullets[i].end();) {
            if (bullet->y > SCALE_MAX) {
                bullet = playerBullets[i].erase(bullet);
            }
            else {
                drawCircle(bullet->x, bullet->y, bulletPlayerRadius);
                bullet->y += bulletPlayerSpeed;
                ++bullet;
            }
        }
    }

    // Draw enemies
    for (auto enemy = enemies.begin(); enemy != enemies.end();) {
        if (enemy->hp <= 3) { 
            glColor3f(0.0f, 1.0f, 0.0f); // Green
        }
        else if (enemy->hp <= 6 && enemy-> hp > 3) {
            glColor3f(1.0f, 1.0f, 0.0f); // Yellow
        }
        else if (enemy->hp > 6) {
            glColor3f(1.0f, 0.0f, 0.0f); // Red
        }
        drawEnemy(enemy->x, enemy->y, enemy->radius, enemy->movingDown);
        ++enemy;

    }

    // Draw enemy bullets
    glColor3f(1.0f, 0.0f, 1.0f); // Pink
    for (auto bullet = enemyBullets.begin(); bullet != enemyBullets.end();) {
        if (bullet->y < SCALE_MIN) {
            bullet = enemyBullets.erase(bullet);
        }
        else {
            drawCircle(bullet->x, bullet->y, bulletEnemyRadius);
            bullet->y -= bulletEnemySpeed;
            ++bullet;
        }
    }
}
void checkCollision() {
    for (auto bullet = enemyBullets.begin(); bullet != enemyBullets.end();) {
        // Use playerRadius / 2 for a smaller hitbox
        if (isPlaneBulletCollision(bullet->x, bullet->y, bulletEnemyRadius, playerX, playerY, playerRadius / 2) && !playerImmortal) {
            bullet = enemyBullets.erase(bullet);
            drawMenu();
            currentState = GameState::MENU;
            system("cls");
            std::cout << "Nice try! You scored " << playerScore << " points!\n\n";
            std::cout << "Do you want to play again? \n";
            std::cout << "1. Easy\n";
            std::cout << "2. Medium\n";
            std::cout << "3. Super Mega Ultra Hard\n";
            std::cout << "4. I don't want to play anymore\n\n";
            scoreToFile("game_log.txt");
        }
        else {
            ++bullet;
        }
    }

    for (auto enemy = enemies.begin(); enemy != enemies.end();) {
        bool hit = false;

        for (size_t i = 0; i < playerBullets.size(); ++i) {
            for (auto bullet = playerBullets[i].begin(); bullet != playerBullets[i].end();) {
                if (isPlaneBulletCollision(bullet->x, bullet->y, bulletPlayerRadius, enemy->x, enemy->y, enemyRadius / 2) && !hit) {
                    if (enemy->hp == 1) {
                        enemy = enemies.erase(enemy);
                        hit = true;
                    }
                    else {
                        enemy->hp--;
                    }
                    bullet = playerBullets[i].erase(bullet);
                    break;
                }
                else {
                    ++bullet;
                }
            }

            if (hit) {
                playerScore += 1;
                break;
            }
        }

        if (!hit) ++enemy;
    }

    for (auto power = powersBullet.begin(); power != powersBullet.end();) {
        if (isPlanePowerCollision(power->x, power->y, powerRadius, playerX, playerY, playerRadius)) {
            power = powersBullet.erase(power);
            powerBulletUp();
        }
        else {
            ++power;
        }
    }

    for (auto power = powersImmortal.begin(); power != powersImmortal.end();) {
        if (isPlanePowerCollision(power->x, power->y, powerRadius, playerX, playerY, playerRadius)) {
            power = powersImmortal.erase(power);
            immortalTime = 0.0f;
            powerImmortalUp();
        }
        else {
            ++power;
        }
    }
}
void InitializeGame() {
    playerImmortal = false;
    playerScore = 0;
    playerX = 0.0f;
    playerY = -0.90f;
    bulletCount = 1;
    enemyCount = 0;
    enemySpeed = 0.2f * playerSpeed;
    bulletEnemySpeed = 2.0f * enemySpeed;
    bulletEnemyChance = 0.2f;
    enemies.clear();
    playerBullets.clear();
    enemyBullets.clear();
    powersBullet.clear();
    powersImmortal.clear();
    playerBullets.resize(bulletCount);
    enemyInit(enemyCount);
}
void setDifficulty(float difficulty) {
    enemyCount += 10 * difficulty;
    enemySpeed *= difficulty;
    bulletEnemyChance *= difficulty;
}
GLFWwindow* createWindow(int width, int height, const char* title) {
    if (!glfwInit()) {
        std::cerr << "Failed to initialize GLFW" << std::endl;
        return nullptr;
    }

    GLFWwindow* window = glfwCreateWindow(width, height, title, NULL, NULL);
    if (window == nullptr) {
        std::cerr << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return nullptr;
    }
    glfwMakeContextCurrent(window);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cerr << "Failed to initialize GLAD" << std::endl;
        return nullptr;
    }
    glViewport(0, 0, width, height);

    // Load the icon image
    int widthIcon, heightIcon, channels;
    unsigned char* iconData = stbi_load("chickenInvaders.png", &widthIcon, &heightIcon, &channels, 0);
    if (iconData) {
        GLFWimage icon[1];
        icon[0].width = widthIcon;
        icon[0].height = heightIcon;
        icon[0].pixels = iconData;

        // Set the window icon
        glfwSetWindowIcon(window, 1, icon);

        // Free the icon data
        stbi_image_free(iconData);
    }
    else {
        std::cerr << "Failed to load icon image" << std::endl;
    }

    return window;
}