#include "Cube.hpp"
#include "Player.hpp"
#include "Skybox.hpp"

class GAME {
    private:
        const char *version = "CubeGame v1.0";
        Player *player = nullptr;
        float target_fps = 60;
        Skybox *skybox = nullptr;

    public:
        void ModelLoad() {
        Player_model = new EAPI_Model_3D("Content/Player/Player.obj");
        Player_model->texture_filtering(false);
        Skybox_model = new EAPI_Model_3D("Content/Skybox/Skybox.obj");
        Skybox_model->texture_filtering(false);

        Cubes::Cobblestone_model = new EAPI_Model_3D("Content/Blocks/Cobblestone/Cobblestone.obj");
        Cubes::Cobblestone_model->texture_filtering(false);
    }

        void GenerateFlatTerrain() {
            for (int x = 0; x<100; x++) {
                for (int y = 0; y<100; y++) {
                    Cubes::Cobblestone *terrainblock = new Cubes::Cobblestone(x, y, 0);
                }
            }
        }

        void MainLoop() {
            Player player(0.0f, 0.0f, 20.0f);
            while (!EAPI_WindowIsClosed()) {
                if (EAPI_GetKey(GLFW_KEY_ESCAPE)) {EAPI_DestroyWindow(); break;}

                player.Update();
                skybox->Update();

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
            skybox = new Skybox;
            GenerateFlatTerrain();

            // Start game
            cout << version << " ; " << EAPI_version << endl;
            EAPI_SetWindowSize(1280, 720);
            EAPI_SetWindowName(version);
            EAPI_MouseLock();
            MainLoop();
        }
};