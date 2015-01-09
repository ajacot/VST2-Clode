#include "singen.h"

//#include "log.h"

//konstruktor
SinGen::SinGen()
{
	//Log("Singen\n");
	freq = 440.0f;
	y = 0.0f;
	v = freq;
}

SinGen::~SinGen() {}

//funkcija za brzo izracunavanje sinusa
//u valnoj tablici sa 4096 uzoraka
//preuzeta sa 
//http://www.musicdsp.org/archive.php?classid=1#241

//funkcija postavlja frekvenciju uzorkovanja za objekt
//te podesava scaler
/*void SinGen::setSampleRate(float p_srate)
{
	sampleRate=p_srate;
}*/

/*float SinGen::apsqrt(float x)
{
	float h = x-1;

	return(1+h/2-h*h/8);
}



//postavljanje parametara oscilatora na pocetku svakog bloka
void SinGen::update(float p_Deg, float p_Bal, float p_Vit)
{
		fDeg= p_Deg; //-6dB maksimalno zbog drugog oscilatora
		fBal= p_Bal;
		fVit= p_Vit;	
}*/

float SinGen::setFreq(float p_Freq){
	v *= p_Freq/freq;
	freq = p_Freq;
	return(freq);
}

//generiranje signala i akumulacija na ulazni bafer
float SinGen::calcule(float dx)
{
	v-=freq*freq*y;
	float m = 300;
	if(v<-m){
		v = -m;
	}else if(v>m){
		v = m;
	}
	y+=dx*v;
	return y;
}



