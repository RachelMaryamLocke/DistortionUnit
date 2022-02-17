/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
DistLevelSliderAudioProcessorEditor::DistLevelSliderAudioProcessorEditor (DistLevelSliderAudioProcessor& p)
    : AudioProcessorEditor (&p), audioProcessor (p)
{
    
    clipButton.setToggleState(true, juce::NotificationType::dontSendNotification);
    clipButton.addListener(this);
    clipButton.setColour(juce::TextButton::ColourIds::buttonOnColourId, juce::Colour(0, 150, 160));
    addAndMakeVisible(clipButton);
    
    mGainSlider.setSliderStyle(juce::Slider::SliderStyle::LinearHorizontal);
    mGainSlider.setRange(0.0f, 1.0f, 0.01f);
    mGainSlider.setValue(0.5f);
    mGainSlider.setColour(juce::Slider::thumbColourId, juce::Colour(255,71,3));
    mGainSlider.addListener(this);
    mGainSlider.setTextBoxStyle(juce::Slider::NoTextBox, 1, 0, 0);
    
    addAndMakeVisible(mGainLabel);
    mGainLabel.setText("Output Gain", juce::dontSendNotification);
    mGainLabel.attachToComponent(&mGainSlider, true);
    mGainLabel.setColour(juce::Label::textColourId, juce::Colour(255,71,3));
    
    mBitDepthSlider.setSliderStyle(juce::Slider::SliderStyle::RotaryHorizontalDrag);
    mBitDepthSlider.setRange(2.0f, 8.0f, 1.0f);
    mBitDepthSlider.setValue(5.0f);
    mBitDepthSlider.setColour(juce::Slider::thumbColourId, juce::Colour(255,71,3));
    mBitDepthSlider.addListener(this);
    mBitDepthSlider.setTextBoxStyle(juce::Slider::NoTextBox, 1, 0, 0);
    
    addAndMakeVisible(mBitDepthLabel);
    mBitDepthLabel.setText("Bit Depth", juce::dontSendNotification);
    mBitDepthLabel.attachToComponent(&mBitDepthSlider, true);
    mBitDepthLabel.setColour(juce::Label::textColourId, juce::Colour(255,71,3));
    
    mUpperClipLevelSlider.setSliderStyle(juce::Slider::SliderStyle::RotaryHorizontalDrag);
    mUpperClipLevelSlider.setRange(0.2f, 0.8f, 0.1f);
    mUpperClipLevelSlider.setValue(0.5f);
    mUpperClipLevelSlider.setColour(juce::Slider::thumbColourId, juce::Colour(0, 150, 160));
    mUpperClipLevelSlider.addListener(this);
    mUpperClipLevelSlider.setTextBoxStyle(juce::Slider::NoTextBox, 1, 0, 0);
    
    addAndMakeVisible(mUpperClipLevelLabel);
    mUpperClipLevelLabel.setText("Hard Clipping Upper Level", juce::dontSendNotification);
    mUpperClipLevelLabel.attachToComponent(&mUpperClipLevelSlider, true);
    mUpperClipLevelLabel.setColour(juce::Label::textColourId, juce::Colour(0, 150, 160));
    
    mLowerClipLevelSlider.setSliderStyle(juce::Slider::SliderStyle::RotaryHorizontalDrag);
    mLowerClipLevelSlider.setRange(0.2f, 0.8f, 0.1f);
    mLowerClipLevelSlider.setValue(0.5f);
    mLowerClipLevelSlider.setColour(juce::Slider::thumbColourId, juce::Colour(0, 150, 160));
    mLowerClipLevelSlider.addListener(this);
    mLowerClipLevelSlider.setTextBoxStyle(juce::Slider::NoTextBox, 1, 0, 0);
    
    addAndMakeVisible(mLowerClipLevelLabel);
    mLowerClipLevelLabel.setText("Hard Clipping Lower Level", juce::dontSendNotification);
    mLowerClipLevelLabel.attachToComponent(&mLowerClipLevelSlider, true);
    mLowerClipLevelLabel.setColour(juce::Label::textColourId, juce::Colour(0, 150, 160));
    
    mArctanClipSlider.setSliderStyle(juce::Slider::SliderStyle::RotaryHorizontalDrag);
    mArctanClipSlider.setRange(1.0f, 9.0f, 1.0f);
    mArctanClipSlider.setValue(5.0f);
    mArctanClipSlider.setColour(juce::Slider::thumbColourId, juce::Colour(255,71,3));
    mArctanClipSlider.addListener(this);
    mArctanClipSlider.setTextBoxStyle(juce::Slider::NoTextBox, 1, 0, 0);
    
    addAndMakeVisible(mArctanLevelLabel);
    mArctanLevelLabel.setText("Soft Clipping Level", juce::dontSendNotification);
    mArctanLevelLabel.attachToComponent(&mArctanClipSlider, true);
    mArctanLevelLabel.setColour(juce::Label::textColourId, juce::Colour(255,71,3));
    
    mWetWetSlider.setSliderStyle(juce::Slider::SliderStyle::RotaryHorizontalDrag);
    mWetWetSlider.setRange(0.0f, 1.0f, 0.01f);
    mWetWetSlider.setValue(0.5f);
    mWetWetSlider.setColour(juce::Slider::thumbColourId, juce::Colour(255,71,3));
    mWetWetSlider.addListener(this);
    mWetWetSlider.setTextBoxStyle(juce::Slider::NoTextBox, 1, 0, 0);
    
    addAndMakeVisible(mWetWetLabel);
    mWetWetLabel.setText("Distortion Mix", juce::dontSendNotification);
    mWetWetLabel.attachToComponent(&mWetWetSlider, true);
    mWetWetLabel.setColour(juce::Label::textColourId, juce::Colour(255,71,3));
    
    mHardGainSlider.setSliderStyle(juce::Slider::SliderStyle::LinearHorizontal);
    mHardGainSlider.setRange(1.0f, 6.0f, 1.0f);
    mHardGainSlider.setValue(1.0f);
    mHardGainSlider.setColour(juce::Slider::thumbColourId, juce::Colour(0, 150, 160));
    mHardGainSlider.addListener(this);
    mHardGainSlider.setTextBoxStyle(juce::Slider::NoTextBox, 1, 0, 0);
    
    addAndMakeVisible(mHardClipGainLabel);
    mHardClipGainLabel.setText("Hard Clip Pre Gain", juce::dontSendNotification);
    mHardClipGainLabel.attachToComponent(&mHardGainSlider, true);
    mHardClipGainLabel.setColour(juce::Label::textColourId, juce::Colour(0, 150, 160));
    
    addAndMakeVisible(mGainSlider);
    addAndMakeVisible(mBitDepthSlider);
    addAndMakeVisible(mUpperClipLevelSlider);
    addAndMakeVisible(mLowerClipLevelSlider);
    addAndMakeVisible(mArctanClipSlider);
    addAndMakeVisible(mWetWetSlider);
    addAndMakeVisible(mHardGainSlider);
 
    setSize (500, 500);
}

DistLevelSliderAudioProcessorEditor::~DistLevelSliderAudioProcessorEditor()
{
}

//==============================================================================

void DistLevelSliderAudioProcessorEditor::paint (juce::Graphics& g)
{
    g.fillAll(juce::Colours::linen);
}

void DistLevelSliderAudioProcessorEditor::resized()
{
    mGainSlider.setBounds(350, 75, 100, 100);
    mBitDepthSlider.setBounds(175, 0, 100, 250);
    mUpperClipLevelSlider.setBounds(175, 100, 100, 250);
    mLowerClipLevelSlider.setBounds(175, 200, 100, 250);
    mArctanClipSlider.setBounds(400, 300, 100, 250);
    mWetWetSlider.setBounds(175, 300, 100, 250);
    mHardGainSlider.setBounds(390, 180, 100, 100);
    clipButton.setBounds(300, 280, 150, 25);
}

void DistLevelSliderAudioProcessorEditor::buttonClicked (juce::Button *button)
{
    if (button == &clipButton)
    {
        if (clipState == ClipState::hard)
        {
            clipButton.onClick = [this]() { soft(); };
        }else if (clipState == ClipState::soft)
        {
            clipButton.onClick = [this]() { hard(); };
        }
    }
}

void DistLevelSliderAudioProcessorEditor::hard()
{
    clipState = ClipState::hard;
    audioProcessor.mVal = 0;
    clipButton.setButtonText("Hard Clip");
    clipButton.setColour(juce::TextButton::ColourIds::buttonOnColourId, juce::Colour(0, 150, 160));
}

void DistLevelSliderAudioProcessorEditor::soft()
{
    clipState = ClipState::soft;
    audioProcessor.mVal = 1;
    clipButton.setButtonText("Soft Clip");
    clipButton.setColour(juce::TextButton::ColourIds::buttonOnColourId, juce::Colour(255,71,3));
}

void DistLevelSliderAudioProcessorEditor::sliderValueChanged(juce::Slider *slider)
{
    if (slider == &mGainSlider)
    {
        audioProcessor.mLevel = mGainSlider.getValue();
    }
    if (slider == &mBitDepthSlider)
    {
        audioProcessor.mBits = mBitDepthSlider.getValue();
    }
    if (slider == &mUpperClipLevelSlider)
    {
        audioProcessor.mUpperClipLevel = mUpperClipLevelSlider.getValue();
    }
    if (slider == &mLowerClipLevelSlider)
    {
        audioProcessor.mLowerClipLevel = mLowerClipLevelSlider.getValue();
    }
    if (slider == &mArctanClipSlider)
    {
        audioProcessor.mArctanLevel = mArctanClipSlider.getValue();
    }
    if (slider == &mWetWetSlider)
    {
        audioProcessor.mWetWet = mWetWetSlider.getValue();
    }
    if (slider == &mHardGainSlider)
    {
        audioProcessor.mHardGainValue = mHardGainSlider.getValue();
    }
}
