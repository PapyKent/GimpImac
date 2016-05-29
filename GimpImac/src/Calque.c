#include "Calque.h"


int initCalque(Calque* calque, const char* nomFichier, TypeOperation operation, int alpha){

    int hauteur=0, longueur=0,i,j,h=0;
    unsigned char * ppm = chargementPPM(nomFichier, &longueur, &hauteur);
    if(ppm == NULL) return 0;
    calque->calqueSuivant = NULL;
    calque->calquePrecedent = NULL;
    calque->operation = operation;
    calque->lut = malloc(sizeof(Lut));
    initLUT((calque->lut));
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
            tmp.r = ppm[3*h];
            tmp.g = ppm[3*h+1];
            tmp.b = ppm[3*h+2];
            calque->tabPixels[i][j] = tmp;
            h++;
        }
    }


    free(ppm);
    calque->alpha = alpha;
    calque->hauteur = hauteur;
    calque->longueur = longueur;
    //printf("%d  %d  %d\n\n",calque->tabPixels[0][0].r,calque->tabPixels[0][0].g,calque->tabPixels[0][0].b);
    return 1;
}


void copieCalque (Calque src, Calque* copie){
    copie->calqueSuivant = src.calqueSuivant;
    copie->calquePrecedent = src.calquePrecedent;
    copie->operation = src.operation;
    copie->lut = malloc(sizeof(Lut));
    copieLUT(*src.lut,(copie->lut));
    //declaration du tableau de Pixels
   int i,j;
    copie->tabPixels = malloc(sizeof(Pixel*) * src.hauteur);
    if (copie->tabPixels)
    {
      for (i = 0; i < src.hauteur; i++)
      {
         copie->tabPixels[i] = malloc(sizeof (Pixel)* src.longueur);
      }
    }

    Pixel tmp ;
    for(i=0;i<src.hauteur;i++){
        for(j=0;j<src.longueur;j++){
            tmp.r = src.tabPixels[i][j].r;
            tmp.g = src.tabPixels[i][j].g;
            tmp.b = src.tabPixels[i][j].b;
            copie->tabPixels[i][j] = tmp;
        }
    }



    copie->alpha = src.alpha;
    copie->hauteur = src.hauteur;
    copie->longueur = src.longueur;

}


void initCalqueBlanc(Calque* calque,TypeOperation operation,int haut, int longu ,int alpha){

    int hauteur=haut, longueur=longu,i,j,h=0;

    calque->calqueSuivant = NULL;
    calque->calquePrecedent = NULL;
    calque->operation = operation;
    calque->lut = malloc(sizeof(Lut));
    initLUT((calque->lut));
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
    for(i=0;i<hauteur;i++){
        for(j=0;j<longueur;j++){
            tmp.r = 255;
            tmp.g = 255;
            tmp.b = 255;
            calque->tabPixels[i][j] = tmp;
            h++;
        }
    }



    calque->alpha = alpha;
    calque->hauteur = hauteur;
    calque->longueur = longueur;

}





void appliquerLUTsurImage(Calque* calque){
   // Pixel calqueFinal [calque->longueur][calque->hauteur];
	int i,j;
	
    for(i = 0; i < calque->hauteur; i++){
        for(j = 0; j < calque->longueur; j++){
			//copie de l'ancien pixel
            //calque->tabPixels[i][j] = calque->tabPixels[i][j];
			
			//on va chercher la nouvelle valeur RGB dans notre LUT	
            calque->tabPixels[i][j].r = (*(calque->lut)).tabR[calque->tabPixels[i][j].r];
            calque->tabPixels[i][j].g = (*(calque->lut)).tabG[calque->tabPixels[i][j].g];
            calque->tabPixels[i][j].b = (*(calque->lut)).tabB[calque->tabPixels[i][j].b];
		}		
	}
	
	
}


void changerOpacite(){
	
	
}

void modifOperationMelange(){
	
	
}

void supprimerCalque(){
	
	
}


unsigned char* calqueToChar (Calque calque){

    unsigned char* retour = malloc(sizeof(char)*calque.longueur*calque.hauteur*3);
    int h=0,i,j;

    for(i=0;i<calque.hauteur;i++){
        for(j=0;j<calque.longueur;j++){
            retour[3*h] =(char) calque.tabPixels[i][j].r ;
            retour[3*h+1] = (char)calque.tabPixels[i][j].g;
            retour[3*h+2]= (char)calque.tabPixels[i][j].b;
            //printf(" %d   %d \n", retour[3*h],calque.tabPixels[i][j].r);
            h++;        }
    }
    return retour;
}


void exportCalque(Calque calque, unsigned char* ret, char* name){
    exportPPM(name, ret, calque.longueur, calque.hauteur);
}
