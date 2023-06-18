#include "DetalleVenta.h"
#include <iostream>
#include <string>

using namespace std;

DetalleVenta::DetalleVenta()
{
	id_producto = 0;
	id_categoria = 0;
	cantidad = 0;
	precio = 0;
	precio_compra = 0;
	setNombre("NONE");
}

void DetalleVenta::setNombre(string Nombre)
{
	strcpy_s(_nombre, Nombre.c_str());
}

void DetalleVenta::setId_Producto(int ID)
{
	id_producto = ID;
}

void DetalleVenta::setId_Categoria(int ID)
{
	id_categoria = ID;
}

void DetalleVenta::setPrecio(float nPrecio)
{
	precio = nPrecio;
}

void DetalleVenta::setPrecioCompra(float precio_compra)
{
	this->precio_compra = precio_compra;
}

void DetalleVenta::setCantidad(int can)
{
	this->cantidad = can;
}

int DetalleVenta::getCantidad()
{
	return cantidad;
}

float DetalleVenta::getPrecioCompra()
{
	return precio_compra;
}

string DetalleVenta::getNombre()
{
	return _nombre;
}

int DetalleVenta::getId_Categoria()
{
	return id_categoria;
}

int DetalleVenta::getId_Producto()
{
	return id_producto;
}

float DetalleVenta::getPrecio()
{
	return precio;
}