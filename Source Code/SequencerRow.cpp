//
//  SequencerRow.cpp
//  JuceBasicAudio
//
//  Created by Stefan Ruffler on 22/12/2016.
//
//

#include "SequencerRow.hpp"

SequencerRow::SequencerRow()
{
    
}

SequencerRow::~SequencerRow()
{
    audioTransportSource.setSource(0);//unload the current file
    deleteAndZero(currentAudioFileSource);//delete the current file
}

void SequencerRow::setPlaying (const bool newState)
{
    if(newState == true)
    {
        audioTransportSource.setPosition(0.0);
        audioTransportSource.start();
    }
    else
    {
        audioTransportSource.stop();
    }
}

/**
 Gets the current playback state of the sequencerRow
 */
bool SequencerRow::isPlaying () const
{
    return audioTransportSource.isPlaying();
}

/**
 Loads the specified file into the transport source
 */
void SequencerRow::loadFile(const File& newFile)
{
    setPlaying(false);
    audioTransportSource.setSource (0);
    //deleteAndZero (currentAudioFileSource);
    
    AudioFormatManager formatManager;
    formatManager.registerBasicFormats();
    
    AudioFormatReader* reader = formatManager.createReaderFor (newFile);
    
    if (reader != 0)
    {
        currentAudioFileSource = new AudioFormatReaderSource (reader, true);
        
        audioTransportSource.setSource (currentAudioFileSource);
    }
    
}

void SequencerRow::setGain(float newGainValue)
{
    audioTransportSource.setGain(newGainValue);
}

//AudioSource
void SequencerRow::prepareToPlay (int samplesPerBlockExpected, double sampleRate)
{
    audioTransportSource.prepareToPlay (samplesPerBlockExpected, sampleRate);
}

void SequencerRow::releaseResources()
{
    audioTransportSource.releaseResources();
}

void SequencerRow::getNextAudioBlock (const AudioSourceChannelInfo& bufferToFill)
{
    audioTransportSource.getNextAudioBlock (bufferToFill);

}
