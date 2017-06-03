/*********************************************************************
 *	Copyright 1992-2008, ZheJiang HuaRay Technology Stock Co.Ltd.
 *						All Rights Reserved
 *	@file 	    		Anchor.h
 *	@author				dzf
 *	@brief				
 *  
 *
 *	@date	        	2017:5:23 
 *	@version			1.00.1
 *	@todo				
**********************************************************************/
#ifndef __ANCHOR_H__
#define __ANCHOR_H__

#include "Feature.h"

typedef struct AnchorInput 
{
	uint8_t *pImgBuf;		/**< 图像缓存 */
	int32_t pos;			/**< 坐标索引 */
}AnchorInput;

class Anchor : public Feature
{
public:
	Anchor();

	/** 初始化特征参数
	 *  
	 * @param [in] stride 图像行摆
	 * @return void 
	 * @note  
	 */
	void init(int32_t stride);

	/** 提取鞍点特征
	 *  
	 * @param [in] input 输入数据
	 * @param [in] param 输入参数（无）
	 * @return bool 提取状态
	 * @note  
	 */
	bool extract(void *input, void *param /* = 0 */);
protected:
private:
	int32_t m_pos[2][16];
};
#endif // __ANCHOR_H__