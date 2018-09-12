//
//  SequencerRowGUI.cpp
//  JuceBasicAudio
//
//  Created by Stefan Ruffler on 22/12/2016.
//
//

#include "SequencerRowGUI.hpp"

/** 
 Constructor - Recieves a reference from a SequencerRow object to control it
 */
SequencerRowGui::SequencerRowGui(SequencerRow& sequencerRow_) : sequencerRow(sequencerRow_),
                                                                thr("FileSelectThread")
{
    
    setTimeSigniture(4);
    
    //File Selector Button
    fileSelectorButton.setButtonText("Select File...");
    addAndMakeVisible(fileSelectorButton);
    fileSelectorButton.addListener(this);
    fileSelectorButton.setColour(TextButton::buttonColourId, Colours::white);
    fileSelectorButton.setColour(TextButton::buttonOnColourId, Colours::lightgoldenrodyellow);
    
    //SoloButton
    addAndMakeVisible(soloButton);
    soloButton.setButtonText("S");
    
    //Mute Button
    addAndMakeVisible(muteButton);
    muteButton.setButtonText("M");
    muteButton.addListener(this);
    muteButton.setColour(TextButton::buttonColourId, Colours::white);
    muteButton.setColour(TextButton::buttonOnColourId, Colours::lightskyblue);
    
    addAndMakeVisible(groupOneButton);
    groupOneButton.setButtonText("1");
    groupOneButton.addListener(this);
    groupOneButton.setColour(TextButton::buttonColourId, Colours::white);
    groupOneButton.setColour(TextButton::buttonOnColourId, Colours::indianred);
    
    addAndMakeVisible(groupTwoButton);
    groupTwoButton.setButtonText("2");
    groupTwoButton.addListener(this);
    groupTwoButton.setColour(TextButton::buttonColourId, Colours::white);
    groupTwoButton.setColour(TextButton::buttonOnColourId, Colours::indianred);

    // Gain Slider
    gainSlider.setRange(0.0, 1.0);
    gainSlider.setValue(0.5);
    gainSlider.hideTextBox(true);
    gainSlider.setSliderStyle(Slider::LinearVertical);
    gainSlider.addListener(this);
    addAndMakeVisible(&gainSlider);
}

/** 
 Plays audio file if sequencer steps toggle state is true 
 */
void SequencerRowGui::playStep(int seequencerPosition)
{
    if (sequencerStep[seequencerPosition].getToggleState())
    {
        sequencerRow.setPlaying(true);
    }
}

/** 
 Stops the audio files playback 
 */
void SequencerRowGui::stopPlayback()
{
    sequencerRow.setPlaying(false);
}

/** 
 Returns a bool value of the mute buttons' toggle state 
 */
bool SequencerRowGui::getMuteButtonToggleState()
{
    return muteButton.getToggleState();
}

/** 
 Resets all the sequencer rows' button toggle states to false 
 */
void SequencerRowGui::resetRowsToggleSate()
{
    for (int i = 0; i < NumOfSteps; i++)
    {
        sequencerStep[i].setToggleState(false, dontSendNotification);
    }
}

/** 
 Resets all the sequencer rows' button alphas 
 */
void SequencerRowGui::resetRowsAlpha()
{
    for (int i = 0; i < NumOfSteps; i++)
        sequencerStep[i].setAlpha(1.0);
}

/** 
 Highlights the current sequencer position
 */
void SequencerRowGui::setSequencerStepPosition(int sequencerPosition)
{
    sequencerStep[sequencerPosition].setAlpha(0.5);
    
    if (sequencerPosition != 0)
        sequencerStep[sequencerPosition - 1].setAlpha(1.0);
    else
        sequencerStep[NumOfSteps - 1].setAlpha(1.0);
}

/** 
 Randomly selects the toggle states for each step in a the row
 */
void SequencerRowGui::randomiseSequencerRow()
{
    for (int i = 0; i < NumOfSteps; i++)
    {
        if (rand() < RAND_MAX / 3)
            sequencerStep[i].setToggleState(true, dontSendNotification);
    }
}

void SequencerRowGui::resized()
{
    Rectangle<int> area(getLocalBounds());
    
    int width = getWidth();
    int fileSelectorWidth = getWidth() / 8;
    int muteButtonWidth = getWidth() / 18;
    int muteButtonHeight = getHeight() / 2;

    int buttonWidth = ((width - (width / 6) - (width / 15)) - muteButtonWidth + 1) / NumOfSteps;
    
    {
        Rectangle<int> sideBarArea (area.removeFromLeft (area.getWidth() / 6));
        
        fileSelectorButton.setBounds(sideBarArea.removeFromLeft(fileSelectorWidth).reduced(5));
        soloButton.setBounds(sideBarArea.removeFromTop(muteButtonHeight).removeFromLeft(muteButtonWidth).reduced(1));
        muteButton.setBounds(sideBarArea.removeFromBottom(muteButtonHeight).removeFromLeft(muteButtonWidth).reduced(1));
    }
    
    {
        Rectangle<int> groupButtonArea (area.removeFromLeft (area.getWidth() / 17));
        
        groupOneButton.setBounds(groupButtonArea.removeFromTop(muteButtonHeight).removeFromLeft(muteButtonWidth).reduced(1));
        groupTwoButton.setBounds(groupButtonArea.removeFromBottom(muteButtonHeight).removeFromLeft(muteButtonWidth).reduced(1));
    }
    
    

    gainSlider.setBounds(area.removeFromLeft(muteButtonWidth).reduced(1));


    for (int i = 0; i < NumOfSteps; i++)
    {
        if ( i == 0 || i == 4 || i == 8 || i == 12)
        {
            sequencerStep[i].setColour(TextButton::buttonColourId, Colours::navajowhite);
            sequencerStep[i].setBounds(area.removeFromLeft(buttonWidth).reduced(2));
        }
        else
            sequencerStep[i].setBounds(area.removeFromLeft(buttonWidth).reduced(1));
    }
}

void SequencerRowGui::buttonClicked(Button* button)
{
    for (int stepIndex = 0; stepIndex < NumOfSteps; stepIndex++)
    {
        if (button == &sequencerStep[stepIndex])
        {
            if (sequencerStep[stepIndex].getToggleState())
                sequencerStep[stepIndex].setToggleState(false, dontSendNotification);
            else
                sequencerStep[stepIndex].setToggleState(true, dontSendNotification);
        }
    }
    
    if (button == &fileSelectorButton)
    {
        thr.startThread();
        
        FileChooser chooser ("Select a Wave file to play...",
                             File::nonexistent,
                             "*.wav");
        
        if (chooser.browseForFileToOpen())
        {
            File file (chooser.getResult());
            
            if(file.existsAsFile())
            {
                sequencerRow.loadFile(file);
            }
            else
            {
                AlertWindow::showMessageBox (AlertWindow::WarningIcon,
                                             "sdaTransport",
                                             "Couldn't open file!\n\n");
            }
            
            thr.stopThread(100);
            
            fileSelectorButton.setButtonText(file.getFileName());
        }
    }
    
    if (button == &muteButton)
    {
        if (muteButton.getToggleState() ==false)
        {
            muteButton.setToggleState(true, dontSendNotification);
            sequencerRow.setGain(0.0);
        }
        else
        {
            muteButton.setToggleState(false, dontSendNotification);
            sequencerRow.setGain(gainSlider.getValue());
        }
    }
}

void SequencerRowGui::setTimeSigniture(int beats)
{
    
    if (beats == 3)
    {
        if (sequencerStep != nullptr)
        {
            delete [] sequencerStep;
        }
        
        NumOfSteps = 12;
    }
    else
    {
        if (sequencerStep != nullptr)
        {
            delete [] sequencerStep;
        }

        NumOfSteps = 16;
    }
    
    sequencerStep = new TextButton[NumOfSteps];
    
    for (int stepIndex = 0; stepIndex < NumOfSteps; stepIndex++)
    {
        sequencerStep[stepIndex].setColour(TextButton::buttonColourId, Colours::floralwhite);
        sequencerStep[stepIndex].setColour(TextButton::buttonOnColourId, Colours::orange);
        sequencerStep[stepIndex].setToggleState(false, dontSendNotification);
        sequencerStep[stepIndex].addListener(this);
        addAndMakeVisible(sequencerStep[stepIndex]);
    }
    
    resized();

}

int SequencerRowGui::getNumOfSteps()
{
    return NumOfSteps;
}

void SequencerRowGui::sliderValueChanged(Slider* slider)
{
    sequencerRow.setGain(gainSlider.getValue());
}

