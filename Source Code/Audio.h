/*
  ==============================================================================

    Audio.h
    Created: 13 Nov 2014 8:14:40am
    Author:  Tom Mitchell

  ==============================================================================
*/

#ifndef AUDIO_H_INCLUDED
#define AUDIO_H_INCLUDED

/**
 Class containing all audio processes
 */

#include "../../JuceLibraryCode/JuceHeader.h"
#include "../SequencerRow.hpp"

class Audio : public AudioIODeviceCallback
{
public:
    /** Constructor */
    Audio();
    
    /** Destructor */
    ~Audio();
    
    /** Returns the audio device manager, don't keep a copy of it! */
    AudioDeviceManager& getAudioDeviceManager() { return audioDeviceManager;}
    
    SequencerRow& getSequencerRow(int rowIndex)
    {
        return sequencerRow[rowIndex];
    }
        
    void audioDeviceIOCallback (const float** inputChannelData,
                                int numInputChannels,
                                float** outputChannelData,
                                int numOutputChannels,
                                int numSamples) override;
    
    void audioDeviceAboutToStart (AudioIODevice* device) override;
    
    void audioDeviceStopped() override;
private:
    
    static const int NumFilePlayers = 8;
    static const int NumOfRows = 8;

    
    AudioDeviceManager audioDeviceManager;
    AudioSourcePlayer audioSourcePlayer;
    MixerAudioSource mixerAudioSource;
    SequencerRow sequencerRow[NumOfRows];
};



#endif  // AUDIO_H_INCLUDED
