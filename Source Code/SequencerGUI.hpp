//
//  SequencerGUI.hpp
//  JuceBasicAudio
//
//  Created by Stefan Ruffler on 22/12/2016.
//
//

#ifndef SequencerGUI_hpp
#define SequencerGUI_hpp

#include "../JuceLibraryCode/JuceHeader.h"
#include "SequencerRowGUI.hpp"
#include "../Audio.h"

class SequencerGUI : public Component,
                     public Timer
{
public:
    
    /** Constructor - Recieves a reference from a Audio object to control it */
    SequencerGUI(Audio& audio_);
    
    /** Destructor */
    ~SequencerGUI();
    
    /** Starts the sequencer timer */
    void startSequencer();
    
    /** Stops the sequencers timer */
    void stopSequencer();
    
    /** Resets all the sequencer row's toggle states */
    void resetSequencerToggleState();
    
    /** Resets all the sequencer row's Alpha values */
    void resetSequencerAlpha();
    
    /** Calculates the tempo from the given value, then stops and starts a timer with new tempo */
    void setTempo(int bpm);
        
    /** Generates a random toggle states for every step on the sequencer  */
    void generateRandomPattern();
    
    void setTimeSig(int beats);
    
    // Component
    void resized() override;
    void timerCallback() override;
    void paint(Graphics &g) override;
    
private:
    static const int NumOfRows = 8;
    int  NumOfSteps;
    int timeSignature;
    
    int sequencerPosition = 0;
    int tempo;
    bool isPlaying = false;
    
    Audio& audio;
    TimeSliceThread sequencerThread;
    SequencerRowGui* sequencerRowGui[NumOfRows];
    MessageManagerLock lockChecker;
    
};

#endif /* SequencerGUI_hpp */
