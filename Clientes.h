#pragma once
#include "Fecha.h"
#include <string>

class Clientes
{
private:
    char _nombre [30];
    char _apellido[30];
    int _dni;
    char _direccion[30];
    int _telefono;
    char _email[30];
    bool _estado;
    Fecha _fechaNacimiento;
    float _deuda;
public:
    Clientes();
    void setNombre(std::string nombre);
    std::string getNombre() const;
    void setApellido(std::string apellido);
    std::string getApellido() const;
    void setDni(int dni);
    int getDni() const;
    void setDireccion(std::string direccion);
    std::string getDireccion() const;
    void setTelefono(int telefono);
    int getTelefono() const;
    void setEmail(std::string email);
    std::string getEmail() const;
    void setEstado( bool estado);
    bool getEstado() const;
    void setFechaNacimiento(const Fecha &fechaNacimiento);
    Fecha getFechaNacimiento() const;
    void setDeuda(float deuda);
    float getDeuda() const;
};


