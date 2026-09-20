EAPI_Model_3D *Player_model = nullptr;

class Player : public EAPI_Object_3D {
    glm::ivec3 coordinates;
    float yaw, pitch;

    public:
        void Update() {
            coordinates.x = position_x;
            coordinates.y = position_y;
            coordinates.z = position_z;

            float mouse_x, mouse_y;
            EAPI_GetMousePosition(&mouse_x, &mouse_y);
            yaw = -mouse_x/12.0f;
            pitch = -mouse_y/12.0f;

            // EAPI_SetCameraPosition(position_x, position_y, position_z + 0.5f);
            EAPI_SetCameraAngle(yaw, pitch);
        }

        Player(float spawn_x, float spawn_y, float spawn_z) : EAPI_Object_3D(Player_model) {
            Player_model = new EAPI_Model_3D("Content/Player/Player.obj");

            EAPI_SetCameraPosition(spawn_x, spawn_y, spawn_z + 0.5f);

            coordinates.x = spawn_x;
            coordinates.y = spawn_y;
            coordinates.z = spawn_z;

            position_x = spawn_x;
            position_y = spawn_y;
            position_z = spawn_z;
        }
};