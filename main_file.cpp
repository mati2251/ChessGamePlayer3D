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
float skret = 0; //skret kół
float deltaTime = 0;
float lastFrame = 0.0f;
Models::Sphere sun(0.5, 36, 36);
Models::Sphere planet1(0.2, 36, 36);
Models::Sphere moon1(0.1, 36, 36);
Models::Sphere planet2(0.25, 36, 36);
Models::Sphere moon2(0.07, 36, 36);
Models::Torus carWheel(0.3, 0.1, 36, 36);



// Camera variables
glm::vec3 cameraPosition = glm::vec3(0.0f, 0.0f, 3.0f);
glm::vec3 cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
glm::vec3 cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);


float cameraSpeed = 0.0f;

//Procedura obsługi błędów
void error_callback(int error, const char* description) {
	fputs(description, stderr);
}

//Procedura obsługi klawiatury
glm::vec3 cameraVelocity(0.0f);
glm::vec3 cameraAcceleration(0.0f, 0.0f, 0.0f);
float accelerationAmount = 5.0f;




float yaw = -90.0f; // Yaw is initially set so that the camera is facing along the positive Z-axis
float pitch = 0.0f;
glm::vec3 worldUp = glm::vec3(0.0f, 1.0f, 0.0f);
glm::vec3 cameraRight;



void updateCameraVectors() {
	// Calculate the new cameraFront vector
	glm::vec3 front;
	front.x = cos(glm::radians(pitch)) * cos(glm::radians(yaw));
	front.y = sin(glm::radians(pitch));
	front.z = cos(glm::radians(pitch)) * sin(glm::radians(yaw));
	cameraFront = glm::normalize(front);

	// Update the cameraRight and cameraUp vectors
	cameraRight = glm::normalize(glm::cross(cameraFront, worldUp));
	cameraUp = glm::normalize(glm::cross(cameraRight, cameraFront));
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

	float sensitivity = 0.05f;
	xoffset *= sensitivity;
	yoffset *= sensitivity;

	yaw += xoffset;
	pitch += yoffset;

	// Limit the pitch to avoid gimbal lock
	if (pitch > 89.0f) {
		pitch = 89.0f;
	}
	if (pitch < -89.0f) {
		pitch = -89.0f;
	}

	updateCameraVectors();
	/*
	glm::vec3 direction;
	direction.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
	direction.y = sin(glm::radians(pitch));
	direction.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
	cameraFront = glm::normalize(direction);
	*/
}

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods) {

	if (action == GLFW_PRESS) {
		if (key == GLFW_KEY_LEFT_SHIFT) {
			accelerationAmount = 20.0f;
		}
	}
	else if (action == GLFW_RELEASE) {
		if (key == GLFW_KEY_LEFT_SHIFT) {
			accelerationAmount = 5.0f;
		}
	}
}

void processInput(GLFWwindow* window) {
	
	glm::vec3 inputAcceleration(0.0f, 0.0f, 0.0f);

	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
		inputAcceleration += accelerationAmount * cameraFront;
	}
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
		inputAcceleration += -accelerationAmount * cameraFront;
	}
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
		inputAcceleration += -accelerationAmount * cameraRight;
	}
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
		inputAcceleration += accelerationAmount * cameraRight;
	}
	if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS) {
		inputAcceleration += accelerationAmount * cameraUp;
	}
	if (glfwGetKey(window, GLFW_KEY_LEFT_CONTROL) == GLFW_PRESS) {
		inputAcceleration += -accelerationAmount * cameraUp;
	}

	cameraAcceleration = inputAcceleration;
}


//Procedura inicjująca
void initOpenGLProgram(GLFWwindow* window) {
	initShaders();
	//************Tutaj umieszczaj kod, który należy wykonać raz, na początku programu************
	glClearColor(0, 0, 0, 1);//Ustaw czarny kolor czyszczenia ekranu
	glEnable(GL_DEPTH_TEST); //Włącz test głębokości pikseli
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	glfwSetKeyCallback(window, key_callback); //Zarejestruj procedurę obsługi klawiatury
	glfwSetCursorPosCallback(window, mouse_callback);

}


//Zwolnienie zasobów zajętych przez program
void freeOpenGLProgram(GLFWwindow* window) {
	freeShaders();
	//************Tutaj umieszczaj kod, który należy wykonać po zakończeniu pętli głównej************
}


void car2() {
	glm::mat4 Ms = glm::mat4(1.0f);
	float wheelAngle = 0.0f;
	float angle = 0.0f;
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


//Procedura rysująca zawartość sceny
void drawScene(GLFWwindow* window, glm::mat4 V) {
	//************Tutaj umieszczaj kod rysujący obraz******************l
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); //Wyczyszczenie bufora kolorów i bufora głębokości

	glm::mat4 P = glm::perspective(glm::radians(50.0f), 1.0f, 1.0f, 50.0f); //Wyliczenie macierzy rzutowania
	//glm::mat4 V = glm::lookAt(glm::vec3(0.0f, 0.0f, -7.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f)); //Wyliczenie macierzy widoku
	//glm::mat4 V = glm::lookAt(cameraPosition, cameraSum, cameraUp);

	spLambert->use();//Aktywacja programu cieniującego
	glUniformMatrix4fv(spLambert->u("P"), 1, false, glm::value_ptr(P)); //Załadowanie macierzy rzutowania do programu cieniującego
	glUniformMatrix4fv(spLambert->u("V"), 1, false, glm::value_ptr(V)); //Załadowanie macierzy widoku do programu cieniującego


	//planets1(angle);
	//planets2(angle);
	//cogs1(angle);
	//cogs2(angle);
	//cogs3(angle);
	//car1(angle);
	car2();

	//Skopiowanie bufora ukrytego do widocznego. Z reguły ostatnie polecenie w procedurze drawScene.
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

	glfwSetTime(0); //Wyzeruj timer

	//Główna pętla
	while (!glfwWindowShouldClose(window)) //Tak długo jak okno nie powinno zostać zamknięte
	{
		float currentFrame = glfwGetTime();
		float deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;

		processInput(window);

		// Update the camera velocity and position
		cameraVelocity += cameraAcceleration * deltaTime;
		cameraVelocity *= 0.99f; // Apply friction
		cameraPosition += cameraVelocity * deltaTime;




		// Update the view matrix
		glm::mat4 V = glm::lookAt(cameraPosition, cameraPosition + cameraFront, cameraUp);

		// Clear buffers and set the view and projection matrices
		drawScene(window, V);
		glfwPollEvents();
	}

	freeOpenGLProgram(window);

	glfwDestroyWindow(window); //Usuń kontekst OpenGL i okno
	glfwTerminate(); //Zwolnij zasoby zajęte przez GLFW
	exit(EXIT_SUCCESS);
}
