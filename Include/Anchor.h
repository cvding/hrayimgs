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
	uint8_t *pImgBuf;		/**< ͼ�񻺴� */
	int32_t pos;			/**< �������� */
}AnchorInput;

class Anchor : public Feature
{
public:
	Anchor();

	/** ��ʼ����������
	 *  
	 * @param [in] stride ͼ���а�
	 * @return void 
	 * @note  
	 */
	void init(int32_t stride);

	/** ��ȡ��������
	 *  
	 * @param [in] input ��������
	 * @param [in] param ����������ޣ�
	 * @return bool ��ȡ״̬
	 * @note  
	 */
	bool extract(void *input, void *param /* = 0 */);
protected:
private:
	int32_t m_pos[2][16];
};
#endif // __ANCHOR_H__