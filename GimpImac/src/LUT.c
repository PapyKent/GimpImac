#include "LUT.h"
#include "Calque.h"
#include <math.h>


void initLUT(Lut* lut){
    int i;
    for(i=0; i<255 ; i++){

        lut->tabR[i] = i;
        lut->tabG[i] = i;
        lut->tabB[i] = i;

    }

}

void copieLUT(Lut lutSRC, Lut* lutCopie){
    int i;
    for(i=0; i<255 ; i++){

        lutCopie->tabR[i] = lutSRC.tabR[i];
        lutCopie->tabG[i] = lutSRC.tabG[i];
        lutCopie->tabB[i] = lutSRC.tabB[i];

    }
}



void addlum(Lut* lut, int para){
	//augmente la luminosité
	int i;
	for(i=0; i<255 ; i++){
		
        if( (lut->tabR[i]+para) < 255)
			lut->tabR[i]+= para;
		else
			lut->tabR[i] = 255;
			
			
        if( (lut->tabG[i]+para) < 255)
			lut->tabG[i]+= para;
		else
			lut->tabG[i] = 255;
			
			
        if( (lut->tabB[i]+para) < 255)
			lut->tabB[i]+= para;
		else
			lut->tabB[i] = 255;
		
	}
	
}



void dimlum(Lut* lut, int para){
	//diminution de la luminosité
	
	int i;
	for(i=0; i<255 ; i++){
		
		if( (lut->tabR[i]-para) > 0)
			lut->tabR[i]-= para;
		else
			lut->tabR[i] = 0;
			
			
		if( (lut->tabG[i]-para) > 0)
			lut->tabG[i]-= para;
		else
			lut->tabG[i] = 0;
			
			
		if( (lut->tabB[i]-para) > 0)
			lut->tabB[i]-= para;
		else
			lut->tabB[i] = 0;
		
	}
	
	
}



void addcon(Lut* lut) { 
	//augmente le contraste
	
	int min = 40;
	int max = 215;
	
	int i;
	
	for (i=0; i<255; i++) {
		
		// pour le ROUGE
		
		if (lut->tabR[i] < min)
			lut->tabR[i] = 0;
		
		else if (lut->tabR[i] > max)
			lut->tabR[i] = 255;
		
		else if (lut->tabR[i] >= min && lut->tabR[i] <= max)
			lut->tabR[i] = round((double)(lut->tabR[i] - min) / (double)(max - min)*255.0);
			
			
		// pour le VERT
		
		if (lut->tabG[i] < min)
			lut->tabG[i] = 0;
		
		else if (lut->tabG[i] > max)
			lut->tabG[i] = 255;
		
		else if (lut->tabG[i] >= min && lut->tabG[i] <= max)
			lut->tabG[i] = round((double)(lut->tabG[i] - min) / (double)(max - min)*255.0);
		
		
		// pour le BLEU
	
		if (lut->tabB[i] < min)
			lut->tabB[i] = 0;
		
		else if (lut->tabB[i] > max)
			lut->tabB[i] = 255;
		
		else if (lut->tabB[i] >= min && lut->tabB[i] <= max)
			lut->tabB[i] = round((double)(lut->tabB[i] - min) / (double)(max - min)*255.0);
	
	}
	
	
	
}

void dimcon(Lut* lut){
	//diminution du contraste
	
	int min = 40;
	int max = 215;
	
	int i;
	
	for (i=0; i<255; i++) {
		
		// pour le ROUGE
		
		lut->tabR[i] = round((double)((lut->tabR[i] * (max-min)) / 255) + min);
		
		// pour le VERT
		
		lut->tabG[i] = round((double)((lut->tabG[i] * (max-min)) / 255) + min);
		
		// pour le BLEU
		
		lut->tabB[i] = round((double)((lut->tabB[i] * (max-min)) / 255) + min);
			
	}
	
	
}


void invert(Lut *lut) {
	//inversion de la couleur
	
	int i;
	
	for (i=0; i<255; i++) {
	
		// pour le ROUGE
		
		lut->tabR[i] = 255 - lut->tabR[i];
		
		// pour le VERT
		
		lut->tabG[i] = 255 - lut->tabG[i];
		
		// pour le BLEU
		
		lut->tabB[i] = 255 - lut->tabB[i];
		
	}
}
	


void sepia(Calque* calque){
   
	int i,j;
	
    for(i = 0; i < calque->hauteur; i++){
        for(j = 0; j < calque->longueur; j++){
			
			float moyenne = (calque->tabPixels[i][j].r + calque->tabPixels[i][j].g + calque->tabPixels[i][j]. b) / 3;
			
            calque->tabPixels[i][j].r = moyenne * 0.784;
            calque->tabPixels[i][j].g = moyenne * 0.588;
            calque->tabPixels[i][j].b = moyenne * 0.392;
		}		
	}
	
}

void noirBlanc(Calque* calque, int para){
   
	int i,j;
	
    for(i = 0; i < calque->hauteur; i++){
        for(j = 0; j < calque->longueur; j++){
			
			float moyenne = (calque->tabPixels[i][j].r + calque->tabPixels[i][j].g + calque->tabPixels[i][j]. b) / 3;
			
			if (moyenne < para) {
				calque->tabPixels[i][j].r = 0;
				calque->tabPixels[i][j].g = 0;
				calque->tabPixels[i][j].b = 0;
			}
           
			if (moyenne >= para) {
				calque->tabPixels[i][j].r = 255;
				calque->tabPixels[i][j].g = 255;
				calque->tabPixels[i][j].b = 255;
			}
            
		}		
	}
	
}
