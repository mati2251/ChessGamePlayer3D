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
Models::Sphere sun(0.5, 36, 36);
Models::Sphere planet1(0.2, 36, 36);
Models::Sphere moon1(0.1, 36, 36);
Models::Sphere planet2(0.25, 36, 36);
Models::Sphere moon2(0.07, 36, 36);
Models::Torus carWheel(0.3, 0.1, 36, 36);
Models::Cube mainBody;
Models::Cube leftWing;
Models::Cube rightWing;
//Procedura obsługi błędów
void error_callback(int error, const char* description) {
	fputs(description, stderr);
}

//Procedura obsługi klawiatury
void key_callback(GLFWwindow* window, int key,
	int scancode, int action, int mods) {

	if (action == GLFW_PRESS) {
		if (key == GLFW_KEY_LEFT) speed=-PI; //Jeżeli wciśnięto klawisz "w lewo" ustaw prędkość na -PI
		if (key == GLFW_KEY_RIGHT) speed = PI; //Jeżeli wciśnięto klawisz "w prawo" ustaw prędkość na PI
		if (key == GLFW_KEY_A) {
			skret = PI / 6;
		}
		if (key == GLFW_KEY_D) {
			skret = -PI / 6;
		}
	}

	if (action == GLFW_RELEASE) {
		if (key == GLFW_KEY_LEFT || key == GLFW_KEY_RIGHT) speed = 0;
		if (key == GLFW_KEY_A || key == GLFW_KEY_D) skret = 0;
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

void planets1(float angle) {
	glm::mat4 Ms = glm::mat4(1.0f); //Macierz słońca to macierz jednostkowa
	glUniformMatrix4fv(spLambert->u("M"), 1, false, glm::value_ptr(Ms));  //Załadowanie macierzy modelu do programu cieniującego
	glUniform4f(spLambert->u("color"), 1, 1, 0, 1); //Słońce ma kolor żółty
	sun.drawSolid(); //Narysowanie obiektu


	glm::mat4 Mp1 = glm::rotate(Ms, angle, glm::vec3(0.0f, 1.0f, 0.0f)); //Macierz planety to macierz słońca pomnożona razy macierz obrotu
	Mp1 = glm::translate(Mp1, glm::vec3(1.5f, 0.0f, 0.0f)); //...i macierz przesunięcia
	glUniformMatrix4fv(spLambert->u("M"), 1, false, glm::value_ptr(Mp1));  //Załadowanie macierzy modelu do programu cieniującego
	glUniform4f(spLambert->u("color"), 0, 1, 0, 1); //Planeta jest zielona
	planet1.drawSolid(); //Narysowanie obiektu

	glm::mat4 Mk1 = glm::rotate(Mp1, angle, glm::vec3(0.0f, 1.0f, 0.0f)); //Macierz księżyca to macierz planety pomnożona razy macierz obrotu
	Mk1 = glm::translate(Mk1, glm::vec3(0.5f, 0.0f, 0.0f));//...i macierz przesunięcia
	glUniformMatrix4fv(spLambert->u("M"), 1, false, glm::value_ptr(Mk1));  //Załadowanie macierzy modelu do programu cieniującego
	glUniform4f(spLambert->u("color"), 0.5, 0.5, 0.5, 1); //Księżyc jest szary
	moon1.drawSolid(); //Narysowanie obiektu
}

void planets2(float angle) {
	glm::mat4 Ms = glm::mat4(1.0f); //Macierz słońca to macierz jednostkowa
	glUniformMatrix4fv(spLambert->u("M"), 1, false, glm::value_ptr(Ms));  //Załadowanie macierzy modelu do programu cieniującego
	glUniform4f(spLambert->u("color"), 1, 1, 0, 1); //Słońce ma kolor żółty
	sun.drawSolid(); //Narysowanie obiektu


	glm::mat4 Mp1 = glm::rotate(Ms, angle, glm::vec3(0.0f, 1.0f, 0.0f)); //Macierz planety to macierz słońca pomnożona razy macierz obrotu
	Mp1 = glm::translate(Mp1, glm::vec3(1.5f, 0.0f, 0.0f)); //...i macierz przesunięcia
	glUniformMatrix4fv(spLambert->u("M"), 1, false, glm::value_ptr(Mp1));  //Załadowanie macierzy modelu do programu cieniującego
	glUniform4f(spLambert->u("color"), 0, 1, 0, 1); //Planeta jest zielona
	planet1.drawSolid(); //Narysowanie obiektu

	glm::mat4 Mk1 = glm::rotate(Mp1, angle, glm::vec3(0.0f, 1.0f, 0.0f)); //Macierz księżyca to macierz planety pomnożona razy macierz obrotu
	Mk1 = glm::translate(Mk1, glm::vec3(0.5f, 0.0f, 0.0f));//...i macierz przesunięcia
	glUniformMatrix4fv(spLambert->u("M"), 1, false, glm::value_ptr(Mk1));  //Załadowanie macierzy modelu do programu cieniującego
	glUniform4f(spLambert->u("color"), 0.5, 0.5, 0.5, 1); //Księżyc jest szary
	moon1.drawSolid(); //Narysowanie obiektu

	glm::mat4 Mp2 = glm::rotate(Ms, angle, glm::vec3(0.0f, 0.0f, 1.0f));  //Macierz planety to macierz słońca pomnożona razy macierz obrotu
	Mp2 = glm::translate(Mp2, glm::vec3(2.0f, 0.0f, 0.0f)); //...i macierz przesunięcia
	glUniformMatrix4fv(spLambert->u("M"), 1, false, glm::value_ptr(Mp2));  //Załadowanie macierzy modelu do programu cieniującego
	glUniform4f(spLambert->u("color"), 0, 0, 1, 1); //Planeta jest niebieska
	planet2.drawSolid();
	
	glm::mat4 Mk2 = glm::rotate(Mp2, angle, glm::vec3(1.0f, 0.0f, 0.0f)); //Macierz księżyca to macierz planety pomnożona razy macierz obrotu
	Mk2 = glm::translate(Mk2, glm::vec3(0.0f, 0.3f, 0.0f));//...i macierz przesunięcia
	glUniformMatrix4fv(spLambert->u("M"), 1, false, glm::value_ptr(Mk2));  //Załadowanie macierzy modelu do programu cieniującego
	glUniform4f(spLambert->u("color"), 0.2, 0.2, 0.2, 1); //Księżyc jest szary
	moon2.drawSolid(); //Narysowanie obiektu
}

void cogs1(float angle) {
	glm::mat4 I = glm::mat4(1.0f);

	glm::mat4 Mt1 = glm::translate(I, glm::vec3(-1.0f, 0.0f, 0.0f)); //Macierz torusa to najpierw przesunięcie do odpowiedniej pozycji...
	Mt1 = glm::rotate(Mt1, angle, glm::vec3(0.0f, 0.0f, 1.0f)); //... potem obrót żeby nasz "tryb" był odpowiednio obrócony
	glUniformMatrix4fv(spLambert->u("M"), 1, false, glm::value_ptr(Mt1));  
	glUniform4f(spLambert->u("color"), 0, 1, 0, 1); 
	Models::torus.drawSolid();

	glm::mat4 Mt2 = glm::translate(I, glm::vec3(1.0f, 0.0f, 0.0f)); //Macierz torusa to najpierw przesunięcie do odpowiedniej pozycji...
	Mt2 = glm::rotate(Mt2, -angle, glm::vec3(0.0f, 0.0f, 1.0f)); //... potem obrót żeby nasz "tryb" był odpowiednio obrócony
	glUniformMatrix4fv(spLambert->u("M"), 1, false, glm::value_ptr(Mt2));
	glUniform4f(spLambert->u("color"), 0, 1, 0, 1); 
	Models::torus.drawSolid();
}

void drawCog(glm::mat4 Mt,float angleDelta) {
	//Załaduj macierz modelu i narysuj torus
	glUniformMatrix4fv(spLambert->u("M"), 1, false, glm::value_ptr(Mt));
	glUniform4f(spLambert->u("color"), 0, 1, 0, 1);
	Models::torus.drawSolid();

	//W pętli narysuj 12 kostek.
	for (int k = 0; k < 12; k++) {
		//Macierz kostki to obrót, żeby wybrać kierunek wokół torusa...
		glm::mat4 Mk = glm::rotate(Mt, glm::radians(k * 30.0f+angleDelta), glm::vec3(0.0f, 0.0f, 1.0f));
		//...przesunięcie żeby dotrzeć na obrzeże torusa...
		Mk = glm::translate(Mk, glm::vec3(1.0f, 0.0f, 0.0f));
		//...i skalowanie żeby pomniejszyć kostkę do porządanych rozmiarów
		Mk = glm::scale(Mk, glm::vec3(0.1f, 0.1f, 0.1f));
		glUniformMatrix4fv(spLambert->u("M"), 1, false, glm::value_ptr(Mk));
		glUniform4f(spLambert->u("color"), 0, 1, 0, 1);
		Models::cube.drawSolid();
	}
}

void cogs2(float angle) {
	glm::mat4 I = glm::mat4(1.0f);

	glm::mat4 Mt1 = glm::translate(I, glm::vec3(-1.05f, 0.0f, 0.0f)); //Macierz torusa to najpierw przesunięcie do odpowiedniej pozycji...
	Mt1 = glm::rotate(Mt1, angle, glm::vec3(0.0f, 0.0f, 1.0f)); //... potem obrót żeby nasz "tryb" był odpowiednio obrócony
	drawCog(Mt1, 0);

	glm::mat4 Mt2 = glm::translate(I, glm::vec3(1.05f, 0.0f, 0.0f)); //Macierz torusa to najpierw przesunięcie do odpowiedniej pozycji...
	Mt2 = glm::rotate(Mt2, -angle, glm::vec3(0.0f, 0.0f, 1.0f)); //... potem obrót żeby nasz "tryb" był odpowiednio obrócony
	drawCog(Mt2, 11);
}

void cogs3(float angle) {
	//---Poniższy kawałek kodu powtarzamy dla każdego obiektu
	//Obliczanie macierzy modelu
	glm::mat4 M = glm::mat4(1.0f);	

	for (int k = 0; k < 6; k++) {
		glm::mat4 Ml = glm::rotate(M, glm::radians(k * 60.0f), glm::vec3(0.0f, 0.0f, 1.0f));
		Ml = glm::translate(Ml, glm::vec3(2.1f, 0.0f, 0.0f));
		Ml = glm::rotate(Ml, angle * (k % 2 == 0 ? 1 : -1), glm::vec3(0.0f, 0.0f, 1.0f));
		drawCog(Ml, k * 15.0f );
	}

}

void car1(float angle) {
	glm::mat4 Ms = glm::mat4(1.0f);
	Ms = glm::rotate(Ms, angle, glm::vec3(0.0f, 1.0f, 0.0f));

	//Podwozie
	glm::mat4 Mp = glm::scale(Ms, glm::vec3(1.5f, 0.125f, 1.0f));
	glUniform4f(spLambert->u("color"), 0, 1, 0, 1);
	glUniformMatrix4fv(spLambert->u("M"), 1, false, glm::value_ptr(Mp));  //Załadowanie macierzy modelu do programu cieniującego
	Models::cube.drawSolid(); //Narysowanie obiektu


	//Koło1
	glm::mat4 Mk1 = Ms;
	Mk1 = glm::translate(Mk1, glm::vec3(1.5f, 0.0f, 1.0f));
	glUniformMatrix4fv(spLambert->u("M"), 1, false, glm::value_ptr(Mk1));  //Załadowanie macierzy modelu do programu cieniującego	
	carWheel.drawWire();

	//Koło2
	glm::mat4 Mk2 = Ms;
	Mk2 = glm::translate(Mk2, glm::vec3(1.5f, 0.0f, -1.0f));	
	glUniformMatrix4fv(spLambert->u("M"), 1, false, glm::value_ptr(Mk2));  //Załadowanie macierzy modelu do programu cieniującego
	carWheel.drawWire();

	//Koło3
	glm::mat4 Mk3 = Ms;
	Mk3 = glm::translate(Mk3, glm::vec3(-1.5f, 0.0f, 1.0f));	
	glUniformMatrix4fv(spLambert->u("M"), 1, false, glm::value_ptr(Mk3));  //Załadowanie macierzy modelu do programu cieniującego
	carWheel.drawWire();

	//Koło4
	glm::mat4 Mk4 = Ms;
	Mk4 = glm::translate(Mk4, glm::vec3(-1.5f, 0.0f, -1.0f));	
	glUniformMatrix4fv(spLambert->u("M"), 1, false, glm::value_ptr(Mk4));  //Załadowanie macierzy modelu do programu cieniującego
	carWheel.drawWire();


}

void car2(float angle,float wheelAngle) {	
	glm::mat4 Ms = glm::mat4(1.0f);
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
void drawScene(GLFWwindow* window,float angle,float wheelAngle) {
	//************Tutaj umieszczaj kod rysujący obraz******************l
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); //Wyczyszczenie bufora kolorów i bufora głębokości
	
	glm::mat4 P = glm::perspective(glm::radians(50.0f), 1.0f, 1.0f, 50.0f); //Wyliczenie macierzy rzutowania
	glm::mat4 V = glm::lookAt(glm::vec3(0.0f, 0.0f, -7.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f)); //Wyliczenie macierzy widoku

	spLambert->use();//Aktywacja programu cieniującego
	glUniformMatrix4fv(spLambert->u("P"), 1, false, glm::value_ptr(P)); //Załadowanie macierzy rzutowania do programu cieniującego
	glUniformMatrix4fv(spLambert->u("V"), 1, false, glm::value_ptr(V)); //Załadowanie macierzy widoku do programu cieniującego
	
	

	drawSpaceship();

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
	float wheelAngle = 0; //Aktualny kąt obrotu kół
	glfwSetTime(0); //Wyzeruj timer
	//Główna pętla
	while (!glfwWindowShouldClose(window)) //Tak długo jak okno nie powinno zostać zamknięte
	{
		angle += speed * glfwGetTime(); //Oblicz przyrost kąta po obrocie
		wheelAngle += -PI / 6 * glfwGetTime();
		glfwSetTime(0); //Wyzeruj timer
		drawScene(window,angle,wheelAngle); //Wykonaj procedurę rysującą
		glfwPollEvents(); //Wykonaj procedury callback w zalezności od zdarzeń jakie zaszły.
	}

	freeOpenGLProgram(window);

	glfwDestroyWindow(window); //Usuń kontekst OpenGL i okno
	glfwTerminate(); //Zwolnij zasoby zajęte przez GLFW
	exit(EXIT_SUCCESS);
}
