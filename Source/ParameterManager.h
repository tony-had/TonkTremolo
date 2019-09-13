/*
  ==============================================================================

	ParameterManager.h
	Created: 13 Sep 2019 11:44:56am
	Author:  tonyh

  ==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"
#include "TremoloParameters.h"

class ParameterManager
{
public:
	ParameterManager(AudioProcessor&);
	~ParameterManager();

	AudioProcessorValueTreeState::ParameterLayout createParameterLayout();

	AudioProcessorValueTreeState valueTreeState;
};
