#include "Feature.h"
#include "Matrix.h"
#include <vector>
#include <iostream>
#include <sstream>

Feature::Feature(int32_t nFeatDims /*= 1*/) : m_ndim(nFeatDims), m_data(0)
{
	if (m_ndim > 0)
	{
		m_data = new float[m_ndim];
		memset(m_data, 0, m_ndim*sizeof(float));
	}
}

bool Feature::reshape(int32_t nFeatDims)
{
	if (nFeatDims <= 0)
	{
		return false;
	}

	if (nFeatDims != m_ndim)
	{
		if (m_data) delete[] m_data;
		m_data = new float[nFeatDims];
		if (!m_data) return false;
		m_ndim = nFeatDims;
	}

	return true;
}

bool Feature::toMat(int32_t rIdx, Matrix2D<float>& mat)
{
	float *pData = mat.data();

	if (!pData || mat.col() != m_ndim ||
		rIdx < 0 || rIdx >= mat.row())
	{
		return false;
	}

	memcpy(pData + rIdx*mat.col(), m_data, m_ndim*sizeof(float));

	return true;
}

Feature::~Feature()
{
	if (m_data)
	{
		delete[] m_data;
	}
	m_data = NULL;
	m_ndim = 0;
}

void Feature::save(std::ofstream& out, int32_t label /*= 1*/, float eps /*= FEA_EPS*/)
{
	if (out.good())
	{
		out << (int32_t)label << " ";
		for (int32_t i = 0; i < m_ndim; i++)
		{
			if (m_data[i] > -eps && m_data[i] < eps) continue;
			out << i + 1 << ":" << m_data[i] << " ";
		}
		out << std::endl;
	}
}

bool Feature::load(std::ifstream& in, int32_t *label /*= 0*/)
{
	int32_t idx;
	float value;
	int32_t nWord;
	char cbuf;
	std::string line;

	nWord = 0;
	if (in.good())
	{
 		while (!in.eof())
		{
			in.get(cbuf);
		
			if (cbuf == '\n')
			{
				break;
			}
			if (cbuf == ':')
			{
				nWord++;
				cbuf = ' ';
			}
			line.push_back(cbuf);
		}

		memset(m_data, 0, m_ndim*sizeof(float));

		std::istringstream strin(line);
		std::string word;

		strin >> *label;
		for (int32_t i = 0; i < nWord; i++)
		{
			strin >> word;
			idx = std::atoi(word.c_str());
			strin >> word;
			value = std::atof(word.c_str());
			if (idx <= 0 || idx > m_ndim) return false;
			m_data[idx-1] = value;
		}
	}

	return true;
}

bool Feature::extract(void *input, void *param /*= 0*/)
{
	return true;
}

float Feature::operator[](size_t index)
{
	return m_data[index];
}

int32_t Feature::length() const
{
	return m_ndim;
}

float* Feature::data() const
{
	return m_data;
}

