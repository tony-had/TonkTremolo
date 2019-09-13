/*
  ==============================================================================

	LFO.h
	Created: 13 Sep 2019 6:27:06pm
	Author:  tonyh

  ==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"

class Lfo
{
public:
	Lfo();
	~Lfo();

	void reset();

	void setSampleRate(double inSampleRate);
	void setBufferSize(int inBufferSize);

	void process(float frequency, float depth, int numberOfSamples);

	std::vector<float> getBuffer();

private:
	double sampleRate;
	int bufferSize;
	float phase;
	std::vector<float> buffer;
};