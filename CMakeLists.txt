﻿# CMakeList.txt : CMake project for Raytrace, include source and define
# project specific logic here.
#

# Add source to this project's executable.
add_executable (Raytrace "main.cpp"  "ray.h" "hittable.h" "sphere.h" "hittable_list.h" "rtweekend.h" "interval.h" "camera.h" "material.h")

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET Raytrace PROPERTY CXX_STANDARD 20)
endif()

# TODO: Add tests and install targets if needed.
