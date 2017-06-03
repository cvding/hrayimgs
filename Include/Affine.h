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
	/** ���������󣬺�ȱ任 */
	Affine();
	
	/** ���÷������
	*
	* @param [in] x ƽ������x
	* @param [in] y ƽ������y
	* @param [in] rotate ��ת�Ƕ�
	* @param [in] skew ���нǶ�
	* @param [in] aspect y/x�ı���
	* @param [in] scale x,y����
	*/
	Affine(float x, float y, float rotate = 0.f, float skew = 0.f, 
		   float aspect = 1.f, float scale = 1.f);
	
	Affine(const Affine& rhs);
	~Affine();

	/** �������÷������
	 *  
	 * @param [in] x ƽ������x
	 * @param [in] y ƽ������y
	 * @param [in] rotate ��ת�Ƕ�
	 * @param [in] skew ���нǶ�
	 * @param [in] aspect y/x�ı���
	 * @param [in] scale x,y����
	 * @return void 
	 * @note  
	 */
	void reset(float x, float y, float rotate = 0.f, float skew = 0.f, 
			   float aspect = 1.f, float scale = 1.f);

	/** ��ӳ��
	 *  
	 * @param [in] isInv �Ƿ�Ϊ��ӳ��
	 * @param [in] src �����
	 * @param [out] dst �����
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

	/** ��ת��
	 *  
	 * @param [in] src ����� 
	 * @param [in] org ԭ��
	 * @return Point2D<float> ��ת������
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