#include "ClientesMenu.h"
#include "rlutil.h"
#include "Funciones.h"
#include <iostream>
using namespace std;

bool ClientesMenu::Mostrar()
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
        cout<<"**********************"<<endl;
        showItem("1- AGREGAR NUEVO CLIENTE", 68, 12, y ==0);
        showItem("2- DAR DE BAJA CLIENTE", 68, 13, y ==1);
        showItem("3- MOSTRAR CLIENTES", 68, 14, y ==2);
        showItem("4- BUSCAR CLIENTE POR DNI", 68, 15, y ==3);
        showItem("5- MODIFICAR E-MAIL", 68, 16, y ==4);
        showItem("6- REACTIVAR CLIENTE", 68, 17, y ==5);
        showItem("0- VOLVER AL MENU PRINCIPAL", 68, 18, y ==6);
        rlutil::locate(68,19);
        cout<<"**********************"<<endl;
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
            if(y>6)
            {
                y=6;
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
                    _managerClientes.Cargar();
                    cout << "DESEA CARGAR OTRO CLIENTE? (S/N): ";
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
                _managerClientes.bajaCliente();
                cout<<"Aprete ENTER para volver atras"<<endl;
                cin.ignore();
                cin.get();
                rlutil::cls();
                break;
            case 2:
                rlutil::cls();
                _managerClientes.mostrarRegistrosClienteActivosNoActivos();
                cout<<"Aprete ENTER para volver atras"<<endl;
                cin.ignore();
                cin.get();
                rlutil::cls();
                break;
            case 3:
                rlutil::cls();
                _managerClientes.buscarClientexDni();
                cout<<"Aprete ENTER para volver atras"<<endl;
                cin.ignore();
                cin.get();
                rlutil::cls();
                break;
            case 4:
                rlutil::cls();
                _managerClientes.modificarEmail();
                cout<<"Aprete ENTER para volver atras"<<endl;
                cin.ignore();
                cin.get();
                rlutil::cls();
                break;
            case 5:
                rlutil::cls();
                _managerClientes.reactivarCliente();
                cout<<"Aprete ENTER para volver atras"<<endl;
                cin.ignore();
                cin.get();
                rlutil::cls();
                break;
            case 6:
                rlutil::cls();
                return false;
                cin.get();
                rlutil::cls();
                break;
            default:
                cout << "OPCION INCORRECTA, VUELVA A INGRESAR" << endl;
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
