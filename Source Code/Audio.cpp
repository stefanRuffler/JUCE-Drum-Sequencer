/*
  ==============================================================================

    Audio.cpp
    Created: 13 Nov 2014 8:14:40am
    Author:  Tom Mitchell

  ==============================================================================
*/

#include "Audio.h"

Audio::Audio()
{
    audioDeviceManager.initialiseWithDefaultDevices (0, 2);
    
    for (int i = 0; i < NumOfRows; i++)
    {
        mixerAudioSource.addInputSource(&sequencerRow[i], true);
    }
    
    audioSourcePlayer.setSource (&mixerAudioSource);
    audioDeviceManager.addAudioCallback (this);
}

Audio::~Audio()
{
    audioDeviceManager.removeAudioCallback (this);
    
    for (int i = 0; i < NumFilePlayers; i++)
    {
        mixerAudioSource.removeAllInputs();
    }
}

void Audio::audioDeviceIOCallback (const float** inputChannelData,
                                           int numInputChannels,
                                           float** outputChannelData,
                                           int numOutputChannels,
                                           int numSamples)
{
    // get the audio from our file player - player puts samples in the output buffer
    audioSourcePlayer.audioDeviceIOCallback (inputChannelData, numInputChannels, outputChannelData, numOutputChannels, numSamples);
    
    //All audio processing is done here
    const float *inL = inputChannelData[0];
    const float *inR = inputChannelData[1];
    float *outL = outputChannelData[0];
    float *outR = outputChannelData[1];
    
    float inSampL;
    float inSampR;
    
    while(numSamples--)
    {
        inSampL = *outL;
        inSampR = *outL;
        
        *outL = inSampL;
        *outR = inSampR;
        
        inL++;
        inR++;
        outL++;
        outR++;
    }
}


void Audio::audioDeviceAboutToStart (AudioIODevice* device)
{
    audioSourcePlayer.audioDeviceAboutToStart (device);
}

void Audio::audioDeviceStopped()
{
    audioSourcePlayer.audioDeviceStopped();
}