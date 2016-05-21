#ifndef LUT
#define LUT

typedef struct Lut{

	//canaux
	int tabR[255] ;
	int tabG[255] ;
	int tabB[255] ;

} Lut;


void resetLUT(Lut* lut);

void addlum(Lut* lut, int para);//augmente la luminosité
void dimlum(int para);//diminution de la luminosité
void addcon(int para);//augmente le contraste
void dimcon(int para);//diminution du contraste
void invert();//inversion de la couleur

// --A DEFINIR -- ajouter pls para
void sepia();//effet sepia


#endif
