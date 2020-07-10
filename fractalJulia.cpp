#include "fractalJulia.h"


void Julia::loadValues(char* reC, char* imC, char* X, char* Y, char* ar){
    Re_C = atof(reC);
    Im_C = atof(imC);
    leftDownX = atof(X);
    leftDownY = atof(Y);
    area = atof(ar);
    // sprawdzic poprawnosc zmian stringow na floaty!
}

void Julia::createJuliaBufor(){
    genJulia( buforJulia, Re_C, Im_C, leftDownX, leftDownY, area );
}

Julia::~Julia(){
    Re_C = 0;
    Im_C = 0;
    leftDownX = 0;
    leftDownY = 0;
    area = 0;
}

void Julia::showParametres(){
        std::cout<<Re_C<<" "<<Im_C<<" "<<" "<<leftDownX<<" "<<leftDownY<<" "<<area<<"\n";
}