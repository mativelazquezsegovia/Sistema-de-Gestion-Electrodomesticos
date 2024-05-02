#include "ManagerVentas.h"
#include "ArchivoClientes.h"
#include "ArchivoElectrodomesticos.h"
#include "ManagerClientes.h"
#include "ManagerElectrodomesticos.h"
#include "Fecha.h"
#include <ctime>
#include "rlutil.h"
#include "Funciones.h"
#include <iostream>
#include <cstdlib>
#include <string>
using namespace std;

ManagerVentas::ManagerVentas() : _archivoVentas("Ventas.dat"), _managerClientes(), _archivoClientes("Clientes.dat"), _managerElectrodomesticos(), _archivoElectrodomesticos("Electrodomesticos.dat")
{
    //inicializando las instancias creadas
}

float ManagerVentas::calcularDescuento(int cantidadProductos, bool mostrarMensaje)
{
    if (mostrarMensaje && cantidadProductos == 1)
    {
        cout << "NO ES POSIBLE APLICAR DESCUENTO, POR NO LLEGAR A LA CANTIDAD MINIMA DE PRODUCTOS"<<  endl;
        return 0;
    }
    float porcentajeDescuento = 0;
    if (cantidadProductos == 2)
    {
        porcentajeDescuento = 10;
    }
    else if (cantidadProductos == 3)
    {
        porcentajeDescuento = 15;
    }
    else if (cantidadProductos == 4)
    {
        porcentajeDescuento = 25;
    }
    else if (cantidadProductos >= 5)
    {
        porcentajeDescuento = 40;
    }
    return porcentajeDescuento;
}

void  ManagerVentas::calcularVuelto(Ventas reg)
{
    float vuelto = reg.getImporteAbonado() - reg.getTotal();
    if (vuelto >= 0)
    {
        cout << "Vuelto $: " << vuelto << endl;
    }
    else
    {
        // Si el importe abonado no cubre el total, mostrar la deuda
        float deuda = reg.getTotal() - reg.getImporteAbonado();
        cout << "El cliente debe $: " << deuda << endl;
    }
}

void ManagerVentas::Cargar()
{
    int nroVenta;
    int dniCliente;
    int codigoElectrodomestico;
    int cantidadProductos,cantidadVendida;
    char metodoPago;
    float total;
    Fecha fechaVenta;
    bool estado;
    int contadorCantidadVendida=0;
    int codigoAnterior = 0;
    float importeAbonado = 0;

    cout << "Nro De Venta: " << endl;
    cin >> nroVenta;
    while (_archivoVentas.validarNumeroVentaRepetido(nroVenta))
    {
        cout << "NRO DE VENTA REPETIDO, INGRESE OTRO: "<<endl;
        cin >> nroVenta;
    }
    cout << "Dni del Cliente:" << endl;
    cin >> dniCliente;
    Clientes regCliente;
    if (_managerClientes.corroborarCliente(dniCliente, regCliente))
    {
        cout << "CLIENTE ENCONTRADO"<<endl;
        if (_archivoVentas.verificarDeuda(dniCliente))
        {
            return;
        }
    }
// Preguntar al usuario cuantos productos desea agregar
    cout << "INGRESE LA CANTIDAD DE PRODCUTOS A COMPRAR: ";
    cin >> cantidadProductos;
    total = 0;  // Inicializar el total de la venta
    float porcentajeDescuento = calcularDescuento(cantidadProductos,false);
    Ventas ventaNueva(nroVenta, dniCliente, codigoElectrodomestico, total, importeAbonado, estado, metodoPago, cantidadProductos,cantidadVendida);

    ventaNueva.limpiarProductos();

    ventaNueva.generarNumeroFacturaAleatorio();
// Agregar productos a la venta
    for (int i = 0; i < cantidadProductos && i < Ventas::getMaxProduct(); i++)
    {
        codigoElectrodomestico= _managerElectrodomesticos.obteneryValidarCodigoElectrodomestico();
        if (_archivoElectrodomesticos.verificarEstadoConStock(codigoElectrodomestico))
        {
            cout << endl;
            char _compra;
            cout << "DESEA COMPRAR ESTE PRODUCTO? (S/N): ";
            cin >> _compra;
            cin.ignore();
            if (_compra == 'S' || _compra == 's')
            {
                float precioUnitario = _archivoElectrodomesticos.obtenerPrecioUnitario(codigoElectrodomestico);
                // Verificar si el codigo cambio
                if (codigoElectrodomestico != codigoAnterior)
                {
                    // Actualizar stock para el codigo anterior
                    _archivoElectrodomesticos.actualizarStock(codigoAnterior, contadorCantidadVendida);
                    // Reiniciar el contador para el nuevo codigo
                    contadorCantidadVendida = 0;
                }
                // Incrementar la cantidad vendida por codigo
                contadorCantidadVendida++;
                // Almacenar el codigo y total del producto en el vector
                ventaNueva.agregarProducto(codigoElectrodomestico, precioUnitario);
                total += precioUnitario;  // Incrementar el total de la venta
                // Actualizar codigoAnterior solo cuando se compra el producto
                codigoAnterior = codigoElectrodomestico;
            }
        }
        else
        {
            cout << "EL ELECTRODOMESTICO NO SE ENCUNTRA DISPONIBLE O NO TIENE STOCK" << endl;
        }
    }
    // Actualizar stock para el último código
    _archivoElectrodomesticos.actualizarStock(codigoAnterior, contadorCantidadVendida);
    // Aplicar descuento
    float descuentoProducto = (total * porcentajeDescuento) / 100;
    total -= descuentoProducto;
    cout << "TOTAL DE LA COMPRA: " << total << endl;
    ventaNueva.setTotal(total);
    ventaNueva.setCantidadProductos(cantidadProductos);

    cout << "Seleccione el metodo de pago (E: Efectivo, T: Tarjeta): ";
    cin >> metodoPago;
    // Validar la entrada del usuario
    while (metodoPago!= 'E' && metodoPago != 'e' && metodoPago != 'T' && metodoPago != 't')
    {
        cout << "Metodo de pago no valido. Debe ser 'E' o 'T': ";
        cin >> metodoPago;
    }
    ventaNueva.setMetodoPago(metodoPago);
// Verificar si el importe abonado es suficiente
    while (importeAbonado < total)
    {
        cout << "Importe Abonado: " << endl;
        cin >> importeAbonado;
        if (importeAbonado < total)
        {
            cout << "EL IMPORTE ABONADO NO ES SUFICIENTE PARA CUBRIR EL TOTAL DE LA VENTA" << endl;
            char _opc;
            cout << "DESEA INGRESAR NUEVAMENTE EL IMPORTE ABONADO? (S/N)  " << endl;
            cin >> _opc;
            if (_opc == 's' || _opc == 'S')
            {
                continue; // Vuelve al inicio del bucle while para ingresar el importe nuevamente
            }
            else
            {
                // Si el usuario no desea ingresar nuevamente el importe abonado
                cout << "DESEA TERMINAR LA VENTA CON EL SALDO ACTUAL? (S/N)  " << endl;
                cin >> _opc;
                // Si el usuario desea terminar la venta con el saldo actual
                if (_opc == 's' || _opc == 'S')
                {
                    // Calcular y actualizar la deuda del cliente
                    float deudaCliente = _archivoVentas.calcularDeudaCliente(dniCliente);
                    ventaNueva.setImporteAbonado(importeAbonado);
                    estado = false;
                    ventaNueva.setEstado(false);
                    break;// Sale del bucle while
                }
                else
                {
                    // Si el usuario no desea terminar la venta con el saldo actual, vuelve al inicio del bucle
                    continue;
                }
            }
        }
        else
        {
            // Importe abonado suficiente
            estado=true;
            ventaNueva.setEstado(true);
            ventaNueva.setImporteAbonado(importeAbonado);
            break;// Sale del bucle while
        }
    }

    //Aca obtengo la fecha actual
    cout << "Fecha Venta: "<< endl;
    fechaVenta = fechaVenta.obtenerFechaActual();
    ventaNueva.setFechaVenta(fechaVenta);
    cout<<fechaVenta.toString() << endl;


    // Agregar la venta al archivo
    if(_archivoVentas.agregaRegistros(ventaNueva))
    {
        cout << "VENTA REGISTRADA" << endl;
    }
    else
    {
        cout << "ERROR AL REGISTRAR LA VENTA" << endl;
    }
}

void ManagerVentas::Mostrar(Ventas reg)
{
    cout << "**********************" << endl;
    cout << "INFORMACION DE LA VENTA: " << endl;
//cout<< "Nro de Factura: " << reg.getNumeroFactura() <<endl;
    cout << "Nro De Venta: " << reg.getNroVenta() << endl;
    cout << "Fecha de Venta: " << reg.getFechaVenta().toString() <<endl;
    // Mostrar información del cliente
    cout << "CLIENTE:" << endl;
    int posCliente = _archivoClientes.buscarCliente(reg.getDniCliente());
    if (posCliente != -1)
    {
        Clientes regCliente = _archivoClientes.leerRegistro(posCliente);
        _managerClientes.Mostrar(regCliente);
    }
    // Mostrar informacion de los productos
    cout << "PRODUCTOS: " << endl;
    for (int i = 0; i < reg.getCantidadProductos() && i < Ventas::getMaxProduct(); i++)
    {
        int _codigoProducto = reg.getCodigoProducto(i);
        float _totalProducto = reg.getTotalProducto(i);
        int posElectrodomestico = _archivoElectrodomesticos.buscarCodigoElectrodomestico(_codigoProducto);
        if (posElectrodomestico != -1)
        {
            Electrodomesticos regElectrodomesticos = _archivoElectrodomesticos.leerRegistro(posElectrodomestico);
            // Mostrar cod, nombre e importe de cada producto en una línea
            cout << "Cod: " << regElectrodomesticos.getCodigo() << " | Nombre: " << regElectrodomesticos.getNombre() << " | Importe $: " << _totalProducto << endl;
        }
    }
    cout<< endl;
    // Mostrar información adicional de la venta
    float porcentajeDescuento = calcularDescuento(reg.getCantidadProductos(),true);
    if(reg.getCantidadProductos()>1)
    {
        cout << "Descuento aplicado" << porcentajeDescuento << "%: $" << (reg.getTotal() * porcentajeDescuento) / 100 << endl;
    }
    cout << "Total de la Compra: $" << reg.getTotal() << endl;
    cout << "Importe Abonado por el cliente fue de $: " << reg.getImporteAbonado() << endl;
    cout << "El metodo de pago fue: " << reg.getMetodoPago() << endl;
    calcularVuelto(reg);
    float deudaCliente = _archivoVentas.calcularDeudaCliente(reg.getDniCliente());
    if (deudaCliente >0 && reg.getImporteAbonado()<reg.getTotal())
    {
        cout << "VENTA CON DEUDA" << endl;
    }
    cout << "**********************" << endl;
}

bool ManagerVentas::Devolucion()
{
    int nroVenta;
    cout << "INGRESE EL NRO DE VENTA SOBRE LA CUAL DESEA HACER LA DEVOLUCION: " << endl;
    cin >> nroVenta;
    cin.ignore();
    int posVenta = _archivoVentas.buscarNroVenta(nroVenta);
    if (posVenta != -1)
    {
        // Leer la venta en esa posición
        Ventas regVenta = _archivoVentas.leerRegistro(posVenta);
        cout << "ESTA ES LA VENTA: " << endl;
        Mostrar(regVenta);
        cout << endl;
        // Realizar devolución total
        char opcion;
        cout << "DESEA REALMENTE DEVOLVER ESTA VENTA? (S/N): ";
        cin >> opcion;
        cin.ignore();
        if (opcion == 'S' || opcion == 's')
        {
            int _codigoDevuelto;
            cout << "INGRESE EL CODIGO QUE DESEA DEVOLVER (0 PARA TERMINAR): " << endl;
            cin >> _codigoDevuelto;
            while (_codigoDevuelto != 0)
            {
                int _contador = 0;
                int _codigoAnterior = _codigoDevuelto;
                while (_codigoDevuelto == _codigoAnterior && _codigoDevuelto != 0)
                {
                    _contador++; // Contar productos con el mismo código
                    cout << "INGRESE EL CODIGO QUE DESEA DEVOLVER: " << endl;
                    cin >> _codigoDevuelto;
                }
                _archivoElectrodomesticos.aumentarStock(_codigoAnterior, _contador);
                _contador = 0; // Resetear el contador
            }

            // Calcular y anular el descuento total de la venta (si aplica)
            float descuentoTotal = calcularDescuento(regVenta.getCantidadProductos(), false);
            float nuevoTotal = regVenta.getTotal() + descuentoTotal; // Anular descuento
            regVenta.setTotal(nuevoTotal);
            regVenta.confirmarEsDevolucion();
            _archivoVentas.remplazarReg(regVenta, posVenta);

            cout << "DEVOLUCION REALIZADA" << endl;
            return true;
        }
        else if (opcion == 'N' || opcion == 'n')
        {
            cout << "DEVOLUCION CANCELADA POR EL USUARIO" << endl;
            return false;
        }
    }
    else
    {
        cout << "NO SE ENCONTRO EL NRO DE VENTA EN LA BASE DE DATOS" << endl;
        return false;
    }
    return false;
}

bool ManagerVentas::mostrarRegistrosVentas()
{
    int cantVentas = _archivoVentas.contarRegistros();
    cout<< "Cantiodad ventas" << cantVentas;
    if (cantVentas == 0)
    {
        cout << "NO HAY VENTAS REGISTRADAS" << endl;
        return false;
    }
    int y = 0;
    bool continuar=true;
    do
    {
        rlutil::setBackgroundColor(rlutil::BLACK);
        rlutil::setColor(rlutil::WHITE);
        rlutil::hidecursor();

        rlutil::locate(68, 10);
        cout << "SELECCIONE UNA OPCION: " << endl;
        rlutil::locate(68, 11);
        cout << "**********************" << endl;
        showItem("1. MOSTRAR VENTAS", 68, 12, y == 0);
        showItem("2. MOSTRAR VENTAS EN EFECTIVO", 68, 13, y == 1);
        showItem("3. MOSTRAR VENTAS CON TARJETA", 68, 14, y == 2);
        showItem("4. MOSTRAR DEVOLUCIONES", 68, 15, y == 3);
        showItem("0. VOLVER AL MENU ANTERIOR", 68, 16, y == 4);
        rlutil::locate(68, 17);
        cout << "**********************" << endl;
        switch (rlutil::getkey())
        {
        case 14: // up
            rlutil::locate(68, 12 + y);
            cout << "  " << endl;
            y--;
            if (y < 0)
            {
                y = 0;
            }
            break;
        case 15: // down
            rlutil::locate(68, 12 + y);
            cout << "  " << endl;
            y++;
            if (y > 4)
            {
                y = 4;
            }
            break;
        case 1: // enter
            switch (y)
            {
            case 0:
                rlutil::cls();
                // Mostrar todas las ventas
                for (int i = 0; i < cantVentas; i++)
                {
                    Ventas ventaActual = _archivoVentas.leerRegistro(i);
                    if (!ventaActual.obtenerEsDevolucion())
                    {
                        Mostrar(ventaActual);
                    }
                }
                cout<<"Aprete ENTER para volver atras"<<endl;
                cin.ignore();
                rlutil::cls();
                break;
            case 1:
                rlutil::cls();
                // Mostrar ventas en efectivo
                for (int i = 0; i < cantVentas; i++)
                {
                    Ventas ventaActual = _archivoVentas.leerRegistro(i);
                    if (ventaActual.getMetodoPago() == 'E' || ventaActual.getMetodoPago() == 'e')
                    {
                        Mostrar(ventaActual);
                    }
                }
                cout<<"Aprete ENTER para volver atras"<<endl;
                cin.ignore();
                rlutil::cls();
                break;
            case 2:
                rlutil::cls();
                // Mostrar ventas con tarjeta
                for (int i = 0; i < cantVentas; i++)
                {
                    Ventas ventaActual = _archivoVentas.leerRegistro(i);
                    if (ventaActual.getMetodoPago() == 'T' || ventaActual.getMetodoPago() == 't')
                    {
                        Mostrar(ventaActual);
                    }
                }
                cout<<"Aprete ENTER para volver atras"<<endl;
                cin.ignore();
                rlutil::cls();
                break;
            case 3:
                rlutil::cls();
                // Mostrar devoluciones
                for (int i = 0; i < cantVentas; i++)
                {
                    Ventas ventaActual = _archivoVentas.leerRegistro(i);
                    if (ventaActual.obtenerEsDevolucion())
                    {
                        Mostrar(ventaActual);
                    }
                }
                cout<<"Aprete ENTER para volver atras"<<endl;
                cin.ignore();
                rlutil::cls();
                break;
            case 4:
                rlutil::cls();
                continuar=false;
                break; // Volver al menú anterior
            default:
                cout << "OPCION INCORRECTA, VUELVA A INGRESAR" << endl;
                break;
            }
            break;
        default:
            break;
        }
    }
    while (continuar);
    cin.ignore();
    return true;
}

//Eliminar una venta
bool ManagerVentas::bajaVenta()
{
    int nroVenta;
    cout << "INGRESE EL NRO DE VENTA QUE DESEA ELIMINAR: ";
    cin >> nroVenta;
    int posVenta = _archivoVentas.buscarNroVenta(nroVenta);
    if (posVenta != -1)
    {
        Ventas regVenta = _archivoVentas.leerRegistro(posVenta);

        cout << "INFORMACION DE LA VENTA A ELIMINAR: " << endl;
        Mostrar(regVenta);

        char _opc;
        cout << "Esta seguro que desea eliminar esta venta? (S/N): ";
        cin >> _opc;
        cin.ignore();
        if (_opc == 's' || _opc == 'S')
        {
            regVenta.setEstado(false);

            if (_archivoVentas.remplazarReg(regVenta, posVenta))
            {
                cout << "VENTA ELIMINADA" << endl;
                return true;
            }
            else
            {
                cout << "ERROR AL ELIMINAR UNA VENTA" << endl;
                return false;
            }
        }
        else
        {
            cout << "ELIMINACION CANCELADA POR EL USUARIO" << endl;
            return false;
        }
    }

    cout << "NRO DE VENTA NO ENCONTRADO" << endl;
    return false;
}


