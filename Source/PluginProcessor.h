/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

//==============================================================================

class DistLevelSliderAudioProcessor  : public juce::AudioProcessor
{
public:
    //==============================================================================
    DistLevelSliderAudioProcessor();
    ~DistLevelSliderAudioProcessor() override;

    //==============================================================================
    void prepareToPlay (double sampleRate, int samplesPerBlock) override;
    void releaseResources() override;

   #ifndef JucePlugin_PreferredChannelConfigurations
    bool isBusesLayoutSupported (const BusesLayout& layouts) const override;
   #endif

    void processBlock (juce::AudioBuffer<float>&, juce::MidiBuffer&) override;

    //==============================================================================
    juce::AudioProcessorEditor* createEditor() override;
    bool hasEditor() const override;

    //==============================================================================
    const juce::String getName() const override;

    bool acceptsMidi() const override;
    bool producesMidi() const override;
    bool isMidiEffect() const override;
    double getTailLengthSeconds() const override;

    //==============================================================================
    int getNumPrograms() override;
    int getCurrentProgram() override;
    void setCurrentProgram (int index) override;
    const juce::String getProgramName (int index) override;
    void changeProgramName (int index, const juce::String& newName) override;

    //==============================================================================
    void getStateInformation (juce::MemoryBlock& destData) override;
    void setStateInformation (const void* data, int sizeInBytes) override;
    
    float mLevel{0.5f}; //level param tied to mGainSlider (controlled by user)
    float mBits{5.0f}; //Alpha value for bit depth (controlled by user)
    float mUpperClipLevel{0.5}; //Upper clip level for hard clipping (controlled by user)
    float mLowerClipLevel{0.5}; //Lower clip level for hard clipping (controlled by user)
    float mArctanLevel{5.0f}; //Clip level for hard clipping (controlled by user)
    float mWetWet;
    float mHardGain;
    float mHardGainValue{1.0f};
    bool mVal{0};
    
private:
    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (DistLevelSliderAudioProcessor)
};
