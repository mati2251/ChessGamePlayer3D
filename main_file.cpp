#define GLM_FORCE_RADIANS

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <stdlib.h>
#include <stdio.h>

void error_callback(int error, const char *description) {
    fputs(description, stderr);
}

void initOpenGLProgram(GLFWwindow *window) {
}

void freeOpenGLProgram(GLFWwindow *window) {
}

void drawScene(GLFWwindow *window) {
}


int main(void) {
    GLFWwindow *window;

    glfwSetErrorCallback(error_callback);

    if (!glfwInit()) {
        fprintf(stderr, "Can't initialize GLFW.\n");
        exit(EXIT_FAILURE);
    }

    window = glfwCreateWindow(500, 500, "OpenGL", NULL,
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
