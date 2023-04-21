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


float speed = 0; //Prędkość kątowa obrotu obiektu

Models::Cube mainBody;
Models::Cube leftWing;
Models::Cube rightWing;
//Procedura obsługi błędów
void error_callback(int error, const char* description) {
	fputs(description, stderr);
}

glm::vec3 cameraPosition(0.0f, 0.0f, 7.0f);
glm::vec3 cameraVelocity(0.0f);
glm::vec3 cameraAcceleration(0.0f);
float cameraYaw = 0.0f;
float cameraPitch = 0.0f;

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods) {
	float accelerationAmount = 1.0f;

	if (action == GLFW_PRESS) {
		if (key == GLFW_KEY_W) {
			cameraAcceleration.z = -accelerationAmount;
		}
		if (key == GLFW_KEY_S) {
			cameraAcceleration.z = accelerationAmount;
		}
	}

	if (action == GLFW_RELEASE) {
		if (key == GLFW_KEY_W || key == GLFW_KEY_S) {
			cameraAcceleration.z = 0;
		}
	}
}

void mouse_callback(GLFWwindow* window, double xpos, double ypos) {
	static double lastX = 0.0;
	static double lastY = 0.0;
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

	float sensitivity = 0.1f;
	xoffset *= sensitivity;
	yoffset *= sensitivity;

	cameraYaw += xoffset;
	cameraPitch += yoffset;

	if (cameraPitch > 89.0f) {
		cameraPitch = 89.0f;
	}
	if (cameraPitch < -89.0f) {
		cameraPitch = -89.0f;
	}
}


//Procedura inicjująca
void initOpenGLProgram(GLFWwindow* window) {
    initShaders();	
	//************Tutaj umieszczaj kod, który należy wykonać raz, na początku programu************
	glClearColor(0, 0, 0, 1);//Ustaw czarny kolor czyszczenia ekranu
	glEnable(GL_DEPTH_TEST); //Włącz test głębokości pikseli
	glfwSetKeyCallback(window, key_callback); //Zarejestruj procedurę obsługi klawiatury
}


//Zwolnienie zasobów zajętych przez program
void freeOpenGLProgram(GLFWwindow* window) {
    freeShaders();
    //************Tutaj umieszczaj kod, który należy wykonać po zakończeniu pętli głównej************
}


void drawSpaceship() {
	// Main body (a long rectangle)
	glm::mat4 mainBodyModel = glm::scale(glm::mat4(1.0f), glm::vec3(1.0f, 0.2f, 0.5f));
	glUniformMatrix4fv(spLambert->u("M"), 1, false, glm::value_ptr(mainBodyModel));
	glUniform4f(spLambert->u("color"), 0.5f, 0.5f, 0.5f, 1.0f); // Set spaceship color
	mainBody.drawSolid();

	// Left wing (a shorter rectangle)
	glm::mat4 leftWingModel = glm::translate(glm::mat4(1.0f), glm::vec3(-0.6f, 0.0f, -0.3f));
	leftWingModel = glm::scale(leftWingModel, glm::vec3(0.4f, 0.15f, 0.4f));
	glUniformMatrix4fv(spLambert->u("M"), 1, false, glm::value_ptr(leftWingModel));
	glUniform4f(spLambert->u("color"), 0.5f, 0.5f, 0.5f, 1.0f); // Set spaceship color
	leftWing.drawSolid();

	// Right wing (a shorter rectangle)
	glm::mat4 rightWingModel = glm::translate(glm::mat4(1.0f), glm::vec3(-0.6f, 0.0f, 0.3f));
	rightWingModel = glm::scale(rightWingModel, glm::vec3(0.4f, 0.15f, 0.4f));
	glUniformMatrix4fv(spLambert->u("M"), 1, false, glm::value_ptr(rightWingModel));
	glUniform4f(spLambert->u("color"), 0.5f, 0.5f, 0.5f, 1.0f); // Set spaceship color
	rightWing.drawSolid();
}

//Procedura rysująca zawartość sceny
void drawScene(GLFWwindow* window,float angle) {
	//************Tutaj umieszczaj kod rysujący obraz******************l
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); //Wyczyszczenie bufora kolorów i bufora głębokości
	
	glm::mat4 P = glm::perspective(glm::radians(50.0f), 1.0f, 1.0f, 50.0f); //Wyliczenie macierzy rzutowania

	// Update view matrix
	glm::vec3 front;
	front.x = cos(glm::radians(cameraYaw)) * cos(glm::radians(cameraPitch));
	front.y = sin(glm::radians(cameraPitch));
	front.z = sin(glm::radians(cameraYaw)) * cos(glm::radians(cameraPitch));
	glm::vec3 cameraFront = glm::normalize(front);
	glm::vec3 cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);
	glm::mat4 V = glm::lookAt(cameraPosition, cameraPosition + cameraFront, cameraUp);

	spLambert->use();//Aktywacja programu cieniującego
	glUniformMatrix4fv(spLambert->u("P"), 1, false, glm::value_ptr(P)); //Załadowanie macierzy rzutowania do programu cieniującego
	glUniformMatrix4fv(spLambert->u("V"), 1, false, glm::value_ptr(V));

	

	drawSpaceship();

	//Skopiowanie bufora ukrytego do widocznego. Z reguły ostatnie polecenie w procedurze drawScene.
	glfwSwapBuffers(window);
}
float deltaTime = 0.0f;
float lastFrame = 0.0f;

float cameraSpeed = 5.0f;

int main(void)
{
	GLFWwindow* window; //Wskaźnik na obiekt reprezentujący okno

	glfwSetErrorCallback(error_callback);//Zarejestruj procedurę obsługi błędów

	if (!glfwInit()) { //Zainicjuj bibliotekę GLFW
		fprintf(stderr, "Nie można zainicjować GLFW.\n");
		exit(EXIT_FAILURE);
	}

	window = glfwCreateWindow(500, 500, "OpenGL", NULL, NULL);  //Utwórz okno 500x500 o tytule "OpenGL" i kontekst OpenGL.

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


	float angle = 0; //Aktualny kąt obrotu obiektu
	while (!glfwWindowShouldClose(window)) //Tak długo jak okno nie powinno zostać zamknięte
	{
		angle += speed * glfwGetTime(); //Oblicz przyrost kąta po obrocie
		deltaTime = glfwGetTime();


		// Calculate deltaTime
		float currentFrame = glfwGetTime();
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;

		// Update camera velocity and position
		cameraVelocity += cameraAcceleration * deltaTime;
		cameraPosition += cameraVelocity * deltaTime;

		// Dampen the camera velocity (simulate drag)
		cameraVelocity *= 0.95f;


		drawScene(window,angle); //Wykonaj procedurę rysującą

		// Set mouse and key callbacks
		glfwSetCursorPosCallback(window, mouse_callback);
		glfwSetKeyCallback(window, key_callback);

		glfwPollEvents(); //Wykonaj procedury callback w zalezności od zdarzeń jakie zaszły.
	}

	freeOpenGLProgram(window);

	glfwDestroyWindow(window); //Usuń kontekst OpenGL i okno
	glfwTerminate(); //Zwolnij zasoby zajęte przez GLFW
	exit(EXIT_SUCCESS);
}
