#include <iostream>
#include <array>
#include "framebuffer.h"
#include "raster.h"
#include "math3d.h"

int main() {
    Framebuffer fb(200, 100);

    fb.clear(Color{40, 40, 40});

    std::array<Vec3, 8> verts = {{
        {-1, -1, -1}, {1, -1, -1},
        {-1, 1, -1}, {1, 1, -1},
        {-1, -1, 1}, {1, -1, 1},
        {-1, 1, 1}, {1, 1, 1}
    }};

    std::array<std::array<int, 3>, 12> tris = {{
        {4, 5, 7}, {4, 7, 6},    // +z
        {0, 2, 3}, {0, 3, 1},    // -z
        {1, 3, 7}, {1, 7, 5},    // +x
        {0, 4, 6}, {0, 6, 2},    // -x
        {6, 7, 3}, {6, 3, 2},    // +y
        {4, 1, 5}, {4, 0, 1}     // -y
    }};

    for(size_t i = 0; i < tris.size(); i++) {
        const Vec3& a = verts[tris[i][0]];
        const Vec3& b = verts[tris[i][1]];
        const Vec3& c = verts[tris[i][2]];

        Vec3 n = (b - a).cross(c - a);
        Vec3 centroid = (a + b + c) * (1.0f / 3.0f);
        float d = n.dot(centroid);

        std::cout << "tri" << i << " d = " << d << (d > 0 ? " PASS\n" : " FAIL\n");
    }

    fb.write_ppm("cube.ppm");

    return 0;
}
