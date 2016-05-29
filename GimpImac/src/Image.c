
#include "Image.h"


void initImage(Image* image,Calque calque){
printf("d");
    image = malloc(sizeof(Image*));
    image->calque->calqueSuivant = NULL;
    image->calque->calquePrecedent = NULL;
    image->calque->operation = calque.operation;
    image->calque->lut = malloc(sizeof(Lut));
    printf("frfrfrf\n");

    initLUT(((image->calque)->lut));
    //declaration du tableau de Pixels
    int i,j;

    image->calque->tabPixels = malloc(sizeof(Pixel*) * calque.hauteur);


    if ( image->calque->tabPixels)
    {
      for (i = 0; i < calque.hauteur; i++)
      {
          printf("%d \n",i);
         image->calque->tabPixels[i] = malloc(sizeof (Pixel)* calque.longueur);
      }
    }
    Pixel tmp ;
    //printf("%d  %d \n", hauteur, longueur);
    for(i=0;i<calque.hauteur;i++){
        for(j=0;j<calque.longueur;j++){
            tmp.r = calque.tabPixels[i][j].r;
            tmp.g = calque.tabPixels[i][j].g;
            tmp.b = calque.tabPixels[i][j].b;
            image->calque->tabPixels[i][j] = tmp;
        }
    }


    image->calque->alpha = calque.alpha ;
    image->calque->hauteur = calque.hauteur ;
    image->calque->longueur = calque.longueur ;

}
