#include "Venta.h"
#include <iostream>
#include "Cliente.h"
#include "Producto.h"
#include "Archivo_Cliente.h"
#include "archivo_producto.h"
#include "Archivo_Venta.h"
#include "Fecha.h"
#include "Menu.h"
#include "Vendedor.h"
#include "Archivo_Vendedor.h"

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

void Venta::setIdCliente(int cliente)
{
	this->idCliente = cliente;
}

void Venta::setProducto(int producto)
{
	this->id_producto = producto;
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

void Venta::setGanancia(float ganancia)
{
	this->ganancia = ganancia;
}

float Venta::getGanancia()
{
	return ganancia;
}
Fecha Venta::getFecha()
{
	return fecha;
}
int Venta::getId()
{
	return id;
}

int Venta::getProducto()
{
	return id_producto;
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
	archivo_producto archivoProducto;
	Producto producto;
	Archivo_Cliente archivoCliente;
	Cliente cliente;
	Archivo_Venta venta;
	Archivo_Vendedor archivoVendedor;
	Vendedor vend;
	int cantClientes = archivoCliente.cantidad_clientes();
	int cantven = venta.cantidad_ventas();
	int cantProd = archivoProducto.cantidad_de_registros();
	int idProducto, idCliente, idVendedor;
	int cantVendedores = archivoVendedor.Cantidad_vendedores();
	int cantidad;
	int cantidadT = 0;
	float precio;
	float total = 0;
	float totalFinal = 0;
	float aumento;
	float descuento;
	int tipoPago;
	float ganancia = 0;
	int cant = archivoProducto.cantidad_de_registros();
	numeroDetalles = 0;

	cout << endl;
	cout << "-------------------------------" << endl;
	cout << "* Ingrese la fecha" << endl;
	fecha.Cargar();
	cout << "-------------------------------" << endl;

	archivoVendedor.Listar_Vendedor(cantVendedores);
	cout << "* Ingrese el ID del vendedor que lo asistio: ";
	cin >> idVendedor;
	while (idVendedor <= 0 || !archivoVendedor.ExisteVendedor(idVendedor))
	{
		cout << "El ID ingresado no existe" << endl;
		cout << "* Ingrese el ID del vendedor que lo asistio: ";
		cin >> idVendedor;
	}
	system("cls");
	while (archivoCliente.cantidad_clientes() == 0)
	{
		string desicion;
		cout << "No hay clientes cargados" << endl;
		cout << "�Desea cargar uno? (S/N)" << endl;
		cin >> desicion;
		if (desicion == "S" || desicion == "s")
		{
			cliente.Cargar();
			archivoCliente.guardar(cliente);
		}
		else if (desicion == "N" || desicion == "n")
		{
			return;
		}
		else
		{
			cout << "Opcion incorrecta" << endl;
			cout << "�Desea cargar uno? (S/N)" << endl;
			cin >> desicion;
		}
	}
	system("cls");
	archivoCliente.listar_clientes(cantClientes);
	cout << "* Ingrese el ID del cliente que realiza la compra: ";
	cin >> idCliente;
	while (!archivoCliente.ExisteCliente(idCliente))
	{
		cout << "El ID ingresado no existe" << endl;
		cout << "* Ingrese el ID del cliente que realiza la comprar: ";
		cin >> idCliente;
	}
	cliente = archivoCliente.leer_clientes(idCliente - 1);
	system("cls");


	///////////////// EMPIEZA LA CARGA DE VARIOS PRODUCTOS
	int cantDet;
	cout << "Ingrese cantidad de productos: ";
	cin >> cantDet;

	for (int i = 0; i < cantDet; i++) {

		archivoProducto.listar(cantProd);
		cout << "* Ingrese el ID del producto que desea comprar: ";
		cin >> idProducto;
		while (!archivoProducto.Existe(idProducto))
		{
			cout << "El ID ingresado no existe" << endl;
			cout << "* Ingrese el ID del producto que desea comprar: ";
			cin >> idProducto;
		}
		int pos = archivoProducto.PosicionEnDisco(idProducto);
		producto = archivoProducto.leer_de_disco(pos);

		cout << "* Ingrese la cantidad que desea comprar: ";
		cin >> cantidad;
		if (cantidad < 0)
		{
			cout << "ingrese una cantidad valida" << endl;
			cout << "* Ingrese la cantidad que desea comprar: ";
			cin >> cantidad;
		}

		if (producto.getStock() == 0 || producto.getStock() < cantidad) {
			cout << "* No hay stock suficiente" << endl;
			cout << "* Quiere ingresar un ID de un producto nuevo?: ";
			cin >> idProducto;
			while (!archivoProducto.Existe(idProducto)) {
				cout << "* El producto no existe..., ingrese uno nuevo: ";
				cin >> idProducto;
			}
			cout << "* Ingrese la cantidad que desea comprar: ";
			cin >> cantidad;
			pos = archivoProducto.PosicionEnDisco(idProducto);
			producto = archivoProducto.leer_de_disco(pos);
			if (cantidad > producto.getStock()) {
				cout << "ingrese una cantidad valida: ";
				cin >> cantidad;
				if (cantidad > producto.getStock() || producto.getStock() == 0 || !archivoProducto.Existe(idProducto)) {
					system("cls");
					cout << "COMPRA CANCELADA POR FALTA DE STOCK" << endl;
					exit(-1);
				}
			}
		}
		producto = archivoProducto.leer_de_disco(pos);
		producto.setStock(producto.getStock() - cantidad);
		archivoProducto.guardar(producto, pos);

		DetalleVenta detalle;
		detalle.setId_Categoria(producto.getId_Categoria());
		detalle.setId_Producto(producto.getId_Producto());
		detalle.setNombre(producto.getNombre());
		detalle.setPrecio(producto.getPrecio());
		detalle.setPrecioCompra(producto.getPrecioCompra());
		detalle.setCantidad(cantidad);

		detalles[numeroDetalles] = detalle;
		numeroDetalles++;
		precio = producto.getPrecio();
		total += precio * cantidad;
		cantidadT += cantidad;
		system("cls");
	}
		
	///////////////// TERMINA LA CARGA DE VARIOS PRODUCTOS

		cout << "* 1- Efectivo 5 % Descuento  //  2 - Tarjeta 8 % Aumento: ";
		cin >> tipoPago;
		float porcentajeEfectivo = 0.05;
		float porcentajeTarjeta = 0.08;
		if (tipoPago != 1 && tipoPago != 2)
		{
			cout << "Opcion incorrecta" << endl;
			cout << "1- Efectivo 5 % Descuento ";
			cout << "2- Tarjeta 8 % Aumento: ";
			cin >> tipoPago;
		}
		descuento = total * porcentajeEfectivo;
		aumento = total * porcentajeTarjeta;
		if (tipoPago == 1)
		{
			totalFinal = total - descuento;
			ganancia = totalFinal - producto.getPrecioCompra() * cantidad;
		}
		else if (tipoPago == 2)
		{
			totalFinal = total + aumento;
			ganancia = total - producto.getPrecioCompra() * cantidad;
		}

		cout << "* 1- Retiro del local  //  2 - Entrega a domicilio: ";
		int tipoEntrega;
		cin >> tipoEntrega;
		if (tipoEntrega != 1 && tipoEntrega != 2)
		{
			cout << "Opcion incorrecta" << endl;
			cout << "Ingrese la forma de entrega" << endl;
			cout << "1- Retiro del local  //  2 - Entrega a domicilio ";
			cin >> tipoEntrega;
		}
		if (tipoEntrega == 2)
		{
			cout << "El envio cuesta $200" << endl;
			totalFinal = totalFinal + 200;
			ganancia = total - producto.getPrecioCompra() * cantidad;
		}
		else if (tipoEntrega == 1) {
			cout << "Retiro en local, no hay costo de envio" << endl;
			ganancia = totalFinal - producto.getPrecioCompra() * cantidad;

		}

		setGanancia(ganancia);
		setEntrega(tipoEntrega);
		setIdVendedor(idVendedor);
		setTipoPago(tipoPago);
		setIdCliente(idCliente);
		setProducto(idProducto);
		setPrecio(precio);
		setTotal(totalFinal);
		setCantidad(cantidadT);
	
	cout << "Se cargo la venta exitosamente..." << endl;
	cout << "-------------------------------------------------------------" << endl << endl;
	}


void Venta::mostrar()
{
	Archivo_Vendedor vendedor;
	Vendedor vende;
	int cant = vendedor.Cantidad_vendedores();
	Archivo_Cliente cliente;
	Cliente cli;
	int cantClientes = cliente.cantidad_clientes();
	archivo_producto archivo;
	Producto producto;
	int cantProd = archivo.cantidad_de_registros();


	cout << "****************************************** " << endl;
	cout << "Fecha: " << getFecha().toString() << endl;
	for (int i = 0; i < cant; i++)
	{
		vende = vendedor.Leer_vendedores(i);
		if (getIdVendedor() == vende.getId_Vendedor())
		{
			cout << "ID de Vendedor: " << getIdVendedor() << "  " << "Nombre: " << vende.getNombre() << endl;
		}
	}
	for (int i = 0; i < cantClientes; i++) 
	{
		cli = cliente.leer_clientes(i);
		if(getIdCliente()==cli.getId_Cliente())
		cout << "ID de Cliente: " << cli.getId_Cliente() << endl;
     }
	cout << "ID de Venta: " << getId() << endl;
	cout << "Cantidad de productos: " << getCantidad() << endl;
	cout << "*******************************************" << endl;
	
	for (int i = 0; i < numeroDetalles; i++) {
	DetalleVenta detalle = detalles[i];
	cout << detalle.getCantidad()<<"x " << detalle.getNombre() << endl;
	cout << detalle.getNombre() <<" ID: " << detalle.getId_Producto() << endl;
	cout <<"Categoria " << detalle.getNombre() <<": " << detalle.getId_Categoria() << endl;
	cout << "Precio: " << detalle.getPrecio() << endl;
	cout << "Precio compra: " << detalle.getPrecioCompra() << endl;
	cout << "*******************************************" << endl;
	}
		
	
	if (getTipoPago() == 1)
	{
		cout << "Tipo de Pago: " << "EFECTIVO  5 % DESCUENTO" <<endl;
	}
	else if (getTipoPago() == 2)
	{
		cout << "Tipo de Pago: " << "TARJETA  8 % AUMENTO" << endl;
	}
	if (getEntrega() == 2)
	{
		cout << "ENTREGA A DOMICILIO" << endl;
	}else if (getEntrega() == 1)
	{
		cout << "RETIRA DEL LOCAL" <<endl;
	}
	cout << "Total a Pagar por el cliente: " << getTotal() << endl;
	cout << "Ganancia total de la cafeteria: " << getGanancia() << endl;
	cout << "****************************************** " << endl;
}

int Venta::getIdCliente()
{
	return idCliente;
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
