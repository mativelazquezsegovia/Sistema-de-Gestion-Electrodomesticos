#include "configuracionMenu.h"
#include "ArchivoClientes.h"
#include "ArchivoVentas.h"
#include "ArchivoElectrodomesticos.h"
#include "rlutil.h"
#include "Funciones.h"
#include <iostream>
using namespace std;

ConfiguracionMenu::ConfiguracionMenu() : _archivoVentas("Ventas.dat"), _archivoClientes("Clientes.dat"),_archivoElectrodomesticos("Electrodomesticos.dat")
{
    // Puedes agregar más inicializaciones si es necesario
}

bool ConfiguracionMenu::Configuracion()
{
    int y=0;
    do
    {
        rlutil::setBackgroundColor(rlutil::BLACK);
        rlutil::setColor(rlutil::WHITE);
        rlutil::hidecursor();

        rlutil::locate(68,10);
        cout << "     QUE DESEA HACER?" << endl;
        rlutil::locate(68,11);
        cout << "********************** " << endl;
        showItem("1. REALIZAR COPIA DE SEGURIDAD INDIVIDUAL", 68, 12, y ==0);
        showItem("2. REALIZAR COPIA DE SEGURIDAD DE TODOS LOS ARCHIVOS", 68, 13, y ==1);
        showItem("3. RESTAURAR COPIA DE SEGURIDAD INDIVIDUAL", 68, 14, y ==2);
        showItem("4. RESTAURAR COPIA DE SEGURIDAD DE TODOS LOS ARCHIVOS", 68, 15, y ==3);
        showItem("0. VOLVER AL MENU PRINCIPAL", 68, 16, y ==4);
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
                if(backUpIndividual())
                {
                    cout<<"Aprete ENTER para volver atras"<<endl;
                    cin.ignore();
                    cin.get();
                }
                rlutil::cls();
                break;
            case 1:
                rlutil::cls();
                if(hacerBackUpTodos())
                {
                    cout<<"Aprete ENTER para volver atras"<<endl;
                    cin.ignore();
                    cin.get();
                }
                rlutil::cls();
                break;
            case 2:
                rlutil::cls();
                if(restaurarBackUpIndividual())
                {
                    cout<<"Aprete ENTER para volver atras"<<endl;
                    cin.ignore();
                    cin.get();
                }
                rlutil::cls();
                break;
            case 3:
                rlutil::cls();
                if(restaurarBackUPTodos())
                {
                    cout<<"Aprete ENTER para volver atras"<<endl;
                    cin.ignore();
                    cin.get();
                }
                rlutil::cls();
                break;
            case 4:
                rlutil::cls();
                return false;
                cin.get();
                rlutil::cls();
            default:
                cout << "OPCION INCORRECTA, VUELVA A INGRESAR" << endl;
                break;
            }
        default:
            break;
        }
    }
    while(true);
    return true;
}

bool ConfiguracionMenu::backUpIndividual()

{
    int y = 0;
    do
    {
        rlutil::setBackgroundColor(rlutil::BLACK);
        rlutil::setColor(rlutil::WHITE);
        rlutil::hidecursor();

        rlutil::locate(68,10);
        cout << "     CONFIGURACION DE COPIAS DE SEGURIDAD" << endl;
        rlutil::locate(68,11);
        cout << "********************** " << endl;

        showItem("1. REALIZAR COPIA DE SEGURIDAD DE CLIENTES", 68, 12, y == 0);
        showItem("2. REALIZAR COPIA DE SEGURIDAD DE ELECTRODOMESTICOS", 68, 13, y == 1);
        showItem("3. REALIZAR COPIA DE SEGURIDAD DE VENTAS", 68, 14, y == 2);
        showItem("0. VOLVER AL MENU PRINCIPAL", 68, 15, y == 3);

        rlutil::locate(68,16);
        cout << "**********************************" << endl;
        switch(rlutil::getkey())
        {
        case 14://up
            rlutil::locate(68, 12 + y);
            cout<< "  " <<endl;
            y--;
            if(y < 0)
            {
                y = 0;
            }
            break;
        case 15://down
            rlutil::locate(68, 12 + y);
            cout<< "  " <<endl;
            y++;
            if(y > 3)
            {
                y = 3;
            }
            break;
        case 1://enter
            switch(y)
            {
            case 0:
                rlutil::cls();
                if (_archivoClientes.hacerBackUpClientes())
                {
                    cout << "COPIA DE SEGURIDAD DE CLIENTES REALIZADA CON EXITO" << endl;
                    cout<<"Aprete ENTER para volver atras"<<endl;
                    cin.ignore();
                    cin.get();
                }
                else
                {
                    cout << "ERROR AL REALIZAR LA COPIA DE SEGURIDAD DE CLIENTES" << endl;
                }
                rlutil::cls();
                break;
            case 1:
                rlutil::cls();
                if (_archivoElectrodomesticos.hacerBackUpElectrodomesticos())
                {
                    cout << "COPIA DE SEGURIDAD DE ELECTRODOMESTICOS REALIZADA CON EXITO" << endl;
                    cout<<"Aprete ENTER para volver atras"<<endl;
                    cin.ignore();
                    cin.get();
                }
                else
                {
                    cout << "ERROR AL REALIZAR LA COPIA DE SEGURIDAD DE ELECTRODOMESTICOS" << endl;
                    cout<<"Aprete ENTER para volver atras"<<endl;
                    cin.ignore();
                    cin.get();
                }
                rlutil::cls();
                break;
            case 2:
                rlutil::cls();
                if (_archivoVentas.hacerBackUpVentas())
                {
                    cout << "COPIA DE SEGURIDAD DE VENTAS REALIZADA CON EXITO" << endl;
                    cout<<"Aprete ENTER para volver atras"<<endl;
                    cin.ignore();
                    cin.get();
                }
                else
                {
                    cout << "ERROR AL REALIZAR LA COPIA DE SEGURIDAD DE VENTAS" << endl;
                    cout<<"Aprete ENTER para volver atras"<<endl;
                    cin.ignore();
                    cin.get();
                }
                rlutil::cls();
                break;
            case 3:
                rlutil::cls();
                return false;
                cin.get();
                rlutil::cls();
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

bool ConfiguracionMenu::restaurarBackUpIndividual()
{
    int y = 0;
    do
    {
        rlutil::setBackgroundColor(rlutil::BLACK);
        rlutil::setColor(rlutil::WHITE);
        rlutil::hidecursor();

        rlutil::locate(68,10);
        cout << "     CONFIGURACION DE RESTAURACION DE COPIAS DE SEGURIDAD" << endl;
        rlutil::locate(68,11);
        cout << "****************************************" << endl;
        showItem("1. RESTAURAR COPIA DE SEGURIDAD DE CLIENTES", 68, 12, y == 0);
        showItem("2. RESTAURAR COPIA DE SEGURIDAD DE ELECTRODOMESTICOS", 68, 13, y == 1);
        showItem("3. RESTAURAR COPIA DE SEGURIDAD DE VENTAS", 68, 14, y == 2);
        showItem("0. VOLVER AL MENU PRINCIPAL", 68, 15, y == 3);
        rlutil::locate(68,16);
        cout << "**********************************" << endl;
        switch(rlutil::getkey())
        {
        case 14://up
            rlutil::locate(68, 12 + y);
            cout<< "  " <<endl;
            y--;
            if(y < 0)
            {
                y = 0;
            }
            break;
        case 15://down
            rlutil::locate(68, 12 + y);
            cout<< "  " <<endl;
            y++;
            if(y > 3)
            {
                y = 3;
            }
            break;
        case 1://enter
            switch(y)
            {
            case 0:
                rlutil::cls();
                if (_archivoClientes.restaurarBackUpClientes())
                {
                    cout << "RESTAURACION DE CLIENTES EXITOSA" << endl;
                    cout<<"Aprete ENTER para volver atras"<<endl;
                    cin.ignore();
                    cin.get();
                }
                else
                {
                    cout << "ERROR AL RESTAURAR LA COPIA DE SEGURIDAD DE CLIENTES" << endl;
                    cout<<"Aprete ENTER para volver atras"<<endl;
                    cin.ignore();
                    cin.get();
                }
                rlutil::cls();
                break;
            case 1:
                rlutil::cls();
                if (_archivoElectrodomesticos.restaurarBackUpElectrodomesticos())
                {
                    cout << "RESTAURACION DE ELECTRODOMESTICOS EXITOSA" << endl;
                    cout<<"Aprete ENTER para volver atras"<<endl;
                    cin.ignore();
                    cin.get();
                }
                else
                {
                    cout << "ERROR AL RESTAURAR LA COPIA DE SEGURIDAD DE ELECTRODOMESTICOS" << endl;
                    cout<<"Aprete ENTER para volver atras"<<endl;
                    cin.ignore();
                    cin.get();
                }
                rlutil::cls();
                break;
            case 2:
                rlutil::cls();
                if (_archivoVentas.restaurarBackUpVentas())
                {
                    cout << "RESTAURACION DE VENTAS EXITOSA" << endl;
                    cout<<"Aprete ENTER para volver atras"<<endl;
                    cin.ignore();
                    cin.get();
                }
                else
                {
                    cout << "ERROR AL RESTAURAR LA COPIA DE SEGURIDAD DE VENTAS" << endl;
                    cout<<"Aprete ENTER para volver atras"<<endl;
                    cin.ignore();
                    cin.get();
                }
                rlutil::cls();
                break;
            case 3:
                rlutil::cls();
                return false;
                cin.get();
                rlutil::cls();
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

bool ConfiguracionMenu::hacerBackUpTodos()
{
    char opc;
    cout << "ESTA SEGURO QUE DESEA REALIZAR UNA COPIA DE SEGURIDAD DE TODOS LOS ARCHIVOS JUNTOS? (S/N): "<<endl;
    cin >> opc;
    if (opc == 's' || opc == 'S')
    {

        if (_archivoClientes.hacerBackUpClientes() && _archivoElectrodomesticos.hacerBackUpElectrodomesticos() && _archivoVentas.hacerBackUpVentas())
        {
            cout << "COPIA DE SEGURIDAD TODOS LOS ARCHIVOS, OK" << endl;
            return true;
        }
        else
        {
            cout<<"NO SE PUDO REALIZAR COPIA DE SEGURIDAD DE TODOS LOS ARCHIVOS"<<endl;
            return false;
        }
    }
    else
    {
        cout << "COPIA DE SEGURIDAD CANCELADA POR EL USUARIO" << endl;
        return false;
    }
}

bool ConfiguracionMenu::restaurarBackUPTodos()
{
    char opc;
    cout << "ESTA SEGURO QUE DESEA RESTAURAR LA COPIA DE SEGURIDAD DE TODOS LOS ARCHIVOS JUNTOS? (S/N): "<<endl;
    cin >> opc;
    if (opc == 's' || opc == 'S')
    {
        if (_archivoClientes.restaurarBackUpClientes() && _archivoElectrodomesticos.restaurarBackUpElectrodomesticos() && _archivoVentas.restaurarBackUpVentas())
        {
            cout << "RESTAURACION DE TODOS LOS ARCHIVOS, OK" << endl;
            return true;
        }
        else
        {
            cout<<"NO SE PUDO RESTAURAR LA COPIA DE SEGURIDAD DE TODOS LOS ARCHIVOS"<<endl;
            return false;
        }
    }
    else
    {
        cout << "RESTAURACION DE ARCHIVOS CANCELADA POR EL USUARIO" << endl;
        return false;
    }
}


