#pragma once
#include "Fecha.h"

class Electrodomesticos
{
private:
    int _codigo;
    char _nombre[30];
    float _precioUnitario;
    int _stock;
    float _capacidad;
    bool  _disponibilidad;
    bool _estado;

public:
    Electrodomesticos();
    void setCodigo(int codigo);
    int getCodigo() const;
    void setNombre(std::string nombre);
    std::string  getNombre() const;
    void setPrecioUnitario(float precioUnitario);
    float getPrecioUnitario() const;
    void setStock(int stock);
    int getStock() const;
    void setCapacidad(float capacidad);
    float getCapacidad() const;
    void setDisponibilidad(bool disponibilidad);
    bool getDisponibilidad() const;
    void setEstado(bool estado);
    bool getEstado() const;
};
