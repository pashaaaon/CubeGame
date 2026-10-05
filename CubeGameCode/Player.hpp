EAPI_Model_3D *Player_model = nullptr;

class Player : public EAPI_Object_3D {
    float yaw, pitch;
    float last_mouse_x, last_mouse_y;
    float velocity = 0.0f;
    float gravity = 9.81f;
    float max_fallSpeed = 30.0f;
    float jump_timer = 0.0f;
    float jump_timer_max = 1.0f;

    public:
        int cubeFaceCheck(Cube *selectedCube) {
            float x_min = selectedCube->position_x - 0.5f;
            float x_max = selectedCube->position_x + 0.5f;
            float y_min = selectedCube->position_y - 0.5f;
            float y_max = selectedCube->position_y + 0.5f;
            float z_min = selectedCube->position_z - 0.5f;
            float z_max = selectedCube->position_z + 0.5f;

            glm::vec3 camDir = SYSTEM_camera_LookAt;
            glm::vec3 camPos = SYSTEM_camera_Position;

            float tx1 = (x_min - camPos.x) / camDir.x;
            float tx2 = (x_max - camPos.x) / camDir.x;
            float ty1 = (y_min - camPos.y) / camDir.y;
            float ty2 = (y_max - camPos.y) / camDir.y;
            float tz1 = (z_min - camPos.z) / camDir.z;
            float tz2 = (z_max - camPos.z) / camDir.z;

            float tx_min = min(tx1, tx2);
            float tx_max = max(tx1, tx2);
            float ty_min = min(ty1, ty2);
            float ty_max = max(ty1, ty2);
            float tz_min = min(tz1, tz2);
            float tz_max = max(tz1, tz2);

            float exitT = min(tx_max, min(ty_max, tz_max));
            float entryT = max(tx_min, max(ty_min, tz_min));

            if (entryT > exitT) {return 7;}

            if (entryT == tx_min) {
                if (camDir.x > 0) {return 1;}
                else {return 2;}
            }

            if (entryT == ty_min) {
                if (camDir.y > 0) {return 3;}
                else {return 4;}
            }

            if (entryT == tz_min) {
                if (camDir.z > 0) {return 5;}
                else {return 6;}
            }

            return 7;
        }

        void interactionUpdate(bool *left_button, bool *right_button) {
            EAPI_Object_3D *selectedObject = EAPI_SelectedMouseObject_3D();
            if (selectedObject == nullptr) {return;}
            
            if (selectedObject->CubeGame_Cube) {
                Cube *selectedCube = static_cast<Cube*>(selectedObject);

                if (*left_button) {
                    *left_button = false;
                    delete selectedCube;
                }
                
                else if (*right_button) {
                    *right_button = false;
                    int cubeFaceLook = cubeFaceCheck(selectedCube);
                    glm::ivec3 newCubeCoords = {selectedCube->position_x, selectedCube->position_y, selectedCube->position_z};

                    switch (cubeFaceLook) {
                        case 1:
                            newCubeCoords.x -= 1;
                            break;
                        case 2:
                            newCubeCoords.x += 1;
                            break;
                        case 3:
                            newCubeCoords.y -= 1;
                            break;
                        case 4:
                            newCubeCoords.y += 1;
                            break;
                        case 5:
                            newCubeCoords.z -= 1;
                            break;
                        case 6:
                            newCubeCoords.z += 1;
                            break;
                        case 7:
                            return;
                    }

                        if (newCubeCoords.x >= 0 && newCubeCoords.x < 100 && \
                            newCubeCoords.y >= 0 && newCubeCoords.y < 100 && \
                            newCubeCoords.z >= 0 && newCubeCoords.z < 100 && \
                            CubeMap[newCubeCoords.x][newCubeCoords.y][newCubeCoords.z] == nullptr) {
                                CubeMap[newCubeCoords.x][newCubeCoords.y][newCubeCoords.z] = new Cubes::Cobblestone(newCubeCoords.x, newCubeCoords.y, newCubeCoords.z);
                        }
                    }
                }

            else if (selectedObject->CubeGame_Entity) {

            } 
            
        }

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

            // check before move
            bool global_x_positive = false;
            bool global_x_negative = false;
            bool global_y_positive = false;
            bool global_y_negative = false;
            bool global_z_positive = false;
            bool global_z_negative = false;
            for (Cube *cube : test_cubes) {
                bool x_positive, x_negative, y_positive, y_negative, z_positive, z_negative;
                EAPI_Collision3D(this, cube, &x_positive, &x_negative, &y_positive, &y_negative, &z_positive, &z_negative);
                if (x_positive) global_x_positive = x_positive;
                if (x_negative) global_x_negative = x_negative;
                if (y_positive) global_y_positive = y_positive;
                if (y_negative) global_y_negative = y_negative;
                if (z_positive) global_z_positive = z_positive;
                if (z_negative) global_z_negative = z_negative;
            }
            if (global_x_positive) {SYSTEM_camera_Position.x -= 0.1f; position_x -= 0.1f;}
            if (global_x_negative) {SYSTEM_camera_Position.x += 0.1f; position_x += 0.1f;}
            if (global_y_positive) {SYSTEM_camera_Position.y -= 0.1f; position_y -= 0.1f;}
            if (global_y_negative) {SYSTEM_camera_Position.y += 0.1f; position_y += 0.1f;}
            if (global_z_positive) {SYSTEM_camera_Position.z -= 0.1f; position_z -= 0.1f; jump_timer = 0.0f;}
            if (global_z_negative) {SYSTEM_camera_Position.z += 0.1f; position_z += 0.1f;}

            // check after move
            float dx = 0.0f;
            float dy = 0.0f;
            float dz = 0.0f;

            glm::vec3 OLDcam = SYSTEM_camera_Position;

            if (EAPI_GetKey(GLFW_KEY_W)) {dy += 0.1f * deltaTime;}
            if (EAPI_GetKey(GLFW_KEY_S)) {dy -= 0.1f * deltaTime;}
            if (EAPI_GetKey(GLFW_KEY_A)) {dx -= 0.1f * deltaTime;}
            if (EAPI_GetKey(GLFW_KEY_D)) {dx += 0.1f * deltaTime;}
            if (EAPI_GetKey(GLFW_KEY_SPACE) && velocity == 0.0f) {
                dz += 0.1f * deltaTime;
                jump_timer += 0.05f * deltaTime;
            }
            if (jump_timer > 0.0f && jump_timer < jump_timer_max) {
                jump_timer += 0.05f * deltaTime;
                if (jump_timer > jump_timer_max) {jump_timer = 0.0f;}
                dz += 0.1f * deltaTime;
            }
            dz -= velocity * deltaTime / 50.0f;

            EAPI_CameraMoveToDirection(dx, dy);

            glm::vec3 NEWcam = SYSTEM_camera_Position;
            NEWcam.z = OLDcam.z + dz;
            position_x = NEWcam.x;
            position_y = NEWcam.y;
            position_z = NEWcam.z;
            
            bool x_check = false;
            bool y_check = false;
            bool z_check = false;
            bool fall = false;
            for (Cube *cube : test_cubes) {
                bool x_positive, x_negative, y_positive, y_negative, z_positive, z_negative;
                EAPI_Collision3D(this, cube, &x_positive, &x_negative, &y_positive, &y_negative, &z_positive, &z_negative);
                if (x_positive || x_negative) {x_check = true;}
                if (y_positive || y_negative) {y_check = true;}
                if (z_positive || z_negative) {z_check = true;}
                if (z_negative) {fall = true;}
            }

            if (!fall) {
                    velocity += gravity * deltaTime / 50;
                    if (velocity > max_fallSpeed) {velocity = max_fallSpeed;}
            }
            else {velocity = 0.0f;}

            if (x_check) {NEWcam.x = OLDcam.x;}
            if (y_check) {NEWcam.y = OLDcam.y;}
            if (z_check) {NEWcam.z = OLDcam.z;}
            SYSTEM_camera_Position = NEWcam;
            position_x = NEWcam.x;
            position_y = NEWcam.y;
            position_z = NEWcam.z;
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
    
        void Update(bool *left_button, bool *right_button) {
            rotateUpdate();
            moveUpdate();
            interactionUpdate(left_button, right_button);
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

            scale_x = 0.3f;
            scale_y = 0.3f;
            scale_z = 1.2f;
        }
};