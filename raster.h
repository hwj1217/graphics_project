#pragma once

#include <algorithm>
#include "framebuffer.h"
#include "math3d.h"

inline float edge_function(const Vec3& a, const Vec3& b, const Vec3& p) {
    return (b.x - a.x) * (p.y - a.y) - (b.y - a.y) * (p.x - a.x);
}

inline void draw_triangle(Framebuffer& fb, const Vec3& v0, const Vec3& v1, const Vec3& v2, Color c) {
    int max_x = static_cast<int> (std::max({v0.x, v1.x, v2.x}));
    int max_y = static_cast<int> (std::max({v0.y, v1.y, v2.y}));
    int min_x = static_cast<int> (std::min({v0.x, v1.x, v2.x}));
    int min_y = static_cast<int> (std::min({v0.y, v1.y, v2.y}));

    if(min_x < 0) {
        min_x = 0;
    }
    if(min_y < 0) {
        min_y = 0;
    }
    if(max_x >= fb.width) {
        max_x = fb.width - 1;
    }
    if(max_y >= fb.height) {
        max_y = fb.height - 1;
    }

    for(int y = min_y; y <= max_y; y++) {
        for(int x = min_x; x <= max_x; x++) {
            Vec3 p = Vec3{x + 0.5f, y + 0.5f, 0.0f};

            float e0 = edge_function(v1, v2, p);
            float e1 = edge_function(v2, v0, p);
            float e2 = edge_function(v0, v1, p);

            if((e0 >= 0 && e1 >= 0 && e2 >= 0) || (e0 <= 0 && e1 <= 0&& e2 <= 0)) {
                fb.set_pixel(x, y, c);
            }
        }
    }
}
