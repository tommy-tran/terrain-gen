#include "Terrain.h"

Terrain::Terrain(int x, int z){
    this->length = x;
    this->width = z;
    this->height = vector<vector<float> >(x, vector<float>(z, 0));
    srand(time(NULL));
}

void Terrain::DrawTerrain(int type){
    int quadChange[4][2] = {{0,0},{0,1},{1,1},{1,0}};
    int triangle1[3][2] = {{0,0},{1,0},{1,1}};
    int triangle2[3][2] = {{0,0},{1,1},{0,1}};
    
    switch(type) {
        case 0:
            for (int i = 0; i < this->length - 1; i++) {
                for (int j = 0; j < this->width - 1; j++) {
                    glBegin(GL_QUADS);
                    for (int v = 0; v < 4; v++) {
                        int x = j + quadChange[v][0];
                        int z = i + quadChange[v][1];
                        float _height = fabs(this->height[x][z] / this->max);
                        glColor3f(_height,_height,_height);
                        glVertex3f(x, this->height[x][z], z);
                    }
                    glEnd();
                }
            }
        break;
        case 1:
            for (int i = 0; i < this->length - 1; i++) {
                for (int j = 0; j < this->width - 1; j++) {
                    glBegin(GL_TRIANGLES);
                    for (int v = 0; v < 3; v++) {
                        int x = i + triangle1[v][0];
                        int z = j + triangle1[v][1];
                        float _height = fabs(this->height[x][z] / this->max);
                        glColor3f(_height,_height,_height);
                        glVertex3f(x, this->height[x][z], z);
                    }
                    glEnd();

                    glBegin(GL_TRIANGLES);
                    for (int v = 0; v < 3; v++) {
                        int x = i + triangle2[v][0];
                        int z = j + triangle2[v][1];
                        float _height = fabs(this->height[x][z] / this->max);
                        glColor3f(_height,_height,_height);
                        glVertex3f(x, this->height[x][z], z);
                    }
                    glEnd();
                }
            }
            break;

        case 2:
            for (int i = 0; i < this->length - 1; i++) {
                for (int j = 0; j < this->width - 1; j++) {
                    glBegin(GL_QUADS);
                    for (int v = 0; v < 4; v++) {
                        int x = j + quadChange[v][0];
                        int z = i + quadChange[v][1];
                        float _height = fabs(this->height[x][z] / this->max);
                        glVertex3f(x, this->height[x][z], z);
                    }
                    glEnd();
                }
            }
            break;
            
        case 3:
        float _height;
        int x;
        int z;
        for (int i = 0; i < this->length - 1; i++) {
            for (int j = 0; j < this->width - 1; j++) {
                glBegin(GL_TRIANGLES);
                for (int v = 0; v < 3; v++) {
                    x = i + triangle1[v][0];
                    z = j + triangle1[v][1];
                    _height = fabs(this->height[x][z] / this->max);
                    glVertex3f(x, this->height[x][z], z);
                }
                glEnd();
                glBegin(GL_TRIANGLES);
                for (int v = 0; v < 3; v++) {
                    int x = i + triangle2[v][0];
                    int z = j + triangle2[v][1];
                    _height = fabs(this->height[x][z] / this->max);
                    glVertex3f(x, this->height[x][z], z);
                }
                glEnd();
            }
        }

    break;
    
    }
    
    
}

void Terrain::reset() {
    srand(time(NULL));
    this->height = vector<vector<float> >(this->length, vector<float>(this->width, 0));
	CircleAlgorithm();
}

void Terrain::CircleAlgorithm() {
    int iterations = 300;
    float disp;
    int radius;
    int x;
    int z;

    while (iterations > 0) {
        x = rand() % this->length; 
        z = rand() % this->width;
    
        disp = this->length / 20;
        radius = this->length / (rand() % 4 + 4);
    
        for (int i = 0; i < this->length; i++) {
            for (int j = 0; j < this->width; j++) {
                int dx = i - x;
                int dz = j - z;
    
                float distance = sqrtf((dx*dx) + (dz*dz));
                float pd = (distance * 2) / radius;
    
                if (fabs(pd) <= 1.0) {
                    float change = disp/2 + cos(pd*3.14)*(disp/2);
                    this->height[i][j] -= change;

                    if (this->max < fabs(height[i][j])) {
                        this->max = fabs(height[i][j]);
                    }
                }
            }
        }
        iterations--;
    }
}

void Terrain::DrawMap() {
    float _height;
    float max = this->length;
    glBegin(GL_POINTS);
        for (int i = 0; i < this->length; i++) {
            for (int j = 0; j < this->width; j++) {
                _height = fabs(this->height[i][j] / this->max);
                glColor3f(_height, _height, _height);
                glVertex2f(i/max,j/max);
            }
        }
    glEnd();
}
