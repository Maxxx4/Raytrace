# Raytrace
A simple ray tracing renderer implemented in C++.

## Features

- Basic ray tracing capabilities
- Rendering of spheres
- Anti-aliasing to reduce jagged edges

## Acknowledgment

This project is based on the excellent book **[Ray Tracing in One Weekend](https://raytracing.github.io/books/RayTracingInOneWeekend.html)** by Peter Shirley. The implementation follows the concepts and structure outlined in the book.

## Requirements

- C++17 or later
- CMake 3.8 or later

## Building the Project
### On Windows (Command Prompt)
1. Create a build directory:
```Console
mkdir build
cd build
```

2. Generate build files:
```Console
cmake ..
```

3. Build the project:
```Console
cmake --build .
```

## Usage
After building, you can run the program by redirecting the output to a file as follows:

```
Raytrace.exe > title.ppm
```

This will generate an image file named title.ppm in the current directory.

PPM files typically need a special viewer, I recommend **[Rhodes College's online PPM viewer](https://www.cs.rhodes.edu/welshc/COMP141_F16/ppmReader.html)**
