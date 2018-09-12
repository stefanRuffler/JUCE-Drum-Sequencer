//
//  SequencerRowGUI.hpp
//  JuceBasicAudio
//
//  Created by Stefan Ruffler on 22/12/2016.
//
//

#ifndef SequencerRowGUI_hpp
#define SequencerRowGUI_hpp

#include <stdio.h>
#include "../JuceLibraryCode/JuceHeader.h"
#include "SequencerRow.hpp"

class SequencerRowGui : public Component,
                        public Button::Listener,
                        public Slider::Listener
{
public:
    
    /** Constructor - Recieves a reference from a SequencerRow object to control it*/
    SequencerRowGui(SequencerRow& sequencerRow_);
    
    /** Plays audio file if sequencer steps toggle state is true */
    void playStep(int sequencerPosition);
    
    /** Stops the audio files playback */
    void stopPlayback();
    
    /** Returns a bool value of the mute buttons' toggle state */
    bool getMuteButtonToggleState();
    
    /** Resets all the sequencer rows' button toggle states to false */
    void resetRowsToggleSate();
    
    /** Resets all the sequencer rows' button alphas */
    void resetRowsAlpha();
    
    /** Highlights the current sequencer position */
    void setSequencerStepPosition(int sequencerPosition);
    
    /** Randomly selects the toggle states for each step in a the row */
    void randomiseSequencerRow();
    
    void setTimeSigniture(int beats);
    
    int getNumOfSteps();
        
    // Component
    void resized() override;
    void buttonClicked(Button* button) override;
    void sliderValueChanged(Slider* slider) override;
    
private:
    
    int NumOfSteps;
    
    SequencerRow& sequencerRow;
    TextButton fileSelectorButton;
    TextButton soloButton;
    TextButton muteButton;
    TextButton groupOneButton;
    TextButton groupTwoButton;
    TextButton* sequencerStep = nullptr;
    Slider gainSlider;
    
    TimeSliceThread thr;
};


#endif /* SequencerRowGUI_hpp */
