/*********************************************************************
 *	Copyright 1992-2008, ZheJiang HuaRay Technology Stock Co.Ltd.
 *						All Rights Reserved
 *	@file 	    		Affine.h
 *	@author				dzf
 *	@brief				
 *  
 *
 *	@date	        	2017:5:23 
 *	@version			1.00.1
 *	@todo				
**********************************************************************/
#ifndef __AFFINE_H__
#define __AFFINE_H__

#include <cstdint>

template <typename T> class Point2D;

class Affine
{
public:
	/** 构造仿射矩阵，恒等变换 */
	Affine();
	
	/** 设置仿射参数
	*
	* @param [in] x 平移坐标x
	* @param [in] y 平移坐标y
	* @param [in] rotate 旋转角度
	* @param [in] skew 错切角度
	* @param [in] aspect y/x的比率
	* @param [in] scale x,y缩放
	*/
	Affine(float x, float y, float rotate = 0.f, float skew = 0.f, 
		   float aspect = 1.f, float scale = 1.f);
	
	Affine(const Affine& rhs);
	~Affine();

	/** 重新设置仿射参数
	 *  
	 * @param [in] x 平移坐标x
	 * @param [in] y 平移坐标y
	 * @param [in] rotate 旋转角度
	 * @param [in] skew 错切角度
	 * @param [in] aspect y/x的比率
	 * @param [in] scale x,y缩放
	 * @return void 
	 * @note  
	 */
	void reset(float x, float y, float rotate = 0.f, float skew = 0.f, 
			   float aspect = 1.f, float scale = 1.f);

	/** 点映射
	 *  
	 * @param [in] isInv 是否为逆映射
	 * @param [in] src 输入点
	 * @param [out] dst 输出点
	 * @return void 
	 * @note  
	 */
	void map(int32_t isInv,const Point2D<float> src, Point2D<float>& dst);

protected:
private:
	float m_a[2][2][2];
	float m_t[2][2];
};

template <typename T>
class Rotate2D
{
public:
	Rotate2D(float r = 0.f,float s = 0.f);
	~Rotate2D();
	void reset(float r, float q = 0.f);

	/** 旋转点
	 *  
	 * @param [in] src 输入点 
	 * @param [in] org 原点
	 * @return Point2D<float> 旋转后坐标
	 * @note  
	 */
	Point2D<float> rotate(const Point2D<T>& src, const Point2D<T>& org);

protected:
private:
	float m_a[2][2];
};

template <typename T>
class Vector2D
{
public:
	Vector2D(float angle, float length = 1.f);
	
	Vector2D(const Vector2D<T>& rhs);
	
	~Vector2D();
	
	Point2D<float> move(const Point2D<T>& src) const;
protected:
private:
	float m_dx;
	float m_dy;
};

#endif // __AFFINE_H__