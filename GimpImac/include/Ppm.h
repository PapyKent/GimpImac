#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifndef PPM_H
#define PPM_H




char* chargementPPM(const char * nomFichier, int * longueur, int * hauteur);
int exportPPM(const char *nomFichier, char* exp, int longueur, int hauteur);
#endif // PPM_H
