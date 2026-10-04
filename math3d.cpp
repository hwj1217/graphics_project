#include <cstdio>
#include <cmath>

constexpr float PI = 3.14159265f;

struct Vec3 {
    float x, y, z;

    Vec3() : x(0), y(0), z(0) {}
    Vec3(float x, float y, float z) : x(x), y(y), z(z) {}

    Vec3 operator+(const Vec3& v) const {   // 向量相加
        return Vec3(x + v.x, y + v.y, z + v.z);
    }
    Vec3 operator-(const Vec3& v) const {   // 向量相減
        return Vec3(x - v.x, y - v.y, z - v.z);
    }
    Vec3 operator*(float s) const {    // 向量縮放
        return Vec3(x * s, y * s, z * s);
    }
    float dot(const Vec3& v) const {    // 向量內積
        return (x * v.x + y * v.y + z * v.z);
    }
    float length() const {    // 向量長度
        return (std::sqrt(dot(*this)));    // dot(*this) 為跟自己內積
    }
    Vec3 normalize() const {
        float l = length();
        if(l < 1e-8f) {
            return Vec3(0.0f, 0.0f, 0.0f);
        }
        else{
            return Vec3(x / l, y / l, z / l);
        }
    }
    Vec3 cross(const Vec3& v) const {    // 向量cross
        return Vec3(y * v.z - z * v.y, z * v.x - x * v.z, x * v.y - y * v.x);
    }

    void print() const {
        printf("(%.2f %.2f %.2f)\n", x, y, z);
    }
};

struct Vec4 {
    float x, y, z, w;

    Vec4() : x(0), y(0), z(0), w(0) {}
    Vec4(float x, float y, float z, float w) : x(x), y(y), z(z), w(w) {}

    static Vec4 point(const Vec3& v) {    // w = 1
        return Vec4 (v.x, v.y, v.z, 1.0f);
    }

    static Vec4 direction(const Vec3& v) {    // w = 0
        return Vec4 (v.x, v.y, v.z, 0.0f);
    }

    void print() const {
        printf("(%.2f %.2f %.2f %.2f)\n", x, y, z, w);
    }
};

struct Mat4 {
    float m[4][4];

    Mat4() {
        for(int row = 0; row < 4; row++) {
            for(int col = 0; col < 4; col++) {
                m[row][col] = 0;
            }
        }
    }

    static Mat4 identity() {
        Mat4 result;
        for(int row = 0; row < 4; row++) {
            for(int col = 0; col < 4; col++) {
                if(row == col) {
                    result.m[row][col] = 1;
                }
            }
        }
        return result;
    }

    static Mat4 translate(float tx, float ty, float tz) {
        Mat4 result = Mat4::identity();
        result.m[0][3] = tx;
        result.m[1][3] = ty;
        result.m[2][3] = tz;
        return result;
    }

    static Mat4 scale(float sx, float sy, float sz) {
        Mat4 result = Mat4::identity();
        result.m[0][0] = sx;
        result.m[1][1] = sy;
        result.m[2][2] = sz;
        return result;
    }

    static Mat4 rotateZ(float angle) {
        Mat4 result = Mat4::identity();
        float c = std::cos(angle);
        float s = std::sin(angle);
        result.m[0][0] = c;
        result.m[0][1] = -s;
        result.m[1][0] = s;
        result.m[1][1] = c;
        return result;
    }

    static Mat4 perspective(float fov, float aspect, float n, float f) {
        float s = 1.0f / std::tan(fov / 2.0f);
        Mat4 result;
        result.m[0][0] = s / aspect;
        result.m[1][1] = s;
        result.m[2][2] = -(f + n) / (f - n);
        result.m[2][3] = -2.0f * f * n / (f - n);
        result.m[3][2] = -1.0f;
        return result;
    }

    static Mat4 lookAt(const Vec3& eye, const Vec3& target, const Vec3& up) {
        Vec3 f = (target - eye).normalize();
        Vec3 r = f.cross(up).normalize();
        Vec3 u = r.cross(f);

        Mat4 result = Mat4::identity();
        result.m[0][0] = r.x;
        result.m[0][1] = r.y;
        result.m[0][2] = r.z;
        result.m[0][3] = -r.dot(eye);
        result.m[1][0] = u.x;
        result.m[1][1] = u.y;
        result.m[1][2] = u.z;
        result.m[1][3] = -u.dot(eye);
        result.m[2][0] = -f.x;
        result.m[2][1] = -f.y;
        result.m[2][2] = -f.z;
        result.m[2][3] = f.dot(eye);

        return result;
    }

    void print() const {
        for(int row = 0; row < 4; row++) {
            for(int col = 0; col < 4; col++) {
                printf("%8.2f", m[row][col]);
            }
            printf("\n");
        }
        printf("\n");
    }

    Mat4 operator*(const Mat4& b) const {
        Mat4 result;
        for(int row = 0; row < 4; row++) {
            for(int col = 0; col < 4; col++) {
                for(int k = 0; k < 4; k++) {
                    result.m[row][col] += m[row][k] * b.m[k][col];
                }
            }
        }
        return result;
    }

    static float radians(float degrees) {
        return degrees * PI / 180.0f;
    }

    Vec4 operator*(const Vec4& v) const {
        Vec4 result;
        result.x = m[0][0] * v.x + m[0][1] * v.y + m[0][2] * v.z + m[0][3] * v.w;
        result.y = m[1][0] * v.x + m[1][1] * v.y + m[1][2] * v.z + m[1][3] * v.w;
        result.z = m[2][0] * v.x + m[2][1] * v.y + m[2][2] * v.z + m[2][3] * v.w;
        result.w = m[3][0] * v.x + m[3][1] * v.y + m[3][2] * v.z + m[3][3] * v.w;
        return result;
    }
};

int main() {
    Mat4 view3 = Mat4::lookAt(Vec3(5, 0, 0), Vec3(0, 0, 0), Vec3(0, 1, 0));
    view3.print();
    (view3 * Vec4::point(Vec3(0, 0, 0))).print();
    (view3 * Vec4::point(Vec3(0, 0, 1))).print();

    Mat4 P = Mat4::perspective(Mat4::radians(90.0f), 1.0f, 1.0f, 10.0f);
    P.print();

    float zs[] = {-1.0f, -5.5f, -10.0f};
    for(float z : zs) {
        Vec4 q = P * Vec4::point(Vec3(1, 1, z));
        printf("z = %6.2f -> ndc z = %.3f\n", z, q.z / q.w);
    }
    return 0;
}
