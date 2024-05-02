#pragma once
#include "Fecha.h"

class Ventas
{
private:
    int _nroVenta;
    int  _dniCliente;
    int _codigoElectrodomestico;
    float _total;
    float _importeAbonado;
    Fecha _fechaVenta;
    bool _estado;
    char  _metodoPago;
    static const int maxProduct=10;
    int _codigosProductos[maxProduct];
    float _totalesProductos[maxProduct];
    int _cantidadProductos;
    int _cantidadVendida;
    std::string _numeroFactura;
    bool _esDevolucion;
public:
    Ventas(int nroVenta, int dniCliente, int codigoElectrodomestico, float total, float importeAbonado, bool estado, char metodoPago, int cantidadProductos, int cantidadVendida);
    Ventas();
    void setNroVenta(int nroVenta);
    int getNroVenta() const;
    void setDniCliente (int  dniCliente);
    int  getDniCliente() const;
    void setCodigoElectrodomestico(int codigoElectrodomestico);
    int getCodigoElectrodomestico() const;
    void setTotal(float total);
    float getTotal() const;
    void setImporteAbonado(float importeAbonado);
    float getImporteAbonado() const;
    void setEstado(bool estado);
    bool getEstado() const;
    void setFechaVenta (const Fecha &fechaVenta);
    Fecha getFechaVenta() const;
    void setMetodoPago(const char metodoPago);
    const char getMetodoPago() const;
    void setCantidadProductos(int cantidadProductos);
    int getCantidadProductos() const;
    void agregarProducto(int codigoElectrodomestico, float _totalProducto);
    static int getMaxProduct();
    int getCodigoProducto(int indice) const;
    float getTotalProducto(int indice) const;
    void setCantidadVendida( int cantidadVendida);
    int getCantidadVendida() const;
    void setNumeroFactura(std::string numeroFactura);
    std::string getNumeroFactura() const;
    void limpiarProductos();
    void generarNumeroFacturaAleatorio();
    void confirmarEsDevolucion();
    bool obtenerEsDevolucion() const;
};
