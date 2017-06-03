#include "Matrix.h"
#include "hrayimgs.h"
#include "Feature.h"
#include <vector>
#include <cstring>
#include <sstream>

#define MAT_ABS(x) ((x < 0) ? -(double)(x) : (double)(x)) 

template <typename T>
Matrix2D<T>::Matrix2D() : m_data(0), m_row(0), m_col(0)
{

}

template <typename T>
Matrix2D<T>::Matrix2D(int32_t row, int32_t col, T *data /*= 0*/) : Matrix2D()
{
	if (row > 0 && col > 0)
	{
		m_data = new T[row * col];
		m_row = row;
		m_col = col;
		if (data)
		{
			memcpy(m_data, data, m_row*m_col*sizeof(T));
		}
		else
		{
			memset(m_data, 0, m_row * m_col * sizeof(T));
		}
	}
}

template <typename T>
Matrix2D<T>::Matrix2D(const Matrix2D<T>& rhs) : Matrix2D(rhs.m_row,rhs.m_col,rhs.m_data)
{
	
}

template <typename T>
Matrix2D<T>::~Matrix2D()
{
	if (m_data)
	{
		delete[] m_data;
	}

	m_data = NULL;
	m_row = 0;
	m_col = 0;
}


template <typename T>
bool Matrix2D<T>::reshape(int32_t row, int32_t col)
{
	if (row <= 0 || col <= 0)
	{
		return false;
	}

	if (m_data) delete[] m_data;
	m_data = new T[row * col];
	if (!m_data) return false;
	m_row = row;
	m_col = col;

	return true;
}


template <typename T>
T * Matrix2D<T>::data() const
{
	return m_data;
}


template <typename T>
void Matrix2D<T>::thres(T thres)
{
	int32_t pos = 0;

	for (int32_t y = 0; y < m_row; y++)
	{
		for (int32_t x = 0; x < m_col; x++)
		{
			if (m_data[pos + x] < thres) m_data[pos + x] = 0;
		}
		pos += m_col;
	}
}

template <typename T>
void Matrix2D<T>::save(std::ofstream& file)
{
	int32_t x, y;

	if (!file.good()) return ;

	for (y = 0; y < m_row; y++)
	{
		for (x = 0; x < m_col; x++)
		{
			file << m_data[y*m_col + x];
			if (x == m_col - 1)
			{
				file << std::endl;
			}
			else
			{
				file << ",";
			}
		}
	}
}

template <typename T>
bool Matrix2D<T>::read(std::string& fileName, bool isFloat)
{
	int32_t nline;
	int32_t nWord;
	int32_t fWord;
	std::vector<T> temp;
	std::string lstr;
	std::string out;
	T node;
	std::ifstream file(fileName);

	if (!file.good()) return false;

	nline = 0;
	fWord = 0;
	while (!file.eof())
	{
		char cbuf;
		lstr.clear();
		nWord = 0;
		while (!file.eof())
		{
			file.get(cbuf);
			if (cbuf == '\n')
			{
				nline++;
				break;
			}
			
			if (cbuf == ',')
			{
				nWord++;
				cbuf = ' ';
			}
			lstr.push_back(cbuf);
		}
		nWord += (lstr.size() > 0);
		
		std::istringstream istr(lstr);
		for (; nWord > 0; nWord--)
		{
			istr >> out;
			if (isFloat)
			{
				node = static_cast<T>(atof(out.c_str()));
			}
			else
			{
				node = static_cast<T>(atoi(out.c_str()));
			}

			temp.push_back(node);
		}
		fWord += nWord;
	}

	if (fWord % nline != 0)
	{
		return false;
	}

	reshape(nline, fWord / nline);

	for (int32_t i = 0; i < fWord; i++)
	{
		m_data[i] = temp[i];
	}

	file.close();

	return false;
}

template <typename T>
void Matrix2D<T>::thres(T minThr, T maxThr)
{
	int32_t x, y;

	for (y = 0; y < m_row; y++)
	{
		for (x = 0; x < m_col; x++)
		{
			T& data = m_data[y * m_col + x];
			if (data > minThr && data < maxThr) data = 0;
		}
	}
}

template <typename T>
void Matrix2D<T>::zero()
{
	if (m_data)	memset(m_data, 0, m_row*m_col*sizeof(T));
}


template <typename T>
int32_t Matrix2D<T>::row() const
{
	return m_row;
}

template <typename T>
int32_t Matrix2D<T>::col() const
{
	return m_col;
}

template <typename T>
bool Matrix2D<T>::toFeature(int32_t rIdx, Feature *feature)
{
	float *pData;
	T *data;
	if (m_row <= 0 || m_col <= 0 || m_data == NULL || 
		rIdx < 0 || rIdx >= m_row || !feature->reshape(m_col))
	{
		return false;
	}


	data = m_data + rIdx * m_col;
	pData = feature->data();
	for (int32_t i = 0; i < m_col; i++)
	{
		pData[i] = static_cast<float>(data[i]);
	}
	
	return true;
}


template <typename T>
void Matrix2D<T>::save(std::ofstream& file, int32_t *pLabel, int32_t nLabel, float eps /*= MAT_EPS*/)
{
	int32_t x, y;
	T value;
	if (!file.good() || nLabel != m_row) return;

	for (y = 0; y < m_row; y++)
	{
		file << pLabel[y] << " ";
		for (x = 0; x < m_col; x++)
		{
			value = m_data[y*m_col + x];
			if ( MAT_ABS(value) >= eps)
			{
				file << x + 1 << ":" << m_data[y*m_col + x] << " ";
			}
		}
	}
}

template class Matrix2D<float>;
template class Matrix2D<double>;
template class Matrix2D<uint32_t>;
template class Matrix2D<uint64_t>;
template class Matrix2D<int32_t>;
template class Matrix2D<int16_t>;
template class Matrix2D<uint8_t>;
