/*
  ==============================================================================

	LFO.cpp
	Created: 13 Sep 2019 6:27:06pm
	Author:  tonyh

  ==============================================================================
*/

#include "LFO.h"

Lfo::Lfo() :
	sampleRate(-1),
	bufferSize(-1),
	phase(0.f)
{
	std::fill(buffer.begin(), buffer.end(), 0);
}

Lfo::~Lfo()
{
}

void Lfo::reset()
{
	phase = 0.f;
	std::fill(buffer.begin(), buffer.end(), 0);
}

void Lfo::setSampleRate(double inSampleRate)
{
	sampleRate = inSampleRate;
}

void Lfo::setBufferSize(int inBufferSize)
{
	bufferSize = inBufferSize;
	buffer.resize(bufferSize);
}

void Lfo::process(float frequency, float rangeMin, float rangeMax, int numberOfSamples)
{
	std::vector<float>::iterator lfoBufferSample;
	for (lfoBufferSample = buffer.begin(); lfoBufferSample != buffer.end(); lfoBufferSample++)
	{
		phase += frequency / sampleRate;

		if (phase > 1.f)
			phase -= 1.f;

		const float lfoValue = sinf(phase * MathConstants<float>::twoPi);
		*lfoBufferSample = jmap(lfoValue, -1.f, 1.f, rangeMin, rangeMax);
	}
}

float* Lfo::getBuffer()
{
	return &buffer[0];
}

float Lfo::triangleWave(float inPhase)
{
	float valueAtPhase;

	if (inPhase > 0.25f && inPhase < 0.75f)
	{
		valueAtPhase = 2.f - 4 * inPhase;
	}
	else
	{
		valueAtPhase = 4 * inPhase;
	}
	return valueAtPhase;
}

float Lfo::sawWave(float inPhase)
{
	float valueAtPhase;

	if (inPhase < 0.5f)
	{
		valueAtPhase = 2 * inPhase;
	}
	else
	{
		valueAtPhase = 2 * inPhase - 2.f;
	}

	return valueAtPhase;
}

float Lfo::inverseSawWave(float inPhase)
{
	float valueAtPhase;

	if (inPhase < 0.5f)
	{
		valueAtPhase = -2 * inPhase;
	}
	else
	{
		valueAtPhase = -2 * inPhase + 2.f;
	}

	return valueAtPhase;
}

float Lfo::squareWave(float inPhase)
{
	float valueAtPhase;

	if (inPhase < 0.5f)
	{
		valueAtPhase = 1.f;
	}
	else
	{
		valueAtPhase = -1.f;
	}

	return valueAtPhase;
}

float Lfo::slopedSquareWave(float inPhase)
{
	float valueAtPhase;

	if (inPhase < 0.02f)
	{
		valueAtPhase = 50 * inPhase;
	}
	else if (inPhase < 0.48f)
	{
		valueAtPhase = 1.f;
	}
	else if (inPhase < 0.52f)
	{
		valueAtPhase = -50 * inPhase + 25.f;
	}
	else if (inPhase < 0.98f)
	{
		valueAtPhase = -1.f;
	}
	else
	{
		valueAtPhase = 50 * inPhase - 50.f;
	}

	return valueAtPhase;
}
