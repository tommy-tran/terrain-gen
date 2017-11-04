#include "Terrain.h"

Terrain::Terrain(int x, int z){
    this->length = x;
    this->width = z;
    this->height = vector<vector<float> >(x, vector<float>(z, 1));
    srand(time(NULL));
}

void Terrain::DrawTerrain(){
    
    int vertexChange[4][2] = {{0,0},{0,1},{1,1},{1,0}};
    for (int i = 0; i < this->length - 1; i++) {
        for (int j = 0; j < this->width - 1; j++) {
            glBegin(GL_QUADS);
            for (int v = 0; v < 4; v++) {
                int x = i + vertexChange[v][0];
                int z = j + vertexChange[v][1];
                float _height = fabs(this->height[x][z] / this->max);
                glColor3f(_height,_height,_height);
                glVertex3f(x, this->height[x][z], z);
            }
            glEnd();
        }
    }
}

void Terrain::CircleAlgorithm() {
    // Random center point of circle
    int iterations = 150;
    while (iterations > 0) {
        int x = rand() % this->length; 
        int z = rand() % this->width;
    
        float disp = this->length / 20;
        int radius = this->length / (rand() % 4 + 4);
    
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
