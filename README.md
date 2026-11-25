# raytracer-cpp

![Final Render](render.png)

A dependency-free CPU path tracer written from scratch in C++23. Renders scenes directly to ASCII PPM (`P3`) using only the C++ standard library, paired with a standard-library Python script to export PNGs without external tools.
### Project Structure

```text
raytracer-cpp/
├── main.cpp           # Scene setup and camera configuration
├── rtweekend.h        # Shared constants, utilities, and thread-local RNG
├── vec3.h             # 3D vector, point, and color math
├── ray.h              # Ray origin, direction, and parametric evaluation
├── color.h            # Gamma-2 correction, clamping, and PPM pixel output
├── hittable.h         # Hit record and abstract geometry interface
├── hittable_list.h    # Scene container with closest-hit traversal
├── sphere.h           # Ray-sphere intersection
├── material.h         # Lambertian, metal, and dielectric scattering models
├── camera.h           # Viewport projection, path tracing loop, and thread pool
├── ppm_to_png.py      # Standard-library ASCII PPM (P3) to PNG converter
└── render.png         # Final rendered output
```

### Features

- **Math Core (`vec3.h`, `ray.h`)**: 3D vector/point arithmetic, dot and cross products, specular reflection, Snell's law refraction, and rejection sampling for unit spheres and disks.
- **Scene Geometry (`hittable.h`, `hittable_list.h`, `sphere.h`)**: Polymorphic `hittable` interface with closest-hit interval tracking and consistent outward/inward surface normal orientation.
- **Materials (`material.h`)**:
  - **Lambertian**: True Lambertian diffuse scattering with near-zero scatter vector guards.
  - **Metal**: Specular reflection with configurable fuzz/roughness.
  - **Dielectric**: Refractive glass with total internal reflection and Schlick's Fresnel approximation.
- **Camera & Sampling (`camera.h`, `color.h`)**:
  - Configurable camera position (`lookfrom`, `lookat`, `vup`) and vertical field of view (`vfov`).
  - Thin-lens depth of field (`defocus_angle`, `focus_dist`).
  - Multi-sample jittered antialiasing, configurable max bounce depth, shadow acne mitigation (`t_min = 0.001`), and gamma-2 color correction.
- **Multithreading**: Dynamic scanline scheduling via `std::atomic` and `std::thread`, thread-local `std::mt19937` RNG, and an in-memory framebuffer.
- **Zero-Dependency PNG Export (`ppm_to_png.py`)**: Converts ASCII `P3` PPM output (including UTF-16 output from Windows PowerShell) directly to compressed PNG using Python's `zlib` and `struct` modules.


> References Peter Shirley, Trevor David Black, Steve Hollasch — Ray Tracing in One Weekend
