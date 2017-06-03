#include "Anchor.h"

Anchor::Anchor() : Feature(2)
{
	memset(m_pos[0], 0, 16 * sizeof(int32_t));
	memset(m_pos[1], 0, 16 * sizeof(int32_t));
}

void Anchor::init(int32_t stride)
{
	/* line 1 */
	m_pos[0][1] = -(stride << 1) - 2;
	m_pos[0][1] = m_pos[0][0] + 1;
	m_pos[0][2] = m_pos[0][1] + 2;
	m_pos[0][3] = m_pos[0][2] + 1;

	/* line 2 */
	m_pos[0][4] = -stride - 2;
	m_pos[0][5] = m_pos[0][4] + 1;
	m_pos[0][6] = m_pos[0][5] + 2;
	m_pos[0][7] = m_pos[0][6] + 1;

	/* line 4 */
	m_pos[0][8] = stride - 2;
	m_pos[0][9] = m_pos[0][8] + 1;
	m_pos[0][10] = m_pos[0][9] + 2;
	m_pos[0][11] = m_pos[0][10] + 1;

	/* line 5 */
	m_pos[0][12] = (stride << 1) - 2;
	m_pos[0][13] = m_pos[0][12] + 1;
	m_pos[0][14] = m_pos[0][13] + 2;
	m_pos[0][15] = m_pos[0][14] + 1;

	/* y */
	/* line 1 */
	m_pos[1][0] = -(stride << 1) - 1;
	m_pos[1][1] = m_pos[1][0] + 1;
	m_pos[1][2] = m_pos[1][1] + 1;

	/* line 2 */
	m_pos[1][3] = -stride - 2;
	m_pos[1][4] = m_pos[1][3] + 2;
	m_pos[1][5] = m_pos[1][4] + 2;

	/* line 3 */
	m_pos[1][6] = -2;
	m_pos[1][7] = -1;
	m_pos[1][8] = +1;
	m_pos[1][9] = +2;

	/* line 4 */
	m_pos[1][10] = stride - 2;
	m_pos[1][11] = m_pos[1][10] + 2;
	m_pos[1][12] = m_pos[1][11] + 2;

	/* line 5 */
	m_pos[1][13] = -(stride << 1) - 1;
	m_pos[1][14] = m_pos[1][13] + 1;
	m_pos[1][15] = m_pos[1][14] + 1;
}

bool Anchor::extract(void *input, void *param /* = 0 */)
{
	AnchorInput *pInput = (AnchorInput *)input;
	int32_t *base;
	uint8_t *pImgBuf = pInput->pImgBuf;
	int32_t pos = pInput->pos;
	int32_t vals[2];

	base = m_pos[0];
	vals[0] = -pImgBuf[base[0] + pos] - pImgBuf[base[1] + pos]
			+ pImgBuf[base[2] + pos] + pImgBuf[base[3] + pos]
			- pImgBuf[base[4] + pos] - pImgBuf[base[5] + pos]
			+ pImgBuf[base[6] + pos] + pImgBuf[base[7] + pos]
			+ pImgBuf[base[8] + pos] + pImgBuf[base[9] + pos]
			- pImgBuf[base[10] + pos] - pImgBuf[base[11] + pos]
			+ pImgBuf[base[12] + pos] + pImgBuf[base[13] + pos]
			- pImgBuf[base[14] + pos] - pImgBuf[base[15] + pos];

	base = m_pos[1];
	vals[1] = -pImgBuf[base[0] + pos] - pImgBuf[base[1] + pos]
			- pImgBuf[base[2] + pos] + pImgBuf[base[3] + pos]
			- pImgBuf[base[4] + pos] + pImgBuf[base[5] + pos]
			+ pImgBuf[base[6] + pos] + pImgBuf[base[7] + pos]
			+ pImgBuf[base[8] + pos] + pImgBuf[base[9] + pos]
			+ pImgBuf[base[10] + pos] - pImgBuf[base[11] + pos]
			+ pImgBuf[base[12] + pos] - pImgBuf[base[13] + pos]
			- pImgBuf[base[14] + pos] - pImgBuf[base[15] + pos];

	m_data[0] = static_cast<float>(vals[0]);
	m_data[1] = static_cast<float>(vals[1]);

	return true;
}

