/*********************************************************************
 *	Copyright 1992-2008, ZheJiang HuaRay Technology Stock Co.Ltd.
 *						All Rights Reserved
 *	@file 	    		Model.h
 *	@author				dzf
 *	@brief				
 *  
 *
 *	@date	        	2017:5:27 
 *	@version			1.00.1
 *	@todo				
**********************************************************************/
#ifndef __MODEL_H__
#define __MODEL_H__

#include <cstdint>

class GammaTabel
{
public:
	GammaTabel();
	GammaTabel(float sigma, float gain = 1.f);
	~GammaTabel();

	void reset(float sigma, float gain = 1.f);

	const uint8_t* tabel() const;
protected:
private:
	uint8_t m_model[256];
};
#endif // __MODEL_H__