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

    // materials
    auto solidEarth    = make<DiffuseLight>(earthTexture);
    auto metallicRed   = make<Metal>(SALMON, 0.0f);
    auto glass         = make<Dielectric>(1.5f);
    auto lightSource   = make<DiffuseLight>(glm::vec3{20.0f});
    auto floorSurface  = make<Lambertian>(DARK_GRAY);

    // objects
    auto sphere1 = make<Sphere>(glm::vec3{0.0f, -0.1f, 3.0f}, 0.9f, solidEarth);
    auto sphere2 = make<Sphere>(glm::vec3{2.0f, -0.1f, 3.0f}, 0.9f, metallicRed);
    auto sphere3 = make<Sphere>(glm::vec3{-2.0f, -0.1f, 3.0f}, 0.9f, glass);
    // auto sphere3 = make<Sphere>(glm::vec3{-0.65f, -0.1f, 2.0f}, 0.9f, glass);
    // auto sphere4 = make<Sphere>(glm::vec3{-2.0f, -0.1f, 3.0f}, -0.72f, glass);

    auto lightSphere = make<Sphere>(glm::vec3{0.0f, -0.5f, 1.5f}, 0.1f, lightSource);

    auto floorSphere = make<Sphere>(glm::vec3{0.0f, -102.0f, 0.0f}, 101.0f, floorSurface);

    // add to scene
    scene.add(sphere1, sphere2, sphere3, floorSphere);

    return scene;
}


} // namespace Raytracer