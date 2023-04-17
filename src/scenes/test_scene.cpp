#include "test_scene.h"

#include "../colours.h"
#include "../materials/includes.h"
#include "../objects/includes.h"
#include "../scene.h"
#include "../textures/includes.h"

#include <memory>
#include <random>


namespace Raytracer
{


Scene testScene()
{
    std::random_device rd;
    std::mt19937 rng(rd());
    std::uniform_real_distribution<float> dist(0.0f, 1.0f);

    #define make std::make_shared
    using namespace Colours;

    Scene scene;

    // textures
    auto earthTexture = make<ImageTexture>("./assets/earth.png");

    // materials
    auto glass        = make<Dielectric>(2.42f);
    auto metal        = make<Metal>(LIGHT_GRAY, 0.0f);
    auto diffuseEarth = make<Lambertian>(earthTexture);
    auto floor        = make<Lambertian>(DARK_GRAY);

    // spheres
    auto leftSphere   = make<Sphere>(glm::vec3{-2.5f, +0.0f, +5.0f}, 1.0f, diffuseEarth);
    auto middleSphere = make<Sphere>(glm::vec3{+0.0f, +0.0f, +5.0f}, 1.0f, glass);
    auto rightSphere  = make<Sphere>(glm::vec3{+2.5f, +0.0f, +5.0f}, 1.0f, metal);
    auto floorSphere  = make<Sphere>(glm::vec3{+0.0f, -1001.0f, +0.0f}, 1000.0f, floor);

    // random small spheres
    constexpr float SPHERE_RADIUS = 0.15f;
    for (int i = -5; i <= 5; ++i)
    {
        for (int j = 0; j <= 10; ++j)
        {
            float rand = dist(rng);

            std::shared_ptr<Material> material;
            auto centre = glm::vec3{i + dist(rng), -1.0f + SPHERE_RADIUS, j + dist(rng)};
            auto albedo = glm::vec3{dist(rng), dist(rng), dist(rng)};
            albedo *= albedo;

            if (rand < 0.6)
                material = make<Lambertian>(albedo);

            else if (rand < 0.9)
                material = make<Metal>(albedo, dist(rng));
            
            else
                material = glass;

            auto sphere = make<Sphere>(centre, SPHERE_RADIUS, material);
            scene.add(sphere);
        }
    }

    // add to scene
    scene.add(leftSphere, middleSphere, rightSphere, floorSphere);

    return scene;

    #undef make
}


} // namespace Raytracer