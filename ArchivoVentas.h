#pragma once
#include "Ventas.h"
#include <string>

class ArchivoVentas
{
private:
    std::string _nombreArchivo;
public:
    ArchivoVentas (std::string nombreArchivo);
   bool  agregaRegistros(Ventas reg);
    int contarRegistros();
    Ventas leerRegistro(int pos);
    bool hacerBackUpVentas();
    bool  restaurarBackUpVentas();
    bool remplazarReg(Ventas reg, int posicionAReemplazar);
    void mostrarHistorialCompras(int _dniCliente);
   float  calcularDeudaCliente(int _dniCliente);
   bool validarNumeroVentaRepetido(int _numVenta);
   int buscarNroVenta(int _nroVenta);
   bool verificarDeuda(int _dniCliente);
};
