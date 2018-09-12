//
//  TransportBar.cpp
//  JuceBasicAudio
//
//  Created by Stefan Ruffler on 22/12/2016.
//
//

#include "TransportBar.hpp"

TransportBar::TransportBar(SequencerGUI& sequencerGUI_) : sequencerGui(sequencerGUI_)
{
    addAndMakeVisible(&playButton);
    playButton.addListener(this);
    playButton.setButtonText("Play");
    playButton.setColour(TextButton::buttonColourId, Colours::darkgrey);
    playButton.setColour(TextButton::buttonOnColourId, Colours::darkgreen);
    
    addAndMakeVisible(timeSigniture);
    timeSigniture.addListener(this);
    timeSigniture.addItem("4/4", 1);
    timeSigniture.addItem("3/4", 2);
    timeSigniture.setSelectedId(1);
    timeSigniture.addSectionHeading("Time Signiture");

    stopButton.addListener(this);
    stopButton.setButtonText("Stop");
    stopButton.setColour(TextButton::buttonColourId, Colours::darkgrey);
    stopButton.setColour(TextButton::buttonOnColourId, Colours::darkred);
    addAndMakeVisible(&stopButton);
    stopButton.setEnabled(false);
    
    resetButton.addListener(this);
    resetButton.setButtonText("Reset");
    resetButton.setColour(TextButton::buttonColourId, Colours::grey);
    resetButton.setColour(TextButton::buttonOnColourId, Colours::darkred);
    addAndMakeVisible(&resetButton);
    
    randomiserButton.addListener(this);
    randomiserButton.setButtonText("Randomise");
    randomiserButton.setColour(TextButton::buttonColourId, Colours::grey);
    randomiserButton.setColour(TextButton::buttonOnColourId, Colours::darkred);
    addAndMakeVisible(&randomiserButton);
    
    tempoSlider.addListener(this);
    tempoSlider.setRange(60, 180, 1);
    tempoSlider.setValue(120);
    tempoSlider.setSliderStyle(Slider::Rotary);
    addAndMakeVisible(&tempoSlider);
}

void TransportBar::resized()
{
    Rectangle<int> area (getLocalBounds());
    int buttonWidth = getWidth() / 4;
    
    playButton.setBounds(area.removeFromLeft(buttonWidth).reduced(1));
    stopButton.setBounds(area.removeFromLeft(buttonWidth).reduced(1));
    resetButton.setBounds(area.removeFromRight(buttonWidth / 2).reduced(1));
    randomiserButton.setBounds(area.removeFromRight(buttonWidth / 2).reduced(1));
    timeSigniture.setBounds(area.removeFromRight(buttonWidth / 2).reduced(1));
    tempoSlider.setBounds(area.removeFromRight(buttonWidth / 2).reduced(1));


}

void TransportBar::buttonClicked(Button* button)
{
    if (button == &playButton)
    {
        sequencerGui.startSequencer();
        playButton.setEnabled(false);
        stopButton.setEnabled(true);
    }
    else if (button == &stopButton)
    {
        sequencerGui.stopSequencer();
        playButton.setEnabled(true);
        stopButton.setEnabled(false);
    }
    else if (button == &resetButton)
    {
        sequencerGui.resetSequencerToggleState();
    }
    else if (button == &randomiserButton)
    {
        sequencerGui.resetSequencerToggleState();
        sequencerGui.generateRandomPattern();
    }
    else if (button == &timeSig3)
    {
        sequencerGui.setTimeSig(3);
        timeSig3.setEnabled(false);
        playButton.setEnabled(true);
        stopButton.setEnabled(false);
        sequencerGui.stopSequencer();

    }
    else if (button == &timeSig4)
    {
        sequencerGui.setTimeSig(4);
        playButton.setEnabled(true);
        stopButton.setEnabled(false);
        sequencerGui.stopSequencer();

    }
}

void TransportBar::sliderValueChanged(Slider* slider)
{
    sequencerGui.setTempo(tempoSlider.getValue());
}

void TransportBar::comboBoxChanged (ComboBox* comboBoxThatHasChanged)
{
    if (comboBoxThatHasChanged == &timeSigniture)
    {
        if (timeSigniture.getSelectedIdAsValue() == 1)
        {
            sequencerGui.setTimeSig(4);
            playButton.setEnabled(true);
            stopButton.setEnabled(false);
            sequencerGui.stopSequencer();
        }
        else
        {
            sequencerGui.setTimeSig(3);
            playButton.setEnabled(true);
            stopButton.setEnabled(false);
            sequencerGui.stopSequencer();
        }
        
    }
}

void TransportBar::paint(Graphics &g)
{
    g.setColour(Colours::floralwhite);
    g.fillAll();
}
