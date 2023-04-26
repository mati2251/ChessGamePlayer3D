/*
Niniejszy program jest wolnym oprogramowaniem; możesz go
rozprowadzać dalej i / lub modyfikować na warunkach Powszechnej
Licencji Publicznej GNU, wydanej przez Fundację Wolnego
Oprogramowania - według wersji 2 tej Licencji lub(według twojego
wyboru) którejś z późniejszych wersji.

Niniejszy program rozpowszechniany jest z nadzieją, iż będzie on
użyteczny - jednak BEZ JAKIEJKOLWIEK GWARANCJI, nawet domyślnej
gwarancji PRZYDATNOŚCI HANDLOWEJ albo PRZYDATNOŚCI DO OKREŚLONYCH
ZASTOSOWAŃ.W celu uzyskania bliższych informacji sięgnij do
Powszechnej Licencji Publicznej GNU.

Z pewnością wraz z niniejszym programem otrzymałeś też egzemplarz
Powszechnej Licencji Publicznej GNU(GNU General Public License);
jeśli nie - napisz do Free Software Foundation, Inc., 59 Temple
Place, Fifth Floor, Boston, MA  02110 - 1301  USA
*/

#define GLM_FORCE_RADIANS

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <stdlib.h>
#include <stdio.h>
#include "constants.h"
#include "allmodels.h"
#include "lodepng.h"
#include "shaderprogram.h"

#include "camera.h"



Camera camera(glm::vec3(0.0f, 0.0f, 3.0f), -90.0f, 0.0f);


void error_callback(int error, const char* description) {
	fputs(description, stderr);
}



void mouse_callback(GLFWwindow* window, double xpos, double ypos) {
	static float lastX = 0.0f;
	static float lastY = 0.0f;
	static bool firstMouse = true;

	if (firstMouse) {
		lastX = xpos;
		lastY = ypos;
		firstMouse = false;
	}

	float xoffset = xpos - lastX;
	float yoffset = lastY - ypos;
	lastX = xpos;
	lastY = ypos;

	camera.processMouseMovement(xoffset, yoffset);
}



void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods) {

	if (action == GLFW_PRESS) {
		if (key == GLFW_KEY_LEFT_SHIFT) {
			camera.setCameraAcceleration(20.0f);
		}
	}
	else if (action == GLFW_RELEASE) {
		if (key == GLFW_KEY_LEFT_SHIFT) {
			camera.setCameraAcceleration(5.0f);
		}
	}
}


void initOpenGLProgram(GLFWwindow* window) {
	initShaders();
	glClearColor(0, 0, 0, 1);
	glEnable(GL_DEPTH_TEST);
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	glfwSetKeyCallback(window, key_callback);
	glfwSetCursorPosCallback(window, mouse_callback);
}


void freeOpenGLProgram(GLFWwindow* window) {
	freeShaders();
}


void car2() {
	Models::Torus carWheel;
	glm::mat4 Ms = glm::mat4(1.0f);
	float wheelAngle = 0.0f;
	float angle = 0.0f;
	float skret = 0.0f;
	Ms = glm::rotate(Ms, angle, glm::vec3(0.0f, 1.0f, 0.0f));

	//Podwozie
	glm::mat4 Mp = glm::scale(Ms, glm::vec3(1.5f, 0.125f, 1.0f));
	glUniform4f(spLambert->u("color"), 0, 1, 0, 1);
	glUniformMatrix4fv(spLambert->u("M"), 1, false, glm::value_ptr(Mp));  //Załadowanie macierzy modelu do programu cieniującego
	Models::cube.drawSolid(); //Narysowanie obiektu


	//Koło1
	glm::mat4 Mk1 = Ms;
	Mk1 = glm::translate(Mk1, glm::vec3(1.5f, 0.0f, 1.0f));
	Mk1 = glm::rotate(Mk1, skret, glm::vec3(0.0f, 1.0f, 0.0f));
	Mk1 = glm::rotate(Mk1, wheelAngle, glm::vec3(0.0f, 0.0f, 1.0f));
	glUniformMatrix4fv(spLambert->u("M"), 1, false, glm::value_ptr(Mk1));  //Załadowanie macierzy modelu do programu cieniującego
	carWheel.drawWire();

	//Koło2
	glm::mat4 Mk2 = Ms;
	Mk2 = glm::translate(Mk2, glm::vec3(1.5f, 0.0f, -1.0f));
	Mk2 = glm::rotate(Mk2, skret, glm::vec3(0.0f, 1.0f, 0.0f));
	Mk2 = glm::rotate(Mk2, wheelAngle, glm::vec3(0.0f, 0.0f, 1.0f));
	glUniformMatrix4fv(spLambert->u("M"), 1, false, glm::value_ptr(Mk2));  //Załadowanie macierzy modelu do programu cieniującego
	carWheel.drawWire();

	//Koło3
	glm::mat4 Mk3 = Ms;
	Mk3 = glm::translate(Mk3, glm::vec3(-1.5f, 0.0f, 1.0f));
	Mk3 = glm::rotate(Mk3, wheelAngle, glm::vec3(0.0f, 0.0f, 1.0f));
	glUniformMatrix4fv(spLambert->u("M"), 1, false, glm::value_ptr(Mk3));  //Załadowanie macierzy modelu do programu cieniującego
	carWheel.drawWire();

	//Koło4
	glm::mat4 Mk4 = Ms;
	Mk4 = glm::translate(Mk4, glm::vec3(-1.5f, 0.0f, -1.0f));
	Mk4 = glm::rotate(Mk4, wheelAngle, glm::vec3(0.0f, 0.0f, 1.0f));
	glUniformMatrix4fv(spLambert->u("M"), 1, false, glm::value_ptr(Mk4));  //Załadowanie macierzy modelu do programu cieniującego
	carWheel.drawWire();


}


void drawSpaceship() {
	Models::Cube mainBody;
	Models::Cube rightWing;
	Models::Cube leftWing;

	glm::vec3 spaceshipOffset = glm::vec3(0.0f, -2.0f, -1.0f);
	glm::mat4 spaceshipModel = glm::translate(glm::mat4(1.0f), camera.getCameraPosition() + spaceshipOffset);

	glm::vec3 right = glm::normalize(glm::cross(camera.getCameraFront(), camera.getCameraUp()));
	glm::mat4 rotationMatrix = glm::mat4(glm::vec4(right, 0.0f), glm::vec4(camera.getCameraUp(), 0.0f), glm::vec4(camera.getCameraFront(), 0.0f), glm::vec4(0.0f, 0.0f, 0.0f, 1.0f));
	spaceshipModel = spaceshipModel * rotationMatrix;


	spaceshipModel = glm::rotate(spaceshipModel, glm::radians(-90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
	spaceshipModel = glm::scale(spaceshipModel, glm::vec3(0.5f, 0.5f, 0.5f));
	
	glm::mat4 mainBodyModel = glm::scale(spaceshipModel, glm::vec3(1.0f, 0.2f, 0.5f));
	glUniformMatrix4fv(spLambert->u("M"), 1, false, glm::value_ptr(mainBodyModel));
	glUniform4f(spLambert->u("color"), 0.5f, 0.5f, 0.5f, 1.0f);
	mainBody.drawSolid();

	
	glm::mat4 leftWingModel = glm::translate(spaceshipModel, glm::vec3(-0.6f, 0.0f, -0.3f));
	leftWingModel = glm::scale(leftWingModel, glm::vec3(0.4f, 0.15f, 0.4f));
	glUniformMatrix4fv(spLambert->u("M"), 1, false, glm::value_ptr(leftWingModel));
	glUniform4f(spLambert->u("color"), 0.5f, 0.5f, 0.5f, 1.0f); 
	leftWing.drawSolid();

	glm::mat4 rightWingModel = glm::translate(spaceshipModel, glm::vec3(-0.6f, 0.0f, 0.3f));
	rightWingModel = glm::scale(rightWingModel, glm::vec3(0.4f, 0.15f, 0.4f));
	glUniformMatrix4fv(spLambert->u("M"), 1, false, glm::value_ptr(rightWingModel));
	glUniform4f(spLambert->u("color"), 0.5f, 0.5f, 0.5f, 1.0f);
	rightWing.drawSolid();
}

float aspectRatio = 1.0f;

void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
	glViewport(0, 0, width, height);

	aspectRatio = static_cast<float>(width) / static_cast<float>(height);

	glm::mat4 projection = glm::perspective(glm::radians(50.0f), aspectRatio, 1.0f, 50.0f);
}

void drawScene(GLFWwindow* window) {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); 

	glm::mat4 P = glm::perspective(glm::radians(50.0f), aspectRatio, 1.0f, 50.0f);
	glm::mat4 V = camera.getViewMatrix();

	spLambert->use();
	glUniformMatrix4fv(spLambert->u("P"), 1, false, glm::value_ptr(P)); 
	glUniformMatrix4fv(spLambert->u("V"), 1, false, glm::value_ptr(V)); 


	car2();

	drawSpaceship();

	glfwSwapBuffers(window);
}


int main(void)
{
	GLFWwindow* window; //Wskaźnik na obiekt reprezentujący okno

	glfwSetErrorCallback(error_callback);//Zarejestruj procedurę obsługi błędów

	if (!glfwInit()) { //Zainicjuj bibliotekę GLFW
		fprintf(stderr, "Nie można zainicjować GLFW.\n");
		exit(EXIT_FAILURE);
	}

	window = glfwCreateWindow(1000, 1000, "OpenGL", NULL, NULL);  //Utwórz okno 500x500 o tytule "OpenGL" i kontekst OpenGL.
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

	if (!window) //Jeżeli okna nie udało się utworzyć, to zamknij program
	{
		fprintf(stderr, "Nie można utworzyć okna.\n");
		glfwTerminate();
		exit(EXIT_FAILURE);
	}

	glfwMakeContextCurrent(window); //Od tego momentu kontekst okna staje się aktywny i polecenia OpenGL będą dotyczyć właśnie jego.
	glfwSwapInterval(1); //Czekaj na 1 powrót plamki przed pokazaniem ukrytego bufora

	if (glewInit() != GLEW_OK) { //Zainicjuj bibliotekę GLEW
		fprintf(stderr, "Nie można zainicjować GLEW.\n");
		exit(EXIT_FAILURE);
	}

	initOpenGLProgram(window); //Operacje inicjujące

	glfwSetTime(0); 
	float deltaTime = 0.0f;
	float lastFrame = 0.0f;
	//Główna pętla
	while (!glfwWindowShouldClose(window)) //Tak długo jak okno nie powinno zostać zamknięte
	{
		float currentFrame = glfwGetTime();
		float deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;

		camera.processKeyboardInput(window, deltaTime);

		

		// Clear buffers and set the view and projection matrices
		drawScene(window);
		glfwPollEvents();
	}

	freeOpenGLProgram(window);

	glfwDestroyWindow(window); //Usuń kontekst OpenGL i okno
	glfwTerminate(); //Zwolnij zasoby zajęte przez GLFW
	exit(EXIT_SUCCESS);
}
