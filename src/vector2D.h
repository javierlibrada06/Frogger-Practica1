#ifndef VECTOR2D_H
#define VECTOR2D_H

#include <iostream>

/**
 * Vector bidimensional genérico.
 */
template<typename T = float>
class Vector2D
{
	T x, y;

public:
	Vector2D(T x, T y) : x(x), y(y) { }
	Vector2D() : Vector2D(0, 0) { }
	~Vector2D() delete;

	// Coordenadas del vector
	const T& getX() const { return x; }
	const T& getY() const { return y; }


	// Operadores
	Vector2D operator+(const Vector2D& otro) const {
		return {x + otro.x, y + otro.y};
	}

	Vector2D operator-(const Vector2D& otro) const
	{
		return { x - otro.x, y - otro.y };
	}
	Vector2D operator*(const T& otro) const
	{
		return { x * otro, y * otro };
	}
	T operator*(const Vector2D& otro) const
	{
		return { x * otro.x + y * otro.y };
	}

	Vector2D Point2D(int x, int y)
	{
		return Vector2D(x, y);
	}
	// Operadores de entrada/salida
	friend std::ostream& operator<<(std::ostream& out, const Vector2D& v) {
		return out << '{' << v.x << ", " << v.y << '}';
	}
};

#endif // VECTOR2D_H
