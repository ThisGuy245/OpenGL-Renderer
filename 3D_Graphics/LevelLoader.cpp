#include "LevelLoader.h"
#include "Primitives.h"

void LevelLoader::loadDefaultLevel(Scene& scene, const Texture& defaultTexture) {
    // Create a ground plane
    Mesh* groundMesh = new Mesh(Primitives::CreatePlane(10.0f, 10.0f, defaultTexture));
    GameObject ground(groundMesh);
    ground.setPosition(glm::vec3(0.0f, -1.0f, 0.0f));
    scene.addObject(ground);

    // Create a cube
    Mesh* cubeMesh = new Mesh(Primitives::CreateCube(1.0f, defaultTexture));
    GameObject cube(cubeMesh);
    cube.setPosition(glm::vec3(0.0f, 0.5f, 0.0f));
    scene.addObject(cube);

    // Create a sphere
    Mesh* sphereMesh = new Mesh(Primitives::CreateSphere(1.0f, 32, defaultTexture));
    GameObject sphere(sphereMesh);
    sphere.setPosition(glm::vec3(2.0f, 1.0f, 0.0f));
    scene.addObject(sphere);
}
