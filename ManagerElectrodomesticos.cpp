#include "ManagerElectrodomesticos.h"
#include "rlutil.h"
#include "Funciones.h"
#include <iostream>
using namespace std;

void ManagerElectrodomesticos::Cargar()
{
    int codigo;
    string nombre;
    float precioUnitario;
    int stock;
    float capacidad;
    bool disponibilidad;

    cout<< "Codigo de Electrodomestico: "<<endl;
    cin>>codigo;
    cin.ignore();
    // Verificar si el código ya está presente
    if (_archivo.validarCodigoRepetido(codigo))
    {
        cout << "EL CODIGO DEL PRODUCTO YA EXISTE NE LA BASE DE DATOS" << endl;
        return;
    }
    cout<< "Nombre Electromestico: "<<endl;
    getline(cin, nombre);
    cout<< "Precio Unitario $: "<<endl;
    cin>>precioUnitario;
    cin.ignore();
    cout<< "Stock: "<<endl;
    cin>>stock;
    cin.ignore();
    cout<< "Capacidad: "<<endl;
    cin>>capacidad;
    cin.ignore();
    cout<< "Disponibilidad (1 para true, 0 para false): "<<endl;
    cin>>disponibilidad;
    if (disponibilidad != 0 && disponibilidad != 1)
    {
        cout << "Opción no valida." << endl;
        disponibilidad = false;
    }
    cin.ignore();

    Electrodomesticos reg;
    reg.setCodigo(codigo);
    reg.setNombre(nombre);
    reg.setPrecioUnitario(precioUnitario);
    reg.setStock(stock);
    reg.setCapacidad(capacidad);
    reg.setDisponibilidad(disponibilidad);
    reg.setEstado(true);
    cout << endl;

    bool ok=_archivo.agregaRegistros(reg);
    if (ok)
    {
        cout << "REGISTRO AGREGADO"<<endl;
    }
    else
    {
        cout << "NO SE CARGO EL REGISTRO"<<endl;
    }
    cout << endl;
}

void ManagerElectrodomesticos::Mostrar(Electrodomesticos reg)
{
    cout<< "Codigo de Electrodomestico: "<< reg.getCodigo() <<endl;
    cout<< "Nombre Electromestico: "<< reg.getNombre() <<endl;
    cout<< "Precio Unitario: "<< reg.getPrecioUnitario() <<endl;
    cout<< "Stock: "<< reg.getStock() << endl;
    cout<< "Capacidad: "<< reg.getCapacidad() <<endl;
    cout<< "Disponibilidad: "<< reg.getDisponibilidad() <<endl;
    cout << "Estado: " << (reg.getEstado()?"Si":"No") << endl;
}

void ManagerElectrodomesticos::Ordenar(Electrodomesticos *vec, int cantidadRegistros)
{
    int i, j, posmin;
    Electrodomesticos aux;
    for ( i = 0; i < cantidadRegistros-1; i++)
    {
        posmin=i;
        for ( j = i+1; j < cantidadRegistros ; j++)
        {
            if(vec[j].getCodigo()<vec[posmin].getCodigo())
            {
                posmin=j;
            }
        }
        if(i!=posmin)
        {
            aux = vec[i];
            vec[i]=vec[posmin];
            vec[posmin]= aux;
        }
    }
}

bool ManagerElectrodomesticos::ListarRegistros(bool mostrarActivos)
{
    int cantRegistros = _archivo.contarRegistros();

    if (cantRegistros == 0)
    {
        cout << "POR EL MOMENTO NO HAY REGISTROS DE ELECTRODOMESTICOS CARGADOS" << endl;
        return false;
    }
    Electrodomesticos *vec = new Electrodomesticos[cantRegistros];
    if (vec == NULL)
    {
        cout << "ERROR AL SOLICITAR MEMORIA" << endl;
        return false;
    }
    // Leer los registros del archivo y almacenarlos en el vector
    for (int x = 0; x < cantRegistros; x++)
    {
        vec[x] = _archivo.leerRegistro(x);
    }
    // Ordenar el vector dinamico
    Ordenar(vec, cantRegistros);
// Mostrar los registros según la condicion
    for(int x=0; x<cantRegistros; x++)
    {
        if (mostrarActivos && vec[x].getEstado())
        {
            Mostrar(vec[x]);
            cout<<"**********************"<<endl;
        }

        else if (!mostrarActivos && !vec[x].getEstado())
        {
            Mostrar(vec[x]);
            cout<<"**********************"<<endl;
        }
    }
    delete [] vec;
    return true;
}

bool  ManagerElectrodomesticos::mostrarRegistrosDisponiblesyEliminados()
{
    int y = 0;
    do
    {
        rlutil::setBackgroundColor(rlutil::BLACK);
        rlutil::setColor(rlutil::WHITE);
        rlutil::hidecursor();

        rlutil::locate(68, 10);
        cout << "QUE DESEA HACER?" << endl;
        rlutil::locate(68, 11);
        cout << "**********************" << endl;
        showItem("1. MOSTRAR PRODUCTOS", 68, 12, y == 0);
        showItem("2. MOSTRAR PRODUCTOS ELIMINADOS", 68, 13, y == 1);
        showItem("0. VOLVER AL MENU ANTERIOR", 68, 14, y == 2);
        rlutil::locate(68, 15);
        cout << "**********************" << endl;

        switch (rlutil::getkey())
        {
        case 14: // up
            rlutil::locate(68, 12 + y);
            cout << "  " << endl;
            y--;
            if (y < 0)
            {
                y = 0;
            }
            break;
        case 15: // down
            rlutil::locate(68, 12 + y);
            cout << "  " << endl;
            y++;
            if (y > 2)
            {
                y = 2;
            }
            break;
        case 1: // enter
            switch (y)
            {
            case 0:
                rlutil::cls();
                if (!ListarRegistros(true))
                {
                    cout <<"ERROR AL LEER EL ARCHIVO" << endl;
                }
                cout<<"Aprete ENTER para volver atras"<<endl;
                cin.get();
                rlutil::cls();
                break;
            case 1:
                rlutil::cls();
                if (!ListarRegistros(false))
                {
                    cout <<"ERROR AL LEER EL ARCHIVO" << endl;
                }
                cout<<"Aprete ENTER para volver atras"<<endl;
                cin.get();
                rlutil::cls();
                break;
            case 2:
                rlutil::cls();
                return false;
                cin.get();
                rlutil::cls();
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

bool  ManagerElectrodomesticos::bajaElectrodomestico()
{
    int _codigoElectrodomestico;
    cout<<"INGRESAR EL CODIGO DEL ELECTRODOMESTICO QUE QUIERE DAR DE BAJA ";
    cin>>_codigoElectrodomestico;
    cin.ignore();
    int cantReg=_archivo.contarRegistros();
    for (int x=0; x<cantReg; x++)
    {
        Electrodomesticos  regElectrodomesticos=_archivo.leerRegistro(x);
        if(regElectrodomesticos.getCodigo()==_codigoElectrodomestico)
        {
            cout << "ESTE ES EL REGISTRO " << endl;
            Mostrar(regElectrodomesticos);
            char opc;
            cout << "ESTA SEGURO QUE DESEA DAR DE BAJA EL PRODUCTO? (S/N) ";
            cin >> opc;
            cin.ignore();
            if (opc == 's' || opc == 'S')
            {
                regElectrodomesticos.setEstado(false);
                if(_archivo.remplazarReg(regElectrodomesticos,x))
                {
                    cout<<"REGISTRO DADO DE BAJA" <<endl;
                    return true;
                }
                else
                {
                    cout<< "ERROR AL DAR DE BAJA EL REGISTRO"<<endl;
                    return false;
                }
            }
            else
            {
                cout<< "BAJA CANCELADA POR EL USUARIO"<<endl;
                return false;
            }
        }
    }
    cout<< "CODIGO NO ENCONTRADO"<<endl;
    return false;
}

bool ManagerElectrodomesticos::buscarElectrodomesticoxCodigo()
{
    int cantReg = _archivo.contarRegistros();
    if (cantReg == 0)
    {
        cout << "NO HAY PRODUCTOS CARGADOS" << endl;
        return false;
    }
    int _codigoElectrodomestico,pos;
    cout<<"INGRESAR EL CODIGO DEL ELECTRODOMESTICO QUE DESEA VER ";
    cin>>_codigoElectrodomestico;
    cin.ignore();
    if (_codigoElectrodomestico <= 0)
    {
        cout << "CODIGO INVALIDO" << endl;
        return false;
    }
    pos=_archivo.buscarCodigoElectrodomestico(_codigoElectrodomestico);
    if(pos==-1)
    {
        cout<<"NO EXISTE EL CODIGO INGRESADO "<<endl;
        return false;
    }
    Electrodomesticos regElectrodomesticos=_archivo.leerRegistro(pos);
    if (!regElectrodomesticos.getEstado())
    {
        cout << "EL PRODUCTO CON ESE CODIGO NO SE ENCUENTRA DISPONIBLE" << endl;
        return false;
    }
    cout<< "ESTE ES EL REGISTRO "<<endl;
    Mostrar(regElectrodomesticos);
    return true;
}

bool ManagerElectrodomesticos::modificarStock()
{
    int cantReg = _archivo.contarRegistros();

    if (cantReg == 0)
    {
        cout << "NO HAY PRODUCTOS CARGADOS" << endl;
        return false;
    }
    int _codigoElectrodomestico,pos;
    cout<<"INGRESAR EL CODIGO DEL ELECTRODOMESTICOS, AL QUE DESEA MODIFICAR EL STOCK ";
    cin>>_codigoElectrodomestico;
    cin.ignore();
    pos=_archivo.buscarCodigoElectrodomestico(_codigoElectrodomestico);
    if(pos==-1)
    {
        cout<<"NO EXISTE EL CODIGO INGRESADO "<<endl;
        return false;
    }
    Electrodomesticos regElectrodomesticos=_archivo.leerRegistro(pos);
    if (!regElectrodomesticos.getEstado())
    {
        cout << "NO SE PUEDE MODIFICAR EL STOCK PORQUE EL PRODUCTO ESTA ELIMINADO" << endl;
        return false;
    }
    cout<< "ESTE ES EL REGISTRO "<<endl;
    Mostrar(regElectrodomesticos);
    int _stockNuevo;
    cout<<"INGRESE EL STOCK DEL PRODUCTO PARA REEMPLAZAR: "<<endl;
    cin>>_stockNuevo;
    cin.ignore();
    cout<<endl;
    char opc;
    cout<<"ESTA SEGURO QUE DESEA REEMPLAZAR EL STOCK DEL PRODUCTO? (S/N) ";
    cin>>opc;
    cin.ignore();
    if(opc=='s'|| opc=='S')
    {
        regElectrodomesticos.setStock(_stockNuevo);
        if(_archivo.remplazarReg(regElectrodomesticos, pos))
        {
            cout<< "SE MODIFICO CORRECTAMENTE EL STOCK"<<endl;
            Mostrar(regElectrodomesticos);
            return true;
        }
        else
        {
            cout<< "ERROR AL MODIFICAR EL STOCK"<<endl;
            return false;
        }
    }
    else
    {
        cout << "MODIFICACION CANCELADA POR EL USUARIO" << endl;
        return false;
    }
}

void ManagerElectrodomesticos::filtrarPorDisponibilidad()
{
    int _opcion;
    bool mostrarAgotados;
    int y = 0;
    do
    {
        rlutil::setBackgroundColor(rlutil::BLACK);
        rlutil::setColor(rlutil::WHITE);
        rlutil::hidecursor();

        rlutil::locate(68, 10);
        cout << "QUE DESEA HACER?" << endl;
        rlutil::locate(68, 11);
        cout << "**********************" << endl;
        showItem("1. MOSTRAR ELECTRODOMESTICOS DISPONIBLES", 68, 12, y == 0);
        showItem("2. MOSTRAR ELECTRODOMESTICOS AGOTADOS", 68, 13, y == 1);
        showItem("0. VOLVER AL MENU ANTERIOR", 68, 14, y == 2);
        rlutil::locate(68, 15);
        cout << "**********************" << endl;

        switch (rlutil::getkey())
        {
        case 14: // up
            rlutil::locate(68, 12 + y);
            cout << "  " << endl;
            y--;
            if (y < 0)
            {
                y = 0;
            }
            break;
        case 15: // down
            rlutil::locate(68, 12 + y);
            cout << "  " << endl;
            y++;
            if (y > 2)
            {
                y = 2;
            }
            break;
        case 1: // enter
            switch (y)
            {
            case 0:
                rlutil::cls();
                mostrarAgotados = false;
                _archivo.mostrarPorDisponibilidad(mostrarAgotados);
                cout<<"Aprete ENTER para volver atras"<<endl;
                cin.get();
                rlutil::cls();
                break;
            case 1:
                rlutil::cls();
                mostrarAgotados = true;
                _archivo.mostrarPorDisponibilidad(mostrarAgotados);
                cout<<"Aprete ENTER para volver atras"<<endl;
                cin.get();
                rlutil::cls();
                break;
            case 2:
                rlutil::cls();
                return; // Volver al menú anterior
                cin.get();
                rlutil::cls();
            default:
                cout << "OPCION INCORRECTA. VUELVA A INGRESAR" << endl;
                break;
            }
            break;
        default:
            break;
        }
    }
    while (true);
}

int ManagerElectrodomesticos::obteneryValidarCodigoElectrodomestico()
{
    int _codigoElectrodomestico;
    bool codigoValido = false;

    while (!codigoValido)
    {
        cout << "Codigo de Electrodomestico: " << endl;
        cin >> _codigoElectrodomestico;

        int posElectrodomesticos = _archivo.buscarCodigoElectrodomestico(_codigoElectrodomestico);
        if (posElectrodomesticos != -1)
        {
            Electrodomesticos regElectrodomesticos = _archivo.leerRegistro(posElectrodomesticos);
            cout << "SU PRODUCTO ES: " << endl;
            cout << "**********************" << endl;
            Mostrar(regElectrodomesticos);
            cout << "**********************" << endl;
            codigoValido = true;
        }
        else
        {
            cout << "EL CODIGO NO COINCIDE CON NINGUN PRODUCTO, VUELVA A INGRESAR NUEVAMENTE EL CODIGO DEL PRODUCTO" << endl;
        }
    }
    return _codigoElectrodomestico;
}

bool ManagerElectrodomesticos::reactivarCodigo()
{
    int y = 0;
    do
    {
        rlutil::setBackgroundColor(rlutil::BLACK);
        rlutil::setColor(rlutil::WHITE);
        rlutil::hidecursor();

        rlutil::locate(68, 10);
        cout << "QUE DESEA HACER?" << endl;
        rlutil::locate(68, 11);
        cout << "**********************" << endl;
        showItem("1. INGRESAR CODIGO", 68, 12, y == 0);
        showItem("2. VER REGISTROS ELIMINADOS", 68, 13, y == 1);
        showItem("0. VOLVER AL MENÚ ANTERIOR", 68, 14, y == 2);
        rlutil::locate(68, 15);
        cout << "**********************" << endl;

        switch (rlutil::getkey())
        {
        case 14: // up
            rlutil::locate(68, 12 + y);
            cout << "  " << endl;
            y--;
            if (y < 0)
            {
                y = 0;
            }
            break;
        case 15: // down
            rlutil::locate(68, 12 + y);
            cout << "  " << endl;
            y++;
            if (y > 2)
            {
                y = 2;
            }
            break;
        case 1: // enter
            switch (y)
            {
            case 0:
                rlutil::cls();
                reactivarElectrodomesticoPorCodigo();
                cout << "Aprete ENTER para volver atras" << endl;
                cin.get();
                rlutil::cls();
                break;
            case 1:
                rlutil::cls();
                if (!ListarRegistros(false))
                {
                    cout << "ERROR AL LEER EL ARCHIVO" << endl;
                    cout << "Aprete ENTER para volver atras" << endl;
                    cin.get();
                    rlutil::cls();
                }
                reactivarElectrodomesticoPorCodigo();
                cout << "Aprete ENTER para volver atras" << endl;
                cin.get();
                rlutil::cls();
                break;
            case 2:
                rlutil::cls();
                return false;
                cin.get();
                rlutil::cls();
            default:
                cout << "OPCION INCORRECTA. VUELVA A INGRESAR" << endl;
                break;
            }
            break;
        default:
            break;
        }
    }
    while (true);
}

bool ManagerElectrodomesticos::reactivarElectrodomesticoPorCodigo()
{
    int cantRegistros = _archivo.contarRegistros();
    if (cantRegistros == 0)
    {
        cout << "POR EL MOMENTO NO HAY REGISTROS DE ELECTRODOMESTICOS" << endl;
        return false;
    }
    int _codigoElectrodomestico;
    cout << "INGRESAR EL CODIGO DEL PRODUTO QUE QUIERE REACTIVAR: ";
    cin >> _codigoElectrodomestico;
    int pos= _archivo.buscarCodigoElectrodomestico(_codigoElectrodomestico);
// Leer el registro del archivo
    Electrodomesticos regElectrodomesticos = _archivo.leerRegistro(pos);
    if (pos != -1)
    {
        if (regElectrodomesticos.getEstado()) // Verificar si ya está activo
        {
            cout << "EL PRODUCTO YA ESTA ACTIVO" << endl;
            return false;
        }
        cout << "ESTE ES EL REGISTRO " << endl;
        Mostrar(regElectrodomesticos);
        char opc;
        cout << "ESTA SEGURO QUE DESEA REACTIVAR EL CODIGO INGRESADO? (S/N) ";
        cin >> opc;
        if (opc == 's' || opc == 'S')
        {
            regElectrodomesticos.setEstado(true);
            // Reemplazar el registro en el archivo
            if (_archivo.remplazarReg(regElectrodomesticos, pos))
            {
                cout << "REGISTRO REACTIVADO" << endl;
                return true;
            }
            else
            {
                cout << "ERROR AL REACTIVAR EL REGISTRO" << endl;
                return false;
            }
        }
        else
        {
            cout << "REACTIVACION CANCELADA POR EL USUARIO" << endl;
            return false;
        }
    }
    cout << "ELECTRODOMESTICO NO ENCONTRADO" << endl;
    return false;
}
