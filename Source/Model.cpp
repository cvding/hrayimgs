#include "Model.h"
#include <cstdio>
#include <cstring>
#include <cmath>

GammaTabel::GammaTabel()
{
	memset(m_model, 0, 256);
}

GammaTabel::GammaTabel(float sigma, float gain /*= 1.f*/)
{
	reset(sigma, gain);
}

GammaTabel::~GammaTabel()
{
	memset(m_model, 0, 256);
}

void GammaTabel::reset(float sigma, float gain /*= 1.f*/)
{
	float step = 1.f / 256;
	float start = 0;
	float value;
	for (int32_t i = 0; i < 256; i++)
	{
		value = gain * powf(start,sigma);

		m_model[i] = (value >= 1) ? 255 : static_cast<uint8_t>(value * 255);

		start += step;
	}
}

const uint8_t* GammaTabel::tabel() const
{
	return m_model;
}

