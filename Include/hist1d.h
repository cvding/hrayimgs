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

	/** �ı�hist���ڴ泤��
	 *  
	 * @param [in] nHist ֱ��ͼ�ڵ����� 
	 * @return bool �ı���״̬
	 * @note �����ǰ���ڴ�
	 */
	bool reshape(int32_t nHist);
	
	/** ���
	 *  
	 * @param [out] dif ���ֱ��ͼ
	 * @param [in] dr ��ְ뾶
	 * @return bool ���״̬ 
	 * @note  
	 */
	bool dif(Hist1D& dif, int32_t dr = 1);

	/** ���Ҳ��岨��
	 *  
	 * @param [in] peak ���岨��
	 * @return void 
	 * @note  
	 */
	void findPeak(std::vector<HistPeak<T>>& peak);

	/** ȫ��Ԫ������ */
	void zero();

	/** ֱ��ͼ���� */
	int32_t length() const;

	/** ֱ��ͼ����
	 *  
	 * @return T* ����ָ��
	 */
	T* data() const;

	/** ȡֱ��ͼԪ��
	 *  
	 * @param [in] index ����
	 * @return T& 
	 * @note ���жϱ߽�
	 */
	T& operator[](size_t index);
protected:
private:
	int32_t m_nhist;
	T *m_phist;
};



#endif // __HIST1D_H__