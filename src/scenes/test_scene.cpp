#include "test_scene.h"

#include "../colours.h"
#include "../materials/includes.h"
#include "../objects/includes.h"
#include "../scene.h"
#include "../textures/includes.h"

#include <memory>


namespace Raytracer
{


Scene testScene()
{
    #define make std::make_shared
    using namespace Colours;

    Scene scene;

    // textures
    auto earthTexture = make<ImageTexture>("./assets/earth.png");
    auto moonTexture  = make<ImageTexture>("./assets/moon.png");

    // materials
    auto solidEarth    = make<DiffuseLight>(earthTexture);
    auto metallicRed   = make<Metal>(SALMON, 1.0f);
    auto glass         = make<Dielectric>(2.42f);
    auto lightSource   = make<DiffuseLight>(moonTexture);
    auto floorSurface  = make<Metal>(DARK_GRAY, 0.1f);

    // objects
    auto sphere1 = make<Sphere>(glm::vec3{0.0f, -0.1f, 3.0f}, 0.9f, solidEarth);
    auto sphere2 = make<Sphere>(glm::vec3{2.0f, -0.1f, 3.0f}, 0.9f, metallicRed);
    auto sphere3 = make<Sphere>(glm::vec3{-2.0f, -0.1f, 3.0f}, 0.9f, glass);
    auto sphere4 = make<Sphere>(glm::vec3{-2.0f, -0.1f, 6.0f}, 0.9f, metallicRed);
    // auto sphere3 = make<Sphere>(glm::vec3{-0.65f, -0.1f, 2.0f}, 0.9f, glass);
    // auto sphere4 = make<Sphere>(glm::vec3{-2.0f, -0.1f, 3.0f}, -0.72f, glass);

    auto lightSphere = make<Sphere>(glm::vec3{0.0f, -0.5f, 1.5f}, 0.1f, lightSource);

    auto floorSphere = make<Sphere>(glm::vec3{0.0f, -102.0f, 0.0f}, 101.0f, floorSurface);

    // add to scene
    scene.add(sphere1, sphere2, sphere3, sphere4, floorSphere, lightSphere);

    return scene;

    #undef make
}


} // namespace Raytracer