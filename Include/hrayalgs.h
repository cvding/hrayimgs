/*********************************************************************
 *	Copyright 1992-2008, ZheJiang HuaRay Technology Stock Co.Ltd.
 *						All Rights Reserved
 *	@file 	    		hrayalgs.h
 *	@author				dzf
 *	@brief				
 *  
 *
 *	@date	        	2017:5:24 
 *	@version			1.00.1
 *	@todo				
**********************************************************************/
#ifndef __HRAYALGS_H__
#define __HRAYALGS_H__

#include <cstdint>
#include <sstream>

template <typename T,typename VT>
T iconvert(const VT& value)
{
	T tvalue;
	std::stringstream stream;

	stream << value;
	stream >> tvalue;

	return tvalue;
}

#endif // __HRAYALGS_H__