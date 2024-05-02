#include <ctime>
#include <iostream>
#include "fecha.h"
using namespace std;

int Fecha::getDia() const
{
    return _dia;
}
int Fecha::getMes() const
{
    return _mes;
}
int Fecha::getAnio() const
{
    return _anio;
}
void Fecha::setDia(int dia)
{
    _dia = dia;
}
void Fecha::setMes(int mes)
{
    _mes = mes;
}
void Fecha::setAnio(int anio)
{
    _anio = anio;
}
Fecha::Fecha()
{
    time_t t = time(NULL);
    struct tm *f = localtime(&t);
    _dia = (*f).tm_mday; // Indirecciona f y accede a tm_mday
    _mes = f->tm_mon + 1; // Indirecciona f y accede a tm_mon
    _anio = f->tm_year + 1900;
    _diaSemana = f->tm_wday;
}
Fecha::Fecha(int dia, int mes, int anio)
{
    setDia(dia);
    setMes(mes);
    setAnio(anio);
    _diaSemana = -1;
}
std::string Fecha::toString()
{
    std::string valorADevolver;
    valorADevolver = std::to_string(_dia) + "/" + std::to_string(_mes) + "/" + std::to_string(_anio);
    return valorADevolver;
}

std::string Fecha::getNombreDia()
{
    std::string nombres[7] = {"Domingo", "Lunes", "Martes", "Miercoles", "Jueves", "Viernes", "Sabado"};
    if (_diaSemana >= 0 && _diaSemana <= 6)
    {
        return nombres[_diaSemana];
    }
    return "";
}
bool Fecha::Cargar()
{
    int dia;
    int mes;
    int anio;

    bool p=false, q=false, r=false; // para ver si es bisiesto
    bool bisiesto=false;
    int diamax;

    cout<<"Anio: ";
    cin>>anio;
    while (anio<=0)
    {
        cout<<"Anio Incorrecto. Mayor a 0"<<endl;
        //return false;
        cout<<"Anio: ";
        cin>>anio;
    }
    if(anio%4==0)
    {
        p=true;
    }
    if(anio%100==0)
    {
        q=true;
    }
    if(anio%400==0)
    {
        r=true;
    }
    if(p==true&&(q==false||r==true))
    {
        bisiesto=true;
    }
    cout<<"Mes: ";
    cin>>mes;
    while(mes<=0||mes>12)
    {
        cout<<"MES INCORRECTO, DEL 1 AL 12."<<endl;
        //return false;
        cout<<"Mes: ";
        cin>>mes;
    }
    if (mes==1||mes==3||mes==5||mes==7||mes==8||mes==10||mes==12)
    {
        diamax=31;
    }
    else if(mes==4||mes==6||mes==9||mes==11)
    {
        diamax=30;
    }
    else if(mes==2&&bisiesto)
    {
        diamax=29;
    }
    else
    {
        diamax=28;
    }

    cout<<"Dia: ";
    cin>>dia;
    while(dia<=0||dia>diamax)
    {
        cout<<"Dia Incorrecto."<<endl;
        //return false;
        cout<<"Dia: ";
        cin>>dia;
    }
    setAnio(anio);
    setMes(mes);
    setDia(dia);
    return true;
}

Fecha Fecha::obtenerFechaActual()
{
    time_t t = time(NULL);
    struct tm *f = localtime(&t);
    int dia = (*f).tm_mday;
    int mes = f->tm_mon + 1;
    int anio = f->tm_year + 1900;

    Fecha fechaActual(dia, mes, anio);
    return fechaActual;
}
