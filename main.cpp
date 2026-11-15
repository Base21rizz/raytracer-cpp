#include <iostream>

int main() {
    // Image dimensions
    const int image_width = 256;
    const int image_height = 256;

    // Render header
    // P3 means colors are in ASCII, followed by width, height, and max color (255)
    std::cout << "P3\n" << image_width << ' ' << image_height << "\n255\n";

    // Write pixel data
    for (int j = 0; j < image_height; ++j) {
        // Use clog to print progress to the terminal (cout is redirected to the file)
        std::clog << "\rScanlines remaining: " << (image_height - j) << ' ' << std::flush;
        for (int i = 0; i < image_width; ++i) {
            
            // Calculate gradient colors (normalized 0.0 to 1.0)
            auto r = double(i) / (image_width - 1);
            auto g = double(j) / (image_height - 1);
            auto b = 0.0; // Blue is locked at 0

            // Translate [0.0, 1.0] to [0, 255]
            int ir = static_cast<int>(255.999 * r);
            int ig = static_cast<int>(255.999 * g);
            int ib = static_cast<int>(255.999 * b);

            std::cout << ir << ' ' << ig << ' ' << ib << '\n';
        }
    }
    std::clog << "\rDone.                 \n";
}