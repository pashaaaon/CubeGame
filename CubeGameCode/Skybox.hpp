EAPI_Model_3D *Skybox_model = nullptr;

class Skybox : EAPI_Object_3D {
    public:
        void Update() {
            position_x = SYSTEM_camera_Position.x;
            position_y = SYSTEM_camera_Position.y;
            position_z = SYSTEM_camera_Position.z;
        }

        Skybox() : EAPI_Object_3D(Skybox_model) {
            GlobalScene->add_object(this);

            scale_x = 40.0f;
            scale_y = 40.0f;
            scale_z = 40.0f;
        }
};