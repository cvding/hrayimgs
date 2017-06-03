#include <Affine.h>
#include <cmath>
#include "Shape.h"

Affine::Affine()
{
	for (int32_t i = 0; i < 2; i++)
	{
		for (int32_t r = 0; r < 2; r++)
		{
			for (int32_t c = 0; c < 2; c++)
			{
				m_a[i][r][c] = 0;
			}
		}
		m_t[i][0] = 0;
		m_t[i][1] = 0;
	}

	m_a[0][0][0] = 1;
	m_a[0][1][1] = 1;

	m_a[1][0][0] = 1;
	m_a[1][1][1] = 1;
}

Affine::Affine(float x, float y, float rotate /*= 0.f*/, float skew /*= 0.f*/, 
			   float aspect /*= 1.f*/, float scale /*= 1.f*/)
{
	reset(x, y, rotate, skew, aspect, scale);
}

Affine::Affine(const Affine& rhs)
{
	for (int32_t i = 0; i < 2; i++)
	{
		for (int32_t r = 0; r < 2; r++)
		{
			for (int32_t c = 0; c < 2; c++)
			{
				m_a[i][r][c] = rhs.m_a[i][r][c];
			}
		}
		m_t[i][0] = rhs.m_t[i][0];
		m_t[i][1] = rhs.m_t[i][1];
	}
}

Affine::~Affine()
{
	for (int32_t i = 0; i < 2; i++)
	{
		for (int32_t r = 0; r < 2; r++)
		{
			for (int32_t c = 0; c < 2; c++)
			{
				m_a[i][r][c] = 0;
			}
		}
		m_t[i][0] = 0;
		m_t[i][1] = 0;
	}

	m_a[0][0][0] = 1;
	m_a[0][1][1] = 1;

	m_a[1][0][0] = 1;
	m_a[1][1][1] = 1;
}

void Affine::reset(float x, float y, float rotate /*= 0.f*/, float skew /*= 0.f*/, float aspect /*= 1.f*/, float scale /*= 1.f*/)
{
	float r, q;
	float a, b, c, d;
	float det;
	float ratio;

	r = -rotate;
	q = -skew;

	a = scale * cosf(r);
	b = -scale * aspect * sinf(r + q);
	c = scale * sinf(r);
	d = scale * aspect * cosf(r + q);

	m_a[0][0][0] = a;
	m_a[0][0][1] = b;
	m_a[0][1][0] = c;
	m_a[0][1][1] = d;
	m_t[0][0] = -(a * x + b * y);
	m_t[0][1] = -(c * x + d * y);


	det = m_a[0][0][0] * m_a[0][1][1] - m_a[0][0][1] * m_a[0][1][0];
	ratio = 1.f / det;

	a = m_a[0][1][1] * ratio;
	b = -m_a[0][0][1] * ratio;
	c = -m_a[0][1][0] * ratio;
	d = m_a[0][0][0] * ratio;

	m_a[1][0][0] = a;
	m_a[1][0][1] = b;
	m_a[1][1][0] = c;
	m_a[1][1][1] = d;

	m_t[1][0] = -(a * m_t[0][0] + b * m_t[0][1]);
	m_t[1][1] = -(c * m_t[0][0] + d * m_t[0][1]);
}

void Affine::map(int32_t isInv, const Point2D<float> src, Point2D<float>& dst)
{
	int32_t idx = (isInv == 1);

	dst.x = src.x * m_a[idx][0][0] + src.y * m_a[idx][0][1] + m_t[idx][0];
	dst.y = src.x * m_a[idx][1][0] + src.y * m_a[idx][1][1] + m_t[idx][1];
}

template <typename T>
Rotate2D<T>::Rotate2D(float r /*= 0.f*/, float s /*= 0.f*/)
{
	reset(r, s);
}


template <typename T>
Rotate2D<T>::~Rotate2D()
{
	m_a[0][0] = 1;
	m_a[0][1] = 0;
	m_a[1][0] = 0;
	m_a[1][1] = 1;
}


template <typename T>
void Rotate2D<T>::reset(float r, float q /*= 0.f*/)
{
	float a, b, c, d;

	r = -r;
	q = -q;

	a = cosf(r);
	b = -sinf(r + q);
	c = sinf(r);
	d = cosf(r + q);

	m_a[0][0] = a;
	m_a[0][1] = b;
	m_a[1][0] = c;
	m_a[1][1] = d;
}

template <typename T>
Point2D<float> Rotate2D<T>::rotate(const Point2D<T>& src, const Point2D<T>& center)
{
	Point2D<float> dst;
	Point2D<T> temp(src);

	temp.x -= center.x;
	temp.y -= center.y;

	dst.x = static_cast<float>(temp.x * m_a[0][0] + temp.y * m_a[0][1] + center.x);
	dst.y = static_cast<float>(temp.x * m_a[1][0] + temp.y * m_a[1][1] + center.y);

	return dst;
}


template <typename T>
Vector2D<T>::Vector2D(float angle, float length /*= 1.f*/) : m_dx(0), m_dy(0)
{
	m_dx = cosf(angle) * length;
	m_dy = sinf(angle) * length;
}


template <typename T>
Vector2D<T>::Vector2D(const Vector2D<T>& rhs)
{
	m_dx = rhs.m_dx;
	m_dy = rhs.m_dy;
}


template <typename T>
Vector2D<T>::~Vector2D()
{
	m_dx = 0;
	m_dy = 0;
}


template <typename T>
Point2D<float> Vector2D<T>::move(const Point2D<T>& src) const
{
	Point2D<float> dst;

	dst.x = static_cast<float>(src.x + m_dx);
	dst.y = static_cast<float>(src.y + m_dy);

	return dst;
}



template class Rotate2D<float>;
template class Rotate2D<int32_t>;

template class Vector2D<float>;
template class Vector2D<int32_t>;
