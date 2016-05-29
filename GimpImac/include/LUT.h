#include <stdlib.h>
#include <stdio.h>

#ifndef LUT
#define LUT

typedef struct Lut{

	//canaux
	int tabR[255] ;
	int tabG[255] ;
	int tabB[255] ;

} Lut;

void initLUT(Lut* lut);
void copieLUT(Lut lutSRC, Lut* lutCopie);

void addlum(Lut* lut, int para);//augmente la luminosité
void dimlum(Lut* lut, int para);//diminution de la luminosité
void addcon(Lut* lut);//augmente le contraste
void dimcon(Lut* lut);//diminution du contraste
void invert(Lut* lut);//inversion de la couleur
void sepia(Lut* lut);//applique un effet sepia à l'image

// --A DEFINIR -- ajouter pls para
void sepia();//effet sepia


#endif
