#include "Archivo_Cliente.h"
#include "Archivo_Producto.h"
#include "Archivo_Venta.h"
#include "Archivo_Vendedor.h"
#include "Menu.h"
#include "rlutil.h"


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

DetalleVenta Venta::getDetalle(int i)
{
	return detalles[i];
}

int Venta::getNumerodetalles()
{
	return numeroDetalles;
}
void Venta::cargar()
{
	archivo_producto archivoProducto;
	Producto producto;
	Archivo_Cliente archivoCliente;
	Archivo_Vendedor archivoVendedor;
	int cantClientes = archivoCliente.cantidad_clientes();
	int cantProd = archivoProducto.cantidad_de_registros();
	int idProducto, idCliente, idVendedor;
	int cantVendedores = archivoVendedor.Cantidad_vendedores();
	int cantidad = 0;
	int cantidadT = 0;
	float precio = 0;
	float precioCompra = 0;
	float total = 0;
	float totalCompra = 0;
	float ganancia = 0;
	numeroDetalles = 0;

	cout << endl;
	cout << "-------------------------------" << endl;
	cout << "* Ingrese la fecha" << endl;
	fecha.Cargar();
	cout << "-------------------------------" << endl;

	system("cls");
	archivoVendedor.Listar_Vendedor(cantVendedores);
	string input1;
	bool esNumero = false;
	bool cumpleCondicion = false;
	cout << "* Ingrese el ID del vendedor que lo asistio: ";
	getline(cin, input1);

	while (!esNumero || !cumpleCondicion) {
		bool todosDigitos = true;
		for (char c : input1) {
			if (!isdigit(c)) {
				todosDigitos = false;
				break;
			}
		}

		if (!todosDigitos) {
			rlutil::setColor(rlutil::RED);
			cout << "El ID debe ser un valor numerico. Ingrese nuevamente: ";
			rlutil::setColor(rlutil::BLACK);
			getline(cin, input1);
			continue;
		}

		int num = stoi(input1);
		if (num > 0 && archivoVendedor.ExisteVendedor(num)) {
			esNumero = true;
			cumpleCondicion = true;
		}
		else {
			rlutil::setColor(rlutil::RED);
			cout << "El ID debe ser mayor a 0 y debe existir: ";
			rlutil::setColor(rlutil::BLACK);
			getline(cin, input1);
		}
	}
	idVendedor = stoi(input1);

	system("cls");

	archivoCliente.listar_clientes(cantClientes);
	string input2;
	esNumero = false;
	cumpleCondicion = false;
	cout << "* Ingrese el ID del cliente que realiza la compra: ";
	getline(cin, input2);

	while (!esNumero || !cumpleCondicion) {
		bool todosDigitos = true;
		for (char c : input2) {
			if (!isdigit(c)) {
				todosDigitos = false;
				break;
			}
		}

		if (!todosDigitos) {
			rlutil::setColor(rlutil::RED);
			cout << "El ID debe ser un valor numerico. Ingrese nuevamente: ";
			rlutil::setColor(rlutil::BLACK);
			getline(cin, input2);
			continue;
		}

		int num2 = stoi(input2);
		if (num2 > 0 && archivoCliente.ExisteCliente(num2)) {
			esNumero = true;
			cumpleCondicion = true;
		}
		else {
			rlutil::setColor(rlutil::RED);
			cout << "El ID debe ser mayor a 0 y debe existir: ";
			rlutil::setColor(rlutil::BLACK);
			getline(cin, input2);
		}
	}

	idCliente = stoi(input2);
	system("cls");

	int cantDet;
	string input3;
	esNumero = false;
	cumpleCondicion = false;
	cout << "Ingrese cantidad de productos diferentes que va a adquirir: ";
	getline(cin, input3);

	while (!esNumero || !cumpleCondicion) {
		bool todosDigitos = true;
		for (char c : input3) {
			if (!isdigit(c)) {
				todosDigitos = false;
				break;
			}
		}

		if (!todosDigitos) {
			rlutil::setColor(rlutil::RED);
			cout << "La cantidad debe ser un valor numerico. Ingrese nuevamente: ";
			rlutil::setColor(rlutil::BLACK);
			getline(cin, input3);
			continue;
		}

		int num3 = stoi(input3);
		if (num3 > 0 && num3 <= cantProd) {
			esNumero = true;
			cumpleCondicion = true;
		}
		else {
			rlutil::setColor(rlutil::RED);
			cout << "La cantidad debe ser mayor a 0 y menor a la cantidad de productos: ";
			rlutil::setColor(rlutil::BLACK);
			getline(cin, input3);
		}
	}

	cantDet = stoi(input3);
	///////////////// EMPIEZA LA CARGA DE VARIOS PRODUCTOS

	for (int i = 0; i < cantDet; i++) {
		if (archivoProducto.Stock_total() <= 0) {
			rlutil::setColor(rlutil::RED);
			cout << "No quedo stock de ningun producto" << endl;
			rlutil::setColor(rlutil::BLACK);
			system("pause");
			system("cls");
			continue;
		}
		archivoProducto.listar(cantProd);
		cout << "* Ingrese el ID del producto que desea comprar: ";
		cin >> idProducto;
		int pos = archivoProducto.PosicionEnDisco(idProducto);
		producto = archivoProducto.leer_de_disco(pos);

		while (!archivoProducto.Existe(idProducto) || (producto.getStock() <= 0))
		{
			rlutil::setColor(rlutil::RED);
			cout << "El ID ingresado no es valido, no existe o falta stock" << endl;
			rlutil::setColor(rlutil::BLACK);
			cout << "* Ingrese el ID del producto que desea comprar: ";
			cin >> idProducto;
			pos = archivoProducto.PosicionEnDisco(idProducto);
			producto = archivoProducto.leer_de_disco(pos);
		}
	
		cout << "* Ingrese la cantidad que desea comprar: ";
		cin >> cantidad;
		while (cantidad < 0 || cantidad == 0 || producto.getStock() < cantidad)
		{
			rlutil::setColor(rlutil::RED);
			cout << "ingrese una cantidad valida, mayor a 0 y mayor o igual a el stock: ";
			rlutil::setColor(rlutil::BLACK);
			cin >> cantidad;
		}

		if ((producto.getStock() - cantidad) < 10)
		{
			cout << "*********************************************************" << endl;
			cout << "** Quedan menos de 10 unidades del producto seleccionado **" << endl;
			cout << "*********************************************************" << endl;
			system("pause");
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
		precioCompra = producto.getPrecioCompra();
		total += precio * cantidad;
		totalCompra += precioCompra * cantidad;
		cantidadT += cantidad;
		system("cls");
	}
	
		
	///////////////// TERMINA LA CARGA DE VARIOS PRODUCTOS
		rlutil::setColor(rlutil::BLACK);
		ganancia = total - totalCompra;
		int tipoEntrega;
		string input4;
		esNumero = false;
		cumpleCondicion = false;
		cout << "* 1- Retiro del local  //  2 - Entrega a domicilio: ";
		cin.ignore();
		getline(cin, input4);

		while (!esNumero || !cumpleCondicion) {
			bool todosDigitos = true;
			for (char c : input4) {
				if (!isdigit(c)) {
					todosDigitos = false;
					break;
				}
			}

			if (!todosDigitos) {
				rlutil::setColor(rlutil::RED);
				cout << "El tipo de entrega debe ser un valor numerico. Ingrese nuevamente: ";
				rlutil::setColor(rlutil::BLACK);
				getline(cin, input4);
				continue;
			}

			int num4 = stoi(input4);
			if (num4 == 1 || num4 == 2) {
				esNumero = true;
				cumpleCondicion = true;
			}
			else {
				rlutil::setColor(rlutil::RED);
				cout << "El tipo de entrega debe ser 1(Retiro del local) o 2(Entrega a domicilio): ";
				rlutil::setColor(rlutil::BLACK);
				getline(cin, input4);
			}
		}
		tipoEntrega = stoi(input4);
		if (tipoEntrega == 2)
		{
			cout << "El envio cuesta $200" << endl;
			total = total + 200;
			system("pause");
		}
		else if (tipoEntrega == 1) {
			cout << "Retiro en local, no hay costo de envio" << endl;
			system("pause");
		}

		setGanancia(ganancia);
		setEntrega(tipoEntrega);
		setIdVendedor(idVendedor);
		setIdCliente(idCliente);
		setProducto(idProducto);
		setPrecio(precio);
		setTotal(total);
		setCantidad(cantidadT);
	
	cout << "Se cargo la venta exitosamente..." << endl;
	cout << "-------------------------------------------------------------" << endl << endl;
	}


void Venta::mostrar()
{
	Archivo_Vendedor vendedor;
	Vendedor vende;
	Archivo_Cliente cliente;
	Cliente clie;
	int cantC = cliente.cantidad_clientes();
	int cantV = vendedor.Cantidad_vendedores();

	cout << "****************************************** " << endl;
	cout << "Fecha: " << getFecha().toString() << endl;
	for (int i = 0; i < cantV; i++)
	{
		vende = vendedor.Leer_vendedores(i);
		if (getIdVendedor() == vende.getId_Vendedor())
		{
			cout << "ID de Vendedor: " << getIdVendedor() << "  " << "Nombre: " << vende.getNombre() << endl;
		}
	}

	for (int i = 0; i < cantC; i++)
	{
		clie = cliente.leer_clientes(i);
		if (getIdCliente() == clie.getId_Cliente())
		{
			cout << "ID de Cliente: " << getIdCliente() << "  " << "Nombre: " << clie.getNombre() << endl;
		}
	}
	cout << "ID de Venta: " << getId() << endl;
	cout << "Cantidad de productos: " << getCantidad() << endl;
	
	for (int i = 0; i < numeroDetalles; i++) {
	cout << "-" << endl;
	DetalleVenta detalle = detalles[i];
	cout << detalle.getCantidad()<<" unidades de " <<" " << detalle.getNombre() << endl;
	cout << detalle.getNombre() <<" ID: " << detalle.getId_Producto() << endl;
	cout <<"Categoria " << detalle.getNombre() <<": " << detalle.getId_Categoria() << endl;
	cout << "Precio: $" << detalle.getPrecio() << endl;
	cout << "Precio compra: $" << detalle.getPrecioCompra() << endl;
	}
	cout << "-" << endl;
	
	if (getEntrega() == 2)
	{
		cout << "ENTREGA A DOMICILIO $200" << endl;
	}else if (getEntrega() == 1)
	{
		cout << "RETIRA DEL LOCAL (sin costo)" <<endl;
	}
	cout << "Total a Pagar por el cliente: $" << getTotal() << endl;
	cout << "Ganancia total de la cafeteria: $" << getGanancia() << endl;
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

void Venta::setIdVendedor(int vendedor)
{
	this->idVendedor = vendedor;
}

int Venta::getIdVendedor()
{
	return idVendedor;
}
