#include <iostream>
#include <array>
#include "framebuffer.h"
#include "raster.h"
#include "math3d.h"

using Tri = std::array<int, 3>;

bool check_winding(const std::array<Vec3, 8>& verts, const std::array<Tri, 12>& tris) {
    bool ok = true;
    for(size_t i = 0; i < tris.size(); i++) {
        const Vec3& a = verts[tris[i][0]];
        const Vec3& b = verts[tris[i][1]];
        const Vec3& c = verts[tris[i][2]];

        Vec3 n = (b - a).cross(c - a);
        Vec3 centroid = (a + b + c) * (1.0f / 3.0f);
        float d = n.dot(centroid);
        std::cout <<"i = " << i << ", d = " << d << (d > 0 ? ", PASS" : ", FAIL") << "\n";
        if(d <= 0) {
            ok = false;
        }
    }
    return ok;
}

int main() {
    Framebuffer fb(800, 600);

    fb.clear(Color{40, 40, 40});

    Mat4 M = Mat4::identity();
    Mat4 V = Mat4::lookAt(Vec3(3, 2, 4), Vec3(0, 0, 0), Vec3(0, 1, 0));
    Mat4 P = Mat4::perspective(Mat4::radians(60.0f), static_cast<float>(fb.width) / fb.height, 1.0f, 10.0f);

    Mat4 mvp = P * V * M;

    std::array<Vec3, 8> verts = {{
        {-1, -1, -1}, {1, -1, -1},
        {-1, 1, -1}, {1, 1, -1},
        {-1, -1, 1}, {1, -1, 1},
        {-1, 1, 1}, {1, 1, 1}
    }};

    std::array<Tri, 12> tris = {{
        {4, 5, 7}, {4, 7, 6},    // +z
        {0, 2, 3}, {0, 3, 1},    // -z
        {1, 3, 7}, {1, 7, 5},    // +x
        {0, 4, 6}, {0, 6, 2},    // -x
        {6, 7, 3}, {6, 3, 2},    // +y
        {4, 1, 5}, {4, 0, 1}     // -y
    }};

    if(!check_winding(verts, tris)) {
        return 1;
    }

    std::array<Vec3, 8> screen;

    for(size_t i = 0; i < verts.size(); i++) {
        Vec4 clip = mvp * Vec4::point(verts[i]);

        float x_ndc = clip.x / clip.w;
        float y_ndc = clip.y / clip.w;
        float z_ndc = clip.z / clip.w;

        float x_screen = (x_ndc + 1) * (fb.width * 0.5f);
        float y_screen = (1 - y_ndc) * (fb.height * 0.5f);
        float z_screen = z_ndc;

        screen[i] = {x_screen, y_screen, z_screen};

        std::cout << "clip.w = " << clip.w << ", screen " << i << " = ";
        screen[i].print();
    }

    fb.write_ppm("cube.ppm");

    return 0;
}
