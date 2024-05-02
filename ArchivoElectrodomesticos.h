#pragma once
#include "Electrodomesticos.h"
#include <string>

class ArchivoElectrodomesticos
{
private:
    std::string _nombreArchivo;
public:
    ArchivoElectrodomesticos (std::string nombreArchivo);
    bool agregaRegistros(Electrodomesticos reg);
    Electrodomesticos leerRegistro(int pos);
    int contarRegistros();
    int buscarCodigoElectrodomestico(int _codigoElectrodomestico);
    bool validarCodigoRepetido(int _codigoElectrodomestico);
    float obtenerPrecioUnitario(int _codigoElectrodomestico);
    bool remplazarReg(Electrodomesticos reg, int posicionAReemplazar);
    void mostrarPorDisponibilidad(bool mostrarAgotados);
    bool hacerBackUpElectrodomesticos();
    bool  restaurarBackUpElectrodomesticos();
    bool actualizarStock(int _codigoElectrodomestico, int _cantidadVendida);
    bool aumentarStock(int _codigoElectrodomestico, int _cantidadDevuelta);
    void leer(Electrodomesticos *vec, int cantidadRegistrosALeer);
    bool verificarEstadoConStock(int _codigoElectrodomestico);
};
