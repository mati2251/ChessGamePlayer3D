#define GLM_FORCE_RADIANS

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <cstdlib>
#include <cstdio>
#include "../include/glm/glm.hpp"
#include "../include/glm/gtc/type_ptr.hpp"
#include "chessboard/chessboard.h"
#include "obj_reader/obj_reader.h"

float aspectRatio = 1;
ProgramState *programState;
ObjReader *objReader;

void error_callback(int error, const char *description) {
    fputs(description, stderr);
}

void keyCallback(GLFWwindow *window, int key, int scancode, int action, int mods) {
    programState->rotateController->keyCallback(window, key, scancode, action, mods);
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
    programState = ProgramState::getInstance();
    objReader = new ObjReader("../resources/pawn.obj", "../resources/wood_black.png");
    glfwSetKeyCallback(window, keyCallback);
}

void freeOpenGLProgram(GLFWwindow *window) {
}

void drawScene(GLFWwindow *window) {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    Chessboard chessboard;
    programState->rotateController->rotateM();
    chessboard.draw(programState->M);
    glm::mat4 pawn = glm::translate(programState->M, glm::vec3(0, 0, 0.5));
    objReader->draw(pawn);
    glfwSwapBuffers(window);
}

int main(void) {
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
