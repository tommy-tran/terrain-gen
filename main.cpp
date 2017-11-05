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
float camPos[3];
float camTarget[3];
float yRotate = 0;
float xRotate = 0;
float zRotate = 0;
int mode = 0;
int shape = 0;
int size;
int mapDisplay;

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
		case 'w':
			mode = (mode + 1) % 3;
			break;
		case 't':
			shape = (shape + 1) % 2;
			if (shape == 0) {
				glCullFace(GL_FRONT);
			} else {
				glCullFace(GL_BACK);
			}
			break;
		case 'r':
			terrain->reset();
			glutPostWindowRedisplay(mapDisplay);
			break;
		case 'o':
			camPos[Y] -= 1.5f;
			camTarget[Y] -=1.5f;
			break;
		case 'j':
			camPos[X] -= 1.5f;
			camTarget[X] -= 1.5f;
			break;
		case 'u':
			camPos[Y] += 1.5f;
			camTarget[Y] +=1.5f;
			break;
		case 'l':
			camPos[X] += 1.5f;
			camTarget[X] +=1.5f;
			break;
		case 'i':
			camPos[Z] += 1.5f;
			camTarget[Z] +=1.5f;
			break;
		case 'k':
			camPos[Z] -= 1.5f;
			camTarget[Z] -=1.5f;
			break;
	}
}



void special(int key, int xIn, int yIn){
	switch (key){
		case GLUT_KEY_DOWN:
			if (xRotate > -8) {
				xRotate -= 0.5f;
			}
			break;
		case GLUT_KEY_UP:
			if (xRotate < 8) {
				xRotate += 0.5f;
			}
			break;
		case GLUT_KEY_LEFT:
			yRotate -= 0.5f;
			glutPostWindowRedisplay(mapDisplay);
			glutPostRedisplay();
			break;
		case GLUT_KEY_RIGHT:
			yRotate += 0.5f;
			glutPostWindowRedisplay(mapDisplay);
			glutPostRedisplay();
			break;
	}
}

void init(void)
{
	glClearColor(0, 0, 0, 0);
	glColor3f(0.5, 0.3, 0.7);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(45, 1, 1, 1000);

	cout << "******************\n\nTerrain Generator\n\n******************\n";
	cout << "Controls:\nq: Quit				w: Toggle wireframe mode\nr: Randomize Terrain		t: Switch between Quads and Triangles\ni: Move camera forward		k: Move camera backwards\nj: Move Camera left		l: Move Camera right\nu: Move Camera down		o: Move Camera up\n";
	cout << "Please input a size for the terrain(50-300): \n";
	cin >> size;

	camTarget[0] = size/2;
	camTarget[1] = 0;
	camTarget[2] = size/2;

	camPos[0] = size/2;
	camPos[1] = -size * 0.85;
	camPos[2] = -size/2;

	terrain = new Terrain(size,size);
	terrain->CircleAlgorithm();
}

void display(void)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	gluLookAt(camPos[0], camPos[1], camPos[2], camTarget[0], camTarget[1], camTarget[2], 0,-1,0);

	glTranslatef(size/2,0,size/2);
	glPushMatrix();
		glRotatef(5 * yRotate, 0, 1, 0);
		glRotatef(5 * xRotate, 0, 0, 1);
		glTranslatef(-size/2,0,-size/2);
		
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
					glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
					glColor3f(0,0,0);
					terrain->DrawTerrain(shape + mode);
				glPopMatrix();
		}
		
	glPopMatrix();

	glutSwapBuffers();
}

void displayMap(void)
{
	glMatrixMode(GL_MODELVIEW);
	glClearColor(0,0,0,0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();

	glRotatef(5 * yRotate, 0, 0, -1);
	glScalef(2,2,1);
	
	glTranslatef(-0.5, -0.5, 0);
	terrain->DrawMap();

	glutSwapBuffers();
}

void reshape(int w, int h)
{
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(45, 1, 1, 1000);

	glMatrixMode(GL_MODELVIEW);
	glViewport(0, 0, w, h);
}

void reshape2(int w, int h)
{
	glViewport(0,0,w,h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
}

void FPSTimer(int value){ 
	glutTimerFunc(30, FPSTimer, 0);
	glutPostRedisplay();
}

/* main function - program entry point */
int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	init();
	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);
	glutInitWindowSize(720, 480);
	glutInitWindowPosition(50, 50);
	glutCreateWindow("Terrain Generator");
	glutDisplayFunc(display);
	glutKeyboardFunc(keyboard);
	glutSpecialFunc(special);
	glutReshapeFunc(reshape);
	glutTimerFunc(120, FPSTimer, 0);
	glEnable(GL_DEPTH_TEST);

	glCullFace(GL_FRONT);
	glFrontFace(GL_CCW);
	glEnable(GL_CULL_FACE);

	mapDisplay = glutCreateWindow("Map");
	glutPositionWindow(800,50);
	glutReshapeWindow(size * 1.2, size * 1.2);
	glutReshapeFunc(reshape2);
	glutDisplayFunc(displayMap);
	glutSpecialFunc(special);

	glutMainLoop();				//starts the event glutMainLoop
	return(0);					//return may not be necessary on all compilers
}
