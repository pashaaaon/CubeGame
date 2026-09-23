EAPI_Model_3D *Player_model = nullptr;

class Player : public EAPI_Object_3D {
    float yaw, pitch;
    float last_mouse_x, last_mouse_y;

    public:
        void moveUpdate() {
            // cubes for collision
            vector<Cube*> test_cubes;
            for (int x=-1; x<2; x++) {
                for (int y=-1; y<2; y++) {
                    for (int z=-1; z<2; z++) {
                        if (x+(int)position_x >= 0 && x+(int)position_x < 100) {
                            if (y+(int)position_y >= 0 && y+(int)position_y < 100) {
                                if (z+(int)position_z >= 0 && z+(int)position_z < 100) {
                                    if (CubeMap[x+(int)position_x][y+(int)position_y][z+(int)position_z] != nullptr) {
                                        test_cubes.push_back(CubeMap[x+(int)position_x][y+(int)position_y][z+(int)position_z]);
                                    } 
                                }
                            }
                        }
                    }
                }
            }

            // check
            float dx = 0.0f;
            float dy = 0.0f;
            float dz = 0.0f;

            float cam_x, cam_y, cam_z;
            EAPI_GetCameraPosition(&cam_x, &cam_y, &cam_z);

            if (EAPI_GetKey(GLFW_KEY_W)) {dy += 0.1f;}
            if (EAPI_GetKey(GLFW_KEY_S)) {dy -= 0.1f;}
            if (EAPI_GetKey(GLFW_KEY_A)) {dx -= 0.1f;}
            if (EAPI_GetKey(GLFW_KEY_D)) {dx += 0.1f;}
            if (EAPI_GetKey(GLFW_KEY_SPACE)) {dz += 0.1f;}
            if (EAPI_GetKey(GLFW_KEY_LEFT_SHIFT)) {dz -= 0.1f;}

            EAPI_CameraMoveToDirection(dx, dy);

            float new_cam_x, new_cam_y, new_cam_z;
            EAPI_GetCameraPosition(&new_cam_x, &new_cam_y, &new_cam_z);
            new_cam_z = cam_z + dz;
            position_x = new_cam_x;
            position_y = new_cam_y;
            position_z = new_cam_z;
            
            bool x_check = false;
            bool y_check = false;
            bool z_check = false;
            for (Cube *cube : test_cubes) {
                bool x_positive, x_negative, y_positive, y_negative, z_positive, z_negative;
                EAPI_Collision3D(cube, this, &x_positive, &x_negative, &y_positive, &y_negative, &z_positive, &z_negative);
                if (x_positive || x_negative) {x_check = true;}
                if (y_positive || y_negative) {y_check = true;}
                if (z_positive || z_negative) {z_check = true;}
                // cout << cube->coordinates.x << ' ' << cube->coordinates.y << ' ' <<cube->coordinates.z << endl;
                cout << position_x << ' ' << position_y << ' ' << position_z << endl;
            }

            if (x_check) {new_cam_x = cam_x;}
            if (y_check) {new_cam_y = cam_y;}
            if (z_check) {new_cam_z = cam_z;}
            EAPI_SetCameraPosition(new_cam_x, new_cam_y, new_cam_z);
            position_x = new_cam_x;
            position_y = new_cam_y;
            position_z = new_cam_z;
        }

        void rotateUpdate() {
            float mouse_x, mouse_y;
            EAPI_GetMousePosition(&mouse_x, &mouse_y);
            yaw += (last_mouse_x-mouse_x)/12.0f;
            pitch += (last_mouse_y-mouse_y)/12.0f;
            if (pitch >= 90.0f) {pitch = 89.9f;}
            else if (pitch <= -90.0f) {pitch = -89.9f;}
            EAPI_SetCameraAngle(yaw, pitch);
            last_mouse_x = mouse_x;
            last_mouse_y = mouse_y;
        }
    
        void Update() {
            rotateUpdate();
            moveUpdate();
        }

        Player(float spawn_x, float spawn_y, float spawn_z) : EAPI_Object_3D(Player_model) {
            EAPI_GetMousePosition(&last_mouse_x, &last_mouse_y);
            while (true) {
                if (!SYSTEM_current_model->SYSTEM_loadthread && SYSTEM_current_model->SYSTEM_modelRAM) {
                    SYSTEM_current_model->SYSTEM_loadVRAM();
                    break;
                }
            }

            EAPI_SetCameraPosition(spawn_x, spawn_y, spawn_z);
            position_x = spawn_x;
            position_y = spawn_y;
            position_z = spawn_z;

            scale_x = 0.5f;
            scale_y = 0.5f;
            scale_z = 0.5f;
        }
};