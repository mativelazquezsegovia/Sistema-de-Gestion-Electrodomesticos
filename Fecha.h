#pragma once
#include <string>

class Fecha
{
private:
    int _dia, _mes, _anio;
    int _diaSemana;
public:
    int getDia() const;
    int getMes() const;
    int getAnio() const;
    std::string getNombreDia();
    void setDia(int dia);
    void setMes(int mes);
    void setAnio(int anio);
    Fecha();
    Fecha(int dia, int mes, int anio);
    std::string toString();
    bool Cargar();
    void Mostrar();
    Fecha obtenerFechaActual();
};
