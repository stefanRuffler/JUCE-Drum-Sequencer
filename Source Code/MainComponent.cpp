/*
  ==============================================================================

    This file was auto-generated!

  ==============================================================================
*/

#include "MainComponent.h"


//==============================================================================
MainComponent::MainComponent (Audio& audio_) : audio (audio_),
                                               sequencerGui (audio_),
                                               transportBar(sequencerGui)
{
    addAndMakeVisible(sequencerGui);
    addAndMakeVisible(transportBar);
    
    setSize (500, 400);
}

MainComponent::~MainComponent()
{
    
}

void MainComponent::resized()
{
    Rectangle<int> area (getLocalBounds());
    int transportBarHeight = getHeight() / 10;
    
    transportBar.setBounds(area.removeFromTop(transportBarHeight).reduced(1));
    sequencerGui.setBounds(area.removeFromTop(getHeight() - transportBarHeight).reduced(2));
}

//MenuBarCallbacks==============================================================
StringArray MainComponent::getMenuBarNames()
{
    const char* const names[] = { "File", 0 };
    return StringArray (names);
}

PopupMenu MainComponent::getMenuForIndex (int topLevelMenuIndex, const String& menuName)
{
    PopupMenu menu;
    if (topLevelMenuIndex == 0)
        menu.addItem(AudioPrefs, "Audio Prefrences", true, false);
    return menu;
}

void MainComponent::menuItemSelected (int menuItemID, int topLevelMenuIndex)
{
    if (topLevelMenuIndex == FileMenu)
    {
        if (menuItemID == AudioPrefs)
        {
            AudioDeviceSelectorComponent audioSettingsComp (audio.getAudioDeviceManager(),
                                                            0, 2, 2, 2, true, true, true, false);
            audioSettingsComp.setSize (450, 350);
            DialogWindow::showModalDialog ("Audio Settings",
                                           &audioSettingsComp, this, Colours::lightgrey, true);
        }
    }
}

