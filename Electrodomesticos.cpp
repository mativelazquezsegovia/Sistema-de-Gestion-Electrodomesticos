#include "Electrodomesticos.h"
#include <iostream>
#include <cstring>
#include <string>

Electrodomesticos::Electrodomesticos()
{
    _estado=true;
}
void Electrodomesticos::setCodigo(int codigo)
{
    _codigo=codigo;
}
int Electrodomesticos::getCodigo() const
{
    return _codigo;
}
void Electrodomesticos::setNombre(std::string nombre)
{
    if(nombre.length() < 30) //usando .length() verificola cantidad copiada
    {
        strcpy(_nombre,nombre.c_str());
    }
    else
    {
        std::cout<< "EL NOMBRE NO DEBE SUPERAR LOS 30 CARACTERES" << std::endl;
    }
}
std::string  Electrodomesticos::getNombre() const
{
    return _nombre;
}
void Electrodomesticos::setPrecioUnitario(float precioUnitario)
{
    if (precioUnitario > 0)
    {
        _precioUnitario=precioUnitario;
    }
    else
    {
        std::cout << "EL PRECIO UNITARIO DEBE SER POSITIVO" << std::endl;
    }
}
float Electrodomesticos::getPrecioUnitario() const
{
    return _precioUnitario;
}
void Electrodomesticos::setStock(int stock)
{
    if (stock >= 0)
    {
        _stock=stock;
    }
    else
    {
        std::cout << "EL STOCK NO PUEDE SER NEGATIVO" << std::endl;
    }
}
int Electrodomesticos::getStock() const
{
    return _stock;
}
void Electrodomesticos::setCapacidad(float capacidad)
{
    _capacidad=capacidad;
}
float Electrodomesticos::getCapacidad() const
{
    return _capacidad;
}
void Electrodomesticos::setDisponibilidad(bool disponibilidad)
{
    _disponibilidad=disponibilidad;
}
bool Electrodomesticos::getDisponibilidad() const
{
    return _disponibilidad;
}
void Electrodomesticos::setEstado(bool estado)
{
    _estado=estado;
}
bool Electrodomesticos::getEstado() const
{
    return _estado;
}

