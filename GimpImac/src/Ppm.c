#include "Ppm.h"
#define SIZEMAX 5000000

 unsigned char* chargementPPM(const char * nomFichier, int* longueur, int*hauteur){


    //on ouvre le fichier
    FILE * imageFile;
    imageFile = fopen(nomFichier, "r");

    //on vérifie que le fichier est bien charge
    if(imageFile == NULL) {
           fprintf(stderr, "Erreur lors du chargement de l'image.\n");
           return NULL;
       }

    int i = 0;
    char* ligne = malloc(sizeof(char)*SIZEMAX);
    int type, imLong, imHaut, valMax;


        //on recupere les infos importantes de l'image
        //PPM ligne1:type ligne2:taille ligne3: val max
    while( i < 3){

        fgets (ligne, SIZEMAX, imageFile);
        if(ligne == NULL)//fin de fichier
               return NULL;
        //on ignore les commentaires
        if(ligne[0] != '#'){
            //sscanf retourne le nombre d'éléments remplis avec succès (les options qui suivent le format de lecture)
            if(i == 0){
                if(sscanf(ligne, "P%u", &type)<1)
                    return NULL;
                i++;
            }
            else if(i == 1){
                if(sscanf(ligne, "%u %u", &imLong, &imHaut)<2)
                    return NULL;
                i++;
            }
            else if(i == 2){
                if(sscanf(ligne, "%u",&valMax)<1)
                    return NULL;
                i++;
            }
        }
    }
    //printf("type : %d    l:%d   h:%d  val:%d  \n\n",type,imLong,imHaut,valMax);
    //on verifie nos valeurs
    if(imLong < 0 || imHaut < 0 )return NULL;
    if(valMax < 0 )return NULL;
    //on lit maintenant l'image
    //on declare le tableau ou l'on va stocker nos valeurs
    unsigned char* tabImage = malloc(sizeof(char)*3*imLong*imHaut);


    //on distingue 2 cas, dépendant du format de l'image
    //fread (pointeur on l'on va stocker nos données, taille en bits des éléments lus, nombre de membres à lire, fichier)

    if(type == 6){
        //format couleur
        fread(tabImage, 1, 3*(imLong*imHaut), imageFile);
    }
    else if (type == 5){
        //format en niveaux de gris
        char* tabGris = malloc(imLong*imHaut);
        fread(tabGris, 1, (imLong*imHaut), imageFile);
        for(i=0 ; i<(imLong*imHaut) ; i++){
            int niveauGris = tabGris[i];
            tabImage[3*i] = niveauGris;
            tabImage[3*i+1] = niveauGris;
            tabImage[3*i+2] = niveauGris;

        }
        free(tabGris);

    }
    else{
         fprintf(stderr, "Format de l'image non pris en charge.\n");
         return NULL;
    }


    *longueur = imLong,
    *hauteur = imHaut;

    fclose(imageFile);
    return tabImage;


}


 int exportPPM(const char *nomFichier, unsigned char* exp, int longueur, int hauteur) {

     FILE *fichier = fopen(nomFichier,"w");
     if(!fichier) {
         fprintf(stderr, "Problème lors de l'ouverture du fichier d'export.\n");
         return 0;
     }
     fprintf(fichier, "P6\n%u %u\n255\n", longueur, hauteur);
     fwrite(exp, 1, longueur*hauteur*3, fichier);
     fclose(fichier);
     return 1;
 }
