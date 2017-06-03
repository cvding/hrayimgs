#include "qrbound.h"
#define NOFOUND -1

typedef struct QrSignBound
{
	int32_t head;
	int32_t tail;
}QrSignBound;

static int32_t mvSearchPositiveL(int32_t nHist, int32_t *pHist, int32_t thres, QrSignBound bound, int32_t nRadiu)
{
	int32_t i;
	int32_t ival;					/**< 记录最大值位置 */
	int32_t sval;					/**< 记录最大值 */

	ival = bound.head;
	sval = pHist[ival];

	/* 设置向左初始未搜索到极值 */
	for (i = bound.head - 1; i >= bound.tail; i--)
	{
		if (sval < pHist[i] && pHist[i] > thres)
		{
			sval = pHist[i];
			ival = i;
		}

		if (sval > thres &&
			(ival - i >= nRadiu || ival - bound.tail < nRadiu))
		{
			return ival;
		}
	}

	return NOFOUND;
}

static int32_t mvSearchNegativeL(int32_t nHist, int32_t *pHist, int32_t thres, QrSignBound bound, int32_t nRadiu)
{
	int32_t i;
	int32_t ival;					/**< 记录最大值位置 */
	int32_t sval;					/**< 记录最大值 */

	thres = (thres < 0) ? thres : -thres;

	ival = bound.head;
	sval = pHist[ival];

	/* 设置向左初始未搜索到极值 */
	for (i = bound.head - 1; i >= bound.tail; i--)
	{
		if (sval > pHist[i] && pHist[i] < thres)
		{
			sval = pHist[i];
			ival = i;
		}

		if (sval < thres &&
			(ival - i >= nRadiu || ival - bound.tail < nRadiu))
		{
			return ival;
		}
	}

	return NOFOUND;
}

static int32_t mvSearchPositiveR(int32_t nHist, int32_t *pHist, int32_t thres, QrSignBound bound, int32_t nRadiu)
{
	int32_t i;
	int32_t ival;					/**< 记录最大值位置 */
	int32_t sval;					/**< 记录最大值 */

	ival = bound.head;
	sval = pHist[ival];

	/* 设置向左初始未搜索到极值 */
	for (i = bound.head - 1; i <= bound.tail; i++)
	{
		if (sval < pHist[i] && pHist[i] > thres)
		{
			sval = pHist[i];
			ival = i;
		}

		if (sval > thres &&
			(i - ival >= nRadiu || bound.tail - ival < nRadiu))
		{
			return ival;
		}
	}

	return NOFOUND;
}

static int32_t mvSearchNegativeR(int32_t nHist, int32_t *pHist, int32_t thres, QrSignBound bound, int32_t nRadiu)
{
	int32_t i;
	int32_t ival;					/**< 记录最大值位置 */
	int32_t sval;					/**< 记录最大值 */

	thres = (thres < 0) ? thres : -thres;

	ival = bound.head;
	sval = pHist[ival];

	/* 设置向左初始未搜索到极值 */
	for (i = bound.head - 1; i <= bound.tail; i++)
	{
		if (sval > pHist[i] && pHist[i] < thres)
		{
			sval = pHist[i];
			ival = i;
		}

		if (sval < thres &&
			(i - ival >= nRadiu || bound.tail - ival < nRadiu))
		{
			return ival;
		}
	}

	return NOFOUND;
}
QRBound::QRBound() : Feature(6)
{

}

bool QRBound::extract(void *input, void *param /* = 0 */)
{
	QRBoundInput *pInput = (QRBoundInput *)input;
	QRBoundParam *pParam = (QRBoundParam *)param;
	int32_t *pHist = pInput->pHist;
	int32_t nHist = pInput->nHist;
	int32_t nRadiu = pParam->schRad;

	/* 中心起点 */
	/* 向左搜索最大的负值 */
	int32_t center;
	QrSignBound bound;
	int32_t pos[6];
	pos[0] = pos[1] = pos[2] = pos[3] = pos[4] = pos[5] = -1;

	center = nHist >> 1;
	bound.head = center;
	bound.tail = 0;
	pos[2] = mvSearchNegativeL(nHist, pHist, pParam->schNegThr, bound, nRadiu);
	if (pos[2] < 0) return false;

	/* 再向左搜索最大的正值 */
	bound.head = pos[2] - 1;
	pos[1] = mvSearchPositiveL(nHist, pHist, pParam->schPosThr, bound, nRadiu);
	if (pos[1] < 0) return false;

	/* 最后想左搜索最大的负值 */
	bound.head = pos[1] - 1;
	pos[0] = mvSearchNegativeL(nHist, pHist, pParam->schNegThr, bound, nRadiu);
	if (pos[0] < 0) return false;

	/* 中心起点 */
	/* 向右搜索最大的正值 */
	bound.head = center;
	bound.tail = nHist - 1;
	pos[3] = mvSearchPositiveR(nHist, pHist, pParam->schPosThr, bound, nRadiu);
	if (pos[3] < 0) return false;
	/* 在向右搜索最大的负值 */
	bound.head = pos[3] + 1;
	pos[4] = mvSearchNegativeR(nHist, pHist, pParam->schNegThr, bound, nRadiu);
	if (pos[4] < 0) return false;
	/* 组后向右搜索最大的正值 */
	bound.head = pos[4] + 1;
	pos[5] = mvSearchPositiveR(nHist, pHist, pParam->schPosThr, bound, nRadiu);
	if (pos[5] < 0) return false;

	m_data[0] = (float)pos[0] - center;
	m_data[1] = (float)pos[1] - center;
	m_data[2] = (float)pos[2] - center;
	m_data[3] = (float)pos[3] - center;
	m_data[4] = (float)pos[4] - center;
	m_data[5] = (float)pos[5] - center;

	return true;
}

