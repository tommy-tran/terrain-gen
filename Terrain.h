#ifndef __TERRAIN_H__
#define __TERRAIN_H__

#include <vector>

using namespace std;

class Terrain{
public:
    int length;
    int width;
    Terrain();

    void CreateTerrain(int x, int z);
    void DrawTerrain();

private:
};

#endif
