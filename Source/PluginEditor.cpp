/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
PlayStatusPluginAudioProcessorEditor::PlayStatusPluginAudioProcessorEditor (PlayStatusPluginAudioProcessor& p)
    : AudioProcessorEditor (&p), processor (p)
{
    setSize (400, 100);
	startTimer(50);
}

PlayStatusPluginAudioProcessorEditor::~PlayStatusPluginAudioProcessorEditor()
{
}

//==============================================================================
void PlayStatusPluginAudioProcessorEditor::paint (Graphics& g)
{
	const auto& info = processor.positionInfo;
	String status;
	Colour color{ Colours::black };
	if (info.isPlaying)
	{
		color = Colours::green;
		status = "PLAY";
	}
	if (info.isRecording)
	{
		color = Colours::red;
		status = "RECORD";
	}
	g.fillAll(color);
	if (status.isEmpty() == false)
	{
		g.setColour(Colours::white);
		g.setFont(40.0);
		g.drawText(status, 0, 0, getWidth(), getHeight(), Justification::centred);
	}
}

void PlayStatusPluginAudioProcessorEditor::resized()
{
    // This is generally where you'll want to lay out the positions of any
    // subcomponents in your editor..
}

void PlayStatusPluginAudioProcessorEditor::timerCallback()
{
	repaint();
}
