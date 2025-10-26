#pragma once

#include "fpm/fixed.hpp"
#include "fpm/math.hpp"

namespace RJPhysics
{
	struct Vec2
	{
		fpm::q16_16 x;
		fpm::q16_16 y;

		// CONSTRUCTORS
		Vec2() {
			this->x = fpm::q16_16(0);
			this->y = fpm::q16_16(0);
		}
		Vec2(fpm::q16_16 x, fpm::q16_16 y) {
			this->x = x;
			this->y = y;
		}

		// SHORTHANDS
		static const Vec2 Up;
		static const Vec2 Down;
		static const Vec2 Right;
		static const Vec2 Left;
		static const Vec2 Zero;

		// OPERATIONS
		inline static fpm::q16_16 Dot(Vec2 a, Vec2 b) {
			return (a.x * b.x) + (a.y * b.y);
		}
		inline static fpm::q16_16 Cross(Vec2 a, Vec2 b) {
			return (a.x * b.y) - (a.y * b.x);
		}
		inline static fpm::q16_16 Length(Vec2 a) {
			return sqrt((a.x * a.x) + (a.y * a.y));
		}
		inline static fpm::q16_16 Distance(Vec2 a, Vec2 b) {
			return Vec2::Length(a - b);
		}
		inline static Vec2 Normalize(Vec2 a) {
			fpm::q16_16 len = Vec2::Length(a);
			return Vec2((a.x / len), (a.y / len));
		}

		// OPERATOR OVERLOADS

		// vector-vector operations
		inline Vec2 operator +(Vec2 other) {
			return Vec2(this->x + other.x, this->y + other.y);
		}
		inline Vec2 operator -(Vec2 other) {
			return Vec2(this->x - other.x, this->y - other.y);
		}
		inline Vec2 operator *(Vec2 other) {
			return Vec2(this->x * other.x, this->y * other.y);
		}
		inline Vec2 operator /(Vec2 other) {
			return Vec2(this->x / other.x, this->y / other.y);
		}

		// vector-scalar operations
		inline Vec2 operator +(fpm::q16_16 a) {
			return Vec2(this->x + a, this->y + a);
		}
		inline Vec2 operator -(fpm::q16_16 a) {
			return Vec2(this->x - a, this->y - a);
		}
		inline Vec2 operator *(fpm::q16_16 a) {
			return Vec2(this->x * a, this->y * a);
		}
		inline Vec2 operator /(fpm::q16_16 a) {
			return Vec2(this->x / a, this->y / a);
		}
	};

	// SHORTHANDS

	inline const Vec2 Vec2::Up = Vec2(fpm::q16_16(0), fpm::q16_16(1));
	inline const Vec2 Vec2::Down = Vec2(fpm::q16_16(0), fpm::q16_16(-1));
	inline const Vec2 Vec2::Right = Vec2(fpm::q16_16(1), fpm::q16_16(0));
	inline const Vec2 Vec2::Left = Vec2(fpm::q16_16(-1), fpm::q16_16(0));
	inline const Vec2 Vec2::Zero = Vec2(fpm::q16_16(0), fpm::q16_16(0));
}