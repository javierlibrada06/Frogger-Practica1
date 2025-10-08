#pragma once
template <class T>
class Vector2D
{
	T x;
	T y;
	
public: 
	
	Vector2D() : x(0), y(0) {}
	Vector2D(T x, T y) : x(x), y(y) {}
	~Vector2D() delete;
	getX() return x;
	getY() return y;
	constexpr Vector2D Suma(Vector2D& constexpr s) {
		return Vector2D(this->x + s.x, this->y + s.y);
	}
	constexpr Vector2D Resta(Vector2D& constexpr) {
		return Vector2D(this->x - s.x, this->y - s.y);
	}
	T ProductoEscalar(Vector2D& constexpr) {
		return (this->x * s.x + this->y * s.y);
	}
	Vector2D ProductoEscalarPorVector(T& constexpr k) {
		return Vector2D(this->x * k, this->y * K);
	}
	Vector2D Point2D(int x, int y) {
		return Vector2D(x, y);
	}
};



