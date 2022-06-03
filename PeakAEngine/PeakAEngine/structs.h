#pragma once


struct Rectf
{
	float x, y;
	float width, height;
};

struct Color4f
{
	float r, g, b, a;
};

struct Vector2f
{
	Vector2f operator+(const Vector2f& other)
	{return { x + other.x, y + other.y };}
	Vector2f operator*(float multiplier)
	{return { x * multiplier, y * multiplier };}
	float x, y;
};
struct Vector3f
{
	float x, y, z;
};