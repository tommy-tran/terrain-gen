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
#define W 3

//Globals
float camPos[] = {50, -40, -20};	//where the camera is
float camTarget[] = { 50, 0, 30};

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
			camPos[X] -= 0.1f;
			camTarget[X] -=0.1f;
			break;

		case 's':
			if ( mod == GLUT_ACTIVE_ALT) {
				camPos[Y] += 0.1f;
				camTarget[Y] +=0.1f;	
			} else {
				camPos[Z] -= 0.1f;
				camTarget[Z] -=0.1f;
			}
			break;

		case 'd':
			camPos[X] += 0.1f;
			camTarget[X] += 0.1f;
			break;
		case 'w':
			if ( mod == GLUT_ACTIVE_ALT) {
				camPos[Y] -= 0.1f;
				camTarget[Y] -=0.1f;	
			} else {
				camPos[Z] += 0.1f;
				camTarget[Z] +=0.1f;
			}
			break;
		
	}
}

void special(int key, int xIn, int yIn){
	switch (key){
		case GLUT_KEY_DOWN:
			camTarget[Z] -= 0.2f;
			break;
		case GLUT_KEY_UP:
			camTarget[Z] += 0.2f;
			break;
		case GLUT_KEY_LEFT:
			camTarget[X] -= 0.2f;
			break;
		case GLUT_KEY_RIGHT:
			camTarget[X] += 0.2f;
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
	glColor3f(1, 1, 1);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(45, 1, 1, 100);

	terrain = new Terrain();
	terrain->CreateTerrain(100, 100);
}

void display(void)
{

	glClear(GL_COLOR_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	gluLookAt(camPos[0], camPos[1], camPos[2], camTarget[0], camTarget[1], camTarget[2], 0,0,1);
	
	// scale the entire solar system
	// glScalef(SceneScale, SceneScale, SceneScale);

	glPushMatrix();
		terrain->DrawTerrain();
	glPopMatrix();

	glutSwapBuffers();
}

void reshape(int w, int h)
{
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	//gluOrtho2D(0, w, 0, h);
	gluPerspective(45, (float)((w+0.0f)/h), 1, 100);

	glMatrixMode(GL_MODELVIEW);
	glViewport(0, 0, w, h);
}

void FPSTimer(int value){ //60fps
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

	init();

	// createOurMenu();


	glutMainLoop();				//starts the event glutMainLoop
	return(0);					//return may not be necessary on all compilers
}
