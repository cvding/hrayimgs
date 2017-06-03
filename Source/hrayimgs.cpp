#include "hrayimgs.h"
#include "hist1d.h"
#include "Matrix.h"
#include "Affine.h"
#include "Shape.h"
#include "Model.h"
#include <cstdlib>
#include <string.h>
#include <cmath>
#include <algorithm>

#define checkimage(pBuffer,width,height) if (!pBuffer || width <= 0 || height <= 0) return false
/** Ë«ÏßÐÔ²åÖµ */
#define xvmInterpolation2D(pos,stride,pImgBuf,xrate,yrate) \
	(pImgBuf[pos] * (1-xrate) * (1-yrate) + \
	 pImgBuf[pos+1] * xrate * (1-yrate) +\
	 pImgBuf[pos+stride] * (1-xrate) * yrate +\
	 pImgBuf[pos+stride+1] * xrate * yrate)

HRAYGray::HRAYGray() : m_width(0), m_height(0), m_buffer(0)
{

}

HRAYGray::HRAYGray(int32_t width, int32_t height, uint8_t *pImgBuf /*= 0*/) :
m_width(0), m_height(0), m_buffer(0)
{
	if (width > 0 && height > 0)
	{
		m_width = width;
		m_height = height;
		m_buffer = new uint8_t[width*height];
		if (pImgBuf)
		{
			memcpy(m_buffer, pImgBuf, width*height);
		}
		else
		{
			memset(m_buffer, 0, width*height);
		}
	}
}

HRAYGray::HRAYGray(const HRAYGray& rhs) : m_width(0), m_height(0), m_buffer(0)
{
	if (rhs.m_width >= 0 && rhs.m_height >= 0 && rhs.m_buffer)
	{
		m_width = rhs.m_width;
		m_height = rhs.m_height;
		m_buffer = new uint8_t[m_width*m_height];
		memcpy(m_buffer, rhs.m_buffer, m_width*m_height);
	}
}

HRAYGray::~HRAYGray()
{
	if (m_buffer)
	{
		delete[] m_buffer;
	}
	m_buffer = NULL;
	m_width = 0;
	m_height = 0;
}

bool HRAYGray::reshape(int32_t width, int32_t height)
{
	if (width <= 0 || height <= 0)
	{
		return false;
	}

	if (m_width != width || m_height != height)
	{
		m_width = width;
		m_height = height;
		if (m_buffer) delete[] m_buffer;
		m_buffer = new uint8_t[width * height];
		if (!m_buffer)
		{
			return false;
		}
	}

	return true;
}

bool HRAYGray::roi(Point2D<int32_t> ul, Point2D<int32_t> lr, HRAYGray& out)
{
	int32_t width, height;

	width = lr.x - ul.x + 1;
	height = lr.y - ul.y + 1;

	if (width <= 0 || height <= 0 || m_width <= 0 ||
		m_height <= 0)
	{
		return false;
	}

	out.reshape(width, height);

	for (int32_t y = ul.y; y <= lr.y; y++)
	{
		memcpy(m_buffer + y*m_width + ul.x, out.m_buffer + (y - ul.y)*out.m_width, 
			   out.m_width);
	}

	return true;
}

bool HRAYGray::roi(Point2D<float> point, Size2D<int32_t> size, float angle[2], HRAYGray& out)
{
	int32_t i;
	int32_t pos;
	int32_t x, y;
	int32_t ox, oy;
	int32_t hw, hh;
	Point2D<float> src;
	Point2D<float> dst;
	uint8_t *pDstBuf;
	float xrate, yrate;
	Affine aff(point.x, point.y, angle[0], angle[1]);

	if (m_width <= 0 || m_height <= 0) return false;

	if (size.width % 2 == 0 || size.height % 2 == 0) return false;

	hw = size.width >> 1;
	hh = size.height >> 1;

	i = 0;
	if (out.reshape(size.width, size.height) == false) return false;

	pDstBuf = out.data();
	for (y = -hh; y <= hh; y++)
	{
		for (x = -hw; x <= hw; x++)
		{
			src.set((float)x, (float)y);
			aff.map(1, src, dst);

			ox = static_cast<int32_t>(dst.x);
			oy = static_cast<int32_t>(dst.y);
			if (ox < 0 || oy < 0 ||
				ox >= m_width || oy >= m_height)
			{
				pDstBuf[i] = 255;
			}
			else
			{
				pos = oy * m_width + ox;
				xrate = dst.x - ox;
				yrate = dst.y - oy;

				pDstBuf[i] = (uint8_t)xvmInterpolation2D(pos, m_width, m_buffer, xrate, yrate);
			}
			i++;
		}
	}

	return true;
}

bool HRAYGray::gamma(const GammaTabel& tabel, HRAYGray& out)
{
	int32_t pos;
	const uint8_t *T;
	if (!out.reshape(m_width,m_height))
	{
		return false;
	}
	
	T = tabel.tabel();

	pos = 0;
	for (int32_t y = 0; y < m_height; y++)
	{
		for (int32_t x = 0; x < m_width; x++)
		{
			out.m_buffer[pos + x] = T[m_buffer[pos + x]];
		}
		pos += m_width;
	}

	return true;
}

bool HRAYGray::linebufs(Point2D<int32_t> head, Point2D<int32_t> tail, Hist1D<uint8_t>& lbuf)
{
	int32_t pos;
	int32_t ix, iy;
	float xrate, yrate;
	int32_t dis;
	std::vector<Point2D<float>> pts;

	if (m_width <= 0 || m_height <= 0) return false;

	mvSplitSegment(head, tail, pts);

	dis = pts.size();
	if (dis <= 0 || !lbuf.reshape(dis))
	{
		return false;
	}
	
	for (int32_t i = 0; i < dis; i++)
	{
		ix = static_cast<int32_t>(pts[i].x);
		iy = static_cast<int32_t>(pts[i].y);
		xrate = pts[i].x - ix;
		yrate = pts[i].y - iy;
		pos = iy * m_width + ix;
		lbuf[i] = (uint8_t)xvmInterpolation2D(pos, m_width, m_buffer, xrate, yrate);
	}

	return true;
}

int32_t HRAYGray::mean() const
{
	int32_t ibyte;
	int32_t mean;
	int32_t pos;

	if (m_width <= 0 || m_height <= 0)
	{
		return -1;
	}

	ibyte = m_width * m_height;
	
	mean = 0;
	pos = 0;
	for (int32_t y = 0; y < m_height; y++)
	{
		for (int32_t x = 0; x < m_width; x++)
		{
			mean += m_buffer[pos+x];
		}
		pos += m_width;
	}

	return mean / ibyte;
}

bool HRAYGray::gsmooth5x5(HRAYGray& out)
{
	/*
	*	const int16_t ker[5] = { 1, 4, 6, 4, 1 };
	*/
	const int16_t hsize = 2;

	uint32_t sum;
	int32_t imsize;
	int32_t stride;
	int32_t x, y, i, ypos;
	int32_t *pAuxTmp = NULL;
	uint32_t *pAuxIdx = NULL;
	int32_t whmax;
	int32_t *p = NULL;
	uint8_t *pSrc = m_buffer;
	uint8_t *pDst;

	if (m_width <= 0 || m_height <= 0 ||
		!out.reshape(m_width,m_height))
	{
		return false;
	}
	pDst = out.data();

	whmax = std::max(m_width, m_height) + 4;
	pAuxTmp = new int32_t[m_width*m_height];
	pAuxIdx = new uint32_t[whmax];
	p = pAuxTmp;

	stride = m_width;
	imsize = m_width*m_height;
	//	pAuxIdx += imsize;
	for (i = 0; i < hsize; i++)
	{
		pAuxIdx[i] = hsize - i;
		pAuxIdx[i + stride + hsize] = stride - 2 - i;
	}

	for (i = hsize; i < m_width + hsize; i++)
	{
		pAuxIdx[i] = i - hsize;
	}

	for (y = 0; y < m_height; y++)
	{
		for (x = 0; x < m_width; x++)
		{
			sum = pSrc[pAuxIdx[x + 0]] +
				((pSrc[pAuxIdx[x + 1]] + pSrc[pAuxIdx[x + 2]] +
				pSrc[pAuxIdx[x + 3]]) << 2) + (pSrc[pAuxIdx[x + 2]] << 1) +
				pSrc[pAuxIdx[x + 4]];

			pAuxTmp[x] = sum;
		}
		pAuxTmp += stride;
		pSrc += stride;
	}

	pAuxIdx[0] = stride << 1;
	pAuxIdx[1] = stride;
	pAuxIdx[m_height + 2] = (m_height - 2) * stride;
	pAuxIdx[m_height + 1] = (m_height - 1) * stride;

	ypos = 0;
	for (i = hsize; i < m_height + hsize; i++)
	{
		pAuxIdx[i] = ypos;
		ypos += stride;
	}

	pAuxTmp = p;
	for (x = 0; x < m_width; x++)
	{
		for (y = 0; y < m_height; y++)
		{
			ypos = pAuxIdx[y + 2] + x;
			sum = pAuxTmp[pAuxIdx[y] + x] +
				((pAuxTmp[pAuxIdx[y + 1] + x] + pAuxTmp[ypos] +
				pAuxTmp[pAuxIdx[y + 3] + x]) << 2) + (pAuxTmp[ypos] << 1) +
				pAuxTmp[pAuxIdx[y + 4] + x];

			pDst[ypos] = sum >> 8;
		}
	}

	delete[] pAuxIdx;
	delete[] pAuxTmp;

	return true;
}

bool HRAYGray::sgradx(Matrix2D<int16_t>& grad)
{
	int32_t x, y;
	int32_t pos, xpos;
	int16_t *pGrad;

	if (!grad.reshape(m_height, m_width)) return false;

	grad.zero();

	pos = m_width;
	pGrad = grad.data();
	for (y = 0; y < m_height -1; y++)
	{
		for (x = 0; x < m_width - 1; x++)
		{
			xpos = pos + x;
			pGrad[xpos] = m_buffer[xpos + 1] - m_buffer[xpos];
		}
		pos += m_width;
	}

	return true;
}

bool HRAYGray::integral(Matrix2D<uint32_t>& intimg)
{
	int32_t x, y;
	uint32_t s1;
	int32_t iwidth, iheight;
	uint32_t *pItgCur;
	uint8_t *pImgCur;


	if (m_width <= 0 || m_height <= 0 ||
		!intimg.reshape(m_height + 1, m_width + 1))
	{
		return false;
	}

	intimg.zero();

	pImgCur = m_buffer;
	pItgCur = intimg.data();

	iwidth = intimg.col();
	iheight = intimg.row();

	for (x = 0; x < iwidth; x++) *(pItgCur++) = 0;
	for (y = 1; y < iheight; y++)
	{
		*(pItgCur++) = 0;
		s1 = 0;
		for (x = 1; x < iwidth; x++) {
			uint8_t pix = *pImgCur++;
			s1 += pix;

			*pItgCur = *(pItgCur - iwidth) + s1;

			pItgCur++;
		}
	}

	return true;
}

bool HRAYGray::integral(Matrix2D<uint64_t>& intimg)
{
	int32_t x, y;
	uint32_t s1;
	int32_t iwidth, iheight;
	uint64_t *pItgCur;
	uint8_t *pImgCur;


	if (m_width <= 0 || m_height <= 0 ||
		!intimg.reshape(m_height + 1, m_width + 1))
	{
		return false;
	}

	intimg.zero();

	pImgCur = m_buffer;
	pItgCur = intimg.data();

	iwidth = intimg.col();
	iheight = intimg.row();

	for (x = 0; x < iwidth; x++) *(pItgCur++) = 0;
	for (y = 1; y < iheight; y++)
	{
		*(pItgCur++) = 0;
		s1 = 0;
		for (x = 1; x < iwidth; x++) {
			uint8_t pix = *pImgCur++;
			s1 += pix;

			*pItgCur = *(pItgCur - iwidth) + s1;

			pItgCur++;
		}
	}

	return true;
}

bool HRAYGray::hist(Hist1D<int32_t>& dhist)
{
	int32_t pos;
	int32_t *pData;
	if (m_width <= 0 || m_height <= 0)
	{
		return false;
	}

	if (!dhist.reshape(256)) return false;

	pData = dhist.data();
	dhist.zero();
	pos = 0;
	for (int32_t y = 0; y < m_height; y++)
	{
		for (int32_t x = 0; x < m_width; x++)
		{
			int32_t pix = m_buffer[pos + x];
			pData[pix]++;
		}
		pos += m_width;
	}

	return true;
}

bool HRAYGray::imnear(int32_t width, int32_t height, HRAYGray& out)
{
	int32_t xpos;
	int32_t x, y;
	int32_t iy;
	float xrate, yrate;
	int32_t *idx;
	if (m_width <= 0 || m_height <= 0) return false;

	if (!out.reshape(width, height)) return false;

	idx = new int32_t[width];

	xrate = static_cast<float>(m_width) / width;
	yrate = static_cast<float>(m_height) / height;

	for (x = 0; x < width; x++)
	{
		idx[x] = static_cast<int32_t>(x * xrate + 0.5f);
	}

	xpos = 0;
	for (y = 0; y < height; y++)
	{
		iy = static_cast<int32_t>(y * yrate + 0.5f);
		for (x = 0; x < width; x++)
		{
			int32_t pos = iy * m_width + idx[x];

			out.m_buffer[xpos + x] = m_buffer[pos];
		}
		xpos += m_width;
	}

	delete[] idx;
	return true;
}

bool HRAYGray::imblinear(int32_t width, int32_t height, HRAYGray& out)
{
	int32_t xpos;
	int32_t x, y;
	int32_t iy;
	float fy;
	float xrate, yrate;
	float *fidx;
	int32_t *idx;
	if (m_width <= 0 || m_height <= 0) return false;

	if (!out.reshape(width, height)) return false;

	idx = new int32_t[width];
	fidx = new float[width];

	xrate = static_cast<float>(m_width) / width;
	yrate = static_cast<float>(m_height) / height;

	for (x = 0; x < width; x++)
	{
		float trate = x * xrate;
		idx[x] = static_cast<int32_t>(trate);
		fidx[x] = trate - idx[x];
	}

	xpos = 0;
	for (y = 0; y < height; y++)
	{
		fy = y * yrate;
		iy = static_cast<int32_t>(fy);
		fy -= iy;
		for (x = 0; x < width; x++)
		{
			int32_t pos = iy * m_width + idx[x];

			out.m_buffer[xpos + x] = (uint8_t)xvmInterpolation2D(pos,m_width,m_buffer,fidx[x],fy);
		}
		xpos += m_width;
	}

	delete[] fidx;
	delete[] idx;
	
	return true;
}

bool HRAYGray::xproj(Hist1D<int32_t>& proj)
{
	int32_t pos;
	if (m_width <= 0 || m_height <= 0 ||
		!proj.reshape(m_width))
	{
		return false;
	}
	
	proj.zero();
	pos = 0;
	for (int32_t y = 0; y < m_height; y++)
	{
		for (int32_t x = 0; x < m_width; x++)
		{
			proj[x] += m_buffer[pos + x];
		}
		pos += m_width;
	}

	return true;
}

bool HRAYGray::yproj(Hist1D<int32_t>& proj)
{
	int32_t pos;
	if (!m_buffer || m_width <= 0 || m_height <= 0 ||
		!proj.reshape(m_height))
	{
		return false;
	}

	proj.zero();
	pos = 0;
	for (int32_t y = 0; y < m_height; y++)
	{
		for (int32_t x = 0; x < m_width; x++)
		{
			proj[y] += m_buffer[pos + x];
		}
		pos += m_width;
	}

	return true;
}

int32_t HRAYGray::width() const
{
	return m_width; 
}

int32_t HRAYGray::height() const
{
	return m_height;
}

uint8_t* HRAYGray::data() const
{
	return m_buffer;
}

uint8_t HRAYGray::data(int32_t pos)
{
	return m_buffer[pos];
}

uint8_t HRAYGray::data(int32_t x, int32_t y)
{
	return m_buffer[y*m_width + x];
}

bool HRAYGray::sgrady(Matrix2D<int16_t>& grad)
{
	int32_t x, y;
	int32_t pos, xpos;
	int16_t *pGrad;

	if (!grad.reshape(m_height, m_width)) return false;

	grad.zero();

	pos = m_width;
	pGrad = grad.data();
	for (y = 1; y < m_height; y++)
	{
		for (x = 1; x < m_width; x++)
		{
			xpos = pos + x;
			pGrad[xpos] = m_buffer[xpos + 1] - m_buffer[xpos];
		}
		pos += m_width;
	}

	return true;
}

