#include "Terrain.h"

Terrain::Terrain(int x, int z){
    this->length = x;
    this->width = z;
    this->height = vector<vector<float> >(x, vector<float>(z, 0));
    srand(time(NULL));
}

void Terrain::DrawTerrain(int type, int wire, bool groovy){
    int quadChange[4][2] = {{0,0},{0,1},{1,1},{1,0}};
    int triangle1[3][2] = {{0,0},{1,0},{1,1}};
    int triangle2[3][2] = {{0,0},{1,1},{0,1}};

    float _height;
    int x;
    int z;
    float r;
    float g;
    float b;

    switch(type) {
        case 0:
            for (int i = 0; i < this->length - 1; i++) {
                for (int j = 0; j < this->width - 1; j++) {
                    glBegin(GL_QUADS);
                    for (int v = 0; v < 4; v++) {
                        x = j + quadChange[v][0];
                        z = i + quadChange[v][1];
                        _height = fabs(this->height[x][z] / this->max);
                        if ((wire == 0) || (wire == 1)) {
                            if (_height < 0.2) {
                                glColor3f(_height, 0.4, 0);
                            } else if (_height < 0.8) {
                                glColor3f(0.2 + 0.8 * ((_height - 0.2) / 0.6), 0.4 , 0);
                            } else {
                                glColor3f(1, 0.4 + 0.6 * ((_height - 0.8)/0.2), (_height - 0.8)/0.2); 
                            }
                        } else {
                            if (_height < 0.1) {
                                glColor3f(0, 0, _height);
                            } else if (_height < 0.7) {
                                r = 0.2 * ((_height - 0.2) / 0.5);
                                g = 0.3 * ((_height - 0.2) / 0.5);
                                b = 0.1 + 0.3 * (_height - 0.2)/0.5;
                                glColor3f(r,g,b);
                            } else {
                                r = 0.2 + 0.8 * ((_height - 0.7) / 0.3);
                                g = 0.3 + 0.7 * ((_height - 0.7) / 0.3);
                                b = 0.4 + 0.6 * ((_height - 0.7) / 0.3);
                                glColor3f(r,g,b);
                            }
                        }
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
                        x = i + triangle1[v][0];
                        z = j + triangle1[v][1];
                        _height = fabs(this->height[x][z] / this->max);
                        if ((wire == 0) || (wire == 1)) {
                            if (_height < 0.2) {
                                glColor3f(_height, 0.4, 0);
                            } else if (_height < 0.8) {
                                glColor3f(0.2 + 0.8 * ((_height - 0.2) / 0.6), 0.4 , 0);
                            } else {
                                glColor3f(1, 0.4 + 0.6 * ((_height - 0.8)/0.2), (_height - 0.8)/0.2); 
                            }
                        } else {
                            if (_height < 0.1) {
                                glColor3f(0, 0, _height);
                            } else if (_height < 0.7) {
                                r = 0.2 * ((_height - 0.2) / 0.5);
                                g = 0.3 * ((_height - 0.2) / 0.5);
                                b = 0.1 + 0.3 * (_height - 0.2)/0.5;
                                glColor3f(r,g,b);
                            } else {
                                r = 0.2 + 0.8 * ((_height - 0.7) / 0.3);
                                g = 0.3 + 0.7 * ((_height - 0.7) / 0.3);
                                b = 0.4 + 0.6 * ((_height - 0.7) / 0.3);
                                glColor3f(r,g,b);
                            }
                        }
                        glVertex3f(x, this->height[x][z], z);
                    }
                    glEnd();

                    glBegin(GL_TRIANGLES);
                    for (int v = 0; v < 3; v++) {
                        x = i + triangle2[v][0];
                        z = j + triangle2[v][1];
                        _height = fabs(this->height[x][z] / this->max);
                        if ((wire == 0) || (wire == 1)) {
                            if (_height < 0.2) {
                                glColor3f(_height, 0.4, 0);
                            } else if (_height < 0.8) {
                                glColor3f(0.2 + 0.8 * ((_height - 0.2) / 0.6), 0.4 , 0);
                            } else {
                                glColor3f(1, 0.4 + 0.6 * ((_height - 0.8)/0.2), (_height - 0.8)/0.2); 
                            }
                            
                        } else {
                            if (_height < 0.1) {
                                glColor3f(0, 0, _height);
                            } else if (_height < 0.7) {
                                r = 0.2 * ((_height - 0.2) / 0.5);
                                g = 0.3 * ((_height - 0.2) / 0.5);
                                b = 0.1 + 0.3 * (_height - 0.2)/0.5;
                                glColor3f(r,g,b);
                            } else {
                                r = 0.2 + 0.8 * ((_height - 0.7) / 0.3);
                                g = 0.3 + 0.7 * ((_height - 0.7) / 0.3);
                                b = 0.4 + 0.6 * ((_height - 0.7) / 0.3);
                                glColor3f(r,g,b);
                            }
                        }
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
                        x = j + quadChange[v][0];
                        z = i + quadChange[v][1];
                        _height = fabs(this->height[x][z] / this->max);
                        if (groovy) {
                            glColor3f(rand() / (float)RAND_MAX * _height, rand() / (float)RAND_MAX * _height, rand() / (float)RAND_MAX * _height);
                        } else {
                            if (wire == 0) {
                                if (_height < 0.2) {
                                    glColor3f(_height, 0.4, 0);
                                } else if (_height < 0.8) {
                                    glColor3f(0.2 + 0.8 * ((_height - 0.2) / 0.6), 0.4 , 0);
                                } else {
                                    glColor3f(1, 0.4 + 0.6 * ((_height - 0.8)/0.2), (_height - 0.8)/0.2); 
                                }
                            } else if (wire == 1) {
                                glColor3f(0.3, 0.2, 0.1);
                            } else if (wire == 2) {
                                if (_height < 0.1) {
                                    glColor3f(0, 0, _height);
                                } else if (_height < 0.7) {
                                    r = 0.2 * ((_height - 0.2) / 0.5);
                                    g = 0.3 * ((_height - 0.2) / 0.5);
                                    b = 0.1 + 0.3 * (_height - 0.2)/0.5;
                                    glColor3f(r,g,b);
                                } else {
                                    r = 0.2 + 0.8 * ((_height - 0.7) / 0.3);
                                    g = 0.3 + 0.7 * ((_height - 0.7) / 0.3);
                                    b = 0.4 + 0.6 * ((_height - 0.7) / 0.3);
                                    glColor3f(r,g,b);
                                }
                            } else {
                                glColor3f(0.1, 0.3, 0.5);
                            }
                        }
                        glVertex3f(x, this->height[x][z], z);
                    }
                    glEnd();
                }
            }
            break;

        case 3:
        for (int i = 0; i < this->length - 1; i++) {
            for (int j = 0; j < this->width - 1; j++) {
                glBegin(GL_TRIANGLES);
                for (int v = 0; v < 3; v++) {
                    x = i + triangle1[v][0];
                    z = j + triangle1[v][1];
                    _height = fabs(this->height[x][z] / this->max);
                    if (groovy) {
                        glColor3f(rand() / (float)RAND_MAX * _height, rand() / (float)RAND_MAX * _height, rand() / (float)RAND_MAX * _height);
                    } else {
                        if (wire == 0) {
                            if (_height < 0.2) {
                                glColor3f(_height, 0.4, 0);
                            } else if (_height < 0.8) {
                                glColor3f(0.2 + 0.8 * ((_height - 0.2) / 0.6), 0.4 , 0);
                            } else {
                                glColor3f(1, 0.4 + 0.6 * ((_height - 0.8)/0.2), (_height - 0.8)/0.2); 
                            }
                        } else if (wire == 1) {
                            glColor3f(0.3, 0.2, 0.1);
                        } else if (wire == 2) {
                            if (_height < 0.1) {
                                glColor3f(0, 0, _height);
                            } else if (_height < 0.7) {
                                r = 0.2 * ((_height - 0.2) / 0.5);
                                g = 0.3 * ((_height - 0.2) / 0.5);
                                b = 0.1 + 0.3 * (_height - 0.2)/0.5;
                                glColor3f(r,g,b);
                            } else {
                                r = 0.2 + 0.8 * ((_height - 0.7) / 0.3);
                                g = 0.3 + 0.7 * ((_height - 0.7) / 0.3);
                                b = 0.4 + 0.6 * ((_height - 0.7) / 0.3);
                                glColor3f(r,g,b);
                            }
                        } else {
                            glColor3f(0.1, 0.3, 0.5);
                        }
                    }
                    glVertex3f(x, this->height[x][z], z);
                }
                glEnd();
                glBegin(GL_TRIANGLES);
                for (int v = 0; v < 3; v++) {
                    x = i + triangle2[v][0];
                    z = j + triangle2[v][1];
                    _height = fabs(this->height[x][z] / this->max);
                    if (groovy) {
                        glColor3f(rand() / (float)RAND_MAX * _height, rand() / (float)RAND_MAX * _height, rand() / (float)RAND_MAX * _height);
                    } else {
                        if (wire == 0) {
                            if (_height < 0.2) {
                                glColor3f(_height, 0.4, 0);
                            } else if (_height < 0.8) {
                                glColor3f(0.2 + 0.8 * ((_height - 0.2) / 0.6), 0.4 , 0);
                            } else {
                                glColor3f(1, 0.4 + 0.6 * ((_height - 0.8)/0.2), (_height - 0.8)/0.2); 
                            }
                        } else if (wire == 1) {
                            glColor3f(0.3, 0.2, 0.1);
                        } else if (wire == 2) {
                            if (_height < 0.1) {
                                glColor3f(0, 0, _height);
                            } else if (_height < 0.7) {
                                r = 0.2 * ((_height - 0.2) / 0.5);
                                g = 0.3 * ((_height - 0.2) / 0.5);
                                b = 0.1 + 0.3 * (_height - 0.2)/0.5;
                                glColor3f(r,g,b);
                            } else {
                                r = 0.2 + 0.8 * ((_height - 0.7) / 0.3);
                                g = 0.3 + 0.7 * ((_height - 0.7) / 0.3);
                                b = 0.4 + 0.6 * ((_height - 0.7) / 0.3);
                                glColor3f(r,g,b);
                            }
                        } else {
                            glColor3f(0.1, 0.3, 0.5);
                        }
                    }
                    glVertex3f(x, this->height[x][z], z);
                }
                glEnd();
            }
        }
    break;
    }
}

void Terrain::reset(int iterations) {
    srand(time(NULL));
    this->height = vector<vector<float> >(this->length, vector<float>(this->width, 0));
	CircleAlgorithm(iterations);
}

void Terrain::CircleAlgorithm(int iterations) {
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
