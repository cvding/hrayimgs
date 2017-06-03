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
	int32_t schRad;		/**< �����뾶 */
	int32_t schPosThr;	/**< ��������Ե��ֵ */
	int32_t schNegThr;	/**< ��������Ե��ֵ */
}QRBoundParam;

class QRBound : public Feature
{
public:
	QRBound();

	/** ������ȡ
	 *  
	 * @param [in] input ��������
	 * @param [in] param �������
	 * @return bool ��ȡ״̬
	 * @note  
	 */
	bool extract(void *input, void *param /* = 0 */);
	
protected:
private:
};
#endif // __QRBOUND_H__