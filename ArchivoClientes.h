#pragma once
#include "Clientes.h"
#include <string>

class ArchivoClientes
{
private:
    std::string _nombreArchivo;
public:
    ArchivoClientes (std::string nombreArchivo);
    bool agregaRegistros( Clientes reg);
    Clientes leerRegistro(int pos);
    int contarRegistros();
    int buscarCliente(int _dniCliente);
    bool  validarDniRepetido(int _dniCliente);
    bool remplazarReg(Clientes reg, int posicionAReemplazar);
    bool hacerBackUpClientes();
    bool  restaurarBackUpClientes();
    void leer(Clientes *vec, int cantidadRegistrosALeer);
};
