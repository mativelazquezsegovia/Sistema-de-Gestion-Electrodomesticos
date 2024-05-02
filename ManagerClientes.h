#pragma once
#include "Clientes.h"
#include "ArchivoClientes.h"
#include "ArchivoVentas.h"

class ManagerClientes
{
private:
    ArchivoClientes _archivo = ArchivoClientes ("Clientes.dat");
    ArchivoVentas _archivoVentas = ArchivoVentas ("Ventas.dat");
public:
    ManagerClientes();
    void Cargar();
    void Mostrar(Clientes reg);
    bool corroborarCliente(int _dniCliente, Clientes &regCliente);
    bool ListarRegistros(bool mostrarActivos);
    bool  bajaCliente();
    bool  mostrarRegistrosClienteActivosNoActivos();
    bool buscarClientexDni();
    bool modificarEmail();
    void Ordenar(Clientes *vec, int cantidadRegistros);
    bool reactivarCliente();
    bool reactivarClientePorDNI();
};
