#pragma once

#include "hittable.h"

class camera {
public:
	double aspect_ratio = 1; // Ratio of width to height
	int image_width = 100; // Rendered image width in pixels   

    void render(const hittable& scene) {

		initialize();

        std::cout << "P3\n" << image_width << ' ' << image_height << "\n255\n"; // Defining file type, image w and h, and max color value

        for (int j = 0; j < image_height; j++) {
            std::clog << "\rScanlines remaining: " << (image_height - j) << ' ' << std::flush;
            for (int i = 0; i < image_width; i++) {
                auto pixel_center = pixel00_loc + (i * pixel_delta_u) + (j * pixel_delta_v);
                auto ray_direction = pixel_center - center;
                ray r(center, ray_direction);

                color pixel_color = ray_color(r, scene);
                write_color(std::cout, pixel_color);
            }
        }

        std::clog << "\rDone.                 \n";
    }

private:
    int    image_height;   // Rendered image height
    point3 center;         // Camera center
    point3 pixel00_loc;    // Location of pixel 0, 0
    vec3   pixel_delta_u;  // Offset to pixel to the right
    vec3   pixel_delta_v;  // Offset to pixel below

    void initialize() {
        image_height = static_cast<int>(image_width / aspect_ratio);
        image_height = (image_height < 1) ? 1 : image_height; // Make sure height is at least 1
        
        center = point3(0, 0, 0);

		// Viewport dimensions
        auto focal_length = 1.0;
        auto viewport_height = 2.0;
        auto viewport_width = viewport_height * aspect_ratio;

		//calculate vectors across horizontal and vertical viewport edges
        auto viewport_u = vec3(viewport_width, 0, 0);
        auto viewport_v = vec3(0, -viewport_height, 0);

        // Calculate the horizontal and vertical delta vectors from pixel to pixel
        pixel_delta_u = viewport_u / image_width;
        pixel_delta_v = viewport_v / image_height;

        // Calculate the location of the top left pixel
        auto viewport_top_left = center
            - vec3(0, 0, focal_length)
            - viewport_u * 0.5
            - viewport_v * 0.5;
        pixel00_loc = viewport_top_left + 0.5 * (pixel_delta_u + pixel_delta_v);
        
    }

    color ray_color(const ray& r, const hittable& scene) const {

        hit_record rec;

        if (scene.hit(r, interval(0, infinity), rec)) {
            return 0.5 * (rec.normal + color(1, 1, 1));
        }

        vec3 unit_direction = unit_vector(r.direction());
        auto a = 0.5 * (unit_direction.y() + 1.0);
        return (1.0 - a) * color(0.949, 0.125, 0.929) + a * color(1, 0.514, 0.008);
    }
};