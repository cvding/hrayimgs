#include "Shape.h"
#include <cmath>

template <typename T>
Point2D<T>::Point2D() :x(0), y(0)
{

}

template <typename T>
Point2D<T>::Point2D(T x, T y)
{
	this->x = x;
	this->y = y;
}


template <typename T>
Point2D<T>::~Point2D()
{
	this->x = -1;
	this->y = -1;
}


template <typename T>
void Point2D<T>::set(T x, T y)
{
	this->x = x;
	this->y = y;
}

template <typename T>
float Point2D<T>::distance(const Point2D<T>& rhs) const
{
	float dx = static_cast<float>(rhs.x - this->x);
	float dy = static_cast<float>(rhs.y - this->y);
	return sqrtf(dx*dx + dy*dy);
}


template <typename T>
Size2D<T>::Size2D() :width(0), height(0)
{
	
}


template <typename T>
Size2D<T>::Size2D(T width, T height)
{
	this->width = width;
	this->height = height;
}


template <typename T>
Size2D<T>::~Size2D()
{
	this->width = 0;
	this->height = 0;
}



template <typename T>
void mvSplitSegment(const Point2D<T>& head, const Point2D<T>& tail, std::vector<Point2D<float>>& pts)
{
	float x, y;
	float dx, dy;
	Point2D<float> temp;
	int32_t dis = static_cast<int32_t>(head.distance(tail));

	dx = static_cast<float>((tail.x - head.y) / dis);
	dy = static_cast<float>((tail.y - head.y) / dis);

	pts.clear();
	x = static_cast<float>(head.x);
	y = static_cast<float>(head.y);
	for (int32_t i = 0; i < dis; i++)
	{
		temp.set(x, y);
		pts.push_back(temp);
		x += dx;
		y += dy;
	}
}




template void mvSplitSegment<float>(const Point2D<float>& head, const Point2D<float>& tail, std::vector<Point2D<float>>&);
template void mvSplitSegment<int32_t>(const Point2D<int32_t>& head, const Point2D<int32_t>& tail, std::vector<Point2D<float>>&);

template class Point2D<float>;
template class Point2D<double>;
template class Point2D<int32_t>;
template class Point2D<int16_t>;

template class Size2D<float>;
template class Size2D<double>;
template class Size2D<int16_t>;
template class Size2D<int32_t>;
