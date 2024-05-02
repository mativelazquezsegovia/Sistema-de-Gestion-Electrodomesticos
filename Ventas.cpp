#include "Ventas.h"
#include <iostream>
#include <ctime>
#include <cstring>


Ventas::Ventas(int nroVenta, int dniCliente, int codigoElectrodomestico, float total, float importeAbonado, bool estado, char metodoPago, int cantidadProductos, int cantidadVendida)
    : _nroVenta(nroVenta), _dniCliente(dniCliente), _codigoElectrodomestico(codigoElectrodomestico), _total(total), _importeAbonado(importeAbonado), _estado(estado), _metodoPago(metodoPago), _cantidadProductos(cantidadProductos), _cantidadVendida(cantidadVendida)
{
    limpiarProductos();//limpio el vector de productos en cada venta
    generarNumeroFacturaAleatorio();// asigno un nro aleatorio como nro de factura
}
Ventas::Ventas() {}

void Ventas::setNroVenta(int nroVenta)
{
    _nroVenta=nroVenta;
}
int Ventas::getNroVenta() const
{
    return _nroVenta;
}
void Ventas::setDniCliente (int  dniCliente)
{
    _dniCliente=dniCliente;
}
int  Ventas::getDniCliente() const
{
    return _dniCliente;
}
void Ventas::setCodigoElectrodomestico(int codigoElectrodomestico)
{
    _codigoElectrodomestico=codigoElectrodomestico;
}
int Ventas::getCodigoElectrodomestico() const
{
    return _codigoElectrodomestico;
}
void Ventas::setTotal(float total)
{
    if (total >= 0)
    {
        _total=total;
    }
    else
    {
        std::cout << "EL MONTO DEBE SER POSITIVO" << std::endl;
    }
}
float Ventas::getTotal() const
{
    return _total;
}
void Ventas::setImporteAbonado(float importeAbonado)
{
    if (importeAbonado >= 0)
    {
        _importeAbonado=importeAbonado;
    }
    else
    {
        std::cout << "EL IMPORTE ABONADO NO PUEDE SER NEGATIVO" << std::endl;
    }
}
float Ventas::getImporteAbonado() const
{
    return _importeAbonado;
}
void Ventas::setEstado(bool estado)
{
    _estado=estado;
}
bool Ventas::getEstado() const
{
    return _estado;
}
void Ventas::setFechaVenta(const Fecha &fechaVenta)
{
    _fechaVenta=fechaVenta;
}
Fecha Ventas::getFechaVenta() const
{
    return _fechaVenta;
}
void Ventas::setMetodoPago(const char metodoPago)
{
    if (metodoPago == 'E' || metodoPago == 'e' || metodoPago == 'T' || metodoPago == 't')
    {
        _metodoPago=metodoPago;
    }
    else
    {
        std::cout << "METODO DE PAGO NO VALIDO" << std::endl;
    }
}
const char Ventas::getMetodoPago() const
{
    return _metodoPago;
}
void Ventas::setCantidadProductos(int cantidadProductos)
{
    _cantidadProductos = cantidadProductos;
}

int Ventas::getCantidadProductos() const
{
    return _cantidadProductos;
}
void Ventas::agregarProducto(int codigoElectrodomestico, float precioUnitario)
{
    if (_cantidadProductos < maxProduct)//verifico si la cantidad es menor que el maximo
    {
        _codigosProductos[_cantidadProductos] = codigoElectrodomestico; //guardo en el vector el codigo de electrodomestico
        _totalesProductos[_cantidadProductos] =precioUnitario; //gaurdo en el vector el total de los productos
        _cantidadProductos++; // cuento la cantidad de productos en la venta
    }
    else
    {
        std::cout << "NO SE PUEDEN AGREGAR MAS PRODUCTOS A ESTA VENTA" << std::endl;
    }
}
int Ventas::getMaxProduct()
{
    return maxProduct;
}
int Ventas::getCodigoProducto(int indice) const
{
    if (indice >= 0 && indice < _cantidadProductos)//Verifico que el indice este dentro del rango valido
    {
        return _codigosProductos[indice];//Devuelvo el codigo del producto de acuerdo al indice en el vector
    }
    return -1;
}
float Ventas::getTotalProducto(int indice) const
{
    if (indice >= 0 && indice < _cantidadProductos)//Verifico que el indice este dentro del rango válido.
    {
        return _totalesProductos[indice];//Devuelvo el total del producto de acuerdo al indice en el vector
    }
    return -1;
}
void Ventas::setCantidadVendida( int cantidadVendida)
{
    _cantidadVendida=cantidadVendida;
}
int Ventas::getCantidadVendida() const
{
    return _cantidadVendida;
}
void Ventas::setNumeroFactura(std::string  numeroFactura)
{
    _numeroFactura = numeroFactura;
}
std::string Ventas::getNumeroFactura() const
{
    return _numeroFactura;
}
void Ventas::limpiarProductos()
{
    _cantidadProductos = 0;
    for (int i = 0; i < maxProduct; ++i)
    {
        _codigosProductos[i] = 0;
        _totalesProductos[i] = 0;
    }
}
void Ventas::generarNumeroFacturaAleatorio()
{
    srand(time(0));
    int numeroAleatorio = rand() % (9999) + 1;  // Rango de 1 a 10000
    _numeroFactura=std::to_string(numeroAleatorio);
}

void Ventas::confirmarEsDevolucion()
{
    _esDevolucion = true;
}

bool Ventas::obtenerEsDevolucion() const
{
    return _esDevolucion;
}
