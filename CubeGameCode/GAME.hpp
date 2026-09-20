#include "Cube.hpp"
#include "Player.hpp"

class GAME {
    private:
        string version = "v1.0";
        Player *player = nullptr;

    public:
        void GenerateFlatTerrain() {
            for (int x = 0; x<20; x++) {
                for (int y = 0; y<20; y++) {
                    Cubes::Cobblestone *terrainblock = new Cubes::Cobblestone(x, y, 0);
                }
            }
        }

        void MainLoop() {
            Player player(0.0f, 0.0f, 20.0f);
            while (!EAPI_WindowIsClosed()) {
                float dx = 0.0f;
                float dy = 0.0f;
                float dz = 0.0f;

                if (EAPI_GetKey(GLFW_KEY_W)) {dy += 0.5f;}
                if (EAPI_GetKey(GLFW_KEY_S)) {dy -= 0.5f;}
                if (EAPI_GetKey(GLFW_KEY_A)) {dx -= 0.5f;}
                if (EAPI_GetKey(GLFW_KEY_D)) {dx += 0.5f;}
                if (EAPI_GetKey(GLFW_KEY_SPACE)) {dz += 0.5f;}
                if (EAPI_GetKey(GLFW_KEY_LEFT_SHIFT)) {dz -= 0.5f;}

                EAPI_CameraMoveToDirection(dx, dy);
                player.Update();

                EAPI_Render();
            }
        }

        GAME() {
            // Engine INIT
            bool engine_check = EAPI_Init(true, true);
            if (!engine_check) {throw invalid_argument("Init status: Engine Error");}
            GlobalScene = new EAPI_Scene_3D;
            EAPI_SelectScene3D((EAPI_Scene_3D*)GlobalScene);
            
            // Load models
            try {ModelLoad();}
            catch (...) {throw invalid_argument("Init status: ModelLoad");}
            
            // Creating game map
            CubeMap_Init();
            GenerateFlatTerrain();

            // Start game
            cout << "CubeGame " << version << " ; " << EAPI_version << endl;
            MainLoop();
        }
};