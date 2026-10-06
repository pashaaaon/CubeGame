#define MAP_SAVE true
#define MAP_LOAD false

#include <fstream>

class MapLoader {
    public:
        MapLoader(bool mode) {
            const char path[] = "Saved.cubegame";

            // Save
            if (mode == MAP_SAVE) {
                ofstream file(path);
                
                for (int x = 0; x < 100; x++) {
                    for (int y = 0; y < 100; y++) {
                        for (int z = 0; z < 100; z++) {
                            if (CubeMap[x][y][z] == nullptr) file << '0' << '\n';
                            else file << CubeMap[x][y][z]->index << '\n';
                        }
                    }
                }
            }

            // Load
            else {
                ifstream file(path);

                for (int x = 0; x < 100; x++) {
                    for (int y = 0; y < 100; y++) {
                        for (int z = 0; z < 100; z++) {
                            if (CubeMap[x][y][z] != nullptr) {
                                delete CubeMap[x][y][z];
                                CubeMap[x][y][z] = nullptr;
                            }

                            string current_string;
                            getline(file, current_string);
                            if (current_string != "" && current_string != "0\n") Cubes::CubeCreator(stoi(current_string), x, y, z);
                        }
                    }
                }
            }
        }
};