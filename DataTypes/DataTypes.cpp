#pragma once
#include "DataTypes.h"

Vector3::Vector3() :x(0), y(0), z(0) {};
Vector3::Vector3(double _x, double _y, double _z)
{
	x = _x;
	y = _y;
	z = _z;
}
Vector3::Vector3(Vector3& other)
{
	this->x = other.x;
	this->y = other.y;
	this->z = other.z;
}
Vector3::Vector3(Vector3&& other) noexcept
{
	this->x = other.x;
	this->y = other.y;
	this->z = other.z;

	other.x = 0;
	other.y = 0;
	other.z = 0;
}

Vector3& Vector3::operator=(const Vector3& other)
{
	this->x = other.x;
	this->y = other.y;
	this->z = other.z;

	return *this;
}

Vector3& Vector3::operator+(const Vector3& other)
{
	Vector3* new_vector = new Vector3(this->x + other.x, this->y + other.y, this->z + other.z);
	return *new_vector;
}
Vector3& Vector3::operator-(const Vector3& other)
{
	Vector3* new_vector = new Vector3(this->x - other.x, this->y - other.y, this->z - other.z);
	return *new_vector;
}

Vector3& Vector3::operator*(double value)
{
	Vector3* new_vector = new Vector3(this->x * value, this->y * value, this->z * value);
	return *new_vector;
}
Vector3& Vector3::operator/(double value)
{
	Vector3* new_vector = new Vector3(this->x / value, this->y / value, this->z / value);
	return *new_vector;
}

bool Vector3::operator==(const Vector3& other)
{
	if (this->x == other.x && this->y == other.y && this->z == other.z)
	{
		return true;
	}
	return false;
}
bool Vector3::operator!=(const Vector3& other)
{
	if (this->x != other.x || this->y != other.y || this->z != other.z)
	{
		return true;
	}
	return false;
}