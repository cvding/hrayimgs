/*********************************************************************
 *	Copyright 1992-2008, ZheJiang HuaRay Technology Stock Co.Ltd.
 *						All Rights Reserved
 *	@file 	    		Feature.h
 *	@author				dzf
 *	@brief				特征提取
 *  
 *
 *	@date	        	2017:5:22 
 *	@version			1.00.1
 *	@todo				
**********************************************************************/
#ifndef __FEATURE_H__
#define __FEATURE_H__

#include <cstdint>
#include <fstream>

#define FEA_EPS 0.000001f

template <typename T> class Matrix2D;

class Feature
{
public:
	/** 特征构造方法
	 *  
	 * @param [in] nFeatDims 特征维度
	 */
	Feature(int32_t nFeatDims = 1);
	
	/** 扩展特征内存
	 *  
	 * @param [in] nFeatDims 特征维度
	 * @return bool 扩展状态
	 * @note  
	 */
	bool reshape(int32_t nFeatDims);

	/** 转换到矩阵
	 *  
	 * @param [in] rIdx 拷贝到矩阵的行数
	 * @param [out] mat 输出矩阵
	 * @return bool 拷贝状态
	 * @note  
	 */
	bool toMat(int32_t rIdx, Matrix2D<float>& mat);

	/** 特征析构方法
	 */
	virtual ~Feature();
	
	/** 保存特征值到硬盘
	 *  
	 * @param [in] out 文件句柄（输出）
	 * @param [in] label 特征标签
	 * @param [in] eps 特征精度
	 * @return void 
	 * @note  
	 */
	void save(std::ofstream& out, int32_t label = 1, float eps = FEA_EPS);
	
	/** 加载特征值到内存
	 *  
	 * @param [in] in 文件句柄（输入）
	 * @param [in] label 特征标签
	 * @return bool 加载状态
	 * @note  
	 */
	bool load(std::ifstream& in, int32_t *label = 0);

	/** 提取特征值
	 *  
	 * @param [in] input 输入数据
	 * @param [in] param 输出参数
	 * @return bool 提取状态
	 * @note 自定义结构体
	 */
	virtual bool extract(void *input, void *param = 0);

	/** 获取某一维度特征
	 *  
	 * @param [in] index 维度索引
	 * @return float 维度特征
	 * @note 特征值没有边界判断
	 */
	float operator[](size_t index);

	/** 获取特征维度
	 *  
	 * @return int32_t 特征维度
	 */
	int32_t length() const;

	/** 获取数据指针
	 *  
	 * @return float* 数据指针
	 */
	float* data() const;
protected:
	float  *m_data;
	int32_t m_ndim;
};
#endif // __FEATURE_H__