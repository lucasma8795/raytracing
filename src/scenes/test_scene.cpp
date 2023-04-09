#include "test_scene.h"

#include "../colours.h"
#include "../scene.h"

#include "../objects/sphere.h"

#include "../materials/metal.h"
#include "../materials/solid.h"
#include "../materials/surface_normal.h"

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

    // objects
    auto sphere1 = std::make_shared<Sphere>(glm::vec3{0.0f, 0.0f, 3.0f}, 0.9f, metallicRed);
    auto sphere2 = std::make_shared<Sphere>(glm::vec3{2.0f, 0.0f, 3.0f}, 0.9f, solidBlue);
    auto sphere3 = std::make_shared<Sphere>(glm::vec3{-2.0f, 0.0f, 3.0f}, 0.9f, surfaceNormal);

    // add to scene
    scene.add(sphere1, sphere2, sphere3);

    return scene;
}


} // namespace Raytracer