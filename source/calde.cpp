#include "calde.h"

#include <math.h>

//konstruktor
Calde::Calde():prec(0.f), pente(0)
{
	sampleRate=44100;
}

Calde::~Calde() {}

//funkcija za brzo izracunavanje sinusa
//u valnoj tablici sa 4096 uzoraka
//preuzeta sa 
//http://www.musicdsp.org/archive.php?classid=1#241

//funkcija postavlja frekvenciju uzorkovanja za objekt
//te podesava scaler
void Calde::setSampleRate(float p_srate)
{
	sampleRate=p_srate;
}
/*
float Calde::apsqrt(float x)
{
	float av = 1;
	if (x<0)
	{
		x = -x;
		av = -1;
	}
	while(x>1){
		x = x/4.0;
		av = av*2.0;
	}
	//float h = ((x<0) ? -x : x)-1;
	float out = 1-(0.975-x)*(0.975-x);

	return(av * out);
}*/



//postavljanje parametara oscilatora na pocetku svakog bloka
void Calde::update(float p_Deg, float p_Bal, float p_Vit)
{
		fDeg= p_Deg; //-6dB maksimalno zbog drugog oscilatora
		fBal= p_Bal;
		fVit= p_Vit;	
}

//generiranje signala i akumulacija na ulazni bafer
float Calde::calcule(float value)
{
	float tmp_pente, ppente;
	
	tmp_pente = (value-prec)*sampleRate;
	ppente = (tmp_pente-pente)*sampleRate;

	prec = value;
	pente = tmp_pente+0.01f;
	freq = pente*fVit/sqrtf(fDeg*fDeg-prec*prec);
	freq = freq<0 ? freq * (1-fBal*2) : freq;
	//freq = prec*100.0*fVit+0.1;
	//freq = ((pente<0) ? -pente :pente)*fVit/apsqrt(fDeg*fDeg-prec*prec)*fBal;
	//freq += apsqrt(ppente/prec)*(1-fBal)*fVit;
	//freq += ((prec==0) ? 0 : ppente)*(1-fBal)*fVit;
	//freq = ((freq<0) ? -freq :freq);
	return freq;
}



