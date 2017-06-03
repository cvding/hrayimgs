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

	/** �ı��ڴ��С
	 *  
	 * @param [in] width ͼ��Ŀ��
	 * @param [in] height ͼ��ĸ߶�
	 * @return bool �ı���״̬
	 * @note �����ı��ڴ��С
	 */
	bool reshape(int32_t width, int32_t height);

	/** ��ȡROIͼ��
	 *  
	 * @param [in] ul ���϶���
	 * @param [in] lr ���¶���
	 * @param [out] out ���ͼ��
	 * @return bool ��ȡ״̬
	 * @note  
	 */
	bool roi(Point2D<int32_t> ul, Point2D<int32_t> lr, HRAYGray& out);

	/** ��ȡROIͼ��
	 *  
	 * @param [in] point ��������
	 * @param [in] size ���γߴ�
	 * @param [in] angle ת���Ƕ�
	 * @param [out] out ���ͼ��
	 * @return bool ��ȡ״̬
	 * @note ͼ������ϵ
	 */
	bool roi(Point2D<float> point, Size2D<int32_t> size, float angle[2], HRAYGray& out);
	
	/** ��ͼ�����gamma�任
	 *  
	 * @param [in] tabel gamma�任�� 
	 * @param [out] out ���ͼ��
	 * @return bool �任״̬
	 * @note  
	 */
	bool gamma(const GammaTabel& tabel, HRAYGray& out);

	bool linebufs(Point2D<int32_t> head, Point2D<int32_t> tail, Hist1D<uint8_t>& lbuf);

	int32_t mean() const;

	/** ��˹ƽ��5x5
	 *  
	 * @param [in] out ���ͼ��
	 * @return bool ƽ����״̬
	 * @note [1 4 8 4 1]
	 */
	bool gsmooth5x5(HRAYGray& out);

	/** ���ü��ݶȼ���x�����ݶ�
	 *  
	 * @param [in] grad �ݶ�
	 * @return bool ����״̬
	 * @note [-1 +1] 
	 */
	bool sgradx(Matrix2D<int16_t>& grad);

	/** ����ͼ��
	 *  
	 * @param [in] intimg ����ͼ��
	 * @return bool �����ͼ״̬
	 * @note  
	 */
	bool integral(Matrix2D<uint32_t>& intimg);

	/** ƽ������ͼ��
	 *  
	 * @param [in] intimg ƽ������ͼ��
	 * @return bool ��ƽ������ͼ��״̬
	 * @note  
	 */
	bool integral(Matrix2D<uint64_t>& intimg);

	/** �Ҷ�ֱ��ͼ
	 *  
	 * @param [out] dhist �Ҷ�ֱ��ͼ
	 * @return bool ����״̬
	 * @note  
	 */
	bool hist(Hist1D<int32_t>& dhist);

	/** ����ڲ�ֵ�㷨
	 *  
	 * @param [in] width ���ͼ��Ŀ��
	 * @param [in] height ���ͼ��ĸ߶�
	 * @param [out] out ���ͼ��
	 * @return bool ����״̬
	 * @note  
	 */
	bool imnear(int32_t width, int32_t height, HRAYGray& out);

	/** ˫���Բ�ֵ�㷨
	 *  
	 * @param [in] width ���ͼ��Ŀ��
	 * @param [in] height ���ͼ��ĸ߶�
	 * @param [out] out ���ͼ��
	 * @return bool ����״̬
	 * @note  
	 */
	bool imblinear(int32_t width, int32_t height, HRAYGray& out);

	/** ��ȡx����ͶӰ
	 *  
	 * @param [out] proj ͶӰֱ��ͼ 
	 * @return bool ͶӰ״̬
	 * @note 
	 */
	bool xproj(Hist1D<int32_t>& proj);

	/** ��ȡy����ͶӰ
	 *  
	 * @param [out] proj ͶӰֱ��ͼ
	 * @return bool ͶӰ״̬
	 * @note  
	 */
	bool yproj(Hist1D<int32_t>& proj);

	/** ͼ����
	 *  
	 * @return int32_t ���ֵ
	 * @note  
	 */
	int32_t width() const;

	/** ͼ��߶�
	 *  
	 * @return int32_t �߶�ֵ
	 * @note  
	 */
	int32_t height() const;

	/** ��ȡ����ָ��
	 *  
	 * @return uint8_t* ����ָ��
	 * @note  
	 */
	uint8_t* data() const;

	/** ��ȡ��������
	 *  
	 * @param [in] pos ��������
	 * @return uint8_t �Ҷ�ֵ
	 * @note  
	 */
	uint8_t data(int32_t pos);

	/** ��ȡ����ֵ
	 *  
	 * @param [in] x x����
	 * @param [in] y y����
	 * @return uint8_t �Ҷ�ֵ
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