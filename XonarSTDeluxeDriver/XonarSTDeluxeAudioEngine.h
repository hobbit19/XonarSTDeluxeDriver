//
//  XonarSTDeluxeAudioEngine.h
//  XonarSTDeluxeDriver
//
//  Created by Gene Chen on 2015-01-27.
//  Copyright (c) 2015 Gene Chen. All rights reserved.
//

#ifndef _XONARSTDELUXEAUDIOENGINE_H
#define _XONARSTDELUXEAUDIOENGINE_H

#include <IOKit/audio/IOAudioEngine.h>

#include "XonarSTDeluxeAudioDevice.h"

#define XonarSTDeluxeAudioEngine com_GeneC_driver_XonarSTDeluxeEngine

class IOFilterInterruptEventSource;
class IOInterruptEventSource;

class XonarSTDeluxeAudioEngine : public IOAudioEngine
{
    OSDeclareDefaultStructors(XonarSTDeluxeAudioEngine)
    
    XonarSTDeluxeAudioDeviceRegisters	*deviceRegisters;
    
    SInt16							*outputBuffer;
    SInt16							*inputBuffer;
    
    IOFilterInterruptEventSource	*interruptEventSource;
    
public:
    
    virtual bool init(XonarSTDeluxeAudioDeviceRegisters *regs);
    virtual void free();
    
    virtual bool initHardware(IOService *provider);
    virtual void stop(IOService *provider);
    
    virtual IOAudioStream *createNewAudioStream(IOAudioStreamDirection direction, void *sampleBuffer, UInt32 sampleBufferSize);
    
    virtual IOReturn performAudioEngineStart();
    virtual IOReturn performAudioEngineStop();
    
    virtual UInt32 getCurrentSampleFrame();
    
    virtual IOReturn performFormatChange(IOAudioStream *audioStream, const IOAudioStreamFormat *newFormat, const IOAudioSampleRate *newSampleRate);
    
    virtual IOReturn clipOutputSamples(const void *mixBuf, void *sampleBuf, UInt32 firstSampleFrame, UInt32 numSampleFrames, const IOAudioStreamFormat *streamFormat, IOAudioStream *audioStream);
    virtual IOReturn convertInputSamples(const void *sampleBuf, void *destBuf, UInt32 firstSampleFrame, UInt32 numSampleFrames, const IOAudioStreamFormat *streamFormat, IOAudioStream *audioStream);
    
    static void interruptHandler(OSObject *owner, IOInterruptEventSource *source, int count);
    static bool interruptFilter(OSObject *owner, IOFilterInterruptEventSource *source);
    virtual void filterInterrupt(int index);
};

#endif /* _XONARSTDELUXEAUDIOENGINE_H */