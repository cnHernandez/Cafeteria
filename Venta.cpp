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
#include <vector>
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

void Venta::setIdCliente(Cliente cliente)
{
	this->cliente = cliente;
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
	int cantven=venta.cantidad_ventas();
	int cantProd = archivo.cantidad_de_registros();
	
	Cliente cliente;
	int id, idCliente, idVendedor;
	int cantidad;
	float precio;
	float total=0;
	float totalFinal = 0;
	float aumento;
	float descuento;
	int tipoPago = 0;
	int dia, mes, anio;
	int cant = archivo.cantidad_de_registros();
	std::cout << endl;
	std::cout << "-------------------------------------------------------------" << endl;
	std::cout << "* Ingrese la fecha" << std::endl;
	fecha.Cargar();

	std::cout << "* Ingrese el ID del vendedor que lo asistio: ";
	std::cin >> idVendedor;
	while (idVendedor <= 0 || idVendedor > 4)
	{
		std::cout << "El ID ingresado no existe" << std::endl;
		std::cout << "* Ingrese el ID del vendedor que lo asistio: ";
		std::cin >> idVendedor;
	}
	std::cout << "* Ingrese el ID del cliente que realiza la compra: ";
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
		std::cout << "* Ingrese el ID del cliente que realiza la comprar: ";
		std::cin >> idCliente;
	}
	cliente = archivoCliente.leer_clientes(idCliente - 1);
	std::cout << "* Ingrese el ID del producto que desea comprar: ";
	std::cin >> id;
	while (id <= 0 || id > cant)
	{
		std::cout << "El ID ingresado no existe" << std::endl;
		std::cout << "* Ingrese el ID del producto que desea comprar: " ;
		std::cin >> id;
	}
	int opcion;
	producto = archivo.leer_de_disco(id - 1);
	
	std::cout << "* Ingrese la cantidad que desea comprar: ";
	std::cin >> cantidad;
	
	precio = producto.getPrecio();
	total = precio * cantidad;
	
	std::cout << "* 1- Efectivo 5 % Descuento  //  2 - Tarjeta 8 % Aumento: " ;
	std::cin >> tipoPago;
	float porcentajeEfectivo = 0.05;
	float porcentajeTarjeta = 0.08;
		if (tipoPago != 1 && tipoPago != 2)
		{
			std::cout << "Opcion incorrecta" << std::endl;
			std::cout << "1- Efectivo 5 % Descuento" << std::endl;
			std::cout << "2- Tarjeta 8 % Aumento: " ;
			std::cin >> tipoPago;
		}
		descuento  = total * porcentajeEfectivo;
		aumento = total * porcentajeTarjeta;
		if (tipoPago == 1)
		{
			totalFinal = total - descuento;
		}
		else if (tipoPago == 2)
		{
			totalFinal = total + aumento;
		}
		//std::cout << "Ingrese la forma de entrega" << std::endl;
		std::cout << "* 1- Retiro del local  //  2 - Entrega a domicilio: ";
		int tipoEntrega;
		cin >> tipoEntrega;
		if (tipoEntrega != 1 && tipoEntrega != 2)
		{
			std::cout << "Opcion incorrecta" << std::endl;
			std::cout << "Ingrese la forma de entrega" << std::endl;
			std::cout << "1- Retiro del local  //  2 - Entrega a domicilio " << endl;
			cin >> tipoEntrega;
		}
		if (tipoEntrega == 2)
		{
			cout<<"El envio cuesta $200"<<endl;
			totalFinal = totalFinal + 200;
		}
		else if (tipoEntrega == 1) {
			cout << "Retiro en local, no hay costo de envio" << endl;
		
		}
		
	setEntrega(tipoEntrega);
	setIdVendedor(idVendedor);
	setTipoPago(tipoPago);
	setIdCliente(cliente);
	setProducto(producto);
	setCantidad(cantidad);
	setPrecio(precio);
	setTotal(totalFinal);
	cout << "Se cargo la venta exitosamente..." << endl;
	cout << "-------------------------------------------------------------" << endl << endl;
	}


void Venta::mostrar()
{
	
		std::cout << "****************************************** " << std::endl;
		std::cout << "Fecha: " << getFecha().toString() << std::endl;
		std::cout << "ID de Vendedor: " << getIdVendedor() << std::endl;
		std::cout << "ID de Cliente: " << getIdCliente().getId_Cliente() << std::endl;
		std::cout << "ID de Venta: " << getId() << std::endl;
		std::cout << "Cantidad: " << getCantidad() << std::endl;
		std::cout << "Producto: " << getProducto().getNombre() << std::endl;
		std::cout << "Precio: " << getPrecio() << std::endl;
		
	
	if (getIdVendedor() == 1)
	{
		std::cout <<"Nombre del vendedor : Juan" << std::endl;
	}
	if (getIdVendedor() == 2)
	{
		std::cout << "Nombre del vendedor : Pedro" << std::endl;
	}
	if (getIdVendedor() == 3)
	{
		std::cout << "Nombre del vendedor : Romina" << std::endl;
	}
	if (getIdVendedor() == 4)
	{
		std::cout <<"Nombre del vendedor : Carla" << std::endl;
	}

	if (getTipoPago() == 1)
	{
		std::cout << "Tipo de Pago: " << "EFECTIVO  5 % DESCUENTO" << std::endl;
	}
	else if (getTipoPago() == 2)
	{
		std::cout << "Tipo de Pago: " << "TARJETA  8 % AUMENTO" << std::endl;
	}
	if (getEntrega() == 2)
	{
		std::cout << "ENTREGA A DOMICILIO" << std::endl;
	}
	if (getEntrega() == 1)
	{
		std::cout << "RETIRA DEL LOCAL" << std::endl;
	}
	std::cout << "Total a Pagar: " << getTotal() << std::endl;
	std::cout << "****************************************** " << std::endl;
}

Cliente Venta::getIdCliente()
{
	return cliente;
}
void Venta::setEntrega(int tipoEntrega)
{
	this-> entrega = tipoEntrega;
}
int Venta::getEntrega()
{
	return entrega;

}
void Venta::setTipoPago(int tipoPago)
{
	this->tipoPago = tipoPago;
}

int Venta::getTipoPago()
{
	return tipoPago;
	
}

void Venta::setIdVendedor(int vendedor)
{
	this->idVendedor = vendedor;
}

int Venta::getIdVendedor()
{
	return idVendedor;
}







