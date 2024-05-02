#include "ArchivoClientes.h"
#include <cstdio>
#include <iostream>
using namespace std;

ArchivoClientes::ArchivoClientes(string nombreArchivo)
{
    _nombreArchivo=nombreArchivo;
}

bool ArchivoClientes::agregaRegistros( Clientes reg)
{
    FILE* p; // abro el archivo en modo AB
    p=fopen(_nombreArchivo.c_str(),"ab");
    if(p==NULL)
    {
        return false;// Si no se pudo abrir el archivo, se retorna false
    }
    int escribio= fwrite(&reg,sizeof (Clientes),1,p);// aca devuelvo la cantidad de elementos escritos correctamente.
    fclose(p); // cierro el archivo
    return escribio; // retorno la cantidad de elementos escritos, 1 si es correcto
}

Clientes ArchivoClientes::leerRegistro(int pos)
{
    Clientes reg; // creo un objeto clientes para almacenar
    FILE *p;
    p=fopen(_nombreArchivo.c_str(), "rb"); //abro el archivo en modo lectura
    if(p==NULL)
    {
        return reg; // sino lo abro retorno un objeto vacio
    }
    fseek(p, sizeof reg*pos,0); //me dezplazo al inicio archivo
    fread(&reg, sizeof reg,1, p); //leo la informacion del archivo
    fclose(p); //cierro
    return reg; //retorno el objeto con la informacion leido
}

int ArchivoClientes::contarRegistros()
{
    FILE *p;
    p=fopen(_nombreArchivo.c_str(),"rb");//abro el archivo en modo lectura
    if(p==NULL)
    {
        return -1;//si no lo abro retorno -1 como error
    }
    fseek(p, 0,2);// me desplazo al final del archivo
    int tam=ftell(p);//obtengo el tamaño en bytes
    fclose(p);
    return tam/sizeof(Clientes);//divido el tamaño total y retorno la cantidad de registros
}

int ArchivoClientes::buscarCliente(int _dniCliente)
{
    Clientes reg; // creo un objeto
    int pos=0;//con pos represento la posicion del cliente
    FILE *p;//creo el puntero
    p=fopen(_nombreArchivo.c_str(), "rb");//abro el archivo en modo lectura
    if(p==NULL)
    {
        return -1; // sino lo abro devuelvo -1 como error
    }
    while(fread(&reg,sizeof reg,1,p)==1)//leo cada registro del archivo
    {
        if(_dniCliente==reg.getDni())//comparo el dni que busco con los del archivo
        {
            fclose(p);
            return pos;//si lo encuentro retorno la posicion y cierro el archivo
        }
        pos++;//aumento el contador hasta encontralo
    }
    fclose(p);
    return -1; //sino lo encuentro cierro el archivo y retorno -1
}

bool ArchivoClientes::validarDniRepetido(int _dniCliente)
{
    Clientes reg;
    FILE *p;
    p=fopen(_nombreArchivo.c_str(),"rb");
    if(p==NULL)
    {
        return false;
    }
    bool _dniRepetido = false;//declaro este booleano para indicar si lo encontre
    while(fread(&reg,sizeof reg,1,p)==1)//leo los registros
    {
        if(_dniCliente==reg.getDni())//comparo el dni recibido como parametro
        {
            _dniRepetido = true; // DNI encontrado, ya está registrado
            break;
        }
    }
    fclose(p);
    return _dniRepetido;//retorno si esta repetido o no
}

bool ArchivoClientes::remplazarReg(Clientes reg, int posicionAReemplazar)
{
    FILE *p = fopen(_nombreArchivo.c_str(), "rb+");//abro el archivo en modo lectura y escritura
    if (p == NULL)
    {
        return false;
    }
    fseek(p, posicionAReemplazar * sizeof(Clientes), SEEK_SET);// muevo el puntero de posición en el archivo al inicio del registro que se va a reemplazar.
    bool pudoEscribir = fwrite(&reg, sizeof(Clientes), 1, p);// intento escribir el nuevo registro en la posición especificada.
    fclose(p);
    return pudoEscribir;//retorno si pude escribir
}

bool ArchivoClientes::hacerBackUpClientes()
{
// Crear un objeto Clientes para almacenar los registros durante la copia
    Clientes reg;
    // Abrir el archivo en modo lectura
    FILE* p = fopen(_nombreArchivo.c_str(), "rb");
    if (p == NULL)
    {
        return false;
    }
    // Crear un archivo de respaldo llamado "ClientesBackup.dat" en modo escritura ("wb")
    FILE* b = fopen("ClientesBackup.dat", "wb");
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

bool  ArchivoClientes::restaurarBackUpClientes()
{
    Clientes reg;
    FILE *p, *b;
    p = fopen("ClientesBackup.dat", "rb");
    if (p == NULL)
    {
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

void ArchivoClientes::leer(Clientes *vec, int cantidadRegistrosALeer)
{
    FILE *p;
    p=fopen(_nombreArchivo.c_str(),"rb");
    if(p==NULL)
    {
        cout<<"NO SE PUDO LEER EL ARCHIVO"<<endl;
        return;
    }
    fread(vec, sizeof(Clientes), cantidadRegistrosALeer, p);//leo registros del archivo y los almaceno en el vector dinamico
    fclose(p);
}

