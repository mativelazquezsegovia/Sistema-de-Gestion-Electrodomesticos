#include "ArchivoElectrodomesticos.h"
#include "ManagerElectrodomesticos.h"
#include <cstdio>
#include <iostream>
using namespace std;

ArchivoElectrodomesticos::ArchivoElectrodomesticos(string nombreArchivo)
{
    _nombreArchivo=nombreArchivo;
}

bool ArchivoElectrodomesticos::agregaRegistros(Electrodomesticos reg)
{
    FILE* p;
    p=fopen(_nombreArchivo.c_str(),"ab");
    if(p==NULL)
    {
        return false;
    }
    int escribio= fwrite(&reg,sizeof (Electrodomesticos),1,p);
    fclose(p);
    return escribio;
}

Electrodomesticos ArchivoElectrodomesticos::leerRegistro(int pos)
{
    Electrodomesticos reg;
    FILE *p;
    p=fopen(_nombreArchivo.c_str(), "rb");
    if(p==NULL)
    {
        return reg;
    }
    fseek(p, sizeof reg*pos,0);
    fread(&reg, sizeof reg,1, p);
    fclose(p);
    return reg;
}

int ArchivoElectrodomesticos::contarRegistros()
{
    FILE *p;
    p=fopen(_nombreArchivo.c_str(),"rb");
    if(p==NULL)
    {
        return -1;
    }
    fseek(p, 0,2);
    int tam=ftell(p);
    fclose(p);
    return tam/sizeof(Electrodomesticos);
}

int ArchivoElectrodomesticos::buscarCodigoElectrodomestico(int _codigoElectrodomestico)
{
    Electrodomesticos reg;
    int pos=0;
    FILE *p;
    p=fopen(_nombreArchivo.c_str(), "rb");
    if(p==NULL)
    {
        return -1;
    }
    while(fread(&reg,sizeof reg,1,p)==1)
    {
        if(_codigoElectrodomestico==reg.getCodigo())
        {
            fclose(p);
            return pos;
        }
        pos++;
    }
    fclose(p);
    return -1;
}

bool ArchivoElectrodomesticos::verificarEstadoConStock(int _codigoElectrodomestico)
{
    Electrodomesticos reg;
    FILE *p = fopen(_nombreArchivo.c_str(), "rb");
    if (p == NULL)
    {
        cout << "ERROR AL ABRIR EL ARCHIVO" << endl;
        return false;
    }
    while (fread(&reg, sizeof(reg), 1, p) == 1)
    {
        if (reg.getCodigo() == _codigoElectrodomestico && reg.getEstado() && reg.getStock() > 0)
        {
            fclose(p);
            return true;
        }
    }
    fclose(p);
    return false; // Si no se encontro devolvemos false
}

bool ArchivoElectrodomesticos::validarCodigoRepetido(int _codigoElectrodomestico)
{
    Electrodomesticos reg;
    FILE *p;
    p=fopen(_nombreArchivo.c_str(),"rb");
    if(p==NULL)
    {
        return false;
    }
    bool _codigoRepetido = false;
    while(fread(&reg,sizeof reg,1,p)==1)
    {
        if(_codigoElectrodomestico==reg.getCodigo())
        {
            _codigoRepetido = true; // codigo encontrado, ya esta registrado
            break;
        }
    }
    fclose(p);
    return _codigoRepetido;
}

bool ArchivoElectrodomesticos::remplazarReg(Electrodomesticos reg, int posicionAReemplazar)
{
    FILE *p = fopen(_nombreArchivo.c_str(), "rb+");
    if (p == NULL)
    {
        return false;
    }
    fseek(p, posicionAReemplazar * sizeof(Electrodomesticos), SEEK_SET);// nos posiiconamos en el registro que queremos reemplzar
    bool pudoEscribir = fwrite(&reg, sizeof(Electrodomesticos), 1, p);
    fclose(p);
    return pudoEscribir;
}
//Funcion para obtener el precio del producto la usamos en ventas
float ArchivoElectrodomesticos::obtenerPrecioUnitario(int _codigoElectrodomestico)
{
    Electrodomesticos reg;
    FILE *p = fopen(_nombreArchivo.c_str(), "rb");
    if (p == NULL)
    {
        return -1;
    }
    int pos = buscarCodigoElectrodomestico(_codigoElectrodomestico);
    if (pos != -1)
    {
        fseek(p, pos * sizeof(Electrodomesticos), SEEK_SET);
        fread(&reg, sizeof(Electrodomesticos), 1, p);
        fclose(p);
        float _precioUnitario = reg.getPrecioUnitario();
        if (_precioUnitario > 0)
        {
            return _precioUnitario; // Devolver el precio si es valido
        }
        else
        {
            cout << "Precio no valido para el electrodomestico" << endl;
            return -1;
        }
    }
    else
    {
        cout << "Electrodomestico no encontrado" << endl;
        fclose(p);
        return -1;
    }
}

void ArchivoElectrodomesticos::mostrarPorDisponibilidad(bool mostrarAgotados)
{
    Electrodomesticos reg;
    FILE *p = fopen(_nombreArchivo.c_str(), "rb");
    if (p == NULL)
    {
        cout << "ERROR AL ABRIR EL ARCHIVO" << endl;
        return;
    }
    bool hayElectrodomesticos = false;
    while (fread(&reg, sizeof(reg), 1, p) == 1)
    {
        if ((mostrarAgotados&& reg.getStock() == 0 && reg.getEstado()) || (!mostrarAgotados && reg.getStock() > 0 && reg.getEstado()))
        {
            // Imprime la informacion directamente
            cout <<"Codigo: "<< reg.getCodigo() <<  " | Nombre: " << reg.getNombre() << " | Precio: " << reg.getPrecioUnitario() << " | Stock: " << reg.getStock() << endl;
            hayElectrodomesticos = true;
        }
    }
    fclose(p);
    if (!hayElectrodomesticos)
    {
        cout << "NO HAY ELECTRODOMESTICOS CARGADOS" << endl;
    }
}

bool ArchivoElectrodomesticos::hacerBackUpElectrodomesticos()
{
    // Crear un objeto para almacenar los registros durante la copia
    Electrodomesticos reg;
    // Abrir el archivo en modo lectura ("rb")
    FILE* p = fopen(_nombreArchivo.c_str(), "rb");
    if (p == NULL)
    {
        cout<<"ERROR AL ABRIR EL ARCHIVO"<<endl;
        return false;
    }
    // Crear un archivo de respaldo llamado "...Backup.dat" en modo escritura ("wb")
    FILE* b = fopen("ElectrodomesticosBackup.dat", "wb");
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

bool  ArchivoElectrodomesticos::restaurarBackUpElectrodomesticos()
{
    Electrodomesticos reg;
    FILE *p, *b;
    p = fopen("ElectrodomesticosBackup.dat", "rb");
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

bool ArchivoElectrodomesticos::actualizarStock(int _codigoElectrodomestico, int _cantidadVendida)
{
    int posElectrodomestico = buscarCodigoElectrodomestico(_codigoElectrodomestico);
    if (posElectrodomestico != -1)
    {
        Electrodomesticos regElectrodomestico = leerRegistro(posElectrodomestico);
        // Verificamos si hay stock para realizar la venta
        if (regElectrodomestico.getStock() >= _cantidadVendida)
        {
            // Actualizar el stock restando la cantidad vendida
            regElectrodomestico.setStock(regElectrodomestico.getStock() - _cantidadVendida);
           // Reemplazar el registro actualizado en el archivo
            return remplazarReg(regElectrodomestico, posElectrodomestico);
        }
        else
        {
            cout << "EL STOCK NO CUBRE LA VENTA A REALIZAR" << endl;
            return false;
        }
    }
    else
    {
        return false;// Si no se encontro en el archivo
    }
}

bool ArchivoElectrodomesticos::aumentarStock(int _codigoElectrodomestico, int _cantidadDevuelta)
{
    int posElectrodomestico = buscarCodigoElectrodomestico(_codigoElectrodomestico);
    if (posElectrodomestico != -1)
    {
        Electrodomesticos regElectrodomestico = leerRegistro(posElectrodomestico);
        // Aumentar el stock sumando la cantidad devuelta
        regElectrodomestico.setStock(regElectrodomestico.getStock() + _cantidadDevuelta);
// Reemplazar el registro actualizado en el archivo
        if(remplazarReg(regElectrodomestico, posElectrodomestico))
        {
            return true; //Stock actualizado
        }
        else
        {
            cout << "ERROR AL ACTUALIZAR EL STOCK EN EL ARCHIVO" << endl;
            return false; //Error al reemplazar el registro en el archivo
        }
    }
    else
    {
        return false;// Nose encontro en el archivo
    }
}

void ArchivoElectrodomesticos::leer(Electrodomesticos *vec, int cantidadRegistrosALeer)
{
    FILE *p;
    p=fopen(_nombreArchivo.c_str(),"rb");
    if(p==NULL)
    {
        cout<<"NO SE PUDO LEER EL ARCHIVO"<<endl;
        return;
    }
    // Leer los registros desde el archivo y almacenarlos
    fread(vec, sizeof(Electrodomesticos), cantidadRegistrosALeer, p);
    fclose(p);
}
