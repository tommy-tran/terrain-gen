#include <stdio.h>
#include <stdlib.h>

#ifdef __APPLE__
#  include <OpenGL/gl.h>
#  include <OpenGL/glu.h>
#  include <GLUT/glut.h>
#else
#  include <GL/gl.h>
#  include <GL/glu.h>
#  include <GL/freeglut.h>
#endif


#include "Terrain.h"
Terrain *terrain;

#define X 0
#define Y 1
#define Z 2

//Globals
float camPos[] = {0, -60, 0};	//where the camera is
float camTarget[] = {50, 0, 50};
float yRotate = 0;
float xRotate = 0;
float zRotate = 0;
int mode = 0;
int shape = 0;

//OpenGL functions
//keyboard stuff
void keyboard(unsigned char key, int xIn, int yIn)
{
	int mod = glutGetModifiers();
	
	switch (key)
	{
		case 'q':
		case 27:	//27 is the esc key
			exit(0);
			break;

		case 'x':
			if ( mod == GLUT_ACTIVE_ALT)
				printf("x ALT\n");
			else
				printf("x\n");

		case 'a':
			camPos[X] -= 0.5f;
			camTarget[X] -=0.5f;
			break;

		case 's':
			if ( mod == GLUT_ACTIVE_ALT) {
				camPos[Y] += 0.5f;
				camTarget[Y] +=0.5f;	
			} else {
				camPos[Z] -= 0.5f;
				camTarget[Z] -=0.5f;
			}
			break;

		case 'd':
			camPos[X] += 0.5f;
			camTarget[X] += 0.5f;
			break;
		case 'w':
			mode = (mode + 1) % 3;
			break;

		case 't':
			shape = (shape + 1) % 2;
			break;
		case 'r':
			terrain->reset();
			break;
		// case 'w':
		// 	if ( mod == GLUT_ACTIVE_ALT) {
		// 		camPos[Y] -= 0.5f;
		// 		camTarget[Y] -=0.5f;	
		// 	} else {
		// 		camPos[Z] += 0.5f;
		// 		camTarget[Z] +=0.5f;
		// 	}
		// 	break;
	}
}



void special(int key, int xIn, int yIn){
	switch (key){
		case GLUT_KEY_DOWN:
			// camPos[Z] -= 0.5f;
			xRotate -= 0.5f;
			break;
		case GLUT_KEY_UP:
			// camPos[Z] += 0.5f;
			xRotate += 0.5f;
			break;
		case GLUT_KEY_LEFT:
			// camPos[X] -= 0.5f;
			yRotate -= 0.5f;
			break;
		case GLUT_KEY_RIGHT:
			// camPos[X] += 0.5f;
			yRotate += 0.5f;
			break;
	}
}
//mouse
void mouse(int btn, int state, int x, int y){

	if (btn == GLUT_LEFT_BUTTON){

		if (state == GLUT_UP){
		}

		if (state == GLUT_DOWN){
		}
	}
}
void mouseMotion(int x, int y){
}
void mousePassiveMotion(int x, int y){
}


//initialization
void init(void)
{
	glClearColor(0, 0, 0, 0);
	glColor3f(0.5, 0.3, 0.7);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(45, 1, 1, 1000);

	terrain = new Terrain(100,100);
	terrain->CircleAlgorithm();
}

void display(void)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	gluLookAt(camPos[0], camPos[1], camPos[2], camTarget[0], camTarget[1], camTarget[2], 0,-1,0);

	glTranslatef(50,0,50);
	glPushMatrix();
		glRotatef(5 * yRotate, 0, 1, 0);
		glRotatef(5 * xRotate, 0, 0, 1);
		glTranslatef(-50,0,-50);
		
		switch(mode) {
			case 0:
				glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
				terrain->DrawTerrain(shape);
				break;
			case 1:
				glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
				terrain->DrawTerrain(shape);
				break;
			case 2:
				glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
				terrain->DrawTerrain(shape);
				glPushMatrix();
					// glTranslatef(0,-0.1,0);
					glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
					glColor3f(1,1,1);
					terrain->DrawTerrain(shape + mode);
				glPopMatrix();
		}
		
	glPopMatrix();

	glutSwapBuffers();
}

void reshape(int w, int h)
{
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	//gluOrtho2D(0, w, 0, h);
	gluPerspective(45, 1, 1, 2000);

	glMatrixMode(GL_MODELVIEW);
	glViewport(0, 0, w, h);
}

void FPSTimer(int value){ 
	glutTimerFunc(17, FPSTimer, 0);
	glutPostRedisplay();
}

/* main function - program entry point */
int main(int argc, char** argv)
{
	glutInit(&argc, argv);		//starts up GLUT
	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);

	glutInitWindowSize(500, 500);
	glutInitWindowPosition(100, 100);

	glutCreateWindow("Terrain Generator");	//creates the window

	//display callback
	glutDisplayFunc(display);

	//keyboard callback
	glutKeyboardFunc(keyboard);
	glutSpecialFunc(special);

	//mouse callbacks
	glutMouseFunc(mouse);
	glutMotionFunc(mouseMotion);
	glutPassiveMotionFunc(mousePassiveMotion);

	//resize callback
	glutReshapeFunc(reshape);

	//fps timer callback
	glutTimerFunc(17, FPSTimer, 0);

	glEnable(GL_DEPTH_TEST);
	init();

	// createOurMenu();


	glutMainLoop();				//starts the event glutMainLoop
	return(0);					//return may not be necessary on all compilers
}
