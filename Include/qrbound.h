/*********************************************************************
 *	Copyright 1992-2008, ZheJiang HuaRay Technology Stock Co.Ltd.
 *						All Rights Reserved
 *	@file 	    		qrbound.h
 *	@author				dzf
 *	@brief				
 *  
 *
 *	@date	        	2017:5:22 
 *	@version			1.00.1
 *	@todo				
**********************************************************************/
#ifndef __QRBOUND_H__
#define __QRBOUND_H__

#include "Feature.h"

typedef struct QRBoundInput 
{
	int32_t  nHist;
	int32_t *pHist;
}QRBoundInput;

typedef struct QRBoundParam 
{
	int32_t schRad;		/**< 搜索半径 */
	int32_t schPosThr;	/**< 搜索正边缘阈值 */
	int32_t schNegThr;	/**< 搜索负边缘阈值 */
}QRBoundParam;

class QRBound : public Feature
{
public:
	QRBound();

	/** 特征提取
	 *  
	 * @param [in] input 输入数据
	 * @param [in] param 输入参数
	 * @return bool 提取状态
	 * @note  
	 */
	bool extract(void *input, void *param /* = 0 */);
	
protected:
private:
};
#endif // __QRBOUND_H__