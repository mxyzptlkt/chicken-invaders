#pragma once

#include <GLFW/glfw3.h>
#include <iostream>

const float R1 = 0.0f, G1 = 1.0f, B1 = 0.0f; // Green
const float R2 = 1.0f, G2 = 1.0f, B2 = 0.0f; // Yellow
const float R3 = 1.0f, G3 = 0.0f, B3 = 0.0f; // Red
const float R4 = 1.0f, G4 = 1.0f, B4 = 1.0f; // White
const float menuBarX1 = -0.5f, menuBarY1 = 0.2f;
const float menuBarX2 = -0.5f, menuBarY2 = 0.0f;
const float menuBarX3 = -0.5f, menuBarY3 = -0.2f;
const float menuBarX4 = -0.5f, menuBarY4 = -0.4f;
const float menuBarWidth = 1.0f, menuBarHeight = 0.1f;

void drawRectangle(float x, float y, float width, float height, float r, float g, float b) {
    glBegin(GL_QUADS);
    glColor3f(r, g, b);
    glVertex2f(x, y);
    glVertex2f(x + width, y);
    glVertex2f(x + width, y + height);
    glVertex2f(x, y + height);
    glEnd();
}
void drawMenu() {
    drawRectangle(menuBarX1, menuBarY1, menuBarWidth, menuBarHeight, R1, G1, B1); // Easy option
    drawRectangle(menuBarX2, menuBarY2, menuBarWidth, menuBarHeight, R2, G2, B2); // Medium option
    drawRectangle(menuBarX3, menuBarY3, menuBarWidth, menuBarHeight, R3, G3, B3); // Hard option
    drawRectangle(menuBarX4, menuBarY4, menuBarWidth, menuBarHeight, R4, G4, B4); // Exit option
}