#include "test_scene.h"

#include "../colours.h"
#include "../materials/includes.h"
#include "../objects/includes.h"
#include "../scene.h"
#include "../textures/includes.h"

#include <memory>


namespace Raytracer
{


Scene planets()
{
    #define make std::make_shared
    using namespace Colours;

    Scene scene;

    // textures
    auto earthTexture = make<ImageTexture>("./assets/earth.png");
    auto moonTexture  = make<ImageTexture>("./assets/moon.png");
    auto sunTexture   = make<ImageTexture>("./assets/sun.png");

    // materials
    auto sunMaterial   = make<DiffuseLight>(sunTexture, 5.0f);
    auto earthMaterial = make<Lambertian>(earthTexture);
    auto moonMaterial  = make<Lambertian>(moonTexture);

    // objects
    auto sun   = make<Sphere>(glm::vec3{0.0f, 0.0f, 4.0f}, 1.5f, sunMaterial);
    auto earth = make<Sphere>(glm::vec3{-3.0f, 0.0f, 4.0f}, 1.0f, earthMaterial);
    auto moon  = make<Sphere>(glm::vec3{3.0f, 0.0f, 4.0f}, 0.5f, moonMaterial);

    // add to scene
    scene.add(sun, earth, moon);

    return scene;
}


} // namespace Raytracer