/*********************************************************************
 *	Copyright 1992-2008, ZheJiang HuaRay Technology Stock Co.Ltd.
 *						All Rights Reserved
 *	@file 	    		Shape.h
 *	@author				dzf
 *	@brief				
 *  
 *
 *	@date	        	2017:5:23 
 *	@version			1.00.1
 *	@todo				
**********************************************************************/
#ifndef __SHAPE_H__
#define __SHAPE_H__

#include <cstdint>
#include <vector>

template <typename T>
class Point2D
{
public:
	/** 构造二维点数据 */
	Point2D();
	Point2D(const Point2D<T>& rhs);

	/** 构造二维点数据
	 *  
	 * @param [in] x x坐标
	 * @param [in] y y坐标
	 * @note  
	 */
	Point2D(T x, T y);
	
	void set(T x, T y);

	float distance(const Point2D<T>& rhs) const;

	~Point2D();
public:
	T x;
	T y;
};

template <typename T>
Point2D<T>::Point2D(const Point2D<T>& rhs)
{
	this->x = rhs.x;
	this->y = rhs.y;
}

template <typename T>
class Size2D
{
public:
	Size2D();
	Size2D(T width, T height);
	~Size2D();
public:
	T width;
	T height;
};


template <typename T>
void mvSplitSegment(const Point2D<T>& head, const Point2D<T>& tail, std::vector<Point2D<float>>& pts);

#endif // __SHAPE_H__