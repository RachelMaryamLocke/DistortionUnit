/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"
#include <math.h>
#define PI 3.14

//==============================================================================
DistLevelSliderAudioProcessor::DistLevelSliderAudioProcessor()
#ifndef JucePlugin_PreferredChannelConfigurations
     : AudioProcessor (BusesProperties()
                     #if ! JucePlugin_IsMidiEffect
                      #if ! JucePlugin_IsSynth
                       .withInput  ("Input",  juce::AudioChannelSet::stereo(), true)
                      #endif
                       .withOutput ("Output", juce::AudioChannelSet::stereo(), true)
                     #endif
                       )
#endif
{
}

DistLevelSliderAudioProcessor::~DistLevelSliderAudioProcessor()
{
}

//==============================================================================
const juce::String DistLevelSliderAudioProcessor::getName() const
{
    return JucePlugin_Name;
}

bool DistLevelSliderAudioProcessor::acceptsMidi() const
{
   #if JucePlugin_WantsMidiInput
    return true;
   #else
    return false;
   #endif
}

bool DistLevelSliderAudioProcessor::producesMidi() const
{
   #if JucePlugin_ProducesMidiOutput
    return true;
   #else
    return false;
   #endif
}

bool DistLevelSliderAudioProcessor::isMidiEffect() const
{
   #if JucePlugin_IsMidiEffect
    return true;
   #else
    return false;
   #endif
}

double DistLevelSliderAudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int DistLevelSliderAudioProcessor::getNumPrograms()
{
    return 1;   // NB: some hosts don't cope very well if you tell them there are 0 programs,
                // so this should be at least 1, even if you're not really implementing programs.
}

int DistLevelSliderAudioProcessor::getCurrentProgram()
{
    return 0;
}

void DistLevelSliderAudioProcessor::setCurrentProgram (int index)
{
}

const juce::String DistLevelSliderAudioProcessor::getProgramName (int index)
{
    return {};
}

void DistLevelSliderAudioProcessor::changeProgramName (int index, const juce::String& newName)
{
}

//==============================================================================
void DistLevelSliderAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    // Use this method as the place to do any pre-playback
    // initialisation that you need..
}

void DistLevelSliderAudioProcessor::releaseResources()
{
    // When playback stops, you can use this as an opportunity to free up any
    // spare memory, etc.
}

#ifndef JucePlugin_PreferredChannelConfigurations
bool DistLevelSliderAudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
{
  #if JucePlugin_IsMidiEffect
    juce::ignoreUnused (layouts);
    return true;
  #else
    // This is the place where you check if the layout is supported.
    // In this template code we only support mono or stereo.
    if (layouts.getMainOutputChannelSet() != juce::AudioChannelSet::mono()
     && layouts.getMainOutputChannelSet() != juce::AudioChannelSet::stereo())
        return false;

    // This checks if the input layout matches the output layout
   #if ! JucePlugin_IsSynth
    if (layouts.getMainOutputChannelSet() != layouts.getMainInputChannelSet())
        return false;
   #endif

    return true;
  #endif
}
#endif

void DistLevelSliderAudioProcessor::processBlock (juce::AudioBuffer<float>& buffer, juce::MidiBuffer& midiMessages)
{
    //find the length of the buffer
    int numSamples = buffer.getNumSamples();
    
    //check for samples
    if (numSamples == 0)
    {
        return;
    }
    
    //find number of output channels
    int numOutputs = getTotalNumOutputChannels();
    
    //Find write (output) pointers
    auto channelDataL = buffer.getWritePointer(0);
    auto channelDataR = buffer.getWritePointer(0);
    if (numOutputs == 2)
    {
        channelDataR = buffer.getWritePointer(1);
    }
    
    //set up storage for input sample
    float ip = 0.0f;
    
    //---------------------------------------------
    
    //BEGIN MAIN TIME LOOP
    for(int n = 0; n < numSamples; ++n)
    {
        //read input samples
        ip = buffer.getSample(0, n);
        
        //--------------------------------------------------------------------------------------
        
        ///Apply First Series Distortion(Bit Reduction)
        
        float bitCrush{0.0}; //temp value for bit reduction current sample
        float ampValues = pow(2.0f, (mBits - 1.0f));
        bitCrush = ceil(ampValues * ip) * (1.0f/ampValues);
        
        ///Apply Second Series Distortion(Rectification)
        
        float fullWaveRect{0.0}; //temp value for bit reduction current sample

        if (bitCrush >= 0)
        {
            fullWaveRect = bitCrush;
        } else
        {
            fullWaveRect = -1 * bitCrush;
        }
        
        ///Apply Parallel Distortion (hard/arctan clipping)
        
        float parallel{0.0f};
        
        if (mVal == 0)
        {
            mHardGain = mHardGainValue * ip; 
            ///perform hard clipping
            if (mHardGain > mUpperClipLevel)
            {
                parallel = mUpperClipLevel;
            }else if (mHardGain <= -mLowerClipLevel)
            {
                parallel = -mLowerClipLevel;
            }else
            {
                parallel = mHardGain;
            }
        }else
        {
            ///perform soft arctangent clipping
            parallel = (2/M_PI) * atanf(mArctanLevel * ip);
        }
        
        //--------------------------------------------------------------------------------------
        
        //declare output samples
        
        channelDataL[n] = mLevel * (mWetWet * fullWaveRect + (1 - mWetWet) * parallel);
        
        //big mono
        if (numOutputs == 2)
        {
            channelDataR[n] = channelDataL[n];
        }
    }
}

//==============================================================================
bool DistLevelSliderAudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

juce::AudioProcessorEditor* DistLevelSliderAudioProcessor::createEditor()
{
    return new DistLevelSliderAudioProcessorEditor (*this);
}

//==============================================================================
void DistLevelSliderAudioProcessor::getStateInformation (juce::MemoryBlock& destData)
{
    // You should use this method to store your parameters in the memory block.
    // You could do that either as raw data, or use the XML or ValueTree classes
    // as intermediaries to make it easy to save and load complex data.
}

void DistLevelSliderAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    // You should use this method to restore your parameters from this memory block,
    // whose contents will have been created by the getStateInformation() call.
}

//==============================================================================
// This creates new instances of the plugin..
juce::AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new DistLevelSliderAudioProcessor();
}
