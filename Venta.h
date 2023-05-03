#pragma once
#include <iostream>
#include <string>
#include "Cliente.h"
#include "Producto.h"
#include "Fecha.h"
using namespace std;
class Venta
{
private:
	int id;
	Producto producto;
	int cantidad;
	float precio;
	float total;
	bool estado;
	Fecha fecha;
	Cliente cliente;

public:
	Venta();

	void setIdCliente(Cliente);
	void setId(int);
	void setProducto(Producto);
	void setCantidad(int);
	void setPrecio(float);
	void setTotal(float);
	void setEstado(bool);
	void setFecha(Fecha);

	int getId();
	Cliente getIdCliente();
	Producto getProducto();
	int getCantidad();
	float getPrecio();
	float getTotal();
	bool getEstado();
	Fecha getFecha();
	void cargar();
	void mostrar();
	

};

