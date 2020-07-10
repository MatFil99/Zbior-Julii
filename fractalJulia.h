#ifndef FRACTALJULIA_H_
#define FRACTALJULIA_H_

#include <iostream>
#include <string>

extern "C" void genJulia( char* bufor, float ReC, float ImC, float leftDownX, float leftDownY, float width );

class Julia{
    float Re_C;
    float Im_C;
    float leftDownX;
    float leftDownY;
    float area;

public:
    char buforJulia[640000];
    
    Julia():Re_C(0), Im_C(0),leftDownX(0), leftDownY(0), area(0) {}
    ~Julia();
    void loadValues(char* reC, char* imC, char* X, char* Y, char* ar);   // wczytuje parametry obrazka
    void createJuliaBufor();    // tworzy bufor fraktali
    void showParametres();
};

#endif //