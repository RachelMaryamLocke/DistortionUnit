/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"

//==============================================================================
/**
*/
class DistLevelSliderAudioProcessorEditor  : public juce::AudioProcessorEditor,
                                             public juce::Slider::Listener,
                                             public juce::Button::Listener
{
public:
    DistLevelSliderAudioProcessorEditor (DistLevelSliderAudioProcessor&);
    ~DistLevelSliderAudioProcessorEditor() override;

    //==============================================================================
    void paint (juce::Graphics&) override;
    void resized() override;
    void sliderValueChanged (juce::Slider* slider) override;
    void buttonClicked (juce::Button *button) override;
    void hard();
    void soft();
    

private:
    juce::Slider mGainSlider; //slider control for level controlled by user
    juce::Slider mBitDepthSlider; //slider control for bit depth
    juce::Slider mLowerClipLevelSlider; //slider control for hard clip level
    juce::Slider mUpperClipLevelSlider; //slider control for hard clip level
    juce::Slider mArctanClipSlider; //slider control for arctangent soft clip level
    juce::Slider mWetWetSlider; //slider for wet/wet control
    juce::Slider mHardGainSlider; //slider for hard clipping gain staging
    
    juce::Label mGainLabel;
    juce::Label mBitDepthLabel;
    juce::Label mLowerClipLevelLabel;
    juce::Label mUpperClipLevelLabel;
    juce::Label mArctanLevelLabel;
    juce::Label mWetWetLabel;
    juce::Label mHardClipGainLabel;
    
    enum class ClipState
    {
        hard,
        soft
    };
    
    ClipState clipState { ClipState::hard };
    juce::TextButton clipButton { "Clipping Switch" };
    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    DistLevelSliderAudioProcessor& audioProcessor;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (DistLevelSliderAudioProcessorEditor)
};
