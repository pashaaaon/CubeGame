#include "Cube.hpp"
#include "Player.hpp"
#include "Skybox.hpp"

bool left_button = false;
bool right_button = false;

class GAME {
    private:
        const char *version = "CubeGame v1.0";
        Player *player = nullptr;
        Skybox *skybox = nullptr;

    public:
        static void mouseButton(GLFWwindow *window, int button, int action, int mods) {
            if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS) {left_button = true;}
            if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_RELEASE) {left_button = false;}

            if (button == GLFW_MOUSE_BUTTON_RIGHT && action == GLFW_PRESS) {right_button = true;}
            if (button == GLFW_MOUSE_BUTTON_RIGHT && action == GLFW_RELEASE) {right_button = false;}
        }

        void calc_deltaTime(chrono::time_point<chrono::high_resolution_clock> *last_frame) {
            auto current_frame = chrono::high_resolution_clock::now();
            chrono::duration<double> delta = current_frame - *last_frame;
            deltaTime = 50 * delta.count();
            *last_frame = current_frame;
        }

        void ModelLoad() {
            Player_model = new EAPI_Model_3D("Content/Player/Player.obj");
            Player_model->texture_filtering(false);
            Skybox_model = new EAPI_Model_3D("Content/Skybox/Skybox.obj");
            Skybox_model->texture_filtering(false);

            Cubes::Cobblestone_model = new EAPI_Model_3D("Content/Cubes/Cobblestone/Cobblestone.obj");
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
            Player player(50.0f, 50.0f, 5.0f);
            int window_x, window_y;
            auto last_frame = chrono::high_resolution_clock::now();

            while (!EAPI_WindowIsClosed()) {
                if (EAPI_GetKey(GLFW_KEY_ESCAPE)) {EAPI_DestroyWindow(); break;}
                EAPI_UpdateEvents();

                calc_deltaTime(&last_frame);
                player.Update(&left_button, &right_button);
                skybox->Update();

                EAPI_GetWindowSize(&window_x, &window_y);
                EAPI_Render(window_x*1.5, window_y*1.5);
            }
        }

        GAME() {
            // Engine INIT
            bool engine_check = EAPI_Init(true, true);
            if (!engine_check) {throw invalid_argument("Init status: Engine Error");}
            GlobalScene = new EAPI_Scene_3D;
            EAPI_SelectScene3D((EAPI_Scene_3D*)GlobalScene);
            glfwSetMouseButtonCallback(EAPI_MainWindow, mouseButton);
            
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