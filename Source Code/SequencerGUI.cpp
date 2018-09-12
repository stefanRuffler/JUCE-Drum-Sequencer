//
//  SequencerGUI.cpp
//  JuceBasicAudio
//
//  Created by Stefan Ruffler on 22/12/2016.
//
//

#include "SequencerGUI.hpp"

/** 
 Constructor - Recieves a reference from a Audio object to control it
 */
SequencerGUI::SequencerGUI(Audio& audio_) : audio(audio_),
                                            sequencerThread("SequencerThread")
{
    sequencerThread.startThread();
    NumOfSteps = 16;
    
    for (int i = 0; i < NumOfRows; i++)
    {
        sequencerRowGui[i] = new SequencerRowGui(audio_.getSequencerRow(i));
        addAndMakeVisible(sequencerRowGui[i]);
    }
}

/** 
 Destructor 
 */
SequencerGUI::~SequencerGUI()
{
    stopTimer();
    sequencerThread.stopThread(100);
    
    for (int i = 0; i < NumOfRows; i++)
    {
        delete sequencerRowGui[i];
    }
}

/** 
 Starts the sequencer timer
 */
void SequencerGUI::startSequencer()
{
    isPlaying = true;
    startTimer(tempo);
}

/** 
 Stops the sequencer timer and stops playback of all the loaded audio files
 */
void SequencerGUI::stopSequencer()
{
    isPlaying = false;
    stopTimer();
    sequencerPosition = 0;
    resetSequencerAlpha();
    
    for (int i = 0; i < NumOfRows; i ++)
    {
        sequencerRowGui[i]->stopPlayback();
    }
}

/** 
 Resets all the sequencer row's toggle states
 */
void SequencerGUI::resetSequencerToggleState()
{
    for(int i = 0; i < NumOfRows ; i++)
    {
        sequencerRowGui[i]->resetRowsToggleSate();
    }
}

/** 
 Resets all the sequencer row's Alpha values
 */
void SequencerGUI::resetSequencerAlpha()
{
    for(int i = 0; i < NumOfRows ; i++)
    {
        sequencerRowGui[i]->resetRowsAlpha();
    }
}

/** 
 Calculates the tempo from the given value, then stops and starts a timer with new tempo 
 */
void SequencerGUI::setTempo(int bpm)
{
    tempo = 60000 / (bpm * 4);
    
    if (isPlaying)
    {
        stopTimer();
        startTimer(tempo);
    }
}

/** 
 Generates a random toggle states for every step on the sequencer  
 */
void SequencerGUI::generateRandomPattern()
{
    for (int rowIndex = 0; rowIndex < NumOfRows; rowIndex++)
    {
        sequencerRowGui[rowIndex]->randomiseSequencerRow();
    }
}

void SequencerGUI::setTimeSig(int beats)
{
    stopSequencer();
    
    for (int rowIndex = 0; rowIndex < NumOfRows; rowIndex++)
        sequencerRowGui[rowIndex]->setTimeSigniture(beats);
    
    if (beats == 3)
        NumOfSteps = 12;
    else if(beats == 4)
        NumOfSteps = 16;
}

void SequencerGUI::resized()
{
    Rectangle<int> area(getLocalBounds());
    
    int sequencerRowHeight = getHeight() / NumOfRows;
    
    for (int i = 0; i < NumOfRows; i++)
        sequencerRowGui[i]->setBounds(area.removeFromTop(sequencerRowHeight).removeFromLeft(getWidth()));
}

void SequencerGUI::timerCallback()
{
    if (sequencerPosition == NumOfSteps)
        sequencerPosition = 0;
    
    for (int rowIndex = 0; rowIndex < NumOfRows; rowIndex++)
    {
        sequencerRowGui[rowIndex]->setSequencerStepPosition(sequencerPosition);
    }
    
    for (int i = 0;i < NumOfRows; i ++)
    {
        if (sequencerRowGui[i]->getMuteButtonToggleState() == false)
            sequencerRowGui[i]->playStep(sequencerPosition);
        
    }
    sequencerPosition ++;

}

void SequencerGUI::paint(Graphics &g)
{
    g.setColour(Colours::darkgrey);
    g.fillAll();
}
