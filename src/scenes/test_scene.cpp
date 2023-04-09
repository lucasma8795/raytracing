#include "test_scene.h"

#include "../colours.h"
#include "../scene.h"

#include "../objects/sphere.h"

#include "../materials/includes.h"

#include <memory>


namespace Raytracer
{


Scene testScene()
{
    Scene scene;

    // materials
    auto solidBlue     = std::make_shared<Solid>(Colours::DODGER_BLUE);
    auto solidViolet   = std::make_shared<Solid>(Colours::VIOLET);
    auto surfaceNormal = std::make_shared<SurfaceNormal>();
    auto metallicRed   = std::make_shared<Metal>(Colours::SALMON, 0.0f);
    auto glass         = std::make_shared<Dielectric>(2.0f);

    auto lightSource   = std::make_shared<Solid>(glm::vec3{20.0f});

    auto floorSurface = std::make_shared<Lambertian>(Colours::GOLD);

    // objects
    auto sphere1 = std::make_shared<Sphere>(glm::vec3{0.0f, -0.1f, 3.0f}, 0.9f, metallicRed);
    auto sphere2 = std::make_shared<Sphere>(glm::vec3{2.0f, -0.1f, 3.0f}, 0.9f, glass);
    auto sphere3 = std::make_shared<Sphere>(glm::vec3{-2.0f, -0.1f, 3.0f}, 0.9f, surfaceNormal);

    auto lightSphere = std::make_shared<Sphere>(glm::vec3{0.0f, -0.5f, 1.5f}, 0.1f, lightSource);

    auto floorSphere = std::make_shared<Sphere>(glm::vec3{0.0f, -1002.0f, 0.0f}, 1001.0f, floorSurface);

    // add to scene
    scene.add(sphere1, sphere2, sphere3, floorSphere, lightSphere);

    return scene;
}


} // namespace Raytracer