Chicken Invaders Game
=======================

# Overview
Chicken Invader is a fun 2D game where you control a plane to fight chickens, avoid bullets,
and upgrade your weapon by collecting powers. The game provides an engaging experience as
you try to defeat invading chickens while improving your skills.

## Requirements
- **C++17**: Ensure your project is set to use the C++17 standard in Visual Studio.
- **Visual Studio**: This project is designed to be built and run in Visual Studio.
- **GLFW**: A library for creating windows with OpenGL contexts and managing input.
- **GLAD**: A library that manages OpenGL function pointers, allowing access to modern OpenGL functions.

### Setting Up C++17 in Visual Studio
(When opening this project in Visual Studio, the C++17 setting should apply automatically if
your version is compatible. However, if it does not, follow the steps below to configure 
your project settings manually):

1. Open your project in Visual Studio.
2. Go to **Project > chichkenInvaders Properties**.
3. Under **Configuration Properties**, navigate to **C/C++ > Language**.
4. Set the **C++ Language Standard** to **ISO C++17 Standard (/std:c++17)**.
==============================================================================

I. How to Start the Game
-------------------------
# To run the Chicken Invaders game, follow these steps:

1. Clone or Download the Project: Ensure you have all necessary project files.
2. If you just want to play the game:
   - Open the Project folder → x64 → Release.
   - Run chickenInvaders.exe with a chicken icon.
3. If you want to adjust the game:
   - Open Visual Studio, go to File → Open → Project/Solution, and select the project file.
4. Build and Run:
   - Press F5 or Debug → Start Debugging to build and launch the game.
**Note**: After making adjustments in Debug mode, remember to switch to Release mode to ensure the latest changes are applied to the Release executable:
   - In Visual Studio, select Release from the build configuration dropdown (usually at the top toolbar).
   - Then, go to Build → Rebuild Solution.
   - After rebuilding, the updated chickenInvaders.exe will be available in x64 → Release.

II. Gameplay Overview
----------------------

# Starting the Game
When the game starts, two windows will appear:

1. **Window Console**: Displays your current score throughout the game.
The score is also saved to a file named "game_log.txt" for record-keeping and review.
2. **Game Console**: Provides four options as buttons:
   - **Easy**: Start easy mode.
   - **Medium**: Start medium mode.
   - **Hard**: Start hard mode.
   - **Exit**: Close the game.

Whenever you die, you’ll return to this menu to select a difficulty level or exit.

## In-Game Mechanics
- **Player Controls**: Control a blue plane using the arrow keys or WASD.
  - The plane can move only within the lower half of the game console.

- **Enemies**: Enemies appear in three colors, each requiring a different number of hits to defeat:
   - Green: Basic enemy.
   - Yellow: Moderate difficulty.
   - Red: Toughest enemy.
   - Enemies occupy the upper half of the game console and shoot reality bombs toward the player.

- **Objective**: Shoot the enemies using bullets fired from your plane while avoiding
incoming reality bombs from enemies.

### Power-Ups
- **Weapon Upgrade**: Collect blue triangle power-ups to increase the number of bullets 
you can fire (up to 5 bullets at once).
- **Invincibility**: Collecting a red triangle grants temporary invincibility, turning the 
plane red and allowing you to avoid damage for a few seconds. As invincibility is about 
to expire, the plane will start twinkling to indicate the effect is ending.
=============================================================================================

GOOD LUCK, AND MAY YOU DEFEAT THE INVADERS!

##### Copyright © Kiendeptrai. All rights reserved.
