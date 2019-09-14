/*
  ==============================================================================

	TremoloParameters.h
	Created: 13 Sep 2019 11:52:09am
	Author:  tonyh

  ==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"

enum TremoloFloatParametersEnum
{
	tremoloDepthParameter = 0,
	lfoFrequencyParameter,
	totalNumFloatParameters
};

enum TremoloChoiceParametersEnum
{
	lfoWaveformTypeParameter = 0,
	totalNumChoiceParameters
};

struct TremoloFloatParameter
{
	String parameterId;
	String parameterName;
	NormalisableRange<float> normalisableRange;
	float defaultValue;
	String parameterLabel;
};

struct TremoloChoiceParameter
{
	String parameterId;
	String parameterName;
	StringArray choices;
	int defaultItemIndex;
};

static TremoloFloatParameter tremoloFloatParameters[totalNumFloatParameters] = 
{
	{"TremoloDepth", "Tremolo Depth", NormalisableRange<float>(0.f, 1.f), 50.f, ""},
	{"LfoFrequency", "LFO Frequency", NormalisableRange<float>(0.f, 20.f), 1.f, "Hz"}
};

static TremoloChoiceParameter tremoloChoiceParameters[totalNumChoiceParameters]
{
	{"LfoWaveformType", "LFO Waveform Type", StringArray("Sine", "Triangle", "Saw (rising)", "Saw (falling)", "Square", "Square (sloped edges)"), 0}
};
