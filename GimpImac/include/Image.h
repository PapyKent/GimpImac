#include "Calque.h"



#ifndef IMAGE
#define IMAGE

typedef struct {
    Calque* calque;
} Image;



void initImage(Image* image,Calque calque);
#endif
