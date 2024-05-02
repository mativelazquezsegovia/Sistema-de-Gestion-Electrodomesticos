#pragma once
#include "ArchivoClientes.h"
#include "ArchivoVentas.h"
#include "ArchivoElectrodomesticos.h"

class ConfiguracionMenu
{
private:
    ArchivoVentas _archivoVentas = ArchivoVentas ("Ventas.dat");
    ArchivoClientes _archivoClientes= ArchivoClientes("Clientes.dat");
    ArchivoElectrodomesticos _archivoElectrodomesticos = ArchivoElectrodomesticos ("Electrodomesticos.dat");
public:
    ConfiguracionMenu();
    bool  Configuracion();
    bool backUpIndividual();
    bool restaurarBackUpIndividual();
    bool hacerBackUpTodos();
    bool restaurarBackUPTodos();
};
