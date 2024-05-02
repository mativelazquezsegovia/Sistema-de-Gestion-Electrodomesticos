#include "ArchivoVentas.h"
#include "ManagerVentas.h"
#include <cstdio>
#include <iostream>
using namespace std;

ArchivoVentas::ArchivoVentas(string nombreArchivo)
{
    _nombreArchivo=nombreArchivo;
}

bool ArchivoVentas::agregaRegistros(Ventas reg)
{
    FILE* p;
    p=fopen(_nombreArchivo.c_str(),"ab");
    if(p==NULL)
    {
        return false;
    }
    bool escribio=fwrite(&reg, sizeof (Ventas),1, p) ==1;
    fclose(p);
    return escribio;
}

int ArchivoVentas::contarRegistros()
{
    FILE *p;
    p=fopen(_nombreArchivo.c_str(),"rb");
    if(p==NULL)
    {
        return 0;
    }
    fseek(p, 0,2);
    int tam=ftell(p);
    fclose(p);
    return tam/sizeof(Ventas);
}

Ventas ArchivoVentas::leerRegistro(int pos)
{
    Ventas reg;
    FILE *p;
    p=fopen(_nombreArchivo.c_str(), "rb");
    if(p==NULL)
    {
        return reg;
    }
    fseek(p,sizeof reg*pos,0);
    fread(&reg,sizeof reg,1,p);
    fclose(p);
    return reg;
}

bool ArchivoVentas::remplazarReg(Ventas reg, int posicionAReemplazar)
{
    FILE *p = fopen(_nombreArchivo.c_str(), "rb+");
    if (p == NULL)
    {
        cout << "ERROR AL ABRIR EL ARCHIVO PARA MODIFICAR";
        return false;
    }
    fseek(p, posicionAReemplazar * sizeof(Ventas), SEEK_SET);
    bool pudoEscribir = fwrite(&reg, sizeof(Ventas), 1, p);
    fclose(p);
    if (!pudoEscribir)
    {
        cout << "ERROR AL ESCRIBIR EL NUEVO REGISTRO EN EL ARCHIVO" << endl;
    }
    return pudoEscribir;
}

bool ArchivoVentas::hacerBackUpVentas()
{
    // Crear un objeto Venta para almacenar los registros durante la copia
    Ventas reg;
    // Abrir el archivo en modo lectura ("rb")
    FILE* p = fopen(_nombreArchivo.c_str(), "rb");
    if (p == NULL)
    {
        cout<<"ERROR AL ABRIR EL ARCHIVO"<<endl;
        return false;
    }
    // Crear un archivo de respaldo llamado "VentasBackup.dat" en modo escritura ("wb")
    FILE* b = fopen("VentasBackup.dat", "wb");
    if (b == NULL)
    {
        cout<<"ERROR AL ABRIR EL ARCHIVO DE RESPALDO"<<endl;
        fclose(p);
        return false;
    }
    // Leer registros del archivo  y escribirlos en el archivo de respaldo
    while (fread(&reg, sizeof(reg), 1, p) == 1)
    {
        fwrite(&reg, sizeof(reg), 1, b);
    }
    // Cerramos los archivos
    fclose(p);
    fclose(b);
    // La copia salio bien
    return true;
}

bool  ArchivoVentas::restaurarBackUpVentas()
{
    Ventas reg;
    FILE *p, *b;
    p = fopen("VentasBackup.dat", "rb");
    if (p == NULL)
    {
        cout << "ERROR AL ABRIR ARCHIVO DE BACKUP" << endl;
        return false;
    }
    b = fopen(_nombreArchivo.c_str(), "wb");
    if (b == NULL)
    {
        cout << "ERROR AL ABRIR ARCHIVO PARA RESTAURAR" << endl;
        fclose(p);
        return false;
    }
    while (fread(&reg, sizeof(reg), 1, p) == 1)
    {
        fwrite(&reg, sizeof(reg), 1, b);
    }
    fclose(p);
    fclose(b);
    return true;
}

//Historial de compras de un cliente dado su DNI
void ArchivoVentas::mostrarHistorialCompras(int _dniCliente)
{
    Ventas regVenta;
    ManagerVentas reg;
    bool _tieneCompras = false;
    cout << "HISTORIAL DE COMPRAS: " << endl;
    FILE *p = fopen(_nombreArchivo.c_str(), "rb");
    if (p == NULL)
    {
        cout << "ERROR AL ABRIR EL ARCHIVO DE VENTAS" << endl;
        return;
    }
    while (fread(&regVenta, sizeof(regVenta), 1, p) == 1)// leemos los registros desde el archivo
    {
        if (regVenta.getDniCliente() == _dniCliente)
        {
            reg.Mostrar(regVenta);
            _tieneCompras = true;
            cout << "------------------------" << endl;
        }
    }
    fclose(p);
    if (!_tieneCompras)
    {
        cout << "EL CLIENE NO TIENE COMPRAS REGISTRADAS" << endl;
    }
}

float ArchivoVentas::calcularDeudaCliente(int _dniCliente)
{
    float _deudaTotal = 0;
    Ventas regVenta;
    FILE *p = fopen(_nombreArchivo.c_str(), "rb");
    if (p == NULL)
    {
        cout << "ERROR AL ABRIR EL ARCHIVO " << endl;
        return _deudaTotal;
    }
    while (fread(&regVenta, sizeof(regVenta), 1, p) == 1)
    {
        if (regVenta.getDniCliente() == _dniCliente  && regVenta.getTotal() > regVenta.getImporteAbonado())
        {
            _deudaTotal+= (regVenta.getTotal() - regVenta.getImporteAbonado());
        }
    }
    fclose(p);
    return _deudaTotal;
}

bool ArchivoVentas::validarNumeroVentaRepetido(int _numVenta)
{
    Ventas regVenta;
    FILE *p;
    p = fopen(_nombreArchivo.c_str(), "rb");
    if (p == NULL)
    {
        return false;
    }
    bool numeroVentaRepetido = false;
    while (fread(&regVenta, sizeof regVenta, 1, p) == 1)
    {
        if (_numVenta == regVenta.getNroVenta())
        {
            numeroVentaRepetido = true; // Numero de venta encontrado, ya esta registrado
            break;
        }
    }
    fclose(p);
    return numeroVentaRepetido;
}

int ArchivoVentas::buscarNroVenta(int _nroVenta)
{
    Ventas regVenta;
    int pos = 0;
    FILE *p;
    p = fopen(_nombreArchivo.c_str(), "rb");
    if (p == NULL)
    {
        return -1;
    }
    while (fread(&regVenta, sizeof regVenta, 1, p) == 1)
    {
        if (_nroVenta == regVenta.getNroVenta())
        {
            fclose(p);
            return pos;
        }
        pos++;
    }
    fclose(p);
    return -1;
}

bool ArchivoVentas::verificarDeuda(int _dniCliente)
{
    int cantidadRegistros = contarRegistros();

    if (cantidadRegistros == 0)
    {
        cout << "EL LCIENTE NO POSEE DEUDA" << endl;
        return false;
    }

    float deudaTotal = calcularDeudaCliente(_dniCliente);

    if (deudaTotal > 10000)
    {
        cout << "EL CLIENTE SUPERO LA DEUDA MAXIMA, NO SE PERMITEN MAS OPERACIONES" << endl;
        return true;
    }

    return false;
}
