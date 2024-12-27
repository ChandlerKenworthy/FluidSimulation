#ifndef LINALG_HPP
#define LINALG_HPP

#include <iostream>

struct Vector2 {
    float x;
    float y;
    float mag = sqrtf(x * x + y * y);

    // Constructor for initalisation
    Vector2(float x = 0.0f, float y = 0.0f) : x(x), y(y) { }

    // Overloadedd addition of two vectors
    Vector2 operator+(const Vector2 &other) const {
        return Vector2(x + other.x, y + other.y);
    }

     // Overload += operator
    Vector2& operator+=(const Vector2& other) {
        x += other.x;
        y += other.y;
        return *this; // Return the updated object
    }

    // Overload -= operator
    Vector2& operator-=(const Vector2& other) {
        x -= other.x;
        y -= other.y;
        return *this; // Return the updated object
    }

    Vector2& operator*=(const float scalar) {
        x *= scalar;
        y *= scalar;
        return *this;
    }

    // Overload subtraction of two Vector2 objects
    Vector2 operator-(const Vector2 &other) const {
        return Vector2(x - other.x, y - other.y);
    }

     // Overload multiplication by a scalar (Vector2 * scalar)
    Vector2 operator*(const float scalar) const {
        return Vector2(x * scalar, y * scalar);
    }

    Vector2 operator/(const float scalar) const {
        return Vector2(x / scalar, y / scalar);
    }

    // Overload multiplication by a scalar (scalar * Vector2)
    friend Vector2 operator*(float scalar, const Vector2& vec) {
        return Vector2(vec.x * scalar, vec.y * scalar);
    }

    friend std::ostream& operator<<(std::ostream& os, const Vector2& vec) {
        os << "(" << vec.x << ", " << vec.y << ")";
        return os;
    }
};

const Vector2 VEC_DOWN(0.0, -1.0);
const Vector2 VEC_UP(0.0, 1.0);
const Vector2 VEC_ONES(1.0, 1.0);

#endif