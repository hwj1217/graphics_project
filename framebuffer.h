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

    void clear(Color c);
    void set_pixel(int x, int y, Color c);
    void write_ppm(const char* filename) const;
};

void set_pixel(int x, int y, Color c) {

}

void clear(Color c) {
    for(int y = 0; y < Framebuffer.height; y++) {
        for(int x = 0; x < Framebuffer.width; x++) {

        }
    }
}

void write_ppm(const char* filename) const {

}
