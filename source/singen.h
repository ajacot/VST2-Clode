//oscilator sa potrazivanjem u valnoj tablici

#include "public.sdk/source/vst2.x/audioeffectx.h"

//konstante
#define Pi  3.141592653589793

//enumerator
/*enum
{
	//kNumFrequencies = 128,	// 128 frekvencija, svaka za jednu MIDI notu
	//kWaveSize = 4096		// broj uzoraka u valnoj tablici
};
*/
//deklaracija klase za oscilator
class SinGen
{
public:
	float freq;

	float y;

	SinGen();
	~SinGen();
	
	//funkcije koje se pozivaju u suspendiranom stanju i pri inicijalizaciji
	//void setSampleRate(float p_srate);	

	//float apsqrt(float x);	
	float setFreq(float p_Freq);
	//funkcije koje se pozivaju unutar izvrsavanja processReplacing() funkcije
	//void update(float p_Deg, float p_Bal, float p_Vit); //poziva se jednom po baferu
	float calcule(float value); //akumulira izlazne podatke

	//funkcije koje se pozivaju unutar izvrsavanja processEvents() funkcije

private:

	//podaci odredeni frekvencijom uzorkovanja
	//float sampleRate;

	//parametri odredeni pritisnutom tipkom
	float v;
	
	//float fDeg;
	//float fBal;
	//float fVit;	
};

