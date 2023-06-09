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
	int id_producto;
	int cantidad;
	float precio;
	float total;
	bool estado;
	Fecha fecha;
	int idCliente;
	int tipoPago;
	int idVendedor;
	int entrega;
	float ganancia;
public:
	//sets
	Venta();
	void setGanancia(float);
	void setIdCliente(int id);
	void setId(int);
	void setProducto(int );
	void setCantidad(int);
	void setPrecio(float);
	void setTotal(float);
	void setEstado(bool);
	void setFecha(int,int,int);
	void setTipoPago(int);
	void setIdVendedor(int);
	void setEntrega(int);

	//gets
	float getGanancia();
	int getEntrega();
	int getId();
	int getIdCliente();
	int getProducto();
	int getCantidad();
	float getPrecio();
	float getTotal();
	bool getEstado();
	Fecha getFecha();
	int getTipoPago();
	int getIdVendedor();
	void cargar();
	void mostrar();
	
	

};

