/*********************************************************************
 *	Copyright 1992-2008, ZheJiang HuaRay Technology Stock Co.Ltd.
 *						All Rights Reserved
 *	@file 	    		hrayimgs.h
 *	@author				dzf
 *	@brief				
 *  
 *
 *	@date	        	2017:5:22 
 *	@version			1.00.1
 *	@todo				
**********************************************************************/
#ifndef __HRAYIMGS_H__
#define __HRAYIMGS_H__

#include <cstdint>

class GammaTabel;
template <typename T> class Hist1D;
template <typename T> class Size2D;
template <typename T> class Point2D;
template <typename T> class Matrix2D;
class HRAYGray
{
public:
	HRAYGray();
	HRAYGray(int32_t width, int32_t height, uint8_t *pImgBuf = 0);
	HRAYGray(const HRAYGray& rhs);
	~HRAYGray();

	/** 改变内存大小
	 *  
	 * @param [in] width 图像的宽度
	 * @param [in] height 图像的高度
	 * @return bool 改变后的状态
	 * @note 仅仅改变内存大小
	 */
	bool reshape(int32_t width, int32_t height);

	/** 截取ROI图像
	 *  
	 * @param [in] ul 左上顶点
	 * @param [in] lr 右下顶点
	 * @param [out] out 输出图像
	 * @return bool 截取状态
	 * @note  
	 */
	bool roi(Point2D<int32_t> ul, Point2D<int32_t> lr, HRAYGray& out);

	/** 截取ROI图像
	 *  
	 * @param [in] point 中心坐标
	 * @param [in] size 矩形尺寸
	 * @param [in] angle 转过角度
	 * @param [out] out 输出图像
	 * @return bool 截取状态
	 * @note 图像坐标系
	 */
	bool roi(Point2D<float> point, Size2D<int32_t> size, float angle[2], HRAYGray& out);
	
	/** 对图像进行gamma变换
	 *  
	 * @param [in] tabel gamma变换表 
	 * @param [out] out 输出图像
	 * @return bool 变换状态
	 * @note  
	 */
	bool gamma(const GammaTabel& tabel, HRAYGray& out);

	bool linebufs(Point2D<int32_t> head, Point2D<int32_t> tail, Hist1D<uint8_t>& lbuf);

	int32_t mean() const;

	/** 高斯平滑5x5
	 *  
	 * @param [in] out 输出图像
	 * @return bool 平滑后状态
	 * @note [1 4 8 4 1]
	 */
	bool gsmooth5x5(HRAYGray& out);

	/** 利用简单梯度计算x方向梯度
	 *  
	 * @param [in] grad 梯度
	 * @return bool 计算状态
	 * @note [-1 +1] 
	 */
	bool sgradx(Matrix2D<int16_t>& grad);

	/** 积分图像
	 *  
	 * @param [in] intimg 积分图像
	 * @return bool 求积分图状态
	 * @note  
	 */
	bool integral(Matrix2D<uint32_t>& intimg);

	/** 平方积分图像
	 *  
	 * @param [in] intimg 平方积分图像
	 * @return bool 求平方积分图像状态
	 * @note  
	 */
	bool integral(Matrix2D<uint64_t>& intimg);

	/** 灰度直方图
	 *  
	 * @param [out] dhist 灰度直方图
	 * @return bool 计算状态
	 * @note  
	 */
	bool hist(Hist1D<int32_t>& dhist);

	/** 最近邻插值算法
	 *  
	 * @param [in] width 输出图像的宽度
	 * @param [in] height 输出图像的高度
	 * @param [out] out 输出图像
	 * @return bool 缩放状态
	 * @note  
	 */
	bool imnear(int32_t width, int32_t height, HRAYGray& out);

	/** 双线性插值算法
	 *  
	 * @param [in] width 输出图像的宽度
	 * @param [in] height 输出图像的高度
	 * @param [out] out 输出图像
	 * @return bool 缩放状态
	 * @note  
	 */
	bool imblinear(int32_t width, int32_t height, HRAYGray& out);

	/** 提取x方向投影
	 *  
	 * @param [out] proj 投影直方图 
	 * @return bool 投影状态
	 * @note 
	 */
	bool xproj(Hist1D<int32_t>& proj);

	/** 提取y方向投影
	 *  
	 * @param [out] proj 投影直方图
	 * @return bool 投影状态
	 * @note  
	 */
	bool yproj(Hist1D<int32_t>& proj);

	/** 图像宽度
	 *  
	 * @return int32_t 宽度值
	 * @note  
	 */
	int32_t width() const;

	/** 图像高度
	 *  
	 * @return int32_t 高度值
	 * @note  
	 */
	int32_t height() const;

	/** 获取数据指针
	 *  
	 * @return uint8_t* 数据指针
	 * @note  
	 */
	uint8_t* data() const;

	/** 获取索引数据
	 *  
	 * @param [in] pos 索引坐标
	 * @return uint8_t 灰度值
	 * @note  
	 */
	uint8_t data(int32_t pos);

	/** 获取像素值
	 *  
	 * @param [in] x x坐标
	 * @param [in] y y坐标
	 * @return uint8_t 灰度值
	 * @note  
	 */
	uint8_t data(int32_t x, int32_t y);
protected:
private:
	int32_t m_width;
	int32_t m_height;
	uint8_t *m_buffer;
};
#endif // __HRAYIMGS_H__