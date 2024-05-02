#include "ElectrodomesticosMenu.h"
#include <iostream>
#include "rlutil.h"
#include "Funciones.h"
using namespace std;

bool  ElectrodomesticosMenu::Mostrar()
{
    int  y=0;
    do
    {
        rlutil::setBackgroundColor(rlutil::BLACK);
        rlutil::setColor(rlutil::WHITE);
        rlutil::hidecursor();

        rlutil::locate(68,10);
        cout << "     QUE DESEA HACER?" << endl;
        rlutil::locate(68,11);
        cout<<"********************** "<<endl;
        showItem("1- AGREGAR NUEVO ELECTRODOMESTICO", 68, 12, y ==0);
        showItem("2- DAR DE BAJA ELECTRODOMESTICO", 68, 13, y ==1);
        showItem("3- MOSTRAR LISTADO DE ELECTRODOMESTICOS", 68, 14, y ==2);
        showItem("4- BUSCAR ELECTROMESTICO POR CODIGO", 68, 15, y ==3);
        showItem("5- MODIFICAR STOCK", 68, 16, y ==4);
        showItem("6- FILTRAR POR DISPONIBILIDAD", 68, 17, y ==5);
        showItem("7- REACTIVAR UN PRODUCTO", 68, 18, y ==6);
        showItem("0- VOLVER AL MENU PRINCIPAL", 68, 19, y ==7);
        rlutil::locate(68,20);
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
            if(y>7)
            {
                y=7;
            }
            break;
        case 1://enter
            switch(y)
            {
            case 0:
                char _opcion;
                rlutil::cls();
                do
                {
                    _managerElectrodomesticos.Cargar();
                    cout << "DESEA CARGAR OTRO PRODUCTO? (S/N): ";
                    cin >> _opcion;
                    cin.ignore();
                }
                while (_opcion == 'S' || _opcion == 's');
                cout<<"Aprete ENTER para volver atras"<<endl;
                cin.get();
                rlutil::cls();
                break;
            case 1:
                rlutil::cls();
                _managerElectrodomesticos.bajaElectrodomestico();
                    cout<<"Aprete ENTER para volver atras"<<endl;
                    cin.ignore();
                    cin.get();
                rlutil::cls();
                break;
            case 2:
                rlutil::cls();
                 _managerElectrodomesticos.mostrarRegistrosDisponiblesyEliminados();
                    cout<<"Aprete ENTER para volver atras"<<endl;
                    cin.ignore();
                    cin.get();
                rlutil::cls();
                break;
            case 3:
                rlutil::cls();
                _managerElectrodomesticos.buscarElectrodomesticoxCodigo();
                cout<<"Aprete ENTER para volver atras"<<endl;
                cin.ignore();
                cin.get();
                rlutil::cls();
                break;
            case 4:
                rlutil::cls();
                _managerElectrodomesticos.modificarStock();
                cout<<"Aprete ENTER para volver atras"<<endl;
                cin.ignore();
                cin.get();
                rlutil::cls();
                break;
            case 5:
                rlutil::cls();
                _managerElectrodomesticos.filtrarPorDisponibilidad();
                cout<<"Aprete ENTER para volver atras"<<endl;
                cin.ignore();
                cin.get();
                rlutil::cls();
                break;
            case 6:
                rlutil::cls();
                _managerElectrodomesticos.reactivarElectrodomesticoPorCodigo();
                cout<<"Aprete ENTER para volver atras"<<endl;
                cin.ignore();
                cin.get();
                rlutil::cls();
                break;
            case 7:
                rlutil::cls();
                return false;
                cin.get();
                rlutil::cls();
                break;
            default:
                cout << "OPCION INCORRECTA. VUELVA A INGRESAR" << endl;
                break;
            }
            break;
        default:
            break;
        }
    }
    while(true);
    return true;
}
