#include "interface.h"
#include "string.h"

#include <iostream>

Interface::Interface(const char* title, const char* bPressed, const char* bUnpressed, const char* formSelected, const char* formUnselected, const char* fontFile ){
    al_init();
    al_install_keyboard();
    al_init_image_addon();
    al_init_ttf_addon();

    window = al_create_display(1300, 900);
    al_set_window_title(window, title);
    buforPicture = al_create_bitmap(800, 800);
    buttonPressed = al_load_bitmap(bPressed);
    buttonUnpressed = al_load_bitmap(bUnpressed);
    formUnpressed = al_load_bitmap(formUnselected);
    formPressed = al_load_bitmap(formSelected);
    font = al_load_ttf_font(fontFile, 24, 2);
    eventsQueue = al_create_event_queue();
    al_register_event_source(eventsQueue, al_get_keyboard_event_source());
    welcomeApp();


    if(eventsQueue == NULL){
        std::cout<<"Blad tworzenia kolejki";
    }
    createWindow();
    //int a;
    //std::cin>>a;
}

Interface::~Interface(){
    al_destroy_bitmap(formPressed);
    al_destroy_bitmap(formUnpressed);
    al_destroy_bitmap(buttonPressed);
    al_destroy_bitmap(buttonUnpressed);
    al_destroy_display(window);
    al_destroy_font(font);
    al_destroy_event_queue(eventsQueue);
}

void Interface::createWindow(){
    al_clear_to_color(al_map_rgb(0,25,51));         // background color = dark blue
    al_set_target_bitmap(buforPicture);             
    al_clear_to_color(al_map_rgb(255,255,255));     // bufor's color = white
    al_set_target_backbuffer(window);
    drawWindow();                                   // wklej formularze i bufor na okno glowne
    writeDescriptions();
    al_flip_display();                              // wyswietl okno
}

void Interface::welcomeApp(){
    int a = 0;
    al_clear_to_color(al_map_rgb(255, 255, 45)); // kolor ekranu początkowego
    al_draw_textf(font, al_map_rgb(0, 0, 0), 230, 200, 0, "Generator fraktali");
    al_draw_textf(font, al_map_rgb(0, 0, 0), 200, 240, 0, "Zbiór Julii");
    al_draw_textf(font, al_map_rgb(0, 0, 0), 220, 500, 0, "Autor:");
    al_draw_textf(font, al_map_rgb(0, 0, 0), 220, 550, 0, "Filip Mazur");
    al_flip_display();
    while(a<2){
        sleep(0.8);
        ++a;
    }
}

void Interface::writeDescriptions(){    // opisy formularzy
    al_draw_textf(font, al_map_rgb(255,255,255), 910, 57, 0, "Re (c):");
    al_draw_textf(font, al_map_rgb(255,255,255), 910, 157, 0, "Im (c):");
    al_draw_textf(font, al_map_rgb(255,255,255), 960, 245, 0, "lewy dolny róg obrazka");
    al_draw_textf(font, al_map_rgb(255,255,255), 966, 290, 0, "X:");
    al_draw_textf(font, al_map_rgb(255,255,255), 966, 360, 0, "Y:");
    al_draw_textf(font, al_map_rgb(255,255,255), 900, 458, 0, "zakres:");
}

void Interface::drawWindow(){
    al_draw_bitmap(buforPicture, 50, 50, 0);
    al_draw_bitmap(buttonUnpressed, 1010,520, 0);
    al_draw_bitmap(formPressed, 1000, 50, 0);
    al_draw_bitmap(formUnpressed, 1000, 150, 0);
    al_draw_bitmap(formUnpressed, 1000, 280, 0);
    al_draw_bitmap(formUnpressed, 1000, 350, 0);
    al_draw_bitmap(formUnpressed, 1000, 450, 0);
}

void Interface::manageMenu(){
    char end = 0;
    //ALLEGRO_EVENT ev;
    while( !end ){
        al_wait_for_event(eventsQueue, &ev);
        //al_flush_event_queue( eventsQueue );
        if( ev.type == ALLEGRO_EVENT_KEY_DOWN ){
            switch(ev.keyboard.keycode)
            {
                case ALLEGRO_KEY_DOWN:
                    if(options.selected < 5){
                        options.selected+=1;
                        showActFormDown();
                    }
                    break;
                case ALLEGRO_KEY_UP:
                    if(options.selected > 0){
                        options.selected-=1;
                        showActFormUp();
                    }
                    break;
                case ALLEGRO_KEY_ESCAPE:
                    end = 1;
                    break;
                case ALLEGRO_KEY_ENTER:
                    if(options.selected != 5)
                        loadParametres();
                    else{
                        julia.loadValues(options.Re_C_s, options.Im_C_s, options.leftDownX_s, options.leftDownY_s, options.area_s );
                        julia.createJuliaBufor();
                        drawPicture(julia.buforJulia);
                    }
            }
        }
        
    }
}

void Interface::showActFormDown(){
    switch( options.selected ){
        case 1:
            updateForm (0, 0);
            updateForm (1, 1);
            break;
        case 2:
            updateForm(1, 0);
            updateForm(2, 1);
            break;
        case 3:
            updateForm(2, 0);
            updateForm(3, 1);
            break;
        case 4:
            updateForm(3, 0);
            updateForm(4, 1);
            break;
        case 5:
            updateForm(4, 0);
            updateForm(5, 1);
            break;
    }
    al_flip_display();
}

void Interface::showActFormUp(){
    switch( options.selected ){
        case 0:
            updateForm (0, 1);
            updateForm (1, 0);
            break;
        case 1:
            updateForm(1, 1);
            updateForm(2, 0);
            break;
        case 2:
            updateForm(2, 1);
            updateForm(3, 0);
            break;
        case 3:
            updateForm(3, 1);
            updateForm(4, 0);
            break;
        case 4:
            updateForm(4, 1);
            updateForm(5, 0);
            break;
    }
    al_flip_display();
}

void Interface::loadParametres(){
    switch(options.selected){
        case 0:
            changeValue( options.Re_C_s );
            std::cout << (int)options.selected;
            break;
        case 1:
            std::cout << (int)options.selected;
            changeValue( options.Im_C_s );
            break;
        case 2:
            std::cout << (int)options.selected;
            changeValue (options.leftDownX_s );
            break;
        case 3:
            std::cout << (int)options.selected;
            changeValue( options.leftDownY_s );
            break;
        case 4:
            std::cout << (int)options.selected;
            changeValue( options.area_s );
            break;
    }
}

void Interface::changeValue( char* value ){
    char end = 0;
    int endOfString = strlen (value);
    char keyDownCode = 0;
    while( !end ){
        al_wait_for_event_timed(eventsQueue, &ev, 0.1);
        if( ev.type == ALLEGRO_EVENT_KEY_DOWN ){
            keyDownCode = ev.keyboard.keycode;
            if( keyDownCode <= ALLEGRO_KEY_9 && keyDownCode >= ALLEGRO_KEY_0 && endOfString < MAX_SIZE_STRING - 1  ){
                value[endOfString] = ( keyDownCode + 21);
                value[endOfString+1] = '\0';
                ++endOfString;
            }else if( keyDownCode == ALLEGRO_KEY_FULLSTOP && !strchr( value, '.') && endOfString < MAX_SIZE_STRING - 1 && endOfString != 0 ){ // FULLSTOP == kropka
                value[endOfString] = '.';
                value[endOfString+1] = '\0';
                ++endOfString;
            }else if( keyDownCode == ALLEGRO_KEY_MINUS && endOfString == 0 ){
                value[endOfString] = '-';
                value[endOfString+1] = '\0';
                ++endOfString;
            }else if( keyDownCode == ALLEGRO_KEY_BACKSPACE && endOfString != 0 ){
                value[endOfString - 1 ] = '\0';
                --endOfString;
            }else if( keyDownCode == ALLEGRO_KEY_ENTER ){
                end = 1;
            }
            // funkcja pokazujaca zmiany formularza
            updateForm(options.selected, 1);
            al_flip_display();
        }
    }
    std::cout << "end function\n";
}

void Interface::updateForm( char nrForm, char ifSelected ){
    switch(nrForm){
        case 0:
            if(ifSelected) al_draw_bitmap(formPressed, 1000, 50, 0);
            else al_draw_bitmap(formUnpressed, 1000, 50, 0);
            al_draw_textf( font, al_map_rgb (0,0,0), 1010, 60, 0, "%s", options.Re_C_s);
            break;
        case 1:
            if(ifSelected) al_draw_bitmap(formPressed, 1000, 150, 0);
            else al_draw_bitmap(formUnpressed, 1000, 150, 0);
            al_draw_textf( font, al_map_rgb (0,0,0), 1010, 160, 0, "%s", options.Im_C_s);
            break;
        case 2:
            if(ifSelected) al_draw_bitmap(formPressed, 1000, 280, 0);
            else al_draw_bitmap(formUnpressed, 1000, 280, 0);
            al_draw_textf( font, al_map_rgb (0,0,0), 1010, 290, 0, "%s", options.leftDownX_s);
            break;
        case 3:
            if(ifSelected) al_draw_bitmap(formPressed, 1000, 350, 0);
            else al_draw_bitmap(formUnpressed, 1000, 350, 0);
            al_draw_textf( font, al_map_rgb (0,0,0), 1010, 360, 0, "%s", options.leftDownY_s);
            break;
        case 4:
            if(ifSelected) al_draw_bitmap(formPressed, 1000, 450, 0);
            else al_draw_bitmap(formUnpressed, 1000, 450, 0);
            al_draw_textf( font, al_map_rgb (0,0,0), 1010, 460, 0, "%s", options.area_s);
            break;
        case 5:
            if(ifSelected) al_draw_bitmap ( buttonPressed, 1010, 520, 0);
            else al_draw_bitmap ( buttonUnpressed, 1010, 520, 0);
            break;            
    }
}

void Interface::drawPicture( char* buforJulia ){
    al_set_target_bitmap( buforPicture );
    for( int i=0; i < 800; ++i ){
        for(int j = 0; j < 800; ++j){
            if( julia.buforJulia[i*800 + j] != 0 ){
                al_draw_pixel(i, j, al_map_rgb(11,22,33));
            }else
            {
                al_draw_pixel(i,j, al_map_rgb(255, 255, 255));
            }
            
        }
    }
    al_set_target_backbuffer(window);
    al_draw_bitmap( buforPicture, 50, 50, 0 );
    al_flip_display();
}