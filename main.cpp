#include <glad/glad.h>
#include "menu.h"
#include "config.h"
#include "gameplay.h"


int main() {
    GLFWwindow* window = createWindow(WIDTH, HEIGHT, "Chicken Invaders");
	if (window == NULL)
	{
		return -1;
	}

    while (!glfwWindowShouldClose(window)) {
        switch (currentState) {
            case MENU:
                drawMenu();
                if (glfwGetKey(window, GLFW_KEY_1) == GLFW_PRESS) {
                    difficulty = 1.0f;
                    currentState = GameState::PLAYING;
                }
                if (glfwGetKey(window, GLFW_KEY_2) == GLFW_PRESS) {
                    difficulty = 1.5f;
                    currentState = GameState::PLAYING;
                }
                if (glfwGetKey(window, GLFW_KEY_3) == GLFW_PRESS) {
                    difficulty = 2.0f;
                    currentState = GameState::PLAYING;
                }
                if (glfwGetKey(window, GLFW_KEY_0) == GLFW_PRESS) {
                    currentState = GameState::GAME_OVER;
                }
                InitializeGame();
                setDifficulty(difficulty);
                break;

            case PLAYING:
                std::cout << playerScore << std::endl;
                if (enemies.size() < enemyCount) {
                    enemyInit(getRandomInt(1, enemyCount) - enemies.size());

                }
                powerBulletInit();
                powerImmortalInit();
                playerMove(window);
                enemyMove();
                enemyFire();
                render();
                checkCollision();
                break;

            case GAME_OVER:
                glfwSetWindowShouldClose(window, true);
                break;
            }

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwDestroyWindow(window);
    glfwTerminate();
    return 0;
}
