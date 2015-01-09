//-------------------------------------------------------------------------------------------------------
// VST Plug-Ins SDK
// Version 2.4		$Date: 2006/11/13 09:08:27 $
//
// Category     : VST 2.x SDK Samples
// Filename     : again.cpp
// Created by   : Steinberg Media Technologies
// Description  : Stereo plugin which applies Gain [-oo, 0dB]
//
// © 2006, Steinberg Media Technologies, All Rights Reserved
//-------------------------------------------------------------------------------------------------------

#include "Clode.h"
//#include <fstream>

//using namespace std;

//-------------------------------------------------------------------------------------------------------
AudioEffect* createEffectInstance (audioMasterCallback audioMaster)
{
	return new Clode (audioMaster);
}

//-------------------------------------------------------------------------------------------------------
Clode::Clode (audioMasterCallback audioMaster)
: AudioEffectX (audioMaster, 1, kNumParams)	// 1 program, 1 parameter only
{
	size = 44100;
	cursor = 0;
	vcursor = 0;
	vcursor2 = 0;
	delay = size-1;
	buffer = new float[size];

	setNumInputs (1);		// stereo in
	setNumOutputs (2);		// stereo out
	setUniqueID ('lode');	// identify
	canProcessReplacing ();	// supports replacing output
	//canDoubleReplacing ();	// supports double precision processing

	vGain = 1.0f;		
	//fGain = 1-(1-vGain)*(1-vGain);
	vLong = 0.8f;
	vVit = 0.2f;
	vVolume = 0.5f;
	vPal = 0.5f;

	setParameter(kGain, vGain);
	setParameter(kLong, vLong);
	setParameter(kPal, vPal);
	setParameter(kVit, vVit);
	setParameter(kVolume, vVolume);

	vst_strncpy (programName, "Default", kVstMaxProgNameLen);	// default program name

	resume();
}

//-------------------------------------------------------------------------------------------------------
Clode::~Clode ()
{
	if (buffer)
		delete[] buffer;
	// nothing to do here
}

//----------------------------------------------------------------------------------------------------
void Clode::setDelay (long pdelay)
{
	delay = pdelay;
	cursor = 0;
	/*while(++pdelay<size){
		buffer[pdelay] = 0;
	}*/
}

//------------------------------------------------------------------------
void Clode::resume ()
{
	memset (buffer, 0, size * sizeof (float));
	AudioEffectX::resume ();
}

//-------------------------------------------------------------------------------------------------------
void Clode::setProgramName (char* name)
{
	vst_strncpy (programName, name, kVstMaxProgNameLen);
}

//-----------------------------------------------------------------------------------------
void Clode::getProgramName (char* name)
{
	vst_strncpy (name, programName, kVstMaxProgNameLen);
}

//-----------------------------------------------------------------------------------------
void Clode::setParameter (VstInt32 index, float value)
{
	switch (index)
	{
		case kLong :	vLong = value;fLong = 1-(1-value)*(1-value);				break;
		case kVit :		vVit = value;fVit = value*value*10.0;				break;
		case kPal :		vPal = value;fPal = value*2.0-1.0;				break;
		case kVolume :	vVolume = value;fVolume = value*2.0;				break;
		case kGain :	vGain = value;fGain = value;	break;
	}
}

//-----------------------------------------------------------------------------------------
float Clode::getParameter (VstInt32 index)
{
	float v = 0;

	switch (index)
	{
		case kLong :	v = vLong;	break;
		case kVit :	v = vVit;	break;
		case kPal :	v = vPal;	break;
		case kVolume :	v = vVolume;	break;
		case kGain :	v = vGain;	break;
	}
	return v;
}

//-----------------------------------------------------------------------------------------
void Clode::getParameterName (VstInt32 index, char* label)
{
	switch (index)
	{
		case kLong :	vst_strncpy (label, "byby", kVstMaxParamStrLen);	break;
		case kVit :	vst_strncpy (label, "St-Vit", kVstMaxParamStrLen);	break;
		case kPal :	vst_strncpy (label, "Palier", kVstMaxParamStrLen);	break;
		case kVolume :	vst_strncpy (label, "Volume", kVstMaxParamStrLen);	break;
		case kGain :	vst_strncpy (label, "Quant", kVstMaxParamStrLen);	break;
	}
	
}

//-----------------------------------------------------------------------------------------
void Clode::getParameterDisplay (VstInt32 index, char* text)
{
	switch (index)
	{
		case kLong :	float2string (fLong, text, kVstMaxParamStrLen);	break;
		case kVit :		float2string (fVit, text, kVstMaxParamStrLen);	break;
		case kPal :	float2string (fPal, text, kVstMaxParamStrLen);	break;
		case kVolume :	float2string (fVolume, text, kVstMaxParamStrLen);	break;
		case kGain :	float2string (fGain, text, kVstMaxParamStrLen);	break;
	}
}

//-----------------------------------------------------------------------------------------
void Clode::getParameterLabel (VstInt32 index, char* label)
{
	switch (index)
	{
		case kLong :	vst_strncpy (label, "immortel", kVstMaxParamStrLen);	break;
		case kVit :	vst_strncpy (label, "cours", kVstMaxParamStrLen);	break;
		case kPal :	vst_strncpy (label, "où?", kVstMaxParamStrLen);	break;
		case kVolume :	vst_strncpy (label, "encore", kVstMaxParamStrLen);	break;
		case kGain :	vst_strncpy (label, "plus", kVstMaxParamStrLen);	break;
	}
	
}

//------------------------------------------------------------------------
bool Clode::getEffectName (char* name)
{
	vst_strncpy (name, "Clode", kVstMaxEffectNameLen);
	return true;
}

//------------------------------------------------------------------------
bool Clode::getProductString (char* text)
{
	vst_strncpy (text, "Clode", kVstMaxProductStrLen);
	return true;
}

//------------------------------------------------------------------------
bool Clode::getVendorString (char* text)
{
	vst_strncpy (text, "Bobby", kVstMaxVendorStrLen);
	return true;
}

//-----------------------------------------------------------------------------------------
VstInt32 Clode::getVendorVersion ()
{ 
	return 666; 
}

//-----------------------------------------------------------------------------------------
void Clode::processReplacing (float** inputs, float** outputs, VstInt32 sampleFrames)
{
    float* in  =  inputs[0];
    float* out1 = outputs[0];
    float* out2 = outputs[1];

    while (--sampleFrames >= 0)
	{
		float x = *in++;

		cursor++;
		if (cursor >= size-13)
			cursor = 0;

		float y = buffer[(long)vcursor];
		buffer[(long)vcursor] *= fLong;

		vcursor += (double)fVit;
		if ((long)vcursor >= delay)
			vcursor = 0;

		vcursor2 += (double)fVit;
		if (vcursor2 >= delay*(0.5+vVit))
			vcursor2 = 0;

		y += buffer[(long)vcursor2];
		buffer[(long)vcursor2] *= fLong;

		buffer[(long)vcursor] += x;
		
		if((fprec-fPal)*(x-fPal)<0)
			setDelay((long)cursor+12);
			

		fprec = x;

		*out1++ = (x*(1.0-fGain)+y*fGain)*fVolume;
		if (out2)
			*out2++ = (x*(1.0-fGain)+y*fGain)*fVolume;
	}
}
