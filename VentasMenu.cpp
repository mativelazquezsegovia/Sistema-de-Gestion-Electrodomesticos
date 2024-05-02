#include "VentasMenu.h"
#include <iostream>
#include "rlutil.h"
#include "Funciones.h"
using namespace std;

bool VentasMenu::Mostrar()
{
    int y=0, op=1;
    do
    {
        rlutil::setBackgroundColor(rlutil::BLACK);
        rlutil::setColor(rlutil::WHITE);
        rlutil::hidecursor();

        rlutil::locate(68,10);
        cout << "    QUE DESEA HACER?" << endl;
        rlutil::locate(68,11);
        cout<<"********************** "<<endl;
        showItem("1. NUEVA VENTA",68,12, y ==0);
        showItem("2. MOSTRAR VENTAS",68,13, y ==1);
        showItem("3. ELIMINAR UNA VENTA",68,14, y ==2);
        showItem("4. REALIZAR UNA DEVOLUCION",68,15, y ==3);
        showItem("0. VOLVER AL MENU PRINCIPAL",68,16, y ==4);
        rlutil::locate(68,17);
        cout << "**********************************" << endl;

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
                rlutil::cls();
                _managerVentas.Cargar();
                cout<<"Aprete ENTER para volver atras"<<endl;
                cin.ignore();
                cin.get();
                rlutil::cls();
                break;
            case 1:
                rlutil::cls();
                _managerVentas.mostrarRegistrosVentas();
                cout<<"Aprete ENTER para volver atras"<<endl;
                cin.get();
                rlutil::cls();
                break;
            case 2:
                rlutil::cls();
                _managerVentas.bajaVenta();
                cout<<"Aprete ENTER para volver atras"<<endl;
                cin.get();
                rlutil::cls();
                break;
            case 3:
                rlutil::cls();
                _managerVentas.Devolucion();
                cout<<"Aprete ENTER para volver atras"<<endl;
                cin.get();
                rlutil::cls();
                break;
            case 4:
                op=0;
                break;
            default:
                cout << "OPCION INCORRECTA" << endl;
                break;
            }
            break;
        default:
            break;
        }
    }
    while(op!=0);
    return true;
}

