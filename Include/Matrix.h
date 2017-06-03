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

	/** 初始化数据内存 */
	void zero();

	/** 阈值化,将较小的值置成0 */
	void thres(T thres);

	/** 阈值化,将范围内的值置成0  */
	void thres(T minThr, T maxThr);

	/** 扩展内存
	 *  
	 * @param [in] row 新矩阵的行数
	 * @param [in] col 新矩阵的列数
	 * @return bool 是否成功
	 * @note 初始内存清空
	 */
	bool reshape(int32_t row, int32_t col);

	/** 将矩阵某一行转换为特征
	 *  
	 * @param [in] rIdx 行索引
	 * @param [in] feature 特征结构
	 * @return bool 转换状态
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