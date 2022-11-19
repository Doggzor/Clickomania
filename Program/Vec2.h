#pragma once
#include <cmath>
template<typename T>
struct Vec2
{
public:
	constexpr Vec2() : x((T)0), y((T)0) {}
	constexpr Vec2(T x, T y) : x(x), y(y) {}

	Vec2 operator+(const Vec2& other) const {
		return Vec2(x + other.x, y + other.y);
	}
	Vec2& operator+=(const Vec2& other) {
		return *this = *this + other;
	}
	Vec2 operator-(const Vec2& other) const {
		return Vec2(x - other.x, y - other.y);
	}
	Vec2& operator-=(const Vec2& other) {
		return *this = *this - other;
	}
	Vec2 operator*(T multiplicator) const {
		return Vec2(x * multiplicator, y * multiplicator);
	}
	Vec2& operator*=(T multiplicator) {
		return *this = *this * multiplicator;
	}
	Vec2 operator/(T divisor) const {
		return Vec2(x / divisor, y / divisor);
	}
	Vec2& operator/=(T divisor) {
		return *this = *this / divisor;
	}
	template<typename C>
	explicit operator Vec2<C>() const {
		return Vec2<C>((C)x, (C)y);
	}

	T GetLengthSq() const {
		return x * x + y * y;
	}
	T GetLength() const {
		return (T)sqrt(GetLengthSq());
	}	
	Vec2 Normalized() const {
		const T length = GetLength();
		if (length != (T)0) return *this * ((T)1 / length);
		else return *this;
	}
	Vec2& Normalize() {
		return *this = Normalized();
	}

	T x, y;
};

typedef Vec2<int> Vec2i;
typedef Vec2<float> Vec2f;