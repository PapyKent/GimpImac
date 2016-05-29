#include <SDL/SDL.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <time.h>

#ifndef CALQUE
#define CALQUE


#include "LUT.h"
#include "Pixel.h"
#include "Ppm.h"

typedef enum TypeOperation TypeOperation;

enum TypeOperation
{
    normal, addition, soustraction, fusion
};



typedef struct Calque{

	struct Calque* calqueSuivant;
	struct Calque* calquePrecedent;
	int longueur;
    int hauteur;

	//type d'opérations de mélange 1:addition 2:soustraction 3:fusion
    TypeOperation operation;

	//liste de LUT
	Lut* lut;

	// Image source
	Pixel** tabPixels ;

	//parametre d'opacité
	int alpha;
} Calque;



void initCalqueBlanc(Calque* calque,TypeOperation operation,int haut, int longu ,int alpha);
void copieCalque (Calque src, Calque* copie);
int initCalque(Calque* calque, const char* nomFichier, TypeOperation operation, int alpha);
void appliquerLUTsurImage();
void changerOpacite();
void modifOperationMelange();
void supprimerCalque();

unsigned char* calqueToChar (Calque calque);
void exportCalque(Calque calque, unsigned char* ret, char* name);
#endif
