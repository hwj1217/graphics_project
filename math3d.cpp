#include <cstdio>
#include <cmath>

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
        return (sqrtf(dot(*this)));    // dot(*this) 為跟自己內積
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
};

struct Vec4 {
    float x, y, z, w;

    Vec4() : x(0), y(0), z(0), w(0) {}
    Vec4(float x, float y, float z, float w) : x(x), y(y), z(z), w(w) {}

    static Vec4 point(const Vec3& v) {    // w = 1
        return Vec4 (v.x, v.y, v.z, 1.0);
    }

    static Vec4 direction(const Vec3& v) {    // w = 0
        return Vec4 (v.x, v.y, v.z, 0.0);
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
        result.m[0][0] = cosf(angle);
        result.m[0][1] = -sinf(angle);
        result.m[1][0] = sinf(angle);
        result.m[1][1] = cosf(angle);
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
        return degrees * (float)M_PI / 180.0f;
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

int main(void) {
    Mat4 T = Mat4::translate(5, 0, 0);
    Mat4 R = Mat4::rotateZ(Mat4::radians(90));
    Vec4 p = Vec4::point(Vec3(1, 0, 0));

    Vec4 a = T * R * p;
    Vec4 b = R * T * p;

    a.print();
    b.print();
    return 0;
}
