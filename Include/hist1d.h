/*********************************************************************
 *	Copyright 1992-2008, ZheJiang HuaRay Technology Stock Co.Ltd.
 *						All Rights Reserved
 *	@file 	    		hist1d.h
 *	@author				dzf
 *	@brief				
 *  
 *
 *	@date	        	2017:5:22 
 *	@version			1.00.1
 *	@todo				
**********************************************************************/
#ifndef __HIST1D_H__
#define __HIST1D_H__

#include <cstdint>
#include <vector>

typedef enum PeakType
{
	PEAK_BOT = -1,
	PEAK_TOP = +1
}PeakType;

template <typename T>
class HistPeak
{
public:
	HistPeak();
	~HistPeak();
public:
	PeakType type;
	int32_t  pidx;
	T        pval;
};


template <typename T>
class Hist1D
{
public:
	Hist1D();
	Hist1D(int32_t nHist, T *pHist = 0);
	Hist1D(const Hist1D& rhs);
	~Hist1D();

	/** 改变hist的内存长度
	 *  
	 * @param [in] nHist 直方图节点数量 
	 * @return bool 改变后的状态
	 * @note 清除以前的内存
	 */
	bool reshape(int32_t nHist);
	
	/** 差分
	 *  
	 * @param [out] dif 差分直方图
	 * @param [in] dr 差分半径
	 * @return bool 差分状态 
	 * @note  
	 */
	bool dif(Hist1D& dif, int32_t dr = 1);

	/** 查找波峰波谷
	 *  
	 * @param [in] peak 波峰波谷
	 * @return void 
	 * @note  
	 */
	void findPeak(std::vector<HistPeak<T>>& peak);

	/** 全部元素置零 */
	void zero();

	/** 直方图长度 */
	int32_t length() const;

	/** 直方图数据
	 *  
	 * @return T* 数据指针
	 */
	T* data() const;

	/** 取直方图元素
	 *  
	 * @param [in] index 索引
	 * @return T& 
	 * @note 不判断边界
	 */
	T& operator[](size_t index);
protected:
private:
	int32_t m_nhist;
	T *m_phist;
};



#endif // __HIST1D_H__