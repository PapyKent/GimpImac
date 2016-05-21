#include "LUT.h"

void resetLUT(Lut* lut){
	int i;
	for(i=0; i<255 ; i++){		
		
		lut->tabR[i] = 0;
		lut->tabR[i] = 0;
		lut->tabB[i] = 0;
		
	}
}


void addlum(Lut* lut, int para){
	//augmente la luminosité
	int i;
	for(i=0; i<255 ; i++){
		
		if( (lut->tabR[i]+para) <= 255)
			lut->tabR[i]+= para;
			
			
		if( (lut->tabR[i]+para) <= 255)
			lut->tabR[i]+= para;
			
			
		if( (lut->tabB[i]+para) <= 255)
			lut->tabB[i]+= para;
		
	}
	
}



void dimlum(int para){
	//diminution de la luminosité
	
	
}


void addcon(int para){
	//augmente le contraste
	
	
}

void dimcon(int para){
	//diminution du contraste
	
	
}


void invert(){//255 - couleur actuelle
	//inversion de la couleur
	
	
	
}
