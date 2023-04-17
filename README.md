# Raytracing

A simple real-time ray tracer with a controllable camera.

## Demo
![demo image](demo_light.png)

## Getting Started

### Dependencies
* [SDL2](https://www.libsdl.org/) - window creation
* [glm](https://github.com/g-truc/glm) - math library

### Installing
```
>>> make build
```

### Executing program
```
>>> ./raytracer
```

### Usage
* `Esc` - Quit
* `W`, `A`, `S`, `D` - Move forward, backward, left, right
* `Space`, `LShift` - Move up, down
* `P` - Take a screenshot (saved to `out.png`) and quit

## Features
* Moveable camera
* Accumulation - one sample per pixel per frame, image quality improves over time
* Anti-aliasing
* Materials - diffuse (lambertian), metal, glass (dielectric), light source
* Geometry - spheres only
* Texture - solid colour, image texture

## Todo list
* **Support window resize**
* **(Mouse-controlled) camera rotation**
* **Figure out why multi-threading is making code slower instead of faster**
* Depth of field (camera focus)
* Rectangles and cuboids
* Axis aligned bounding box (AABB)
* Object file loading
* Mist (participating media)
* Perlin noise texture
* [ImGui](https://github.com/ocornut/imgui) to edit scene during runtime

## Acknowledgments
* [_Ray Tracing in One Weekend_](https://raytracing.github.io/books/RayTracingInOneWeekend.html)
* [_Ray Tracing: The Next Week_](https://raytracing.github.io/books/RayTracingTheNextWeek.html)
