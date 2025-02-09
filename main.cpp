#include "rtweekend.h"

#include "color.h"
#include "hittable.h"
#include "hittable_list.h"
#include "sphere.h"
#include "camera.h"

int main() {

	hittable_list scene;

	scene.add(make_shared<sphere>(point3(0, 0, -1), 0.5));
	scene.add(make_shared<sphere>(point3(0, -100.5, -1), 100));

	camera cam;

	cam.aspect_ratio = 16.0 / 9.0;
	cam.image_width = 1080;
	cam.max_depth = 50;

	cam.render(scene);


}