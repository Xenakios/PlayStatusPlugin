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
	plugfont = Font{ "Comic Sans MS",100.0, 0 }; // 100 is size, 0 is style normal
	setSize (500, 150);
	startTimer(50);
}

PlayStatusPluginAudioProcessorEditor::~PlayStatusPluginAudioProcessorEditor()
{
}

//==============================================================================
void PlayStatusPluginAudioProcessorEditor::paint (Graphics& g)
{
	const auto& info = processor.positionInfo;
	String status{ "STOPPED" };
	Colour color{ Colours::black };
	if (info.isPlaying)
	{
		color = Colours::green;
		status = "PLAYING";
	}
	if (info.isRecording)
	{
		color = Colours::red;
		status = "RECORDING";
	}
	g.fillAll(color);
	
	g.setColour(Colours::white);
	g.setFont(plugfont);
	g.drawText(status, 0, 0, getWidth(), getHeight(), Justification::centred);
	
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
