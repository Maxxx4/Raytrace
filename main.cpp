﻿#include "vec3.h"
#include "color.h"
#include "ray.h"

#include <iostream>

color ray_color(const ray& r) {
	vec3 unit_direction = unit_vector(r.direction());
	auto a = 0.5 * (unit_direction.y() + 1.0);
	return (1.0 - a) * color(0.949, 0.125, 0.929) + a * color(1, 0.514, 0.008);
}

int main() {
	// Image
	auto aspect_ratio = 16.0 / 9.0;
	int image_width = 1080;

	int image_height = static_cast<int>(image_width / aspect_ratio);
	image_height = (image_height < 1) ? 1 : image_height; // Make sure height is at least 1

	// Camera
	auto focal_length = 1.0;
	auto viewport_height = 2.0;
	auto viewport_width = viewport_height * viewport_height;
	auto camera_center = point3(0, 0, 0);

	// Calculate vectors across horizontal and vertical viewport edges
	auto viewport_u = vec3(viewport_width, 0, 0);
	auto viewport_v = vec3(0, -viewport_height, 0);

	// Calculate the horizontal and vertical delta vectors from pixel to pixel
	auto pixel_delta_u = viewport_u / image_width;
	auto pixel_delta_v = viewport_v / image_height;

	// Calculate the location of the top left pixel
	auto viewport_top_left = camera_center
		- vec3(0, 0, focal_length) 
		- viewport_u * 0.5 
		- viewport_v * 0.5;

	auto pixel00_loc = viewport_top_left + 0.5 * (pixel_delta_u + pixel_delta_v);

	// Render
	std::cout << "P3\n" << image_width << ' ' << image_height << "\n255\n"; // Defining file type, image w and h, and max color value

	for (int j = 0; j < image_height; j++) {
		std::clog << "\rScanlines remaining: " << (image_height - j) << ' ' << std::flush;
		for (int i = 0; i < image_width; i++) {
			auto pixel_center = pixel00_loc + (i * pixel_delta_u) + (j * pixel_delta_v);
			auto ray_direction = pixel_center - camera_center;
			ray r(camera_center, ray_direction);

			color pixel_color = ray_color(r);
			write_color(std::cout, pixel_color);
		}
	}

	std::clog << "\rDone.                 \n";
	return 0;

}