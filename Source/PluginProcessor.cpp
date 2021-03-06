/*
  ==============================================================================

	This file was auto-generated!

	It contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
TonkTremoloAudioProcessor::TonkTremoloAudioProcessor()
#ifndef JucePlugin_PreferredChannelConfigurations
	: AudioProcessor(BusesProperties()
#if ! JucePlugin_IsMidiEffect
#if ! JucePlugin_IsSynth
		.withInput("Input", AudioChannelSet::stereo(), true)
#endif
		.withOutput("Output", AudioChannelSet::stereo(), true)
#endif
	),
#endif
	parameterManager(*this)
{
	lfo[0].reset(new Lfo());
	lfo[1].reset(new Lfo());
}

TonkTremoloAudioProcessor::~TonkTremoloAudioProcessor()
{
}

//==============================================================================
const String TonkTremoloAudioProcessor::getName() const
{
	return JucePlugin_Name;
}

bool TonkTremoloAudioProcessor::acceptsMidi() const
{
#if JucePlugin_WantsMidiInput
	return true;
#else
	return false;
#endif
}

bool TonkTremoloAudioProcessor::producesMidi() const
{
#if JucePlugin_ProducesMidiOutput
	return true;
#else
	return false;
#endif
}

bool TonkTremoloAudioProcessor::isMidiEffect() const
{
#if JucePlugin_IsMidiEffect
	return true;
#else
	return false;
#endif
}

double TonkTremoloAudioProcessor::getTailLengthSeconds() const
{
	return 0.0;
}

int TonkTremoloAudioProcessor::getNumPrograms()
{
	return 1;   // NB: some hosts don't cope very well if you tell them there are 0 programs,
				// so this should be at least 1, even if you're not really implementing programs.
}

int TonkTremoloAudioProcessor::getCurrentProgram()
{
	return 0;
}

void TonkTremoloAudioProcessor::setCurrentProgram(int index)
{
}

const String TonkTremoloAudioProcessor::getProgramName(int index)
{
	return {};
}

void TonkTremoloAudioProcessor::changeProgramName(int index, const String& newName)
{
}

//==============================================================================
void TonkTremoloAudioProcessor::prepareToPlay(double sampleRate, int samplesPerBlock)
{
	for (int i = 0; i < 2; i++)
	{
		lfo[i]->setSampleRate(sampleRate);
		lfo[i]->setBufferSize(samplesPerBlock);
	}
}

void TonkTremoloAudioProcessor::releaseResources()
{
	for (int i = 0; i < 2; i++)
	{
		lfo[i]->reset();
	}
}

#ifndef JucePlugin_PreferredChannelConfigurations
bool TonkTremoloAudioProcessor::isBusesLayoutSupported(const BusesLayout& layouts) const
{
#if JucePlugin_IsMidiEffect
	ignoreUnused(layouts);
	return true;
#else
	// This is the place where you check if the layout is supported.
	// In this template code we only support mono or stereo.
	if (layouts.getMainOutputChannelSet() != AudioChannelSet::mono()
		&& layouts.getMainOutputChannelSet() != AudioChannelSet::stereo())
		return false;

	// This checks if the input layout matches the output layout
#if ! JucePlugin_IsSynth
	if (layouts.getMainOutputChannelSet() != layouts.getMainInputChannelSet())
		return false;
#endif

	return true;
#endif
}
#endif

void TonkTremoloAudioProcessor::processBlock(AudioBuffer<float>& buffer, MidiBuffer& midiMessages)
{
	ScopedNoDenormals noDenormals;
	auto totalNumInputChannels = getTotalNumInputChannels();
	auto totalNumOutputChannels = getTotalNumOutputChannels();

	// In case we have more outputs than inputs, this code clears any output
	// channels that didn't contain input data, (because these aren't
	// guaranteed to be empty - they may contain garbage).
	// This is here to avoid people getting screaming feedback
	// when they first compile a plugin, but obviously you don't need to keep
	// this code if your algorithm always overwrites all the output channels.
	for (auto i = totalNumInputChannels; i < totalNumOutputChannels; ++i)
		buffer.clear(i, 0, buffer.getNumSamples());

	for (int channel = 0; channel < totalNumInputChannels; ++channel)
	{
		auto* channelData = buffer.getWritePointer(channel);

		float tremoloDepth = *parameterManager.valueTreeState.getRawParameterValue(tremoloFloatParameters[tremoloDepthParameter].parameterId);
		float lfoFrequency = *parameterManager.valueTreeState.getRawParameterValue(tremoloFloatParameters[lfoFrequencyParameter].parameterId);
		int lfoWaveformType = *parameterManager.valueTreeState.getRawParameterValue(tremoloChoiceParameters[lfoWaveformTypeParameter].parameterId);

		lfo[channel]->process(lfoFrequency, 1.f - tremoloDepth, 1.f, lfoWaveformType, buffer.getNumSamples());
		float* lfoBuffer = lfo[channel]->getBuffer();

		for (int i = 0; i < buffer.getNumSamples(); i++)
		{
			channelData[i] *= lfoBuffer[i];
		}
	}
}

//==============================================================================
bool TonkTremoloAudioProcessor::hasEditor() const
{
	return false; // (change this to false if you choose to not supply an editor)
}

AudioProcessorEditor* TonkTremoloAudioProcessor::createEditor()
{
	return new TonkTremoloAudioProcessorEditor(*this);
}

//==============================================================================
void TonkTremoloAudioProcessor::getStateInformation(MemoryBlock& destData)
{
	// You should use this method to store your parameters in the memory block.
	// You could do that either as raw data, or use the XML or ValueTree classes
	// as intermediaries to make it easy to save and load complex data.
}

void TonkTremoloAudioProcessor::setStateInformation(const void* data, int sizeInBytes)
{
	// You should use this method to restore your parameters from this memory block,
	// whose contents will have been created by the getStateInformation() call.
}

//==============================================================================
// This creates new instances of the plugin..
AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
	return new TonkTremoloAudioProcessor();
}
