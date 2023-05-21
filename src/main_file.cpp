#define GLM_FORCE_RADIANS

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <cstdlib>
#include <cstdio>
#include "../include/glm/glm.hpp"
#include "../include/glm/gtc/type_ptr.hpp"
#include "../include/glm/gtc/matrix_transform.hpp"
#include "shaderprogram/shaderprogram.h"
#include "constants.h"

float aspectRatio = 1;
ShaderProgram *sp;

void error_callback(int error, const char *description) {
    fputs(description, stderr);
}

void windowResizeCallback(GLFWwindow *window, int width, int height) {
    if (height == 0) return;
    aspectRatio = (float) width / (float) height;
    glViewport(0, 0, width, height);
}

void initOpenGLProgram(GLFWwindow *window) {
    glClearColor(0, 0, 0, 1);
    glEnable(GL_DEPTH_TEST);
    glfwSetWindowSizeCallback(window, windowResizeCallback);
    sp = new ShaderProgram("../src/shaders/colored/v_colored.glsl", NULL, "../src/shaders/colored/f_colored.glsl");
}

void freeOpenGLProgram(GLFWwindow *window) {
    delete sp;
}


void drawScene(GLFWwindow *window) {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glm::mat4 V = glm::lookAt(
            glm::vec3(0, 0, -5),
            glm::vec3(0, 0, 0),
            glm::vec3(0.0f, 1.0f, 0.0f));

    glm::mat4 P = glm::perspective(50.0f * (float) M_PI / 180.0f, aspectRatio, 0.01f, 200.0f);
    glm::mat4 M = glm::mat4(1.0f);

    sp->use();
    glUniformMatrix4fv(sp->u("P"), 1, false, glm::value_ptr(P));
    glUniformMatrix4fv(sp->u("V"), 1, false, glm::value_ptr(V));
    glUniformMatrix4fv(sp->u("M"), 1, false, glm::value_ptr(V));

    glfwSwapBuffers(window);
}

int main(void) {
    GLFWwindow *window;

    glfwSetErrorCallback(error_callback);

    if (!glfwInit()) {
        fprintf(stderr, "Can't initialize GLFW.\n");
        exit(EXIT_FAILURE);
    }

    window = glfwCreateWindow(1000, 1000, "Asteroid3D", NULL,
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

    while (!glfwWindowShouldClose(window)) {
        drawScene(window);
        glfwPollEvents();
    }

    freeOpenGLProgram(window);

    glfwDestroyWindow(window);
    glfwTerminate();
    exit(EXIT_SUCCESS);
}
