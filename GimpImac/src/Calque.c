#include "Calque.h"


void initCalque(Calque* calque, const char* nomFichier, TypeOperation operation, int alpha){

    int hauteur=0, longueur=0,i,j,h=0;
    char * ppm = chargementPPM(nomFichier, &longueur, &hauteur);

    calque->calqueSuivant = NULL;
    calque->calquePrecedent = NULL;
    calque->operation = operation;
    printf("%d  %d  \n", ppm[0],ppm[1]);
   // Lut* lut = NULL;



    //declaration du tableau de Pixels

    calque->tabPixels = malloc(sizeof(Pixel*) * hauteur);
    if (calque->tabPixels)
    {
      for (i = 0; i < hauteur; i++)
      {
         calque->tabPixels[i] = malloc(sizeof (Pixel)* longueur);
      }
    }

    //remplissage du tableau de Pixels à partir du ppm
    Pixel tmp ;
    //printf("%d  %d \n", hauteur, longueur);
    for(i=0;i<hauteur;i++){
        for(j=0;j<longueur;j++){
            tmp.r = abs(ppm[3*h]);
            tmp.g = abs(ppm[3*h+1]);
            tmp.b = abs(ppm[3*h+2]);
            calque->tabPixels[i][j] = tmp;
            h++;
        }
    }


    free(ppm);
    calque->alpha = alpha;
    calque->hauteur = hauteur;
    calque->longueur = longueur;
    //printf("%d  %d  %d\n\n",calque->tabPixels[0][0].r,calque->tabPixels[0][0].g,calque->tabPixels[0][0].b);

}



void appliquerLUTsurImage(Calque* calque){
    Pixel calqueFinal [calque->longueur][calque->hauteur];
	int i,j;
	
    for(i = 0; i < calque->hauteur; i++){
        for(j = 0; j < calque->longueur; j++){
			//copie de l'ancien pixel
			calqueFinal[i][j] = calque->tabPixels[i][j];
			
			//on va chercher la nouvelle valeur RGB dans notre LUT	
			calqueFinal[i][j].r = (*(calque->lut)).tabR[calqueFinal[i][j].r];
			calqueFinal[i][j].g = (*(calque->lut)).tabG[calqueFinal[i][j].r];
			calqueFinal[i][j].b = (*(calque->lut)).tabB[calqueFinal[i][j].r];
		}		
	}
	
	
}


void ajouterCalqueVierge(){
	
	
}

void changerOpacite(){
	
	
}

void modifOperationMelange(){
	
	
}

void supprimerCalque(){
	
	
}


char* calqueToChar (Calque calque){

    char* retour = malloc(sizeof(char)*calque.longueur*calque.hauteur*3);
    int h=0,i,j;
    for(i=0;i<calque.hauteur;i++){
        for(j=0;j<calque.longueur;j++){
            retour[3*h] = calque.tabPixels[i][j].r;
            retour[3*h+1] = calque.tabPixels[i][j].g;
            retour[3*h+2]= calque.tabPixels[i][j].b;
            h++;
//printf("%d  %d  %d\n\n",i,calque.longueur,calque.hauteur);
        }
    }
    return retour;
}


void exportCalque(Calque calque, char* ret, char* name){
    exportPPM(name, ret, calque.longueur, calque.hauteur);
}
