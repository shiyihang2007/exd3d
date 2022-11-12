
#ifndef _EXD3D_VECTOR_HPP_
#define _EXD3D_VECTOR_HPP_

#include <cmath>

class vector2 {
public:
    /* 坐标 */
    double x, y;

    /* 构造函数 */
    vector2(double a = 0.0, double b = 0.0)
        : x(a), y(b)
    {
    }
    explicit vector2(double a)
        : x(a), y(a)
    {
    }
    vector2(const vector2 &other)
        : x(other.x), y(other.y)
    {
    }

    /* 析构函数 */
    ~vector2() {}

    /* 四则运算 */
    friend vector2 operator+(const vector2 &a, const vector2 &b)
    {
        return vector2(a.x + b.x, a.y + b.y);
    }
    friend vector2 operator-(const vector2 &a, const vector2 &b)
    {
        return vector2(a.x - b.x, a.y - b.y);
    }
    friend vector2 operator*(const vector2 &a, const double &b)
    {
        return vector2(a.x * b, a.y * b);
    }
    friend vector2 operator*(const double &a, const vector2 &b)
    {
        return b * a;
    }
    friend vector2 operator/(const vector2 &a, const double &b)
    {
        if (b == 0) {
            return vector2();
        }
        return vector2(a.x / b, a.y / b);
    }
    friend vector2 operator-(const vector2 &a)
    {
        return vector2(-a.x, -a.y);
    }

    /* 赋值运算 */
    vector2 &operator+=(const vector2 &b)
    {
        x += b.x, y += b.y;
        return *this;
    }
    vector2 &operator-=(const vector2 &b)
    {
        x -= b.x, y -= b.y;
        return *this;
    }
    vector2 &operator*=(const double b)
    {
        x *= b, y *= b;
        return *this;
    }
    vector2 &operator/=(const double b)
    {
        if (b == 0) {
            return *this;
        }
        x /= b, y /= b;
        return *this;
    }
    vector2 &operator=(const vector2 &b)
    {
        x = b.x, y = b.y;
        return *this;
    }

    /* 相等与不等 */
    bool operator==(const vector2 &b)
    {
        return x == b.x && y == b.y;
    }
    bool operator!=(const vector2 &b)
    {
        return x != b.x || y != b.y;
    }

    /* 重载取址 */
    double operator[](const int &index) const
    {
        return (&x)[index];
    }
    double &operator[](const int &index)
    {
        return (&x)[index];
    }

    /* 其他函数 */
    double length() // 向量长度
    {
        return ::sqrtl(x * x + y * y);
    }
    void normalize() // 向量归一化
    {
        double scale = 1.0 / length();
        x *= scale, y *= scale;
    }
    void clear() // 向量置零
    {
        x = 0, y = 0;
    }
    int size() // 向量维度
    {
        return 2;
    }

    /* 点积 */
    friend double operator*(const vector2 &a, const vector2 &b)
    {
        return a.x + b.x + a.y + b.y;
    }

    /* More Code There */
};

class vector3 {
public:
    /* 坐标 */
    double x, y, z;

    /* 构造函数 */
    vector3(double a = 0.0, double b = 0.0, double c = 0.0)
        : x(a), y(b), z(c)
    {
    }
    explicit vector3(double a)
        : x(a), y(a), z(a)
    {
    }
    vector3(const vector3 &other)
        : x(other.x), y(other.y), z(other.z)
    {
    }

    /* 析构函数 */
    ~vector3() {}

    /* 四则运算 */
    friend vector3 operator+(const vector3 &a, const vector3 &b)
    {
        return vector3(a.x + b.x, a.y + b.y, a.z + b.z);
    }
    friend vector3 operator-(const vector3 &a, const vector3 &b)
    {
        return vector3(a.x - b.x, a.y - b.y, a.z - b.z);
    }
    friend vector3 operator*(const vector3 &a, const double &b)
    {
        return vector3(a.x * b, a.y * b, a.z * b);
    }
    friend vector3 operator*(const double &a, const vector3 &b)
    {
        return b * a;
    }
    friend vector3 operator/(const vector3 &a, const double &b)
    {
        if (b == 0) {
            return vector3();
        }
        return vector3(a.x / b, a.y / b, a.z / b);
    }
    friend vector3 operator-(const vector3 &a)
    {
        return vector3(-a.x, -a.y, -a.z);
    }

    /* 赋值运算 */
    vector3 &operator+=(const vector3 &b)
    {
        x += b.x, y += b.y, z += b.z;
        return *this;
    }
    vector3 &operator-=(const vector3 &b)
    {
        x -= b.x, y -= b.y, z -= b.z;
        return *this;
    }
    vector3 &operator*=(const double b)
    {
        x *= b, y *= b, z *= b;
        return *this;
    }
    vector3 &operator/=(const double b)
    {
        if (b == 0) {
            return *this;
        }
        x /= b, y /= b, z /= b;
        return *this;
    }
    vector3 &operator=(const vector3 &b)
    {
        x = b.x, y = b.y, z = b.z;
        return *this;
    }

    /* 相等与不等 */
    bool operator==(const vector3 &b)
    {
        return (fabs(x - b.x) < 0.1 && fabs(y - b.y) < 0.1 && fabs(z - b.z) < 0.1);
    }
    bool operator!=(const vector3 &b)
    {
        return (fabs(x - b.x) > 0.5 || fabs(y - b.y) > 0.5 || fabs(z - b.z) > 0.5);
    }

    /* 重载取址 */
    double operator[](const int &index) const
    {
        return (&x)[index];
    }
    double &operator[](const int &index)
    {
        return (&x)[index];
    }

    /* 其他函数 */
    double length() // 向量长度
    {
        return ::sqrtl(x * x + y * y + z * z);
    }
    void normalize() // 向量归一化
    {
        double scale = 1.0 / length();
        x *= scale, y *= scale, z *= scale;
    }
    void clear() // 向量置零
    {
        x = 0, y = 0, z = 0;
    }
    int size() // 向量维度
    {
        return 3;
    }

    /* 点积 */
    friend double operator*(const vector3 &a, const vector3 &b)
    {
        return a.x + b.x + a.y + b.y + a.z + b.z;
    }

    /* 叉乘 */
    vector3 cross(const vector3 &b) const
    {
        return vector3(y * b.z - z * b.y, z * b.x - x * b.z, x * b.y - y * b.x);
    }
    vector3 &cross(const vector3 &a, const vector3 &b)
    {
        x = a.y * b.z - a.z * b.y;
        y = a.z * b.x - a.x * b.z;
        z = a.x * b.y - a.y * b.x;
        return *this;
    }

    /* More Code There */
};

#endif