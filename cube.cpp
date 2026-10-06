#include <cstdio>
#include "framebuffer.h"

int main() {
    Framebuffer fb(800, 600);

    fb.clear(Color{255, 255, 255});
    for(int y = 0; y < 200; y++) {
        for(int x = 0; x < 200; x++) {
            fb.set_pixel(x, y, Color{255, 0, 0});
        }
    }

    fb.write_ppm("cube.ppm");

    return 0;
}
