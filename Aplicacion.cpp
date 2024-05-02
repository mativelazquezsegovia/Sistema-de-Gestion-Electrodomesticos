#include "Aplicacion.h"
#include "ClientesMenu.h"
#include "ElectrodomesticosMenu.h"
#include "VentasMenu.h"
#include "configuracionMenu.h"
#include <iostream>
#include "rlutil.h"
#include "Funciones.h"
using namespace std;

void Aplicacion::Ejecutar()
{
    int  y=0, op=1;
    do
    {
        rlutil::setBackgroundColor(rlutil::BLACK);
        rlutil::setColor(rlutil::WHITE);
        rlutil::hidecursor();

        rlutil::locate(68,10);
        cout<<"       MILJMCLQ "<<endl;
        rlutil::locate(68,11);
        cout<<"********************** "<<endl;
        showItem("1. CLIENTES", 68, 12, y ==0);
        showItem("2. ELECTRODOMESTICOS", 68, 13, y ==1);
        showItem("3. VENTAS",68,14, y ==2);
        showItem("4. CONFIGURACION",68,15, y ==3);
        showItem("0. SALIR DEL PROGRAMA",68,16, y ==4);
        rlutil::locate(68,17);
        cout<<"********************** "<<endl;

        switch(rlutil::getkey())
        {
        case 14://up
            rlutil::locate(68, 12 + y);
            cout<< "  " <<endl;
            y--;
            if(y<0)
            {
                y=0;
            }
            break;
        case 15://down
            rlutil::locate(68, 12 + y);
            cout<< "  " <<endl;
            y++;
            if(y>4)
            {
                y=4;
            }
            break;
        case 1://enter
            switch(y)
            {
            case 0:
            {
                ClientesMenu menu;
                menu.Mostrar();
            }
            break;
            case 1:
            {
                ElectrodomesticosMenu menu;
                menu.Mostrar();
            }
            break;
            case 2:
            {
                VentasMenu menu;
                menu.Mostrar();
            }
            break;
            case 3:
            {
                ConfiguracionMenu menu;
                menu.Configuracion();
            }
            break;
            case 4:
                rlutil::cls();
                cout << "UTN LABORATORIO II" << endl;
                op=0;
                cin.get();
                rlutil::cls();
                break;
            default:
                cout<<"OPCION INCORRECTA, VUELVA A INGRESAR"<<endl;
                break;
            }
            break;
        default:
            break;
        }
    }
    while(op!=0);
}

