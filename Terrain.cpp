#include <iostream>

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


int length;
int width;

Terrain::Terrain(){
}

void Terrain::CreateTerrain(int x, int z){
    this->length = x;
    this->width = z;
    srand(time(NULL));
}

void Terrain::DrawTerrain(){
    glColor3f(1,1,1);

    glBegin(GL_POINTS);
    for (int i = 0; i < this->length; i++) {
        for (int j = 0; j < this->width; j++) {
            glVertex3f(i,0,j);
        }
    }
    glEnd();

    
    int vertexChange[4][2] = {{0,0},{0,1},{1,1},{1,0}};
    for (int i = 0; i < this->length; i++) {
        for (int j = 0; j < this->width; j++) {
            glBegin(GL_QUADS);
            for (int v = 0; v < 4; v++) {
                int x = i + vertexChange[v][0];
                int z = j + vertexChange[v][1];
                
                glVertex3f(x, 0, z);
            }
            glEnd();
        }
    }
    
}
