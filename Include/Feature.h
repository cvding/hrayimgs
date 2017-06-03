/*********************************************************************
 *	Copyright 1992-2008, ZheJiang HuaRay Technology Stock Co.Ltd.
 *						All Rights Reserved
 *	@file 	    		Feature.h
 *	@author				dzf
 *	@brief				������ȡ
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
	/** �������췽��
	 *  
	 * @param [in] nFeatDims ����ά��
	 */
	Feature(int32_t nFeatDims = 1);
	
	/** ��չ�����ڴ�
	 *  
	 * @param [in] nFeatDims ����ά��
	 * @return bool ��չ״̬
	 * @note  
	 */
	bool reshape(int32_t nFeatDims);

	/** ת��������
	 *  
	 * @param [in] rIdx ���������������
	 * @param [out] mat �������
	 * @return bool ����״̬
	 * @note  
	 */
	bool toMat(int32_t rIdx, Matrix2D<float>& mat);

	/** ������������
	 */
	virtual ~Feature();
	
	/** ��������ֵ��Ӳ��
	 *  
	 * @param [in] out �ļ�����������
	 * @param [in] label ������ǩ
	 * @param [in] eps ��������
	 * @return void 
	 * @note  
	 */
	void save(std::ofstream& out, int32_t label = 1, float eps = FEA_EPS);
	
	/** ��������ֵ���ڴ�
	 *  
	 * @param [in] in �ļ���������룩
	 * @param [in] label ������ǩ
	 * @return bool ����״̬
	 * @note  
	 */
	bool load(std::ifstream& in, int32_t *label = 0);

	/** ��ȡ����ֵ
	 *  
	 * @param [in] input ��������
	 * @param [in] param �������
	 * @return bool ��ȡ״̬
	 * @note �Զ���ṹ��
	 */
	virtual bool extract(void *input, void *param = 0);

	/** ��ȡĳһά������
	 *  
	 * @param [in] index ά������
	 * @return float ά������
	 * @note ����ֵû�б߽��ж�
	 */
	float operator[](size_t index);

	/** ��ȡ����ά��
	 *  
	 * @return int32_t ����ά��
	 */
	int32_t length() const;

	/** ��ȡ����ָ��
	 *  
	 * @return float* ����ָ��
	 */
	float* data() const;
protected:
	float  *m_data;
	int32_t m_ndim;
};
#endif // __FEATURE_H__