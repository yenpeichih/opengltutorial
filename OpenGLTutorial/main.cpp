#include <iostream>
#include <GL/glut.h>
#include <GL/glu.h>
#include <GL/gl.h>
#include <time.h>
 
using namespace std;

void displayCallback();

void reshape(int, int);

void timer(int);

float x_pos = -9.0;
float y_pos = 7.0;
float r = 1.0;
float g = 1.0;
float b = 1.0;
bool go_right = true;
bool go_down = true;
bool colour_change = false;
float z_pos = -15.0;
bool go_big = true;

void init() {
	glClearColor(0.0, 0.0, 0.0, 1.0); //colour of the backgroud
}

int main(int argc, char** argv) {

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE); //double buffer -> front buffer being displayed, back buffer used to draw next frame, then swap

	glutInitWindowPosition(100, 100);
	glutInitWindowSize(600, 600);
	glutCreateWindow("Hellow Happy World!");
	
	glutDisplayFunc(displayCallback);
	glutReshapeFunc(reshape);
	glutTimerFunc(0, timer, 0); //calls a certain function after a specified amount of time (1 sec)
	init();


	glutMainLoop();
}

//each call to this display function is a single frame when animating
void displayCallback() {

	srand(time(NULL));

	if (colour_change) {
		r = (float)rand() / RAND_MAX;
		g = (float)rand() / RAND_MAX;
		b = (float)rand() / RAND_MAX;
		colour_change = false;
	}

	glClear(GL_COLOR_BUFFER_BIT); //clear buffer to default colour
	glLoadIdentity(); //resets current matrix, i.e. resets all changes and transformations etc that has been made

	glTranslatef(x_pos, y_pos, 0.0); //translate the origin, useful for multiples of same preset model w/o altering its drawing geometry

	//draw primitive stuff by specify vertices
	glBegin(GL_POLYGON); //tells OpenGL to begin drawing what

	glColor3f(r, g, b); //colour of the primitive drawn
	glVertex3f(-1.0, 1.0, 0.0);
	glVertex3f(-1.0, -1.0, 0.0);
	glVertex3f(1.0, -1.0, 0.0);
	glVertex3f(1.0, 1.0, 0.0);

	glEnd(); //must end to start the drawing

	//glFlush(); //displays drawn stuff on buffer
	glutSwapBuffers(); //all the above drawing instructions will be carried out on the back buffer, then here swaps it to front

}

//called whenever window is reshaped
void reshape(int width, int height) {

	glViewport(0, 0, width, height); //specify viewport
	glMatrixMode(GL_PROJECTION); //switch to projection matrix, only switch when projection change needed
	glLoadIdentity();

	//gluPerspective(60, 1, 2.0, 50.0);
	gluOrtho2D(-10, 10, -10, 10);
	glMatrixMode(GL_MODELVIEW); //should always be in modelview matrix
}


void timer(int) {

	glutPostRedisplay(); //calls the display function next time when get the chance, i.e. here it's called 60 times in 1 sec
	glutTimerFunc(1000 / 60, timer, 0);

	if (go_right) {
		if (x_pos < 9) {
			x_pos += 0.09;
		} else {
			go_right = false;
			colour_change = true;
		}
	} else {
		if (x_pos > -9) {
			x_pos -= 0.09;
		} else {
			go_right = true;
			colour_change = true;
		}
	}

	if (go_down) {
		if (y_pos > -9) {
			y_pos -= 0.06;
		} else {
			go_down = false;
			colour_change = true;
		}
	} else {
		if (y_pos < 9) {
			y_pos += 0.06;
		} else {
			go_down = true;
			colour_change = true;
		}
	}

	/*if (go_big) {
		if (z_pos < -5.0) {
			z_pos += 0.15;
		} else {
			go_big = false;
			colour_change = true;
		}
	} else {
		if (z_pos > -15.0) {
			z_pos -= 0.15;
		} else {
			go_big = true;
		}
	}*/
}