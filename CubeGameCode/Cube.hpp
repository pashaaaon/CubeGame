class Cube;
Cube* CubeMap[100][100][100];

class Cube : public EAPI_Object_3D {
    private:
        glm::ivec3 coordinates = {0, 0, 0};

    public:
        Cube(EAPI_Model_3D *model, int x, int y, int z) : EAPI_Object_3D(model) {
            GlobalScene->add_object(this);
            CubeMap[x][y][z] = this;

            coordinates.x = x;
            coordinates.y = y;
            coordinates.z = z;

            position_x = float(coordinates.x) * 2.0f;
            position_y = float(coordinates.y) * 2.0f;
            position_z = float(coordinates.z) * 2.0f;
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

void ModelLoad() {
    Cubes::Cobblestone_model = new EAPI_Model_3D("Content/Blocks/Cobblestone/Cobblestone.obj");
    Cubes::Cobblestone_model->texture_filtering(false);
}

void CubeMap_Init() {
    for (int i = 0; i<100; i++) {
        for (int j = 0; j<100; j++) {
            for (int l = 0; l<100; l++) {
                CubeMap[i][j][l] = nullptr;
            }
        }
    }
}