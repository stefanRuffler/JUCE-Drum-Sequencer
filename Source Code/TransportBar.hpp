//
//  TransportBar.hpp
//  JuceBasicAudio
//
//  Created by Stefan Ruffler on 22/12/2016.
//
//

#ifndef TransportBar_hpp
#define TransportBar_hpp

#include <stdio.h>
#include "../JuceLibraryCode/JuceHeader.h"
#include "SequencerGUI.hpp"

class TransportBar : public Component,
                     public Button::Listener,
                     public Slider::Listener,
                     public ComboBoxListener
{
public :
    
    /** Constructor - recieves a reference to a SequencerGUI object to control it */
    TransportBar(SequencerGUI& sequencerGUI_);
    
    //Component
    void resized() override;
    void buttonClicked(Button* button) override;
    void sliderValueChanged(Slider* slider) override;
    void comboBoxChanged (ComboBox* comboBoxThatHasChanged) override;
    void paint(Graphics &g) override;
    
private:
    
    TextButton playButton;
    TextButton stopButton;
    TextButton resetButton;
    TextButton randomiserButton;
    TextButton timeSig3;
    TextButton timeSig4;
    
    ComboBox timeSigniture;
    
    Slider tempoSlider;
    SequencerGUI& sequencerGui;
};

#endif /* TransportBar_hpp */
