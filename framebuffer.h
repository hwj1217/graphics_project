#pragma once
#include <vector>
#include <cstdint>
#include <cstdio>

struct Color {
    uint8_t r, g, b;
};

struct Framebuffer {
    int width, height;
    std::vector<uint8_t> pixels;

    Framebuffer(int w, int h) : width(w), height(h), pixels(w * h * 3, 0) {}

    void set_pixel(int x, int y, Color c) {
        if(x < 0 || y < 0 || x >= width || y >= height) {
            return;
        }

        int index = (y * width + x) * 3;
        pixels[index] = c.r;
        pixels[index + 1] = c.g;
        pixels[index + 2] = c.b;
    }

    void clear(Color c) {
        for(int y = 0; y < height; y++) {
            for(int x = 0; x < width; x++) {
                set_pixel(x, y, c);
            }
        }
    }

    void write_ppm(const char* filename) const {
        FILE* fp = fopen(filename, "wb");
        if(fp == nullptr) {
            return;
        }

        fprintf(fp, "P6\n%d %d\n255\n", width, height);

        fwrite(pixels.data(), 1, pixels.size(), fp);

        fclose(fp);
    }
};
