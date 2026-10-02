class Cube;
Cube* CubeMap[100][100][100];

class Cube : public EAPI_Object_3D {
    public:
        glm::ivec3 coordinates = {0, 0, 0};
        bool placed = false;

        Cube(EAPI_Model_3D *model, int x, int y, int z) : EAPI_Object_3D(model) {
            if (x >= 0 && x < 100 && y >= 0 && y < 100 && z >= 0 && z < 100 || CubeMap[x][y][z] != nullptr) {
                GlobalScene->add_object(this);
                CubeMap[x][y][z] = this;
                CubeGame_Interaction = true;
                CubeGame_Cube = true;
            }
            else {throw std::invalid_argument("Invalid coords");}

            coordinates.x = x;
            coordinates.y = y;
            coordinates.z = z;

            position_x = float(coordinates.x);
            position_y = float(coordinates.y);
            position_z = float(coordinates.z);

            scale_x = 0.5f;
            scale_y = 0.5f;
            scale_z = 0.5f;
        }

        ~Cube() {
            CubeMap[coordinates.x][coordinates.y][coordinates.z] = nullptr;
        }

        void get_coords(unsigned int *x, unsigned int *y, unsigned int *z) {
            *x = coordinates.x; *y = coordinates.y; *z = coordinates.z;
        }

        bool set_coords(unsigned int x, unsigned int y, unsigned int z) {
            coordinates = {x, y, z};
            return true;
        }
};

namespace Cubes {
    #include "Cubes/Cobblestone.hpp"
}

void CubeMap_Init() {
    for (int x = 0; x<100; x++) {
        for (int y = 0; y<100; y++) {
            for (int z = 0; z<100; z++) {
                CubeMap[x][y][z] = nullptr;
            }
        }
    }
}