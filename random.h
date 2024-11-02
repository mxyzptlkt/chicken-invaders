#pragma once

#include <iostream>
#include <random>

inline float getRandomFloat(float min, float max);
inline int getRandomInt(int min, int max);
inline int getSign(float number);

float getRandomFloat(float min, float max) {
    return min + static_cast<float>(rand()) / (static_cast<float>(RAND_MAX / (max - min)));
}
int getRandomInt(int min, int max) {
    return (rand() % (max - min + 1)) + min;
}
int getSign(float number) {
    return (number > 0) ? 1 : (number < 0) ? -1 : 0;
}