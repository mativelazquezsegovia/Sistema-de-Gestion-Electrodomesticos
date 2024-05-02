#include <iostream>
#include "Funciones.h"
#include "rlutil.h"

void showItem(const char* text, int posx, int posy, bool selected)
{
    if (selected)
    {
        rlutil::setBackgroundColor(rlutil::BLUE);
        rlutil::locate(posx - 1, posy);
        std::cout <<" " <<(char)175 << " " << text << " " << (char)174 <<" " <<std::endl;

    }
    else
    {
        rlutil::setBackgroundColor(rlutil::BLACK);
        rlutil::locate(posx-1, posy);
        std::cout << "   " << text << "   "<< std::endl;
    }
    rlutil::setBackgroundColor(rlutil::BLACK);
}

