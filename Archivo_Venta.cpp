#include "Archivo_Venta.h"
#include "Venta.h"
#include "Archivo_Categoria.h"
#include "Archivo_Producto.h"
#include "Archivo_Cliente.h"
#include "archivo_Vendedor.h"
#include "Vendedor.h"
#include "Cliente.h"
#include <iostream>
#include <string>
#include <iomanip>

using namespace std;

bool Archivo_Venta::guardarEnDisco(int cantidad_ventas)
{
	bool guardo;
	FILE *p;
	p = fopen("Ventas.dat", "wb");
	if (p == NULL)
	{
		cout << "Error al abrir el archivo" << endl;
		return false;
	}
	guardo = fwrite(this, sizeof(Archivo_Venta), cantidad_ventas, p);
	fclose(p);
	return guardo;
}
void Archivo_Venta::obtener_venta(Venta* venta, int cant)
{
	FILE* p;
	p = fopen("Ventas.dat", "rb");
	if (p == NULL)
	{
		cout << "Error al abrir el archivo" << endl;
		return;
	}
	fread(venta, sizeof(Venta), cant, p);
	fclose(p);
}


void Archivo_Venta::guardar(Venta venta)
{
	FILE* pFile;
	pFile = fopen("Ventas.dat", "ab");
	if (pFile == nullptr) {
		cout << "No se pudo abrir el archivo" << endl;
		return;
	}
	fwrite(&venta, sizeof(Venta), 1, pFile);
	fclose(pFile);
}

Venta Archivo_Venta::leer_ventas(int pos)
{
	Venta ventas;
	FILE* p;
	p = fopen("Ventas.dat", "rb");
	if (p == nullptr) {
		cout << "Error al abrir el archivo" << endl;
		return ventas;
	}
	fseek(p, pos * sizeof(Venta), SEEK_SET);
	fread(&ventas, sizeof(Venta), 1, p);
	fclose(p);
	return ventas;
}

Venta Archivo_Venta::leer_ventaBK(Venta * vec, int pos)
{
	Venta ventas;
		FILE* p = fopen("ventas.dat", "rb");
		if (p == NULL)
		{
			cout << "Error al abrir el archivo" << endl;;
			return ventas;
		}
		fread(vec, sizeof(Venta),pos, p);
		fclose(p);
	return ventas;
}

bool Archivo_Venta::guardar_bkp(Venta* vec, int cantidad)
{
	FILE* p = fopen("ventas.dat", "ab");
	if (p == NULL)
	{
		return false;
	}

	int cantidadRegistrosEscritos = fwrite(vec, sizeof(Venta), cantidad, p);
	fclose(p);
	return cantidadRegistrosEscritos == cantidad;
}

int Archivo_Venta::get_cantidad_Activa(int pos)
{
	int contador = 0;

	for (int i = 0; i < pos; i++)
	{
		Venta ventas;
		ventas = leer_ventas(i);
		if (ventas.getEstado())
		{
			contador++;
		}
	}
	return contador;
}

void Archivo_Venta::listar_ventas(int pos)
{
	Venta venta;
	for (int i = 0; i < pos; i++) {
		venta = leer_ventas(i);
		if (venta.getEstado()== true) {
		venta.mostrar();
		cout << endl << endl;
		}
	}
}	


int Archivo_Venta::cantidad_ventas()
{
	FILE* pFile;
	int cantidad = 0;
	pFile = fopen("Ventas.dat", "rb");
	if (pFile == nullptr)
	{
		return 0;
	}
	fseek(pFile, 0, SEEK_END);
	cantidad = ftell(pFile) / sizeof(Venta);
	fclose(pFile);
	return cantidad;
}

void Archivo_Venta::listar_x_cliente()
{
	int cant = cantidad_ventas();
	
	Archivo_Cliente Clientes;

	int cantClientes = Clientes.cantidad_clientes();
	Clientes.listar_clientes(cantClientes);
	
	Venta* ventas = new Venta[cant];
	if (ventas == nullptr) {
		cout << "ERROR CON LA MEMORIA DINAMICA" << endl;
		return;
	}

	obtener_venta(ventas, cant);
	Cliente cliente;
	int idCliente;
	cout << "ingrese el ID# del cliente a listar: " << endl;
	cin >> idCliente;
	while (idCliente <= 0 || idCliente > cant)
	{
		cout << "ID# de cliente invalido: " << endl;
		cout << "ingrese el ID# del cliente a listar: " << endl;
		cin >> idCliente;
	}
	cliente=Clientes.leer_clientes(idCliente - 1);
	while(cliente.getEstado()!= true)
	{
		cout << "ID# de cliente invalido: " << endl;
		cout << "ingrese el ID# del cliente a listar: " << endl;
		cin >> idCliente;
		cliente = Clientes.leer_clientes(idCliente - 1);

	}
	system("cls");
	for (int i = 0; i < cantClientes; i++)
	{
		cliente = Clientes.leer_clientes(i);
		if (idCliente == cliente.getId_Cliente())
		{
			cout << "Productos con ID# de Cliente: " << idCliente << "  " << "NOMBRE: " << cliente.getNombre() << endl;
		}
	}
	cout << "Productos con ID# de Cliente: " << idCliente << endl << endl;
	while (idCliente<0 || idCliente>cantClientes)
	{
		cout << "ID# de cliente no posee compras " << endl;
		cout << "ingrese otro ID# del cliente a listar: " << endl;
		cin >> idCliente;
		cliente = Clientes.leer_clientes(idCliente - 1);
	}
	for (int j = 0; j < cantClientes; j++)
	{

		for (int i = 0; i < cant; i++)
		{

			if (idCliente == ventas[i].getIdCliente() && ventas[i].getEstado() && ventas[i].getIdCliente())
			{
				ventas[i].mostrar();
			}

		}
	}
	cout << endl;

	delete[] ventas;
}

void Archivo_Venta::listar_x_fecha()
{
	int cant = cantidad_ventas();
	Venta* ventas = new Venta[cant];
	if (ventas == nullptr) {
		cout << "ERROR CON LA MEMORIA DINAMICA" << endl;
		return;
	}
	obtener_venta(ventas, cant);
	int dia, mes, anio;
	int op;
	bool menu_activo = true;
	while (menu_activo)
	{
		system("cls");
		cout << "---Fecha de Ventas----" << endl << endl;
		cout << " 1- Mes" << endl;
		cout << " 2- Anio" << endl;
		cout << " 3- Recaudacion anual" << endl;
		cout << "-----------------" << endl;
		cout << " 0- SALIR" << endl;
		cout << "-----------------" << endl;
		cin >> op;
		while (op < 0 || op>3)
		{
			cout << "opcion incorrecta, vuelva a ingresar una opcion" << endl;
			cin >> op;
		}
		switch (op)
		{
		case 0:
		{
			menu_activo = false;
		}
		break;
		case 1:
		{
			cout << "ingrese el Mes a listar: ";
			cin >> mes;
			while (mes < 1 || mes > 12)
			{
				cout << "Mes invalido" << endl;
				cout << "ingrese el Mes a listar: ";
				cin >> mes;
			}
			cout << "Ventas con mes: " << mes << endl;
			system("cls");
			for (int i = 0; i < cant; i++)
			{
				if (mes == ventas[i].getFecha().getMes() && ventas[i].getEstado())
				{
					ventas[i].mostrar();
				}
			}
			system("pause");
			cout << endl;
		}
		break;
		case 2:
		{
			cout << "ingrese el anio a listar" << endl;
			cin >> anio;
			while (anio < 2016)
			{
				cout << "Anio invalido" << endl;
				cout << "ingrese el Anio a listar: ";
				cin >> anio;
			}
			system("cls");
			cout << "          VENTAS CON ANIO " << anio << endl << endl;
			for (int i = 0; i < cant; i++)
			{
				if (anio == ventas[i].getFecha().getAnio() && ventas[i].getEstado())
				{
					ventas[i].mostrar();
				}
			}
			system("pause");

		}
		break;
		case 3:
		{
			cout << "ingrese el anio a listar" << endl;
			cin >> anio;
			while (anio < 2016)
			{
				cout << "Anio invalido" << endl;
			    cout << "ingrese el Anio a listar: ";
				cin >> anio;
			}
			float total = 0;
			for (int i = 0; i < cant; i++)
			{
				if (anio == ventas[i].getFecha().getAnio() && ventas[i].getEstado())
				{
					total += ventas[i].getTotal();
				}
			}
			string mes[12] = { "Enero","Febrero","Marzo","Abril","Mayo","Junio","Julio","Agosto","Septiembre","Octubre","Noviembre","Diciembre"
			};
			
			float ventasMensuales[12] = {};
			for (int i = 0; i < cant; i++)
			{
				if (anio == ventas[i].getFecha().getAnio() && ventas[i].getEstado())
				{
					if (ventas[i].getFecha().getMes() == 1)
					{
						ventasMensuales[0] += ventas[i].getTotal();
					}
					else if (ventas[i].getFecha().getMes() == 2)
					{
						ventasMensuales[1] += ventas[i].getTotal();
					}
					else if (ventas[i].getFecha().getMes() == 3)
					{
						ventasMensuales[2] += ventas[i].getTotal();
					}
					else if (ventas[i].getFecha().getMes() == 4)
					{
						ventasMensuales[3] += ventas[i].getTotal();
					}
					else if (ventas[i].getFecha().getMes() == 5)
					{
						ventasMensuales[4] += ventas[i].getTotal();
					}
					else if (ventas[i].getFecha().getMes() == 6)
					{
						ventasMensuales[5] += ventas[i].getTotal();
					}
					else if (ventas[i].getFecha().getMes() == 7)
					{
						ventasMensuales[6] += ventas[i].getTotal();
					}
					else if (ventas[i].getFecha().getMes() == 8)
					{
						ventasMensuales[7] += ventas[i].getTotal();
					}
					else if (ventas[i].getFecha().getMes() == 9)
					{
						ventasMensuales[8] += ventas[i].getTotal();
					}
					else if (ventas[i].getFecha().getMes() == 10)
					{
						ventasMensuales[9] += ventas[i].getTotal();
					}
					else if (ventas[i].getFecha().getMes() == 11)
					{
						ventasMensuales[10] += ventas[i].getTotal();
					}
					else if (ventas[i].getFecha().getMes() == 12)
					{
						ventasMensuales[11] += ventas[i].getTotal();
					}
				}
			}
			system("cls");
			cout << "	RECAUDACION ANUAL: " << anio << endl;
			cout << "---------------------------------------" << endl;
			for (int i = 0; i < 12; i++)
			{
				if (mes[i].size() < 7) {
					cout << mes[i] << "\t\t\t" << "$" << ventasMensuales[i] << endl;
				}
				else {
					cout << mes[i] << "  \t\t" << "$" << ventasMensuales[i] << endl;
				}
			}
			cout << "----------------------------------------" << endl;
			cout << "       RECAUDACION TOTAL: $" << total << endl << endl;
			system("pause");
		}break;

		}
	}
delete[] ventas;
}

void Archivo_Venta::listar_x_producto()
{
	int cant = cantidad_ventas();
	Venta* ventas = new Venta[cant];
	if (ventas == nullptr) {
		cout << "ERROR CON LA MEMORIA DINAMICA" << endl;
		return;
	}
	obtener_venta(ventas, cant);
	archivo_producto productos;
	int cantProductos = productos.cantidad_de_registros();
	productos.listar(cantProductos);
	Producto producto;
	int idProducto;

	cout << "ingrese el ID# del producto a listar: " << endl;
	cin >> idProducto;
	while (idProducto <= 0 || idProducto > cant)
	{
		cout << "ID# de producto invalido: " << endl;
		cout << "ingrese el ID# del producto a listar: " << endl;
		cin >> idProducto;
	}
	producto = productos.leer_de_disco(idProducto - 1);
	while (producto.getEstado() != true)
	{
		cout << "ID# de producto invalido: " << endl;
		cout << "ingrese el ID# del producto a listar: " << endl;
		cin >> idProducto;
		producto = productos.leer_de_disco(idProducto - 1);
	}
	system("cls");
	cout << "Ventas con ID# de Producto: " << idProducto << endl << endl;
	while (idProducto < 0 || idProducto > cantProductos)
	{
		cout << "ID# de producto no posee compras " << endl;
		cout << "ingrese otro ID# del producto a listar: " << endl;
		cin >> idProducto;
		producto = productos.leer_de_disco(idProducto - 1);
	}
	for (int i = 0; i < cant; i++)
	{
		if (idProducto == ventas[i].getProducto() && ventas[i].getEstado())
		{
			cout << "-----------------" << endl;
			ventas[i].mostrar();
		}
	}
	cout << endl;
	delete[] ventas;
}


bool Archivo_Venta::guardar_modificado(Venta venta, int pos)
{
	FILE* p;
	p = fopen("ventas.dat", "rb+");
	if (p == nullptr) {
		cout << "No se pudo abrir el archivo" <<endl;
		return false;
	}
	fseek(p, pos * sizeof(Venta), SEEK_SET);
	fwrite(&venta, sizeof(Venta), 1, p);
	fclose(p);

	return true;
}

void Archivo_Venta::recaudacion_x_vendedor()
{
	Archivo_Vendedor archivo;
	int cantVendedor = archivo.Cantidad_vendedores();
	int cant = cantidad_ventas();
	Venta* ventas = new Venta[cant];
	if (ventas == nullptr) {
		cout << "ERROR CON LA MEMORIA DINAMICA" << endl;
		return;
	}
	if (cant == 0)
	{
		cout << "No existen Ventas cargadas" << endl;
	}
	else {
		obtener_venta(ventas, cant);
	}

	Vendedor* vendedores = new Vendedor[cantVendedor];
	if (vendedores == nullptr) {
		cout << "ERROR CON LA MEMORIA DINAMICA" << endl;
		return;
	}
	if (cantVendedor == 0)
	{
		cout << "No existen Vendedores cargados" << endl;
		system("pause");
	}
	else
	{
		archivo.obtener_vendedor(vendedores, cantVendedor);

		cout << "ingrese el anio a listar" << endl;
		int anio;
		cin >> anio;
		while (anio < 2016)
		{
			cout << "Anio invalido" << endl;
			cout << "ingrese el Anio a listar: ";
			cin >> anio;
		}
		cout << "ingrese el ID del Vendedor " << endl;
		int id;
		cin >> id;
		while (id < 0 || id > cantVendedor)
		{
			cout << "ID invalido" << endl;
			cout << "ingrese el ID del Vendedor: ";
			cin >> id;
		}
		float total = 0;
		float ventasMensuales[12] = {};
		string mes[12] = { "Enero","Febrero","Marzo","Abril","Mayo","Junio","Julio","Agosto","Septiembre","Octubre","Noviembre","Diciembre"
		};
		for (int i = 0; i < cant; i++)
		{
			if (anio == ventas[i].getFecha().getAnio() && ventas[i].getEstado() && ventas[i].getIdVendedor() == id)
			{
				total += ventas[i].getTotal();
				if (ventas[i].getFecha().getMes() == 1)
				{
					ventasMensuales[0] += ventas[i].getTotal();
				}
				else if (ventas[i].getFecha().getMes() == 2)
				{
					ventasMensuales[1] += ventas[i].getTotal();
				}
				else if (ventas[i].getFecha().getMes() == 3)
				{
					ventasMensuales[2] += ventas[i].getTotal();
				}
				else if (ventas[i].getFecha().getMes() == 4)
				{
					ventasMensuales[3] += ventas[i].getTotal();
				}
				else if (ventas[i].getFecha().getMes() == 5)
				{
					ventasMensuales[4] += ventas[i].getTotal();
				}
				else if (ventas[i].getFecha().getMes() == 6)
				{
					ventasMensuales[5] += ventas[i].getTotal();
				}
				else if (ventas[i].getFecha().getMes() == 7)
				{
					ventasMensuales[6] += ventas[i].getTotal();
				}
				else if (ventas[i].getFecha().getMes() == 8)
				{
					ventasMensuales[7] += ventas[i].getTotal();
				}
				else if (ventas[i].getFecha().getMes() == 9)
				{
					ventasMensuales[8] += ventas[i].getTotal();
				}
				else if (ventas[i].getFecha().getMes() == 10)
				{
					ventasMensuales[9] += ventas[i].getTotal();
				}
				else if (ventas[i].getFecha().getMes() == 11)
				{
					ventasMensuales[10] += ventas[i].getTotal();
				}
				else if (ventas[i].getFecha().getMes() == 12)
				{
					ventasMensuales[11] += ventas[i].getTotal();
				}
			}
		}

		system("cls");
		for (int i = 0; i < cantVendedor; i++)
		{
			if (id == vendedores[i].getId_Vendedor())
			{
				cout << "RECAUDACION ANUAL DE : " << vendedores[i].getNombre() << "  " << "EN EL ANIO : " << anio << endl;
				cout << "---------------------------------------" << endl;
			}
		}

		for (int i = 0; i < 12; i++)
		{
			if (mes[i].size() < 7) {
				cout << mes[i] << "\t\t\t" << "$" << ventasMensuales[i] << endl;

			}
			else {
				cout << mes[i] << "  \t\t" << "$" << ventasMensuales[i] << endl;

			}
		}
		cout << "----------------------------------------" << endl;
		cout << "       RECAUDACION TOTAL: $" << total << endl << endl;
		system("pause");
		delete[] ventas;
		delete[] vendedores;
	}
}

void Archivo_Venta::recaudacion_x_producto()
{
	archivo_producto archiProd;
	int cant = cantidad_ventas();
	Venta* ventas = new Venta[cant];
	if (ventas == nullptr) {
		cout << "ERROR CON LA MEMORIA DINAMICA" << endl;
		return;
	}
	if (cant == 0)
	{
		cout << "No se encuentran ventas cargadas" << endl;
	}
	else {
		obtener_venta(ventas, cant);
	}
	Archivo_Categoria archiCat;
	int cantProd = archiProd.cantidad_de_registros();
	Producto* productos = new Producto[cantProd];
	if (productos == nullptr) {
		cout << "ERROR CON LA MEMORIA DINAMICA" << endl;
		return;
	}
	if (cantProd == 0)
	{
		cout << "No se encuentran productos cargados" << endl;
		system("pause");
	}
	else {
		archiProd.obtener_productos(productos, cantProd);
		int cantCat = archiCat.cantidad_categorias();
		Categoria* categorias = new Categoria[cantCat];
		if (categorias == nullptr) {
			cout << "ERROR CON LA MEMORIA DINAMICA" << endl;
			return;
		}
		archiCat.obtener_categorias(categorias, cantCat);
		int anio;

		cout << "ingrese el anio a listar" << endl;
		cin >> anio;
		while (anio < 2016)
		{
			cout << "Anio invalido" << endl;
			cout << "ingrese el Anio a listar: ";
			cin >> anio;
		}
		system("cls");
		string nombre;
		string nombreProd;

		cout << "-------------------------- " << anio << " ----------------------------" << endl << endl;
		cout << "PRODUCTO""  \t\t""CATEGORIA""  \t\t" "RECAUDADO" "  \t\t" << endl << endl;
		float total = 0;

		for (int i = 0; i < cantProd; i++)
		{
			for (int j = 0; j < cant; j++)
			{
				if (productos[i].getId_Producto() == ventas[j].getProducto() && anio == ventas[j].getFecha().getAnio() && ventas[j].getEstado() == true)

				{
					total += ventas[j].getTotal();
					nombreProd = productos[i].getNombre();
				}

			}

			if (categorias[i].get_id() == productos[i].getId_Categoria())
			{
				nombre = categorias[i].getNombre();
			}
			if (nombreProd == productos[i].getNombre())
			{
				cout << setw(28) << setiosflags(ios::left) << productos[i].getNombre() << setw(22) << setiosflags(ios::left) << nombre << "$" << total << endl;
				cout << endl;
			}

		}
		cout << "-------------------------------------------------------------" << endl << endl;
		cout << endl;
		system("pause");
		delete[] ventas;
		delete[] productos;
		delete[] categorias;
	}
}

void Archivo_Venta::recaudacion_x_categoria()
{
	Archivo_Categoria archiCat;
	archivo_producto archivoProd;
	int cantProd = archivoProd.cantidad_de_registros();
	int cant = cantidad_ventas();
	Producto* productos = new Producto[cantProd];
	if (productos == nullptr) {
		cout << "ERROR CON LA MEMORIA DINAMICA" << endl;
		return;
	}
	if (cantProd == 0)
	{
		cout << "No se encuentran productos cargados" << endl;
	}
	else {
		archivoProd.obtener_productos(productos, cantProd);
	}
	Venta* ventas = new Venta[cant];
	if (ventas == nullptr) {
		cout << "ERROR CON LA MEMORIA DINAMICA" << endl;
		return;
	}
	if (cant == 0)
	{
		cout << "No se encuentran ventas cargadas" << endl;
	}
	else {
		obtener_venta(ventas, cant);
	}
	int cantCat = archiCat.cantidad_categorias();
	Categoria* categorias = new Categoria[cantCat];
	if (categorias == nullptr) {
		cout << "ERROR CON LA MEMORIA DINAMICA" << endl;
		return;
	}
	if (cant == 0)
	{
		cout << "No se encuentran categorias cargadas" << endl;
		system("pause");
	}
	else {
		archiCat.obtener_categorias(categorias, cantCat);
		int anio;
		cout << "ingrese el anio a listar" << endl;
		cin >> anio;
		while (anio < 2016)
		{
			cout << "Anio invalido" << endl;
			cout << "ingrese el Anio a listar: ";
			cin >> anio;
		}
		system("cls");

		string nombre;
		cout << "-------------------------- " << anio << " ----------------------------" << endl << endl;
		cout << "CATEGORIA""  \t\t" "RECAUDADO" "  \t\t" << endl << endl;
		for (int i = 0; i < cantCat; i++)
		{
			float total = 0;
			for (int j = 0; j < cantProd; j++)
			{
				for (int x = 0; x < cant; x++)
				{
					if (productos[j].getId_Producto() == ventas[x].getProducto() && anio == ventas[x].getFecha().getAnio() && ventas[x].getEstado())
					{
						if (categorias[i].get_id() == productos[j].getId_Categoria())
						{
							nombre = categorias[i].getNombre();
							total += ventas[x].getTotal();
						}

					}
				}
			}
			if (nombre == categorias[i].getNombre())
			{
				cout << setw(28) << setiosflags(ios::left) << nombre << "$" << total << endl;
			}
		}
		cout << endl;
		cout << "-------------------------------------------------------------" << endl << endl;
		cout << endl;
		system("pause");
		delete[] productos;
		delete[] ventas;
		delete[] categorias;
	}
}


void Archivo_Venta::BajaLogica()
{
	int op;
	Venta venta;
	int cant = cantidad_ventas();
	listar_ventas(cant);
	cout << endl;

	cout << "Ingrese de ID de la venta que desea eliminar: ";
	cin >> op;
	venta = leer_ventas(op - 1);

	while (op<0 || op>cant || !venta.getEstado())
	{
		cout << "ingrese una opcion correcta" << endl;
		cin >> op;
	}
	venta = leer_ventas(op - 1);

	if(op != 0) {
		char op2;
		system("cls");
		cout << "----------------------------------------" << endl;
		venta.mostrar();
		cout << "----------------------------------------" << endl << endl;
		cout << endl;
		cout << "esta seguro de que desea eliminar la venta?" <<endl;
		cout << "[S/N]: ";
		cin >> op2;
		if (op2 == 's' || op2 == 'S')
		{
			venta.setEstado(false);
			guardar_modificado(venta, op - 1);
		}
	}
}


int Archivo_Venta::Modificar_Venta()
{
	int op;
	Venta venta;
	int cant = cantidad_ventas();
	listar_ventas(cant);
	cout << "Ingrese de ID de la venta que desea modificar: ";
	cin >> op;
	system("cls");
	venta = leer_ventas(op - 1);

	while (op<0 || op>cant || !venta.getEstado())
	{
		cout << "ingrese una opcion correcta: ";
		cin >> op;
	}
	if (op != 0)
	{
		venta.cargar();
		char op2;
		cout << "esta seguro de que desea modificar la venta?" <<endl;
		cout << "[S/N]: ";
		cin >> op2;
		if (op2 == 's' || op2 == 'S')
		{
			guardar_modificado(venta, op - 1);
		}
	}
	return op;
}


void Archivo_Venta::ganancia_x_Venta()
{
	Archivo_Categoria archiCat;
	int cant = cantidad_ventas();
	Venta* ventas = new Venta[cant];
	if (ventas == nullptr) {
		cout << "ERROR CON LA MEMORIA DINAMICA" << endl;
		return;
	}
	obtener_venta(ventas, cant);

	for (int i = 0; i < cant; i++)
	{
		cout<< "ID VENTA: "<<ventas[i].getId()<<"  "<<"GANANCIA: "<<ventas[i].getGanancia()<<endl;
	}
	delete[]ventas;
}


void Archivo_Venta::ganancia_x_mes_Anual()
{
	int cant = cantidad_ventas();
	Venta* ventas = new Venta[cant];
	if (ventas == nullptr) {
		cout << "ERROR CON LA MEMORIA DINAMICA" << endl;
		return;
	}
	if (cant == 0)
	{
		cout << "No se encuentran ventas cargadas" << endl;
		system("pause");
	}
	else {
		obtener_venta(ventas, cant);
		int anio;
		cout << "ingrese el anio a listar" << endl;
		cin >> anio;
		while (anio < 2016)
		{
			cout << "Anio invalido" << endl;
			cout << "ingrese el Anio a listar: ";
			cin >> anio;
		}

		float total = 0;
		float ventasMensuales[12] = {};
		string mes[12] = { "Enero","Febrero","Marzo","Abril","Mayo","Junio","Julio","Agosto","Septiembre","Octubre","Noviembre","Diciembre"
		};
		for (int i = 0; i < cant; i++)
		{
			if (anio == ventas[i].getFecha().getAnio() && ventas[i].getEstado())
			{
				total += ventas[i].getGanancia();
				if (ventas[i].getFecha().getMes() == 1)
				{
					ventasMensuales[0] += ventas[i].getGanancia();
				}
				else if (ventas[i].getFecha().getMes() == 2)
				{
					ventasMensuales[1] += ventas[i].getGanancia();
				}
				else if (ventas[i].getFecha().getMes() == 3)
				{
					ventasMensuales[2] += ventas[i].getGanancia();
				}
				else if (ventas[i].getFecha().getMes() == 4)
				{
					ventasMensuales[3] += ventas[i].getGanancia();
				}
				else if (ventas[i].getFecha().getMes() == 5)
				{
					ventasMensuales[4] += ventas[i].getGanancia();
				}
				else if (ventas[i].getFecha().getMes() == 6)
				{
					ventasMensuales[5] += ventas[i].getGanancia();
				}
				else if (ventas[i].getFecha().getMes() == 7)
				{
					ventasMensuales[6] += ventas[i].getGanancia();
				}
				else if (ventas[i].getFecha().getMes() == 8)
				{
					ventasMensuales[7] += ventas[i].getGanancia();
				}
				else if (ventas[i].getFecha().getMes() == 9)
				{
					ventasMensuales[8] += ventas[i].getGanancia();
				}
				else if (ventas[i].getFecha().getMes() == 10)
				{
					ventasMensuales[9] += ventas[i].getGanancia();
				}
				else if (ventas[i].getFecha().getMes() == 11)
				{
					ventasMensuales[10] += ventas[i].getGanancia();
				}
				else if (ventas[i].getFecha().getMes() == 12)
				{
					ventasMensuales[11] += ventas[i].getGanancia();
				}
			}
		}

		system("cls");

		for (int i = 0; i < 12; i++)
		{
			if (mes[i].size() < 7) {
				cout << mes[i] << "\t\t\t" << "$" << ventasMensuales[i] << endl;

			}
			else {
				cout << mes[i] << "  \t\t" << "$" << ventasMensuales[i] << endl;

			}
		}
		cout << "----------------------------------------" << endl;
		cout << "       RECAUDACION TOTAL: $" << total << endl << endl;
		system("pause");
		delete[] ventas;
	}
}