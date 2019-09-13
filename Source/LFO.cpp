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

void Lfo::process(float frequency, float depth, int numberOfSamples)
{
	std::vector<float>::iterator lfoBufferSample;
	for (lfoBufferSample = buffer.begin(); lfoBufferSample != buffer.end(); lfoBufferSample++)
	{
		phase += frequency / sampleRate;

		if (phase > 1.f)
			phase -= 1.f;

		const float lfoValue = sinf(phase * MathConstants<float>::twoPi) * depth;
		*lfoBufferSample = lfoValue;
	}
}

std::vector<float> Lfo::getBuffer()
{
	return buffer;
}
