#pragma once


class Vector3
{
public:
	double x;
	double y;
	double z;

	Vector3();
	Vector3(double _x, double _y, double _z);
	Vector3(Vector3& other);
	Vector3(Vector3&& other) noexcept;
	~Vector3() = default;

	Vector3& operator=(const Vector3& other);

	Vector3& operator+(const Vector3& other);
	Vector3& operator-(const Vector3& other);

	Vector3& operator*(double value);
	Vector3& operator/(double value);

	bool operator==(const Vector3& other);
	bool operator!=(const Vector3& other);

};