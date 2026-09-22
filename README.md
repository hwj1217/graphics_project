# Software Rasterizer from Scratch

A software rasterizer written in C and C++, built without any graphics libraries or APIs (no OpenGL, no Vulkan, no SDL). All output is written to PPM image files.

## Why

Graphics APIs like OpenGL handle the rendering pipeline for you, so it is easy to use them without knowing what happens inside. The goal of this project is to build every stage by hand, to understand what the GPU is actually doing: from transforming vertices to deciding the color of each pixel.

This is also a learning project for moving from C to C++. Stages 1–3 are written in C. From Stage 4 on, the code is in C++.

## Progress

| Stage | Topic | Language | Status |
|---|---|---|---|
| 1 | Framebuffer and PPM output | C | Done |
| 2 | Line drawing (Bresenham) | C | Done |
| 3 | Filled triangles with edge functions and barycentric interpolation | C | Done |
| 4a | `Vec3` vector class | C++ | Done |
| 4b | `Mat4`, `Vec4`, homogeneous coordinates | C++ | Done |
| 4c | Projection: model → view → projection → viewport | C++ | In progress |
| 4d | First 3D cube | C++ | Planned |
| 5 | Full scene with Z-buffer | C++ | Planned |
| 6 | Lighting and textures | C++ | Planned |
| 7 | Ray tracing comparison (optional) | C++ | Planned |

## Build and Run

Requires `gcc` / `g++` on Linux. No external libraries.

Each file is self-contained and compiles on its own.

```bash
# C stages (example)
gcc -g -Wall -Wextra edgefunction.c -o edgefunction
./edgefunction

# C++ stages
g++ -g -Wall -Wextra math3d.cpp -o math3d
./math3d
```

PPM files can be opened with most image viewers.

## Files

| File | Description | Output |
|---|---|---|
| `framebuffer.c` | Stage 1: framebuffer and PPM writer | `output.ppm` |
| `drawline.c` | Stage 2: naive line drawing (baseline for comparison) | `draw_line_naive.ppm` |
| `bresenham.c` | Stage 2: Bresenham's line algorithm | `draw_line_bresenham.ppm` |
| `edgefunction.c` | Stage 3: filled triangles with edge functions, and color interpolation with barycentric coordinates | `edgefunction.ppm` |
| `math3d.cpp` | Stage 4: `Vec3`, `Vec4`, `Mat4` | prints to terminal |

## Design Decisions

- **Right-handed coordinate system.** Verified by checking that x × y = +z.
- **Edge functions instead of scanline.** Fewer special cases, and closer to how real GPUs rasterize triangles.
- **`w = 1` for points, `w = 0` for directions.** This way, translation only affects points.
- **Transforms are read from right to left:** `projection * view * model`.

## References

- [Computer Graphics from Scratch](https://gabrielgambetta.com/computer-graphics-from-scratch/) by Gabriel Gambetta
- [ssloy/tinyrenderer](https://github.com/ssloy/tinyrenderer)
