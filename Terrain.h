#ifndef __TERRAIN_H__
#define __TERRAIN_H__

#include <vector>
#include <iostream>
#include <math.h>
#include <stdlib.h>
#include <stdio.h>
using namespace std;

#ifdef __APPLE__
#  include <OpenGL/gl.h>
#  include <OpenGL/glu.h>
#  include <GLUT/glut.h>
#else
#  include <GL/gl.h>
#  include <GL/glu.h>
#  include <GL/freeglut.h>
#endif




class Terrain{
public:
    int length;
    int width;
    float max;
    vector<vector<float> > height;
    
    
    Terrain(int x, int z);
    
    void DrawTerrain();
    void CircleAlgorithm();

private:
};

#endif
