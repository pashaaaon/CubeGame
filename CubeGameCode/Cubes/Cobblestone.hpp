EAPI_Model_3D *Cobblestone_model = nullptr;

class Cobblestone : public Cube {
    public:
        Cobblestone(int x, int y, int z) : Cube(Cobblestone_model, x, y, z) {}
};