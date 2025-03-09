#include "rtweekend.h"

#include "color.h"
#include "hittable.h"
#include "hittable_list.h"
#include "sphere.h"
#include "camera.h"
#include "material.h"

int main() {

	hittable_list scene;

	auto material_ground = make_shared<lambertian>(color(0.84, 0.36, 0.69)); //0.52, 0.37, 0.76
	auto material_left = make_shared<dielectric>(1.0 / 1.33);
	auto material_middle = make_shared<lambertian>(color(0.0, 0.9, 0.8));
	auto material_right = make_shared<metal>(color(0.98, 0.97, 0.44), 0.5);

	scene.add(make_shared<sphere>(point3(0.0, -100.5, -1.0), 100.0, material_ground));
	scene.add(make_shared<sphere>(point3(-1.0, 0, -1.0), 0.5, material_left));
	scene.add(make_shared<sphere>(point3(0.0, 0.0, -1.0), 0.5, material_middle));
	scene.add(make_shared<sphere>(point3(1, 0.0, -1.0), 0.5, material_right));

	camera cam;

	cam.aspect_ratio = 16.0 / 9.0;
	cam.image_width = 1080;
	cam.max_depth = 50;

	cam.render(scene);


}