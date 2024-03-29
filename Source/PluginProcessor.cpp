/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
PlayStatusPluginAudioProcessor::PlayStatusPluginAudioProcessor()
#ifndef JucePlugin_PreferredChannelConfigurations
     : AudioProcessor (BusesProperties()
                     #if ! JucePlugin_IsMidiEffect
                      #if ! JucePlugin_IsSynth
                       .withInput  ("Input",  AudioChannelSet::stereo(), true)
                      #endif
                       .withOutput ("Output", AudioChannelSet::stereo(), true)
                     #endif
                       )
#endif
{
}

PlayStatusPluginAudioProcessor::~PlayStatusPluginAudioProcessor()
{
}

//==============================================================================
const String PlayStatusPluginAudioProcessor::getName() const
{
    return JucePlugin_Name;
}

bool PlayStatusPluginAudioProcessor::acceptsMidi() const
{
   #if JucePlugin_WantsMidiInput
    return true;
   #else
    return false;
   #endif
}

bool PlayStatusPluginAudioProcessor::producesMidi() const
{
   #if JucePlugin_ProducesMidiOutput
    return true;
   #else
    return false;
   #endif
}

bool PlayStatusPluginAudioProcessor::isMidiEffect() const
{
   #if JucePlugin_IsMidiEffect
    return true;
   #else
    return false;
   #endif
}

double PlayStatusPluginAudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int PlayStatusPluginAudioProcessor::getNumPrograms()
{
    return 1;   // NB: some hosts don't cope very well if you tell them there are 0 programs,
                // so this should be at least 1, even if you're not really implementing programs.
}

int PlayStatusPluginAudioProcessor::getCurrentProgram()
{
    return 0;
}

void PlayStatusPluginAudioProcessor::setCurrentProgram (int)
{
}

const String PlayStatusPluginAudioProcessor::getProgramName (int)
{
    return {};
}

void PlayStatusPluginAudioProcessor::changeProgramName (int index, const String&)
{
}

//==============================================================================
void PlayStatusPluginAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
	positionInfo.isPlaying = false;
	positionInfo.isRecording = false;
}

void PlayStatusPluginAudioProcessor::releaseResources()
{
    
}

#ifndef JucePlugin_PreferredChannelConfigurations
bool PlayStatusPluginAudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
{
  #if JucePlugin_IsMidiEffect
    ignoreUnused (layouts);
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

void PlayStatusPluginAudioProcessor::processBlock (AudioBuffer<float>& buffer, MidiBuffer& midiMessages)
{
    ScopedNoDenormals noDenormals;
    auto totalNumInputChannels  = getTotalNumInputChannels();
    auto totalNumOutputChannels = getTotalNumOutputChannels();
	for (auto i = totalNumInputChannels; i < totalNumOutputChannels; ++i)
        buffer.clear (i, 0, buffer.getNumSamples());
	AudioPlayHead* ph = getPlayHead();
	jassert(ph != nullptr); // plugin is useless in hosts which don't provide the playhead
	if (ph)
	{
		ph->getCurrentPosition(positionInfo);
	}
    // Nothing to do with the audio
}

//==============================================================================
bool PlayStatusPluginAudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

AudioProcessorEditor* PlayStatusPluginAudioProcessor::createEditor()
{
    return new PlayStatusPluginAudioProcessorEditor (*this);
}

//==============================================================================
void PlayStatusPluginAudioProcessor::getStateInformation (MemoryBlock& destData)
{
    // You should use this method to store your parameters in the memory block.
    // You could do that either as raw data, or use the XML or ValueTree classes
    // as intermediaries to make it easy to save and load complex data.
}

void PlayStatusPluginAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    // You should use this method to restore your parameters from this memory block,
    // whose contents will have been created by the getStateInformation() call.
}

//==============================================================================
// This creates new instances of the plugin..
AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new PlayStatusPluginAudioProcessor();
}
