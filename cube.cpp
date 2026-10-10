#include <cstdio>
#include "framebuffer.h"
#include "raster.h"

int main() {
    Framebuffer fb(200, 100);

    fb.clear(Color{40, 40, 40});

    draw_triangle(fb, Vec3{0, 0, 0}, Vec3{80, 80, 0}, Vec3{100, 40, 0}, Color{255, 0, 0});
    draw_triangle(fb, Vec3{120, 20, 0}, Vec3{190, 30, 0}, Vec3{150, 90, 0}, Color{0, 255, 0});
    draw_triangle(fb, Vec3{-30, 60, 0}, Vec3{40, 110, 0}, Vec3{60, 50, 0}, Color{0, 0, 255});
    draw_triangle(fb, Vec3{-50, 10, 0}, Vec3{-20, 10, 0}, Vec3{-30, 40, 0}, Color{100, 0, 0});
    draw_triangle(fb, Vec3{10, 50, 0}, Vec3{50, 50, 0}, Vec3{90 ,50, 0}, Color{0, 100, 0});
    draw_triangle(fb, Vec3{120, 20, 0}, Vec3{150, 90, 0}, Vec3{190, 30, 0}, Color{0, 0, 100});

    fb.write_ppm("cube.ppm");

    return 0;
}
