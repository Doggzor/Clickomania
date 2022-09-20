#pragma once
struct Vector2i
{
	Vector2i() : x(0), y(0) {}
	Vector2i(int x, int y) : x(x), y(y) {}

	Vector2i operator+(const Vector2i& other) const {
		return Vector2i(x + other.x, y + other.y);
	}
	Vector2i& operator+=(const Vector2i& other) {
		return *this = *this + other;
	}
	Vector2i operator-(const Vector2i& other) const {
		return Vector2i(x - other.x, y - other.y);
	}
	Vector2i& operator-=(const Vector2i& other) {
		return *this = *this - other;
	}
	Vector2i operator*(int n) const {
		return Vector2i(x * n, y * n);
	}
	Vector2i& operator*=(int n) {
		return *this = *this * n;
	}

	int x, y;
};
