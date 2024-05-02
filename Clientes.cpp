#include "Clientes.h"
#include <iostream>
#include <string>
#include <cstring>

Clientes::Clientes()
{
    _estado=true;
}

void Clientes::setNombre(std::string nombre)
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
std::string Clientes::getNombre() const
{
    return _nombre;
}
void Clientes::setApellido(std::string apellido)
{
    if (apellido.length() < 30)
    {
        strcpy(_apellido,apellido.c_str());
    }
    else
    {
        std::cout<< "EL APELLIDO NO DEBE SUPERAR LOS 30 CARACTERES" << std::endl;
    }
}
std::string Clientes::getApellido() const
{
    return _apellido;
}
void Clientes::setDni(int dni)
{
    if (dni > 0)
    {
        _dni=dni;
    }
    else
    {
        std::cout << "El DNI DEBE SER UN NUMERO POSITIVO" <<std::endl;
    }
}
int Clientes::getDni() const
{
    return _dni;
}
void Clientes::setDireccion(std::string direccion)
{
    if (direccion.length() < 30)
    {
        strcpy(_direccion,direccion.c_str());
    }
    else
    {
        std::cout<< "LA DIRECCION NO DEBE SUPERAR LOS 30 CARACTERES" << std::endl;
    }
}
std::string Clientes::getDireccion() const
{
    return _direccion;
}
void Clientes::setTelefono(int telefono)
{
    _telefono=telefono;
}
int Clientes::getTelefono() const
{
    return _telefono;
}
void Clientes::setEmail(std::string email)
{
    if (email.length() < 30)
    {
        strcpy(_email,email.c_str());
    }
    else
    {
        std::cout<< "EL EMAIL NO DEBE SUPERAR LOS 30 CARACTERES" << std::endl;
    }
}
std::string Clientes::getEmail() const
{
    return _email;
}
void Clientes::setEstado( bool estado)
{
    _estado=estado;
}
bool Clientes::getEstado() const
{
    return _estado;
}
void Clientes::setFechaNacimiento(const Fecha &fechaNacimiento)
{
    _fechaNacimiento=fechaNacimiento;
}
Fecha Clientes::getFechaNacimiento() const
{
    return _fechaNacimiento;
}
void Clientes::setDeuda(float deuda)
{
    _deuda=deuda;
}
float Clientes::getDeuda() const
{
    return _deuda;
}
