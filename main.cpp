#include <iostream>

#include "interface.h"
#include "fractalJulia.h"



int main(){
    

    char buforJulia[640000];
//    genJulia(buforJulia, -0.14, 0.15, -1.5, -1.5, 3);

    Interface JuliaApp("Zbiór Julii","interface_pictures/checkedButton.bmp","interface_pictures/button.bmp","interface_pictures/checkedForm.bmp","interface_pictures/form.bmp","interface_pictures/courbd.ttf");
    JuliaApp.manageMenu();
    return 0;
}
