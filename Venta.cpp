#include "Venta.h"
#include <iostream>
#include <string>
#include "Cliente.h"
#include "Producto.h"
#include "Archivo_Cliente.h"
#include "archivo_producto.h"
#include "Archivo_Venta.h"
#include "Fecha.h"
#include "Menu.h"
using namespace std;

Venta::Venta()
{
	Archivo_Venta Archivo;
	id=Archivo.cantidad_ventas()+1;
	estado = true;
}

void Venta::setId(int id)
{
	this->id = id;
}

void Venta::setProducto(Producto producto)
{
	this->producto = producto;
}

void Venta::setCantidad(int cantidad)
{
	this->cantidad = cantidad;
}

void Venta::setPrecio(float precio)
{
	this->precio = precio;
}

void Venta::setTotal(float total)
{
	this->total = total;
}

void Venta::setEstado(bool estado)
{
	this->estado = estado;
}

void Venta::setFecha(int dia, int mes, int anio)
{
	fecha.setDia(dia);
	fecha.setMes(mes);
	fecha.setAnio(anio);
}

Fecha Venta::getFecha()
{
	return fecha;
}
int Venta::getId()
{
	return id;
}

Producto Venta::getProducto()
{
	return producto;
}

int Venta::getCantidad()
{
	return cantidad;
}

float Venta::getPrecio()
{
	return precio;
}

float Venta::getTotal()
{
	return total;
}

bool Venta::getEstado()
{
	return estado;
}





void Venta::cargar()
{
	archivo_producto archivo;
	Producto producto;
	Archivo_Cliente archivoCliente;
	Archivo_Venta venta;
	Cliente cliente;
	int id, idCliente;
	int cantidad;
	float precio;
	float total=0;
	float totalFinal = 0;
	float aumento;
	float descuento;
	int tipoPago;
	int dia, mes, anio;

	int cant = archivo.cantidad_de_registros();
	cout << endl;
	cout << "-------------------------------------------------------------" << endl;
	std::cout << "Ingrese la fecha" << std::endl;
	fecha.Cargar();
	std::cout << "Ingrese el ID del cliente que realiza la comprar: ";
	std::cin >> idCliente;
	Menu menu;
	while (archivoCliente.cantidad_clientes() == 0)
	{
		string desicion;
		std::cout << "No hay clientes cargados" << std::endl;
		std::cout << "¿Desea cargar uno? (S/N)" << std::endl;
		std::cin >> desicion;
		if (desicion == "S" || desicion == "s")
		{
			cliente.Cargar();
			archivoCliente.guardar(cliente);
		}
		else if (desicion == "N" || desicion == "n")
		{ return; }
		else
		{
			std::cout << "Opcion incorrecta" << std::endl;
			std::cout << "¿Desea cargar uno? (S/N)" << std::endl;
			std::cin >> desicion;
		}
	}
	while (idCliente <= 0 || idCliente > archivoCliente.cantidad_clientes())
	{
		std::cout << "El ID ingresado no existe" << std::endl;
		std::cout << "Ingrese el ID del cliente que realiza la comprar" << std::endl;
		std::cin >> idCliente;
	}
	cliente = archivoCliente.leer_clientes(idCliente - 1);
	std::cout << "Ingrese el ID del producto que desea comprar: ";
	std::cin >> id;
	while (id <= 0 || id > cant)
	{
		std::cout << "El ID ingresado no existe" << std::endl;
		std::cout << "Ingrese el ID del producto que desea comprar" << std::endl;
		std::cin >> id;
	}
	producto = archivo.leer_de_disco(id - 1);
	std::cout << "Ingrese la cantidad que desea comprar: ";
	std::cin >> cantidad;
	precio = producto.getPrecio();
	std::cout << "Ingrese el tipo de pago" << std::endl;
	std::cout << "1- Efectivo 5 % Descuento  //  2 - Tarjeta 8 % Aumento: " ;
	std::cin >> tipoPago;
	float porcentajeEfectivo = 0.05;
	float porcentajeTarjeta = 0.08;
		if (tipoPago != 1 && tipoPago != 2)
		{
			std::cout << "Opcion incorrecta" << std::endl;
			std::cout << "Ingrese el tipo de pago" << std::endl;
			std::cout << "1- Efectivo 5 % Descuento" << std::endl;
			std::cout << "2- Tarjeta 8 % Aumento" << std::endl;
			std::cin >> tipoPago;
		}
		total = precio * cantidad;
		descuento = total * porcentajeEfectivo;
		aumento = total * porcentajeTarjeta; 
	if (tipoPago == 1)
	{
		totalFinal = total - descuento;
	}
	else if (tipoPago == 2)
	{
		totalFinal = total + aumento;
	}
	setTipoPago(tipoPago);
	setIdCliente(cliente);
	setProducto(producto);
	setCantidad(cantidad);
	setPrecio(precio);
	setTotal(totalFinal);
	cout << "-------------------------------------------------------------" << endl << endl;
	system("pause");
}

void Venta::mostrar()
{

	std::cout << "****************************************** " << std::endl;
	std::cout << "Fecha: " << getFecha().toString() << std::endl;
	std::cout << "ID de Cliente: " << getIdCliente().getId_Cliente() << std::endl;
	std::cout << "ID de Venta: " << getId() << std::endl;
	std::cout << "Producto: " << getProducto().getNombre() << std::endl;
	std::cout << "Cantidad: " << getCantidad() << std::endl;
	std::cout << "Precio: " << getPrecio() << std::endl;
	if (getTipoPago() == 1)
	{
		std::cout << "Tipo de Pago: " << "EFECTIVO  5 % DESCUENTO" << std::endl;
	}
	else if (getTipoPago() == 2)
	{
		std::cout << "Tipo de Pago: " << "TARJETA  8 % AUMENTO" << std::endl;
	}
	std::cout << "Total a Pagar: " << getTotal() << std::endl;
	std::cout << "****************************************** " << std::endl;
}

void Venta::setIdCliente(Cliente cliente)
{
this-> cliente = cliente;
}

Cliente Venta::getIdCliente()
{
	return cliente;
}

void Venta::setTipoPago(int tipoPago)
{
	this->tipoPago = tipoPago;
}

int Venta::getTipoPago()
{
	return tipoPago;
	
}






