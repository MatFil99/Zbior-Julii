#ifndef INTERFACE_H_
#define INTERFACE_H_

#include <string>
#include "fractalJulia.h"

#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>

const int MAX_SIZE_STRING = 16;

struct menuOptions{
    char selected = 0;
    char Re_C_s[MAX_SIZE_STRING] = "";           //_s - string
    char Im_C_s[MAX_SIZE_STRING] = "";
    char leftDownX_s[MAX_SIZE_STRING] = "";
    char leftDownY_s[MAX_SIZE_STRING] = "";
    char area_s[MAX_SIZE_STRING] = "";
    const char* fileName = "zbiorJulii.bmp";
};

class Interface{
    menuOptions options;
    Julia julia;
    const char* form1 = "Re(C):";
    const char* form2 = "Im(C):";
    const char* form3 = "leftDown X:";
    const char* form4 = "leftDown Y:";
    const char* form5 = "zakres:";

    ALLEGRO_DISPLAY* window;
    ALLEGRO_BITMAP* formPressed;
    ALLEGRO_BITMAP* formUnpressed;
    ALLEGRO_BITMAP* buttonPressed;
    ALLEGRO_BITMAP* buttonUnpressed;
    ALLEGRO_BITMAP* buforPicture;
    ALLEGRO_FONT* font;
    ALLEGRO_KEYBOARD_STATE keyboard;
    ALLEGRO_EVENT_QUEUE* eventsQueue;
    ALLEGRO_EVENT ev;

    private:
    Interface(){}
    public:
    Interface( const char* title, const char* bPressed, const char* bUnpressed, const char* formSelected, const char* formUnselected, const char* fontFile );
    ~Interface();
    void createWindow();
    void welcomeApp();
    void drawWindow();
    void writeDescriptions();
    
    void manageMenu();
    void loadParametres();
    void showActFormDown();
    void showActFormUp();
    void changeValue( char* );
    void updateForm( char, char );
    void drawPicture( char* buforJulia );
};

#endif //