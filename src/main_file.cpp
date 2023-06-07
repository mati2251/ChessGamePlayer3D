#define GLM_FORCE_RADIANS

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <cstdlib>
#include <cstdio>
#include "../include/glm/glm.hpp"
#include "../include/glm/gtc/type_ptr.hpp"
#include "chessboard/chessboard.h"
#include "figure/figure.h"
#include "game/game.h"

float aspectRatio = 1;
ProgramState *programState;
Game *game;
std::string fileName;

void error_callback(int error, const char *description) {
    fputs(description, stderr);
}

void keyCallback(GLFWwindow *window, int key, int scancode, int action, int mods) {
    programState->rotateController->keyCallback(window, key, scancode, action, mods);
    if (key == GLFW_KEY_SPACE && action == GLFW_PRESS) {
        game->nextMove();
    }
}

void windowResizeCallback(GLFWwindow *window, int width, int height) {
    if (height == 0) return;
    aspectRatio = (float) width / (float) height;
    glViewport(0, 0, width, height);
}

void initOpenGLProgram(GLFWwindow *window) {
    glClearColor(0.7, 0.7, 0.7, 1);
    glEnable(GL_DEPTH_TEST);
    glfwSetWindowSizeCallback(window, windowResizeCallback);
    game = new Game();
    programState = ProgramState::getInstance();
    glfwSetKeyCallback(window, keyCallback);
    game->loadGameFile(fileName);
}

void freeOpenGLProgram(GLFWwindow *window) {
}

void drawScene(GLFWwindow *window) {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    Chessboard chessboard;
    programState->rotateController->rotateM();
    chessboard.draw(glm::mat4(programState->M));
    game->draw();
    glfwSwapBuffers(window);
}

int main(int argc, char **argv) {
    if(argc != 2) {
        printf("Usage: ./chess <game_file>\n");
        exit(EXIT_FAILURE);
    }
    fileName = argv[1];
    GLFWwindow *window;

    glfwSetErrorCallback(error_callback);

    if (!glfwInit()) {
        fprintf(stderr, "Can't initialize GLFW.\n");
        exit(EXIT_FAILURE);
    }

    window = glfwCreateWindow(1000, 1000, "Chess", NULL,
                              NULL);

    if (!window) {
        fprintf(stderr, "Can't create window.\n");
        glfwTerminate();
        exit(EXIT_FAILURE);
    }

    glfwMakeContextCurrent(window);
    glfwSwapInterval(1);

    if (glewInit() != GLEW_OK) {
        fprintf(stderr, "Can't initialize GLEW.\n");
        exit(EXIT_FAILURE);
    }

    initOpenGLProgram(window);
    glfwSetTime(0);
    while (!glfwWindowShouldClose(window)) {
        drawScene(window);
        glfwPollEvents();
    }

    freeOpenGLProgram(window);

    glfwDestroyWindow(window);
    glfwTerminate();
    exit(EXIT_SUCCESS);
}
