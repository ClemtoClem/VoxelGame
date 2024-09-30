#ifndef MATH_VECTOR3D_HPP
#define MATH_VECTOR3D_HPP

#include <glm/glm.hpp>
#include <glm/gtx/quaternion.hpp>

template <typename T>
class Vector3D {
public:
    /**
     * Constructs a new Vector3D with the given values.
     * @param nx The x component of the vector.
     * @param ny The y component of the vector.
     * @param nz The z component of the vector.
     */
    constexpr Vector3D(T nx = 0.0f, T ny = 0.0f, T nz = 0.0f)
        : _x(nx), _y(ny), _z(nz) {}

    /**
     * Constructs a new Vector3D with the given value for all components.
     * @param n The value to set all components to.
     */
    constexpr Vector3D(T n): _x(n), _y(n), _z(n) {}

    /**
     * Constructs a new Vector3D from a glm::vec3.
     * @param v The glm::vec3 to construct from.
     */
    constexpr Vector3D(const glm::vec<3, T, glm::packed_highp>& v) : _x(v.x), _y(v.y), _z(v.z) {}

    /* Getters */
    
    T x() const { return _x; }
    T y() const { return _y; }
    T z() const { return _z; }
    glm::vec<3, T, glm::packed_highp> get() const {
        return glm::vec<3, T, glm::packed_highp>(_x, _y, _z);
    }

    /* Setters */
    
    void x(T nx) { _x = nx; }
    void y(T ny) { _y = ny; }
    void z(T nz) { _z = nz; }
    void set(T nx, T ny, T nz) { _x = nx; _y = ny; _z = nz; }
    void set(const glm::vec<3, T, glm::packed_highp>, & v) { _x = v.x; _y = v.y; _z = v.z; }
    void set(const Vector3D<T>& v) {
        _x = static_cast<T>(v._x);
        _y = static_cast<T>(v._y);
        _z = static_cast<T>(v._z);
    }

    /* Operators */

    /**
     * Adds the given vector to this vector.
     * @param v The vector to add.
     * @return The sum of the two vectors.
     */
    template <typename U>
    Vector3D<T> operator+(const Vector3D<U>& v) const {
        return Vector3D<T>(
            _x + static_cast<T>(v._x),
            _y + static_cast<T>(v._y),
            _z + static_cast<T>(v._z)
        );
    }

    /**
     * Adds the given vector from this vector.
     * @param v The vector to add.
     * @return Self.
     */
    template <typename U>
    Vector3D<T>& operator+=(const Vector3D<U>& v) const {
        _x += static_cast<T>(v._x);
        _y += static_cast<T>(v._y);
        _z += static_cast<T>(v._z);
        return *this;
    }

    /**
     * Subtracts the given vector from this vector.
     * @param v The vector to subtract.
     * @return The difference of the two vectors.
     */
    template <typename U>
    Vector3D<T> operator-(const Vector3D<U>& v) const {
        return Vector3D<T>(
            _x - static_cast<T>(v._x),
            _y - static_cast<T>(v._y),
            _z - static_cast<T>(v._z)
        );
    }

    /**
     * Subtracts the given vector from this vector.
     * @param v The vector to subtract.
     * @return Self.
     */
    template <typename U>
    Vector3D<T>& operator-=(const Vector3D<U>& v) const {
        _x -= static_cast<T>(v._x);
        _y -= static_cast<T>(v._y);
        _z -= static_cast<T>(v._z);
        return *this;
    }

    /**
     * Multiplies this vector by the given scalar.
     * @param s The scalar to multiply by.
     * @return The product of the vector and the scalar.
     */
    template <typename U>
    Vector3D<T> operator*(const U& s) const {
        return Vector3D<T>(
            _x * static_cast<T>(s),
            _y * static_cast<T>(s),
            _z * static_cast<T>(s)
        );
    }

    /**
     * Multiplies this vector by the given scalar.
     * @param s The scalar to multiply by.
     * @return Self.
     */
    template <template U>
    Vector3D<T>& operator*=(const U& s) const {
        _x *= static_cast<T>(s);
        _y *= static_cast<T>(s);
        _z *= static_cast<T>(s);
        return *this;
    }

    /**
     * Divides this vector by the given scalar.
     * @param s The scalar to divide by.
     * @return The quotient of the vector and the scalar.
     */
    template <typename U>
    Vector3D<T> operator/(const U& s) const {
        return Vector3D<T>(
            _x / static_cast<T>(s),
            _y / static_cast<T>(s),
            _z / static_cast<T>(s)
        );
    }

    /**
     * Divides this vector by the given scalar.
     * @param s The scalar to divide by.
     * @return Self.
     */
    template <template U>
    Vector3D<T>& operator/=(const U& s) const {
        _x /= static_cast<T>(s);
        _y /= static_cast<T>(s);
        _z /= static_cast<T>(s);
        return *this;
    }

    /**
     * Accesses the component at the given index.
     * @param i The index of the component to access.
     * @return The component at the given index.
     * @throws std::out_of_range If the index is out of range.
     */
    T operator[](size_t i) const {
        switch (i) {
            case 0: return _x;
            case 1: return _y;
            case 2: return _z;
            default: throw std::out_of_range("Index out of range");
        }
    }

    /**
     * Accesses the component at the given index.
     * @param i The index of the component to access.
     * @return The component at the given index.
     * @throws std::out_of_range If the index is out of range.
     */
    T& operator[](size_t i) {
        switch (i) {
            case 0: return _x;
            case 1: return _y;
            case 2: return _z;
            default: throw std::out_of_range("Index out of range");
        }
    }

    /* Comparison operators */

    /**
     * Compares this vector to the given vector.
     * @param v The vector to compare to.
     * @return True if the two vectors are equal, false otherwise.
     */
    template <typename U>
    constexpr bool operator==(const Vector3D<U>& v) const {
        return _x == static_cast<T>(v._x) && _y == static_cast<T>(v._y) && _z == static_cast<T>(v._z);
    }

    /**
     * Compares this vector to the given vector.
     * @param v The vector to compare to.
     * @return True if the two vectors are not equal, false otherwise.
     */
    template <typename U>
    constexpr bool operator!=(const Vector3D<U>& v) const {
        return _x != static_cast<T>(v._x) || _y != static_cast<T>(v._y) || _z != static_cast<T>(v._z);
    }

    /**
     * Compares this vector to the given vector.
     * @param v The vector to compare to.
     * @return True if this vector is less than the given vector, false otherwise.
     */
    template <template U>
    constexpr bool operator<(const Vector3D<U>& v) const {
        return _x < static_cast<T>(v._x) ||
            (_x == static_cast<T>(v._x) && _y < static_cast<T>(v._y)) ||
            (_x == static_cast<T>(v._x) && _y == static_cast<T>(v._y) && _z < static_cast<T>(v._z));
    }

    /**
     * Compares this vector to the given vector.
     * @param v The vector to compare to.
     * @return True if this vector is less than or equal to the given vector, false otherwise.
     */
    template <template U>
    constexpr bool operator<=(const Vector3D<U>& v) const {
        return _x <= static_cast<T>(v._x) ||
            (_x == static_cast<T>(v._x) && _y <= static_cast<T>(v._y)) ||
            (_x == static_cast<T>(v._x) && _y == static_cast<T>(v._y) && _z <= static_cast<T>(v._z));
    }

    /**
     * Compares this vector to the given vector.
     * @param v The vector to compare to.
     * @return True if this vector is greater than the given vector, false otherwise.
     */
    template <template U>
    constexpr bool operator>(const Vector3D<U>& v) const {
        return _x > static_cast<T>(v._x) ||
            (_x == static_cast<T>(v._x) && _y > static_cast<T>(v._y)) ||
            (_x == static_cast<T>(v._x) && _y == static_cast<T>(v._y) && _z > static_cast<T>(v._z));
    }

    /**
     * Compares this vector to the given vector.
     * @param v The vector to compare to.
     * @return True if this vector is greater than or equal to the given vector, false otherwise.
     */
    template <template U>
    constexpr bool operator>=(const Vector3D<U>& v) const {
        return _x >= static_cast<T>(v._x) ||
            (_x == static_cast<T>(v._x) && _y >= static_cast<T>(v._y)) ||
            (_x == static_cast<T>(v._x) && _y == static_cast<T>(v._y) && _z >= static_cast<T>(v._z));
    }

    /* Utility functions */

    /**
     * Returns the dot product of this vector and the given vector.
     * @param v The vector to dot with.
     * @return The dot product of the two vectors.
     */
    template <typename U>
    T dotProduct(const Vector3D<U>& v) const {
        return _x * static_cast<T>(v._x) + _y * static_cast<T>(v._y) + _z * static_cast<T>(v._z);
    }

    /**
     * Returns the cross product of this vector and the given vector.
     * @param v The vector to cross with.
     * @return The cross product of the two vectors.
     */
    template <typename U>
    Vector3D<T> crossProduct(const Vector3D<U>& v) const {
        return Vector3D<T>(
            _y * static_cast<T>(v._z) - _z * static_cast<T>(v._y),
            _z * static_cast<T>(v._x) - _x * static_cast<T>(v._z),
            _x * static_cast<T>(v._y) - _y * static_cast<T>(v._x)
        );
    }

    /**
     * Get length of the vector.
     * @return The length of the vector.
     */
    T length() const {
        return std::sqrt<T>(_x * _x + _y * _y + _z * _z);
    }

    /**
     * Get squared length of the vector.
     * @return The squared length of the vector.
     */
    T lengthSquared() const {
        return _x * _x + _y * _y + _z * _z;
    }

    /**
     * Normalizes this vector.
     * @return The normalized vector.
     */
    Vector3D<T> normalize() const {
        T len = length();
        if (len == 0) {
            return Vector3D<T>(0, 0, 0);
        }
        return Vector3D<T>(_x / len, _y / len, _z / len);
    }

    /**
     * Rotates the vector by a specified number of radians around the Y axis and the specified center.
     * @param angle The angle to rotate by.
     * @param center The center of the rotation.
     */
    Vector3D<T> rotateXZBy(double angle, const Vector3D<T>& center) const {
        double cos = std::cos(angle);
        double sin = std::sin(angle);
        T x = _x - center._x;
        T z = _z - center._z;
        Vector3D<T> result(
            x * cos - z * sin,
            center._y,
            x * sin + z * cos
        );
        result.x += center._x;
        result.z += center._z;
        return result;
    }

    /**
     * Rotates the vector by a specified number of radians around the X axis and the specified center.
     * @param angle The angle to rotate by.
     * @param center The center of the rotation.
     */
    Vector3D<T> rotateXY(double angle, const Vector3D<T>& center) const {
        double cos = std::cos(angle);
        double sin = std::sin(angle);
        T x = _x - center._x;
        T y = _y - center._y;
        Vector3D<T> result(
            x * cos - y * sin,
            x * sin + y * cos,
            _z
        );
        result.x += center._x;
        result.y += center._y;
        return result;
    }

    /**
     * Rotates the vector by a specified number of radians around the Z axis and the specified center.
     * @param angle The angle to rotate by.
     * @param center The center of the rotation.
     */
    Vector3D<T> rotateYZ(double angle, const Vector3D<T>& center) const {
        double cos = std::cos(angle);
        double sin = std::sin(angle);
        T y = _y - center._y;
        T z = _z - center._z;
        Vector3D<T> result(
            _x,
            y * cos - z * sin,
            y * sin + z * cos
        );
        result.y += center._y;
        result.z += center._z;
        return result;
    }

    /**
     * Creates an interpolated vector between this vector and another vector.
     * @param v The vector to interpolate to.
     * @param t The interpolation factor.
     * @return The interpolated vector.
     */
    template <typename U>
    Vector3D<T> interpolate(const Vector3D<U>& v, double t) const {
        double invT = 1.0 - t;
        return Vector3D<T>(
            _x * t + static_cast<T>(v._x) * invT,
            _y * t + static_cast<T>(v._y) * invT,
            _z * t + static_cast<T>(v._z) * invT
        );
    }

    /**
     * Creates a quadratically interpolated vector between this and two other vectors.
     * @param v1 The first vector to interpolate between.
     * @param v2 The second vector to interpolate between.
     * @param t The interpolation factor.
     */
    template <typename U, typename V>
    Vector3D<T> interpolateQuadratic(const Vector3D<U>& v1, const Vector3D<V>& v2, double t) const {
        double inv = 1.0 - t;
        double mul0 = inv * inv;
        double mul1 = 2.0 * inv * t;
        double mul2 = t * t;
        return Vector3D<T>(
            _x * mul0 + static_cast<T>(v1._x) * mul1 + static_cast<T>(v2._x) * mul2,
            _y * mul0 + static_cast<T>(v1._y) * mul1 + static_cast<T>(v2._y) * mul2,
            _z * mul0 + static_cast<T>(v1._z) * mul1 + static_cast<T>(v2._z) * mul2
        );
    }

    /**
     * Create a linearly interpolated vector between this and another vector.
     * @param v1 The first vector to interpolate with, maximum at 1.0f
     * @param v2 The second vector to interpolate with, maximum at 0.0f
     * @param t Interpolation value between 0.0f (all vector v1) and 1.0f (all vector v2)
     */
    template <typename U, typename V>
    Vector3D<T> interpolateLinear(const Vector3D<U>& v1, const Vector3D<V>& v2, double t) const {
        return Vector3D<T>(
            _x + static_cast<T>(v1._x) + (static_cast<T>(v1._x) - static_cast<T>(v2._x)) * t,
            _y + static_cast<T>(v1._y) + (static_cast<T>(v1._y) - static_cast<T>(v2._y)) * t,
            _z + static_cast<T>(v1._z) + (static_cast<T>(v1._z) - static_cast<T>(v2._z)) * t
        );
    }

    /**
     * Get the spherical coordinates of the vector.
     * @return The spherical coordinates of the Euler vector.
     * @note The returned vector is in the form of (azimuth, elevation, radius).
     */
    Vector3D<T> sphericalCoordinates() const {
        double azimuth = std::atan2(_y, _x);
        double elevation = std::atan2(_z, std::sqrt(_x * _x + _y * _y));
        double radius = std::sqrt(_x * _x + _y * _y + _z * _z);
        return Vector3D<T>(azimuth, elevation, radius);
    }

    /* Utility functions how to use the vector as a point */

    /**
     * Calculate distance from another point.
     * @param point The point to calculate the distance to.
     * @return The distance between the two points.
     * @note Here, the vector is interpreted as a point.
     */
    template <typename U>
    T distance(const Vector3D<U>& point) const {
        return (*this - point).length();
    }

    /**
     * Calculate squared distance from another point.
     * @param point The point to calculate the distance to.
     * @return The squared distance between the two points.
     * @note Here, the vector is interpreted as a point.
     */
    template <typename U>
    T distanceSquared(const Vector3D<U>& point) const {
        return (*this - point).lengthSquared();
    }

private:
    T _x, _y, _z;
};

#endif // MATH_VECTOR3D_HPP