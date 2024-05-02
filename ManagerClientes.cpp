#include "ManagerClientes.h"
#include "ArchivoVentas.h"
#include "rlutil.h"
#include "Funciones.h"
#include <iostream>
using namespace std;

ManagerClientes::ManagerClientes() : _archivoVentas("Ventas.dat"), _archivo("Clientes.dat")//Inicializo el constructor con las instancias creadas
{
}


void ManagerClientes::Cargar()
{
    string nombre;
    string apellido;
    int dni,dia,mes,anio,telefono;
    string direccion;
    string email;

    cout<< "Dni: "<<endl;
    cin>>dni;
    cin.ignore();
    if (_archivo.validarDniRepetido(dni))
    {
        cout << "EL DNI YA SE ENCUENTRA REGISTRADO EN LA BASE DE DATOS" << endl;
        return;
    }
    cout<< "Nombre: "<<endl;
    getline(cin, nombre);
    cout<< "Apellido: "<< endl;
    getline(cin, apellido);
    cout<< "Direccion: "<<endl;
    getline(cin, direccion);
    cout<< "Telefono: "<<endl;
    cin>>telefono;
    cin.ignore();
    cout<< "E-mail: "<<endl;
    getline(cin, email);
    cout<< "Fecha de Nacimiento: "<<endl;
    cin >> dia;
    cin >> mes;
    cin >> anio;
    //creo un objeto para settear la informacion ingresada
    Clientes reg;
    reg.setDni(dni);
    reg.setNombre(nombre);
    reg.setApellido(apellido);
    reg.setDireccion(direccion);
    reg.setTelefono(telefono);
    reg.setEmail(email);
    reg.setFechaNacimiento(Fecha(dia,mes,anio));
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

void ManagerClientes::Mostrar(Clientes reg)
{
    cout<< "Dni: "<< reg.getDni() <<endl;
    cout<< "Nombre: "<< reg.getNombre() <<endl;
    cout<< "Apellido: "<< reg.getApellido() <<endl;
    cout<< "Direccion: "<< reg.getDireccion() <<endl;
    cout<< "Telefono: "<< reg.getTelefono() << endl;
    cout<< "E-mail: "<< reg.getEmail() << endl;
    cout<< "Fecha de Nacimiento: "<< reg.getFechaNacimiento().toString() <<endl;
    cout << "Estado: " << (reg.getEstado()?"Si":"No") << endl << endl;
}

//Esta funcion corrobora que el cliente exista cuando cargo la venta, sino existe permite cargarlo y grabarlo en el archivo
bool ManagerClientes::corroborarCliente(int _dniCliente, Clientes &regCliente)//funcion que recibe un objeto de clientes, se usa para ventas
{
    int _existeCliente = _archivo.buscarCliente(_dniCliente);//busco el cliente en el archivo
    if (_existeCliente != -1)
    {
        // Aca consulta si existe el cliente, antes de continuar
        regCliente = _archivo.leerRegistro(_existeCliente);
        return true;
    }
    else
    {
        // Cliente no existe, mostrar mensaje y cargar nuevo cliente
        cout << "CLIENTE NO INGRESADO EN BASE DE DATOS, INGRESE NUEVO CLIENTE: " << endl;
        // Solicitar detalles del nuevo cliente
        string nombre, apellido, direccion, email;
        int telefono, dia, mes, anio;
        cout << "Nombre: ";
        getline(cin, nombre);
        cout << "Apellido: ";
        getline(cin, apellido);
        cout << "Direccion: ";
        getline(cin, direccion);
        cout << "Telefono: ";
        cin >> telefono;
        cin.ignore();
        cout << "Email: ";
        getline(cin, email);
        cout<< "Fecha de Nacimiento: "<<endl;
        cin >> dia;
        cin >> mes;
        cin >> anio;

        // Crear un nuevo cliente
        Clientes nuevoCliente;
        nuevoCliente.setDni(_dniCliente);
        nuevoCliente.setNombre(nombre);
        nuevoCliente.setApellido(apellido);
        nuevoCliente.setDireccion(direccion);
        nuevoCliente.setTelefono(telefono);
        nuevoCliente.setEmail(email);
        nuevoCliente.setFechaNacimiento(Fecha(dia, mes, anio));
        nuevoCliente.setEstado(true); // Establecer el estado según lo necesario

        // Agregar el nuevo cliente al archivo
        if (_archivo.agregaRegistros(nuevoCliente))
        {
            cout << "REGISTRO CARGADO" << endl;
            regCliente = nuevoCliente;
            return true;
        }
        else
        {
            cout<< "NO SE PUDO CARGAR EL NUEVO CLIENTE"<<endl;
        }
        return false;
    }
}

void ManagerClientes::Ordenar(Clientes *vec, int cantidadRegistros)
{
    int i, j, posmin;
    Clientes aux;
    //recorro los registros
    for ( i = 0; i < cantidadRegistros-1; i++)
    {
        posmin=i;// asigno como minimo
        for ( j = i+1; j < cantidadRegistros ; j++)
        {
            //comparo los dni y actualizo si es menor
            if(vec[j].getDni()<vec[posmin].getDni())
            {
                posmin=j;
            }
        }
        if(i!=posmin)//intercambio si el minimo no es el actual
        {
            aux = vec[i];
            vec[i]=vec[posmin];
            vec[posmin]= aux;
        }
    }
}
//Funcion para mostrar los registros de acuerdo a su estado
bool ManagerClientes::ListarRegistros(bool mostrarActivos)
{
    int cantRegistros=_archivo.contarRegistros();
    if (cantRegistros == 0)
    {
        cout << "POR EL MOMENTO NO HAY REGISTROS DE CLIENTES CARGADOS" << endl;
        return false;
    }
    Clientes *vec = new Clientes[cantRegistros];
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

//Funcion para mostrar en menu los registros de acuerdo a su estado, llama a la funcion Listar registros
bool  ManagerClientes::mostrarRegistrosClienteActivosNoActivos()
{
    int y=0;
    do
    {
        rlutil::setBackgroundColor(rlutil::BLACK);
        rlutil::setColor(rlutil::WHITE);
        rlutil::hidecursor();

        rlutil::locate(68, 10);
        cout << "QUE DESEA HACER?" << endl;
        rlutil::locate(68, 11);
        cout << "**********************" << endl;
        showItem("1. MOSTRAR CLIENTES ACTIVOS", 68, 12, y == 0);
        showItem("2. MOSTRAR HISTORICO DE CLIENTES", 68, 13, y == 1);
        showItem("0. VOLVER AL MENU ANTERIOR", 68, 14, y == 2);
        rlutil::locate(68, 15);
        cout << "**********************" << endl;

        switch (rlutil::getkey())
        {
        case 14: //up
            rlutil::locate(68, 12 + y);
            cout << "  " << endl;
            y--;
            if (y < 0)
            {
                y = 0;
            }
            break;
        case 15: //down
            rlutil::locate(68, 12 + y);
            cout << "  " << endl;
            y++;
            if (y > 2)
            {
                y = 2;
            }
            break;
        case 1: //enter
            switch (y)
            {
            case 0:
                rlutil::cls();
                //Mostrar Activos
                if(!ListarRegistros(true))
                {
                    cout <<"ERROR AL LEER EL ARCHIVO" << endl;
                }
                cout<<"Aprete ENTER para volver atras"<<endl;
                cin.get();
                rlutil::cls();
                break;
            case 1:
                rlutil::cls();
                // Mostrar eliminados)
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
                return false; //Vuelvo al menu principal
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

//Funcion para dar de baja el cliente, no recibe parametros porque se accede a traves del menu
bool  ManagerClientes::bajaCliente()
{
    int _dniCliente;
    cout<<"INGRESAR EL DNI DEL CLIENTE QUE QUIERE DAR DE BAJA ";
    cin>>_dniCliente;

    int cantRegClientes=_archivo.contarRegistros();
    if (cantRegClientes== 0)
    {
        cout << "POR EL MOMENTO NO HAY REGISTROS DE CLIENTES CARGADOS" << endl;
        return false;
    }
    int pos= _archivo.buscarCliente(_dniCliente);
    if(pos==-1)
    {
        cout<<"NO EXISTE EL CLIENTE "<<endl;
        return false;
    }
    else if (pos != -1)
    {
        // Leer el registro del archivo
        Clientes regClientes = _archivo.leerRegistro(pos);
        cout << "ESTE ES EL REGISTRO " << endl;
        Mostrar(regClientes);
        char opc;
        cout << "ESTA SEGURO QUE DESEA DAR DE BAJA AL CLIENTE? (S/N) ";
        cin >> opc;
        if (opc == 's' || opc == 'S')
        {
            regClientes.setEstado(false);
            // Reemplazar el registro en el archivo
            if (_archivo.remplazarReg(regClientes, pos))
            {
                cout << "REGISTRO DADO DE BAJA" << endl;
                return true;
            }
            else
            {
                cout << "ERROR AL DAR DE BAJA EL REGISTRO" << endl;
                return false;
            }
        }
        else
        {
            cout << "BAJA CANCELADA POR EL USUARIO" << endl;
            return false;
        }
    }
    cout << "CLIENTE NO ENCONTRADO" << endl;
    return false;
}

bool ManagerClientes::buscarClientexDni()
{
    int cantRegistros = _archivo.contarRegistros();
    if (cantRegistros == 0)
    {
        cout << "POR EL MOMENTO NO HAY REGISTROS DE CLIENTES CARGADOS" << endl;
        return false;
    }
    int _dniCliente,pos;
    cout<<"INGRESAR EL DNI DEL CLIENTE QUE DESEA VER ";
    cin>>_dniCliente;
    if (_dniCliente <= 0)
    {
        cout << "DNI INVALIDO" << endl;
        return false;
    }
    pos=_archivo.buscarCliente(_dniCliente);
    if (pos != -1)
    {
        Clientes regclientes = _archivo.leerRegistro(pos);
        cout << "ESTE ES EL REGISTRO " << endl;
        Mostrar(regclientes);
        // Calcular y mostrar la deuda del cliente
        float _deudaCliente = _archivoVentas.calcularDeudaCliente(_dniCliente);
        cout << endl;

        if (_deudaCliente > 0)
        {
            cout << "EL CLIENTE TIENE UNA DEUDA DE $:   " << _deudaCliente << endl;
        }
        else
        {
            cout << "EL CLIENTE NO TIENE DEUDA ACTUALMENTE" << endl;
        }

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
            showItem("1. VER HISTORIAL DE COMPRAS", 68, 12, y == 0);
            showItem("0. VOLVER AL MENU ANTERIOR", 68, 13, y == 1);
            rlutil::locate(68, 14);
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
                if (y > 1)
                {
                    y = 1;
                }
                break;
            case 1: // enter
                switch (y)
                {
                case 0:
                    rlutil::cls();
                    _archivoVentas.mostrarHistorialCompras(_dniCliente);
                    cout << "Aprete ENTER para volver atras" << endl;
                    cin.get();
                    rlutil::cls();
                    break;
                case 1:
                    rlutil::cls();
                    return false;
                    cin.get();
                    rlutil::cls();
                    break;
                default:
                    cout << "OPCION NO VALIDA, VUELVA A INTENTAR." << endl;
                    break;
                }
                break;
            default:
                break;
            }
        }
        while (true);
        return true;
    }
    else
    {
        cout << "NO EXISTE EL CLIENTE CON ESE DNI INGRESADO " << endl;
        return false;
    }
}

bool ManagerClientes::modificarEmail()
{
    int cantRegistros = _archivo.contarRegistros();
    if (cantRegistros == 0)
    {
        cout << "POR EL MOMENTO NO HAY REGISTROS DE CLIENTES CARGADOS" << endl;
        return false;
    }
    int _dniCliente,pos;
    cout<<"INGRESAR EL DNI DEL CLIENTE, AL QUE DESEA MODIFICAR EL E-MAIL ";
    cin>>_dniCliente;
    cin.ignore(); // Limpiar el carácter de nueva línea residual
    pos=_archivo.buscarCliente(_dniCliente);
    if(pos==-1)
    {
        cout<<"NO EXISTE EL CLIENTE "<<endl;
        return false;
    }
    Clientes regClientes=_archivo.leerRegistro(pos);
    if (!regClientes.getEstado())
    {
        cout << "NO SE PUEDE MODIFICAR EL DNI PORQUE EL REGISTRO SE ENCUENTRA ELIMINADO" << endl;
        return false;
    }
    cout<< "ESTE ES EL REGISTRO "<<endl;
    Mostrar(regClientes);
    string _emailNuevo;
    cout<<"INGRESE EL NUEVO E-MAIL PARA REEMPLAZAR: "<<endl;
    getline(cin, _emailNuevo);
    cout<<endl;
    char opc;
    cout<<"ESTA SEGURO QUE DESEA REEMPLAZAR EL E-MAIL? (S/N) ";
    cin>>opc;
    cin.ignore(); // Limpiar el carácter de nueva línea residual
    if(opc=='s'|| opc=='S')
    {
        regClientes.setEmail(_emailNuevo);
        if(_archivo.remplazarReg(regClientes, pos))
        {
            Mostrar(regClientes);
            cout<< "SE MODIFICO CORRECTAMENTE EL E-MAIL"<<endl;
            return true;
        }
        else
        {
            cout<< "ERROR AL MODIFICAR EL E-MAIL"<<endl;
            return false;
        }
    }
    else
    {
        cout << "MODIFICACION CANCELADA POR EL USUARIO" << endl;
        return false;
    }
}


bool ManagerClientes::reactivarCliente()
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
        showItem("1. INGRESAR DNI", 68, 12, y == 0);
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
                return reactivarClientePorDNI();
                cout<<"Aprete ENTER para volver atras"<<endl;
                cin.get();
                rlutil::cls();
            case 1:
                rlutil::cls();
                if (!ListarRegistros(false))
                {
                    cout << "ERROR AL LEER EL ARCHIVO" << endl;
                }
                return reactivarClientePorDNI();
                cout<<"Aprete ENTER para volver atras"<<endl;
                cin.get();
                rlutil::cls();
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
    return true;
}

bool ManagerClientes::reactivarClientePorDNI()
{
    int cantRegistros = _archivo.contarRegistros();
    if (cantRegistros == 0)
    {
        cout << "POR EL MOMENTO NO HAY REGISTROS DE CLIENTES CARGADOS" << endl;
        return false;
    }
    int _dniCliente;
    cout << "INGRESAR EL DNI DEL CLIENTE QUE QUIERE REACTIVAR: ";
    cin >> _dniCliente;
    int cantRegClientes = _archivo.contarRegistros();
    // Buscar el cliente por DNI en el archivo
    int pos = _archivo.buscarCliente(_dniCliente);
    if (pos != -1)
    {
        // Leer el registro del archivo
        Clientes regClientes = _archivo.leerRegistro(pos);
        if (regClientes.getEstado()) // Verificar si el cliente ya está activo
        {
            cout << "EL CLIENTE YA ESTA ACTIVO" << endl;
            return false;
        }
        cout << "ESTE ES EL REGISTRO " << endl;
        Mostrar(regClientes);
        char opc;
        cout << "ESTA SEGURO QUE DESEA REACTIVAR AL CLIENTE? (S/N) ";
        cin >> opc;
        if (opc == 's' || opc == 'S')
        {
            regClientes.setEstado(true);
            // Reemplazar el registro en el archivo
            if (_archivo.remplazarReg(regClientes, pos))
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
    cout << "CLIENTE NO ENCONTRADO " << endl;
    return false;
}

