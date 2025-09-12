#pragma once

namespace sfr {
	template<typename T>
	struct Vector2 {
		Vector2() = default;
		Vector2(T _x, T _y) :
			x(_x), y(_y = 0) {
		}

		T x;
		T y;
	};

	template<typename T>
	struct Vector3 {
		Vector3() = default;
		Vector3(T _x, T _y, T _z) :
			x(_x), y(_y), z(_z) {
		}

		constexpr Vector3<T> operator+(const Vector3<T>& v) const {
			return { x + v.x, y + v.y, z + v.z };
		}

		constexpr Vector3<T>& operator+=(const Vector3<T>& v) {
			x += v.x;
			y += v.y;
			z += v.z;
			return *this;
		}

		constexpr Vector3<T>& operator-=(const Vector3<T>& v) {
			x -= v.x;
			y -= v.y;
			z -= v.z;
			return *this;
		}

		constexpr Vector3<T> operator-(const Vector3<T>& v) const {
			return { x - v.x, y - v.y, z - v.z };
		}

		constexpr Vector3<T> operator*(float scalar) const {
			return { x * scalar, y * scalar, z * scalar };
		}

		constexpr Vector3<T> operator/(float scalar) const {
			return { x / scalar, y / scalar, z / scalar };
		}

		constexpr Vector3<T> operator-() const {
			return { -x , -y , -z };
		}

		constexpr Vector3<T> cross(const Vector3<T>& v) const {
			return { y * v.z - z * v.y, z * v.x - x * v.z, x * v.y - y * v.x };
		}

		constexpr Vector3<T> operator^(const Vector3<T>& v) const {
			return cross(v);
		}

		constexpr bool operator==(const Vector3<T>& v) const {
			return x == v.x && y == v.y && z == v.z;
		}

		constexpr bool operator !=(const Vector3<T>& v) const {
			return !(*this == v);
		}

		constexpr float size() const {
			return sqrtf(x * x + y * y + z * z);
		}

		Vector3<T> normalize() const {
			float invLength = 1.0f / size();

			return{ x * invLength,
					y * invLength,
					z * invLength };
		}

		constexpr float dot(const Vector3<T>& v) const {
			return x * v.x + y * v.y + z * v.z;
		}

		constexpr float operator|(const Vector3<T>& v) const {
			return dot(v);
		}

		T x;
		T y;
		T z;
	};
}
