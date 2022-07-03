#pragma once

class Vector2
{
public:
	int x;
	int y;

	Vector2():x(0),y(0) {}

	Vector2(int x, int y) :x(x), y(y) {}

	Vector2 operator +(const Vector2& you) {
		Vector2 temp;
		temp.x = this->x + you.x;
		temp.y = this->y + you.y;
		return temp;
	}
	Vector2 operator -(const Vector2& you) {
		Vector2 temp;
		temp.x = this->x - you.x;
		temp.y = this->y - you.y;
		return temp;
	}
	bool operator ==(const Vector2& you) const {
		if (this->x == you.x) {
			if (this->y == you.y) {
				return true;
			}
		}
		return false;
	}
	bool operator <=(const Vector2& you) const {
		if (this->x <= you.x) {
			if (this->y <= you.y) {
				return true;
			}
		}
		return false;
	}
	bool operator <(const Vector2& you) const {
		if (this->y == you.y) return this->x < you.x;
		return this->y < you.y;
	}
	bool operator >=(const Vector2& you) const {
		if (this->x >= you.x) {
			if (this->y >= you.y) {
				return true;
			}
		}
		return false;
	}
	bool operator >(const Vector2& you) const {
		if (this->y == you.y) return this->x > you.x;
		return this->y > you.y;
	}
	void operator =(const Vector2& you) {
		this->x = you.x;
		this->y = you.y;
	}

	bool operator !=(const Vector2& you) const {
		if (this->x != you.x || this->y != you.y) {
			return true;
		}
		return false;
	}
};