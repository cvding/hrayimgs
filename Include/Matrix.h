/*********************************************************************
 *	Copyright 1992-2008, ZheJiang HuaRay Technology Stock Co.Ltd.
 *						All Rights Reserved
 *	@file 	    		Matrix.h
 *	@author				dzf
 *	@brief				
 *  
 *
 *	@date	        	2017:5:24 
 *	@version			1.00.1
 *	@todo				
**********************************************************************/
#ifndef __MATRIX_H__
#define __MATRIX_H__

#include <cstdint>
#include <fstream>

#define MAT_EPS 0.000001f

class HRAYGray;
class Feature;


template <typename T>
class Matrix2D
{
public:
	Matrix2D();
	Matrix2D(int32_t row, int32_t col, T *data = 0);
	Matrix2D(const Matrix2D<T>& rhs);
	~Matrix2D();

	/** ��ʼ�������ڴ� */
	void zero();

	/** ��ֵ��,����С��ֵ�ó�0 */
	void thres(T thres);

	/** ��ֵ��,����Χ�ڵ�ֵ�ó�0  */
	void thres(T minThr, T maxThr);

	/** ��չ�ڴ�
	 *  
	 * @param [in] row �¾��������
	 * @param [in] col �¾��������
	 * @return bool �Ƿ�ɹ�
	 * @note ��ʼ�ڴ����
	 */
	bool reshape(int32_t row, int32_t col);

	/** ������ĳһ��ת��Ϊ����
	 *  
	 * @param [in] rIdx ������
	 * @param [in] feature �����ṹ
	 * @return bool ת��״̬
	 * @note 
	 */
	bool toFeature(int32_t rIdx, Feature *feature);

	/** 
	 *  
	 * @param [in] file 
	 * @return void 
	 * @note  
	 */
	void save(std::ofstream& file);
	void save(std::ofstream& file,int32_t *pLabel, int32_t nLabel, float eps = MAT_EPS);
	bool read(std::string& fileName, bool isFloat);

	T *data() const;
	int32_t row() const;
	int32_t col() const;
protected:
	int32_t m_row;
	int32_t m_col;
	T *m_data;
};


#endif // __MATRIX_H__