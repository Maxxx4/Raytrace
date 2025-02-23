#pragma once
#include "vec3.h"
#include "interval.h"


using color = vec3;

inline double linear_to_gamma(double linear_component)
{
    if (linear_component > 0)
        return std::sqrt(linear_component);
    // Inefficient, but simple. Something to look into and change later (Linnear Approximation, first order Taylor series)

    return 0;
}

void write_color(std::ostream& out, const color& pixel_color) {
    auto r = pixel_color.x();
    auto g = pixel_color.y();
    auto b = pixel_color.z();

	r = linear_to_gamma(r);
	g = linear_to_gamma(g);
	b = linear_to_gamma(b); 

    // Translate the [0,1] component values to the byte range [0,255].
	static const interval intensity(0.0, 1.0);
    int rbyte = int(255 * intensity.clamp(r));
    int gbyte = int(255 * intensity.clamp(g));
    int bbyte = int(255 * intensity.clamp(b));

    // Write out the pixel color components.
    out << rbyte << ' ' << gbyte << ' ' << bbyte << '\n';
}