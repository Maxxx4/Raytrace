#pragma once

#include "hittable.h"
#include "material.h"

class camera {
public:
	double aspect_ratio = 1; // Ratio of width to height
	int image_width = 100; // Rendered image width in pixels   
    int samples_per_pixel = 25;   // Count of random samples for each pixel
	int max_depth = 10; // Maximum recursion depth for ray bouncing

    void render(const hittable& scene) {

		initialize();

        std::cout << "P3\n" << image_width << ' ' << image_height << "\n255\n"; // Defining file type, image w and h, and max color value

        for (int j = 0; j < image_height; j++) {
            std::clog << "\rScanlines remaining: " << (image_height - j) << ' ' << std::flush;
            for (int i = 0; i < image_width; i++) {
                color pixel_color(0, 0, 0);
                for (int sample = 0; sample < samples_per_pixel; sample++) {
                    ray r = get_ray(i, j);
                    pixel_color += ray_color(r, max_depth, scene);
                }
                write_color(std::cout, pixel_samples_scale * pixel_color);
            }
        }

        std::clog << "\rDone.                 \n";
    }

private:
    int    image_height;   // Rendered image height
    double pixel_samples_scale;  // Color scale factor for a sum of pixel samples
    point3 center;         // Camera center
    point3 pixel00_loc;    // Location of pixel 0, 0
    vec3   pixel_delta_u;  // Offset to pixel to the right
    vec3   pixel_delta_v;  // Offset to pixel below

    void initialize() {
        image_height = static_cast<int>(image_width / aspect_ratio);
        image_height = (image_height < 1) ? 1 : image_height; // Make sure height is at least 1

        pixel_samples_scale = 1.0 / samples_per_pixel;
        
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

    ray get_ray(int i, int j) const {
        // Construct a camera ray originating from the origin and directed at randomly sampled
        // point around the pixel location i, j.

        auto offset = sample_square();
        auto pixel_sample = pixel00_loc
            + ((i + offset.x()) * pixel_delta_u)
            + ((j + offset.y()) * pixel_delta_v);

        auto ray_origin = center;
        auto ray_direction = pixel_sample - ray_origin;

        return ray(ray_origin, ray_direction);
    }

    vec3 sample_square() const {
        // Returns the vector to a random point in the [-.5,-.5]-[+.5,+.5] unit square.
        return vec3(random_double() - 0.5, random_double() - 0.5, 0);
    }

    color ray_color(const ray& r, int depth, const hittable& scene) const {

		if (depth <= 0) {
			return color(0, 0, 0);
		}

        hit_record rec;

        if (scene.hit(r, interval(0.001, infinity), rec)) {
			ray scattered;
			color attenuation;

			if (rec.mat->scatter(r, rec, attenuation, scattered))
				return attenuation * ray_color(scattered, depth - 1, scene);
			return color(0, 0, 0);
            //vec3 direction = rec.normal + random_unit_vector();/*random_on_hemisphere(rec.normal);*/
            //return 0.9 * ray_color(ray(rec.p, direction), depth - 1, scene); /*(rec.normal + color(1, 1, 1));*/ // For normals
        }

        vec3 unit_direction = unit_vector(r.direction());
        auto a = 0.5 * (unit_direction.y() + 1.0);
		return (1.0 - a) * color(0.949, 0.125, 0.929) + a * color(1, 0.514, 0.008); // Background color gradient
    }
};