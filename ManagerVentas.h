#pragma once
#include "ArchivoClientes.h"
#include "ArchivoElectrodomesticos.h"
#include "Ventas.h"
#include "ArchivoVentas.h"
#include "ManagerClientes.h"
#include "ManagerElectrodomesticos.h"
#include <string>

class ManagerVentas
{
private:
    ArchivoVentas _archivoVentas = ArchivoVentas ("Ventas.dat");
    ArchivoClientes _archivoClientes= ArchivoClientes("Clientes.dat");
    ManagerClientes _managerClientes;
    ArchivoElectrodomesticos _archivoElectrodomesticos = ArchivoElectrodomesticos ("Electrodomesticos.dat");
    ManagerElectrodomesticos _managerElectrodomesticos;
public:
    ManagerVentas();
    void Cargar();
    void Mostrar(Ventas reg);
    bool  mostrarRegistrosVentas();
    float calcularDescuento(int cantidadProductos, bool mostrarMensaje);
    void  calcularVuelto(Ventas reg);
    bool bajaVenta();
    std::string generarNumeroFactura();
    bool Devolucion();
};
