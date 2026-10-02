EAPI_Model_3D *Skybox_model = nullptr;

class Skybox : EAPI_Object_3D {
    public:
        void Update() {
            position_x = SYSTEM_camera_Position.x + 0.3333333f;
            position_y = SYSTEM_camera_Position.y + 0.3333333f;
            position_z = SYSTEM_camera_Position.z + 0.3333333f;
            rotate_angle_x += 0.025f * deltaTime;
        }

        Skybox() : EAPI_Object_3D(Skybox_model) {
            GlobalScene->add_object(this);
            CubeGame_IgnoreRenderDistance = true;

            scale_x = 40.0f;
            scale_y = 40.0f;
            scale_z = 40.0f;
        }
};