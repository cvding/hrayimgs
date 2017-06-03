#include "hist1d.h"
#include <string.h>
#include <cstdlib>

#define xvmSign(x) ((x >= 0) - (x <= 0))

template class HistPeak<int32_t>;
template class HistPeak<uint8_t>;
template class HistPeak<int16_t>;
template class HistPeak<float>;
template class HistPeak<double>;

template class Hist1D<int32_t>;
template class Hist1D<float>;
template class Hist1D<uint8_t>;
template class Hist1D<int16_t>;
template class Hist1D<double>;




template <typename T>
HistPeak<T>::HistPeak()
{
	this->type = PEAK_TOP;
	this->pidx = 0;
	this->pval = 0;
}


template <typename T>
HistPeak<T>::~HistPeak()
{
	this->type = PEAK_TOP;
	this->pidx = 0;
	this->pval = 0;
}


template <typename T>
Hist1D<T>::Hist1D() : m_nhist(0), m_phist(0)
{

}


template <typename T>
Hist1D<T>::Hist1D(const Hist1D& rhs) : m_nhist(0), m_phist(0)
{
	if (rhs.m_nhist > 0 && rhs.m_phist)
	{
		m_nhist = rhs.m_nhist;
		m_phist = new T[rhs.m_nhist];
		memcpy(m_phist, rhs.m_phist, m_nhist*sizeof(T));
	}
}

template <typename T>
Hist1D<T>::~Hist1D()
{
	if (m_phist) delete[] m_phist;
	m_phist = NULL;
	m_nhist = 0;
}

template <typename T>
Hist1D<T>::Hist1D(int32_t nHist, T *pHist /*= 0*/) : m_nhist(0), m_phist(0)
{
	if (nHist > 0)
	{
		m_nhist = nHist;
		m_phist = new T[nHist];
		if (pHist) memcpy(m_phist, pHist, nHist*sizeof(T));
	}
}


template <typename T>
void Hist1D<T>::zero()
{
	if (m_phist) memset(m_phist, 0, m_nhist*sizeof(T));
}

template <typename T>
int32_t Hist1D<T>::length() const
{
	return m_nhist;
}

template <typename T>
T* Hist1D<T>::data() const
{
	return m_phist;
}

template <typename T>
bool Hist1D<T>::reshape(int32_t nHist)
{
	if (nHist <= 0) return false;

	if (nHist != m_nhist)
	{
		m_nhist = nHist;
		if (m_phist) delete[] m_phist;
		m_phist = new T[nHist];
		if (!m_phist) return false;
	}

	return true;
}


template <typename T>
T& Hist1D<T>::operator[](size_t index)
{
	return m_phist[index];
}

template <typename T>
bool Hist1D<T>::dif(Hist1D& dif, int32_t dr /*= 1*/)
{
	T sum;
	if (!dif.reshape(m_nhist)) return false;

	dif.zero();
	for (int32_t i = dr; i < m_nhist - dr; i++)
	{
		sum = 0;
		for (int32_t j = 0; j < dr; j++)
		{
			sum += m_phist[i + j] - m_phist[i - j];
		}
		dif.m_phist[i] = sum;
	}

	return true;
}

template <typename T>
void Hist1D<T>::findPeak(std::vector<HistPeak<T>>& peak)
{
	int32_t i, j, k;
	int32_t aux;
	int32_t m;
	int8_t *pSign = new int8_t[m_nhist];
	int32_t nHist = m_nhist;
	T *pHist = m_phist;
	HistPeak<T> node;

	peak.clear();
	/** idx:0 is not peak */
	pSign[0] = 0;

	/*-------------------------[calc 1-diff]---------------------------*/
	for (i = 1; i < nHist; i++)
	{
		aux = pHist[i] - pHist[i - 1];

		//		xvmSign(aux,sign);
		pSign[i] = xvmSign(aux);
	}

	/*-------------------------[replace 0]---------------------------*/
	m = i - 1;
	if (pSign[m] == 0)
	{
		j = m;
		while (j > 0 && pSign[j] == 0) j--;
		pSign[m] = -pSign[j];
	}

	for (j = i - 1; j > 1; j--)
	{
		if (pSign[j] == 0)
		{
			pSign[j] = pSign[j + 1];
		}
	}

	/*-------------------------[calc 2-diff]---------------------------*/
	k = 0;
	for (i = 1; i < nHist - 1; i++)
	{
		aux = pSign[i + 1] - pSign[i];

		if (aux == -2)
		{
			node.pidx = i;
			node.type = PEAK_TOP;
			node.pval = pHist[i];
			
			peak.push_back(node);
		}
		else if (aux == 2)
		{
			node.pidx = i;
			node.type = PEAK_BOT;
			node.pval = pHist[i];

			peak.push_back(node);
		}
		else
		{
			// do nothing
		}
	}

	delete[] pSign;
}

