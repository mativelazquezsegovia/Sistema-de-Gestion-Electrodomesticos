#pragma once
#include "Electrodomesticos.h"
#include "ArchivoElectrodomesticos.h"

class ManagerElectrodomesticos
{
private:
    ArchivoElectrodomesticos _archivo = ArchivoElectrodomesticos ("Electrodomesticos.dat");
public:
    void Cargar();
    void Mostrar(Electrodomesticos reg);
    bool  ListarRegistros(bool mostrarActivos);
    bool  mostrarRegistrosDisponiblesyEliminados();
    bool  bajaElectrodomestico();
    bool buscarElectrodomesticoxCodigo();
    bool modificarStock();
    void filtrarPorDisponibilidad();
    int obteneryValidarCodigoElectrodomestico();
    void Ordenar(Electrodomesticos *vec, int cantidadRegistros);
    bool reactivarCodigo();
    bool reactivarElectrodomesticoPorCodigo();
};
