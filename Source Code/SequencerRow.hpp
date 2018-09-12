//
//  SequencerRow.hpp
//  JuceBasicAudio
//
//  Created by Stefan Ruffler on 22/12/2016.
//
//

#ifndef SequencerRow_hpp
#define SequencerRow_hpp

#include <stdio.h>
#include "../JuceLibraryCode/JuceHeader.h"

class SequencerRow : public AudioSource
{
    
public:
    
    SequencerRow();
    ~SequencerRow();
    
    void setGain (float newGainValue);
    
    /** Starts or stops the playback of the sequencer rows audio file */
    void setPlaying (const bool newState);
    
    /** Returns the playback state of the audio file */
    bool isPlaying () const;
    
    /** Loads specified file into the transport source of the sequencer row */
    void loadFile(const File& newFile);
    
    //AudioSource
    void prepareToPlay (int samplesPerBlockExpected, double sampleRate);
    void releaseResources();
    void getNextAudioBlock (const AudioSourceChannelInfo& bufferToFill);
    
private:
    
    AudioFormatReaderSource* currentAudioFileSource;
    AudioTransportSource audioTransportSource;
};

#endif /* SequencerRow_hpp */
