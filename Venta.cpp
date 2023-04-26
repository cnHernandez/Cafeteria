#include "Venta.h"
#include <iostream>
#include <string>
#include "Cliente.h"
#include "Producto.h"
#include "Archivo_Cliente.h"
#include "archivo_producto.h"
#include "Archivo_Venta.h"
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
	return precio * cantidad;
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
	float total;

	int cant = archivo.cantidad_de_registros();
	archivo.listar(cant);
	std::cout << std::endl;
	std::cout << "Ingrese el ID del cliente que realiza la comprar" << std::endl;
	std::cin >> idCliente;
	cliente = archivoCliente.leer_clientes(idCliente - 1);
	std::cout << std::endl;
	std::cout << "Ingrese el ID del producto que desea comprar" << std::endl;
	std::cin >> id;
	producto = archivo.leer_de_disco(id - 1);
	std::cout << "Ingrese la cantidad que desea comprar" << std::endl;
	std::cin >> cantidad;
	precio = producto.getPrecio();
	total = precio * cantidad;
	setIdCliente(cliente);
	setProducto(producto);
	setCantidad(cantidad);
	setPrecio(precio);
	setTotal(total);

}

void Venta::mostrar()
{

	std::cout << "********************** " << std::endl;
	std::cout << "ID de Cliente: " << getIdCliente().getId_Cliente() << std::endl;
	std::cout << "ID de Venta: " << getId() << std::endl;
	std::cout << "Producto: " << getProducto().getNombre() << std::endl;
	std::cout << "Cantidad: " << getCantidad() << std::endl;
	std::cout << "Precio: " << getPrecio() << std::endl;
	std::cout << "Total: " << getTotal() << std::endl;
	std::cout << "********************** " << std::endl;
}



void Venta::setIdCliente(Cliente cliente)
{
this-> cliente = cliente;
}

Cliente Venta::getIdCliente()
{
	return cliente;
}


