#include "test_scene.h"

#include "../colours.h"
#include "../scene.h"
#include "../objects/sphere.h"
#include "../materials/solid.h"

#include <memory>


namespace Raytracer
{


Scene testScene()
{
    Scene scene;

    // materials
    auto solidBlueMaterial   = std::make_shared<Solid>(Colours::DODGER_BLUE);
    auto solidVioletMaterial = std::make_shared<Solid>(Colours::VIOLET);

    // objects
    auto sphere1 = std::make_shared<Sphere>(glm::vec3{0.0f, 0.0f, 2.0f}, 1.0f, solidBlueMaterial);
    auto sphere2 = std::make_shared<Sphere>(glm::vec3{2.0f, 0.0f, 2.0f}, 1.0f, solidVioletMaterial);

    // add to scene
    scene.add(sphere1, sphere2);

    return scene;
}


} // namespace Raytracer