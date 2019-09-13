/*
  ==============================================================================

	ParameterManager.cpp
	Created: 13 Sep 2019 11:44:56am
	Author:  tonyh

  ==============================================================================
*/

#include "ParameterManager.h"

ParameterManager::ParameterManager(AudioProcessor& p) :
	valueTreeState(p,
		nullptr,
		"TONKTremolo",
		createParameterLayout())
{
}

ParameterManager::~ParameterManager()
{
}

AudioProcessorValueTreeState::ParameterLayout ParameterManager::createParameterLayout()
{
	AudioProcessorValueTreeState::ParameterLayout parameterLayout;

	// Add float parameters
	for (int i = 0; i < totalNumFloatParameters; i++)
	{
		parameterLayout.add(std::make_unique<AudioParameterFloat>(tremoloFloatParameters[i].parameterId,
			tremoloFloatParameters[i].parameterName,
			tremoloFloatParameters[i].normalisableRange,
			tremoloFloatParameters[i].defaultValue,
			tremoloFloatParameters[i].parameterLabel));
	}

	// Add choice parameters
	for (int i = 0; i < totalNumChoiceParameters; i++)
	{
		parameterLayout.add(std::make_unique<AudioParameterChoice>(tremoloChoiceParameters[i].parameterId,
			tremoloChoiceParameters[i].parameterName,
			tremoloChoiceParameters[i].choices,
			tremoloChoiceParameters[i].defaultItemIndex));
	}
	
	return parameterLayout;
}
