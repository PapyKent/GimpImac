#include <string.h>
#include <stdio.h>
#include <SDL/SDL.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <time.h>

#include "interface.h"
#include "outils.h"

#include "Calque.h"

float tabX[] = { 0.07 , 0.24 , 0.37 , 0.625 , 0.875 , 0.75 , 0.65 , 0.65 , 0.65 , 0.65 , 0.65 , 0.85 , 0.85 , 0.85 , 0.85 , 0.85 };
float tabY[] = { 0.92 , 0.92 , 0.92 , 0.115 , 0.115 , 0.115 , 0.915 , 0.755 , 0.595 , 0.435 , 0.275 , 0.915 , 0.755 , 0.595 , 0.435 , 0.275 };
	
/// ///////////////////////////////////////////////////////////////////////////
/// Tableau representant une image...
unsigned char* image_base = NULL;
unsigned char* image_switch = NULL;
int switch_image = 0;

////////////////////////////      MAIN      ///////////////////////////

/// ///////////////////////////////////////////////////////////////////////////
/// fonction associée aux interruptions clavier
/// - c : caractère saisi
/// - x,y : coordonnée du curseur dans la fenetre
void kbdFunc(unsigned char c, int x, int y) {
    char saisie[100] = {'\0'};
    printf("Touche tapee %c (coord souris %d/%d)\n",c,x,y);
    switch(c) {
        case 't': // Exemple de saisie sur le terminal
            printf("Debraillement sur le terminal\n");
            printf("Merci de rentrer une chaine de caractère :");
            scanf("%s",saisie);
            printf("On a tape %s\n",saisie);
            break;
        case 'i': // Exemple d'utilisation des fonctions de la bibliotheque glimagimp
            printInfo();
            break;
        case 's': // Exemple d'utilisation des fonctions de la bibliotheque glimagimp
            if (!switch_image)
                actualiseImage(image_switch);
            else
                actualiseImage(image_base);
            switch_image = 1-switch_image;
            break;
        case 27: // Touche Escape
            printf("Fin du programme\n");
            exit(0);
            break;
        default :
            printf("Touche non fonctionnelle\n");
    }
}

/// ///////////////////////////////////////////////////////////////////////////
/// fonction associée aux interruptions clavier speciales
/// - c : caractère saisi
/// - x,y : coordonnée du curseur dans la fenêtre
void kbdSpFunc(int c, int x, int y)
{
    printf("Touche speciale utilisee %d (coord souris %d/%d)\n",c,x,y);
    switch(c) {
        case GLUT_KEY_F1 : // quit
            printf("Touche F1\n");
            break;
        default :
            printf("Touche speciale non fonctionnelle\n");
    }
}

/// ///////////////////////////////////////////////////////////////////////////
/// fonction associée aux evenements souris
/// - x,y : coordonnée de la souris dans la fenêtre
void clickMouse(int button,int state,int x,int y) {
    if (button == GLUT_LEFT_BUTTON) {
        printf("Button gauche ");
    }
    else if (button == GLUT_MIDDLE_BUTTON) {
        printf("Button milieu ");
    }
    else { // button == GLUT_RIGHT_BUTTON
        printf("Button droit ");
    }
    if (state == GLUT_DOWN) {
        printf("clique\n");
    }
    else { // state == GLUT_UP
        printf("relache\n");
    }
    
   
		
    if (x == 700) {
		printf("AAAAAAAAAAAAAAAAAAAAAAAAAAAAA\n");
	}
    
    printf("Coordonnees du point clique %d %d\n",x,y);
}

/// ///////////////////////////////////////////////////////////////////////////
/// fonction de personnalisation du rendu
void mondessin() {
   // writeString(0,0,"Section image");
   // fixeCouleur(1.0,0.0,0.0);
   // drawLigne(0.0,0.0,1.0,1.0);
   // fixeCouleur(1.0,1.0,0.0);
   // drawCarre(0.5,0.5,0.7,0.7);
    fixeCouleur(0.96,0.65,0.16);
    drawCarre(0.02,0.96,0.15,0.88);  	/// import export histogramme
    drawCarre(0.17,0.96,0.30,0.88);
    drawCarre(0.32,0.96,0.45,0.88);
    fixeCouleur(0.9,0.4,0.3);
    drawCarre(0.60,0.15,0.65,0.08); 	/// choix du calque
    drawCarre(0.85,0.15,0.90,0.08); 
    drawCarre(0.68,0.15,0.82,0.08);  
    fixeCouleur(1.0,1.0,1.0);
    writeString(0.71,0.915,"LUMINOSITE");
    writeString(0.71,0.755,"CONTRASTE");
    writeString(0.71,0.595,"OPACITE");
    writeString(0.71,0.435,"INVERSER");
    writeString(0.71,0.275,"SEPIA");
    writeString(0.03,0.915,"Importer image");
    writeString(0.18,0.915,"Exporter image");
    writeString(0.34,0.915,"Histogramme");
    writeString(0.615,0.11,"<<");
    writeString(0.87,0.11,">>");
    writeString(0.7,0.11,"Suppr Calque");
    
    fixeCouleur(0.3,0.64,0.87);
    drawDisque(0.65,0.915,0.02);	/// luminosite
    drawDisque(0.65,0.755,0.02);	/// contraste
    drawDisque(0.65,0.595,0.02);	/// opacite
    drawDisque(0.65,0.435,0.02);	/// inverser
    drawDisque(0.65,0.275,0.02);	/// sepia
    
    fixeCouleur(0.25,0.83,0.49);
    drawDisque(0.85,0.915,0.02);	/// luminosite
    drawDisque(0.85,0.755,0.02);	/// contraste
    drawDisque(0.85,0.595,0.02);	/// opacite  
    drawDisque(0.85,0.435,0.02);	/// inverser  
    drawDisque(0.85,0.275,0.02);	/// sepia
    //fixeCouleur(0.0,0.0,1.0);
    //drawCercle(0.7,0.5,0.02);
    fixeCouleur(1.0,1.0,1.0);
}

unsigned char* createImage(unsigned int* w_im,unsigned int* h_im) {
    unsigned int i,j,k;
    *w_im = 800;
    *h_im = 600;

    unsigned char* tabRVB =
        (unsigned char*) malloc((*w_im)*(*h_im)*3*sizeof(unsigned char));
    if (tabRVB == NULL) {
        printf("Erreur d'allocation dans createImage\n");
        exit(1);
    }
    // Pour chaque ligne
    k = 0;
    for(i = 0;i<(*h_im);i++) {
        for(j = 0;j<(*w_im);j++) {
            tabRVB[k++] = (unsigned char)(int)(255*j/(float)(*w_im));
            tabRVB[k++] = (unsigned char)(int)(255*j/(float)(*w_im));
            tabRVB[k++] = (unsigned char)(int)(255*j/(float)(*w_im));
        }
    }
    return tabRVB;
}

unsigned char* createSwitch(unsigned int w_im,unsigned int h_im) {
    unsigned int i,j,k;

    unsigned char* tabRVB2 =
        (unsigned char*) malloc(w_im*h_im*3*sizeof(unsigned char));
    if (tabRVB2 == NULL) {
        printf("Erreur d'allocation dans createImage\n");
        exit(1);
    }
    // Pour chaque ligne
    k = 0;
    for(i = 0;i<h_im;i++) {
        for(j = 0;j<w_im;j++) {
            tabRVB2[k++] = (unsigned char)255;
            tabRVB2[k++] = (unsigned char)(int)(255*i/(float)h_im);
            tabRVB2[k++] = (unsigned char)(int)(255*j/(float)w_im);
        }
    }
    return tabRVB2;
}

void quitte(void) {
    if (image_base != NULL) {
        free(image_base);
    }
}

int main(int argc, char** argv) {
    int i;
    unsigned int w,h;
    // Initialize data;
    w = 800;
    h = 600;
    image_base = NULL;
    // Parse the command line arguments
    printf("Argc = %d\n",argc);
    for (i=1;i<argc;i++) {
        if (strcmp(argv[i],"-h") == 0) {
            printf("Affichage de l'aide\n");
            exit(1);
        }
    }

    // Loading data
    image_base = createImage(&w,&h);
    image_switch = createSwitch(w,h);

    // Loading IHM
    fixeFonctionClicSouris(clickMouse);
    fixeFonctionClavier(kbdFunc);
    fixeFonctionClavierSpecial(kbdSpFunc);
    fixeFonctionDessin(mondessin);




    TypeOperation op = normal;
    Calque calque;
    initCalque(&calque, "../images/F16.512.ppm", op, 1);
    printf("%d  %d\n",calque.longueur,calque.hauteur);




    char* ret = (char*)calqueToChar(calque);
    initGLIMAGIMP_IHM(calque.longueur,calque.hauteur,ret,w+200,h);
    exportCalque(calque,ret,"export.txt");
    //printf("%d  %d  %d\n\n",calque.tabPixels[0][0].r,calque.tabPixels[0][0].g,calque.tabPixels[0][0].b);
    return 0;
}
