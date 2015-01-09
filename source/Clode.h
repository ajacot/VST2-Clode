//-------------------------------------------------------------------------------------------------------
// VST Plug-Ins SDK
// Version 2.4		$Date: 2006/11/13 09:08:27 $
//
// Category     : VST 2.x SDK Samples
// Filename     : again.h
// Created by   : Steinberg Media Technologies
// Description  : Stereo plugin which applies Gain [-oo, 0dB]
//
// © 2006, Steinberg Media Technologies, All Rights Reserved
//-------------------------------------------------------------------------------------------------------

#ifndef __clode__
#define __clode__

#include "public.sdk/source/vst2.x/audioeffectx.h"

enum
{	// Parameters Tags
	kLong = 0,
	kVit,
	kPal,
	kVolume,
	kGain,

	kNumParams
};
//-------------------------------------------------------------------------------------------------------
class Clode : public AudioEffectX
{
public:
	Clode (audioMasterCallback audioMaster);
	~Clode ();

	// Processing
	virtual void processReplacing (float** inputs, float** outputs, VstInt32 sampleFrames);
	//virtual void processDoubleReplacing (double** inputs, double** outputs, VstInt32 sampleFrames);

	// Program
	virtual void setProgramName (char* name);
	virtual void getProgramName (char* name);

	// Parameters
	virtual void setParameter (VstInt32 index, float value);
	virtual float getParameter (VstInt32 index);
	virtual void getParameterLabel (VstInt32 index, char* label);
	virtual void getParameterDisplay (VstInt32 index, char* text);
	virtual void getParameterName (VstInt32 index, char* text);

	virtual void resume ();

	virtual bool getEffectName (char* name);
	virtual bool getVendorString (char* text);
	virtual bool getProductString (char* text);
	virtual VstInt32 getVendorVersion ();

protected:
	void setDelay (long pdelay);

	float* buffer;

	float fGain, vGain;
	float fLong, vLong;
	float fVit, vVit;
	float fVolume, vVolume;
	float fPal, vPal;
	float fprec;

	char programName[kVstMaxProgNameLen + 1];
	
	long delay;
	long size;
	long cursor;
	double vcursor;
	double vcursor2;
};

#endif
