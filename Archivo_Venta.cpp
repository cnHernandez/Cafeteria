#include "Archivo_Venta.h"
#include "Venta.h"
#include "Archivo_Categoria.h"
#include "Archivo_Producto.h"
#include "Archivo_Cliente.h"
#include "archivo_Vendedor.h"
#include "Vendedor.h"
#include "Cliente.h"
#include "Menu.h"
#include <iostream>
#include <string>
#include <iomanip>
#include "rlutil.h"

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
		FILE* p = fopen("Ventas.dat", "rb");
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
	FILE* p = fopen("Ventas.dat", "ab");
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

	while (!Clientes.ExisteCliente(idCliente))
	{
		rlutil::setColor(rlutil::RED);
		cout << "ID# de cliente invalido: " << endl;
		rlutil::setColor(rlutil::BLACK);
		cout << "ingrese el ID# del cliente a listar: ";
		cin >> idCliente;
	}
	cliente=Clientes.leer_clientes(idCliente - 1);

	system("cls");
	for (int i = 0; i < cantClientes; i++)
	{
		cliente = Clientes.leer_clientes(i);
		if (idCliente == cliente.getId_Cliente())
		{
			cout << "Compras de " << cliente.getNombre() << endl;
		}
	}
	bool tuvoVentas = false;
		for (int i = 0; i < cant; i++)
		{
			if (idCliente == ventas[i].getIdCliente() && ventas[i].getEstado() && ventas[i].getIdCliente())
			{
				ventas[i].mostrar();
				tuvoVentas = true;
			}
		}
		if (!tuvoVentas) {
			rlutil::setColor(rlutil::RED);
			cout << "No tuvo ventas aun..." << endl;
			rlutil::setColor(rlutil::BLACK);
		}

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
			rlutil::setColor(rlutil::RED);
			cout << "opcion incorrecta, vuelva a ingresar una opcion" << endl;
			rlutil::setColor(rlutil::BLACK);
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
				rlutil::setColor(rlutil::RED);
				cout << "Mes invalido" << endl;
				rlutil::setColor(rlutil::BLACK);
				cout << "ingrese el Mes a listar: ";
				cin >> mes;
			}
			bool tuvo = false;
			system("cls");
			cout << "Ventas con mes: " << mes << endl;
			for (int i = 0; i < cant; i++)
			{
				if (mes == ventas[i].getFecha().getMes() && ventas[i].getEstado())
				{
					ventas[i].mostrar();
					tuvo = true;
				}
			}
			if (!tuvo) {
				rlutil::setColor(rlutil::RED);
				cout << "NO HUBO VENTAS PARA DICHO MES" << endl;
				rlutil::setColor(rlutil::BLACK);
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
				rlutil::setColor(rlutil::RED);
				cout << "Anio invalido" << endl;
				rlutil::setColor(rlutil::BLACK);
				cout << "ingrese el Anio a listar: ";
				cin >> anio;
			}
			system("cls");
			cout << "          VENTAS DEL ANIO " << anio << endl << endl;
			bool tuvo = false;
			for (int i = 0; i < cant; i++)
			{
				if (anio == ventas[i].getFecha().getAnio() && ventas[i].getEstado())
				{
					ventas[i].mostrar();
					tuvo = true;
				}
			}
			if (!tuvo) {
				rlutil::setColor(rlutil::RED);
				cout << "NO HUBO VENTAS PARA DICHO ANIO" << endl;
				rlutil::setColor(rlutil::BLACK);
			}
			system("pause");

		}
		break;
		case 3:
		{
			system("cls");
			cout << "ingrese el anio a listar" << endl;
			cin >> anio;
			while (anio < 2016)
			{
				rlutil::setColor(rlutil::RED);
				cout << "Anio invalido" << endl;
				rlutil::setColor(rlutil::BLACK);
			    cout << "ingrese el Anio a listar: ";
				cin >> anio;
			}
			float total = 0;
			for (int i = 0; i < cant; i++)
			{
				if (anio == ventas[i].getFecha().getAnio() && ventas[i].getEstado())
				{
					total += ventas[i].getGanancia();
				}
			}
			string mes[12] = { "Enero","Febrero","Marzo","Abril","Mayo","Junio","Julio","Agosto","Septiembre","Octubre","Noviembre","Diciembre"
			};
			
			float ventasMensuales[12] = {};
			for (int i = 0; i < cant; i++)
			{
				if (anio == ventas[i].getFecha().getAnio() && ventas[i].getEstado())
				{
					ventasMensuales[ventas[i].getFecha().getMes() - 1] += ventas[i].getGanancia();	
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
		system("cls");
		cout << "No existen Ventas cargadas" << endl;
		system("pause");
		return;
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
		system("cls");
		cout << "No existen Vendedores cargados" << endl;
		return;
		system("pause");
	}
	else
	{
		archivo.obtener_vendedor(vendedores, cantVendedor);

		cout << "ingrese el anio a listar" << endl;
		int anio;
		cin >> anio;
		if (anio < 2020 || anio > 2023)
		{
			rlutil::setColor(rlutil::RED);
			cout << "Anio invalido" << endl;
			rlutil::setColor(rlutil::BLACK);
			cout << "ingrese el Anio a listar: ";
			cin >> anio;
			if (anio < 2016 || anio > 2023) {
				rlutil::setColor(rlutil::RED);
				cout << "ANIO INVALIDO" << endl;
				rlutil::setColor(rlutil::BLACK);
				system("pause");
				return;
			}
		}
		cout << endl;
		archivo.Listar_Vendedor(cantVendedor);
		cout << "ingrese el ID del Vendedor " << endl;
		int id;
		cin >> id;
		while (id < 0 || id > cantVendedor)
		{
			rlutil::setColor(rlutil::RED);
			cout << "ID invalido" << endl;
			rlutil::setColor(rlutil::BLACK);
			cout << "ingrese el ID del Vendedor: ";
			cin >> id;
		}
		float total = 0;
		float ventasMensuales[12] = {};
		string mes[12] = { "Enero","Febrero","Marzo","Abril","Mayo","Junio","Julio","Agosto","Septiembre","Octubre","Noviembre","Diciembre"};

		for (int i = 0; i < cant; i++)
		{
			if (anio == ventas[i].getFecha().getAnio() && ventas[i].getEstado() && ventas[i].getIdVendedor() == id)
			{
				total += ventas[i].getGanancia();
				ventasMensuales[ventas[i].getFecha().getMes()-1] += ventas[i].getGanancia();
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
		system("cls");
		cout << "ERROR CON LA MEMORIA DINAMICA" << endl;
		system("pause");
		return;
	}
	if (cant == 0)
	{
		system("cls");
		cout << "No se encuentran ventas cargadas" << endl;
		system("pause");
		return;
	}
	else {
		obtener_venta(ventas, cant);
	}
	Archivo_Categoria archiCat;
	int cantProd = archiProd.cantidad_de_registros();
	Producto* productos = new Producto[cantProd];
	if (productos == nullptr) {
		system("cls");
		cout << "ERROR CON LA MEMORIA DINAMICA" << endl;
		system("pause");
		return;
	}
	if (cantProd == 0)
	{
		system("cls");
		cout << "No se encuentran productos cargados" << endl;
		system("pause");
		return;
	}
	else {
		archiProd.obtener_productos(productos, cantProd);
		int cantCat = archiCat.cantidad_categorias();
		Categoria* categorias = new Categoria[cantCat];
		if (categorias == nullptr) {
			system("cls");
			cout << "ERROR CON LA MEMORIA DINAMICA" << endl;
			system("pause");
			return;
		}
		archiCat.obtener_categorias(categorias, cantCat);
		int anio;

		cout << "ingrese el anio a listar" << endl;
		cin >> anio;
		if (anio < 2020 || anio > 2023)
		{
			rlutil::setColor(rlutil::RED);
			cout << "Anio invalido" << endl;
			rlutil::setColor(rlutil::BLACK);
			cout << "ingrese el Anio a listar: ";
			cin >> anio;
			if (anio < 2016 || anio > 2023) {
				rlutil::setColor(rlutil::RED);
				cout << "ANIO INVALIDO" << endl;
				rlutil::setColor(rlutil::BLACK);
				system("pause");
				return;
			}
		}
		system("cls");
		int poscat;
		string nombre;

		string *nombreProd = new string[cantProd];
		
		if (nombreProd == nullptr) {
			return;
		}

		cout << "-------------------------- " << anio << " ----------------------------" << endl << endl;
		cout << "PRODUCTO""  \t\t""CATEGORIA""  \t\t" "RECAUDADO" "  \t\t" << endl << endl;
	

		for (int i = 0; i < cantProd; i++)
		{
			float total = 0;
			int idcat;

				for (int j = 0; j < cant; j++)
				{
					int numD = ventas[j].getNumerodetalles();
					for (int x = 0; x < numD; x++) {
						if (productos[i].getId_Producto() == ventas[j].getDetalle(x).getId_Producto() && anio == ventas[j].getFecha().getAnio() && ventas[j].getEstado() == true)
						{
							total += (ventas[j].getDetalle(x).getCantidad() * ventas[j].getDetalle(x).getPrecio());
							nombreProd[i] = productos[i].getNombre();
							idcat = ventas[j].getDetalle(x).getId_Categoria();
							nombre = categorias[idcat - 1].getNombre();
						}
					}	
				}
			if (nombreProd[i] == productos[i].getNombre() && productos[i].getEstado())
			{
				cout << setw(28) << setiosflags(ios::left) << productos[i].getNombre() << setw(22) << setiosflags(ios::left) << nombre<< "$" << total << endl;
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
		system("cls");
		cout << "ERROR CON LA MEMORIA DINAMICA" << endl;
		system("pause");
		return;
	}
	if (cantProd == 0)
	{
		system("cls");
		cout << "No se encuentran productos cargados" << endl;
		system("pause");
		return;
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
		system("pause");
		return;
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
		rlutil::setColor(rlutil::RED);
		cout << "No se encuentran categorias cargadas" << endl;
		rlutil::setColor(rlutil::BLACK);
		return;
		system("pause");
	}
	else {
		archiCat.obtener_categorias(categorias, cantCat);
		int anio;
		cout << "ingrese el anio a listar" << endl;
		cin >> anio;
		if (anio < 2020 || anio > 2023)
		{
			rlutil::setColor(rlutil::RED);
			cout << "Anio invalido" << endl;
			rlutil::setColor(rlutil::BLACK);
			cout << "ingrese el Anio a listar: ";
			cin >> anio;
			if (anio < 2016 || anio > 2023) {
				rlutil::setColor(rlutil::RED);
				cout << "ANIO INVALIDO" << endl;
				rlutil::setColor(rlutil::BLACK);
				system("pause");
				return;
			}
		}
		system("cls");

		float* total = new float[cantCat] {};
		if (total == nullptr) {
			cout << "ERROR CON LA MEMORIA DINAMICA" << endl;
			return;
		}

		string nombre;
		cout << "-------------------------- " << anio << " ----------------------------" << endl << endl;
		cout << "CATEGORIA""  \t\t" "RECAUDADO" "  \t\t" << endl << endl;
		
		
		for (int i = 0; i < cantProd; i++)
		{	
			int idcat;
			for (int j = 0; j < cant; j++)
			{
				int numD = ventas[j].getNumerodetalles();
				for (int x = 0; x < numD; x++) {
					if (productos[i].getId_Producto() == ventas[j].getDetalle(x).getId_Producto() && anio == ventas[j].getFecha().getAnio() && ventas[j].getEstado() == true)
					{
						total[ventas[j].getDetalle(x).getId_Categoria()-1] += (ventas[j].getDetalle(x).getCantidad() * ventas[j].getDetalle(x).getPrecio());
						idcat = ventas[j].getDetalle(x).getId_Categoria();
					}
				}
			}
		}

		for (int i = 0; i < cantCat; i++) {

			if (categorias[i].getEstado()) {
				cout << setw(28) << setiosflags(ios::left) << categorias[i].getNombre() << "$" << total[i] << endl;
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
		rlutil::setColor(rlutil::RED);
		cout << "ingrese una opcion correcta" << endl;
		rlutil::setColor(rlutil::BLACK);
		cin >> op;
	}
	venta = leer_ventas(op - 1);
	Menu menu;
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
		else if (op2 == 'n' || op2 == 'N')
		{
			menu.menu_Ventas();
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
		rlutil::setColor(rlutil::RED);
		cout << "ingrese una opcion correcta: ";
		rlutil::setColor(rlutil::BLACK);
		cin >> op;
	}
	Menu menu;
	if (op != 0)
	{
		char op2;
		cout << "esta seguro de que desea modificar la venta?" <<endl;
		cout << "[S/N]: ";
		cin >> op2;
		if (op2 == 's' || op2 == 'S')
		{
		venta.cargar();
			guardar_modificado(venta, op - 1);
		}
		else if (op2 == 'n' || op2 == 'N')
		{
			menu.menu_Ventas();
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
		system("cls");
		cout << "No se encuentran ventas cargadas" << endl;
		system("pause");
		return;
	}
	else {
		obtener_venta(ventas, cant);
		int anio;
		cout << "ingrese el anio a listar" << endl;
		cin >> anio;
		if (anio < 2016 || anio > 2023)
		{
			rlutil::setColor(rlutil::RED);
			cout << "Anio invalido" << endl;
			rlutil::setColor(rlutil::BLACK);
			cout << "ingrese el Anio a listar: ";
			cin >> anio;
			if (anio < 2016 || anio > 2023) {
				rlutil::setColor(rlutil::RED);
				cout << "ANIO INVALIDO" << endl;
				rlutil::setColor(rlutil::BLACK);
				system("pause");
				return;
			}
		}

		float total = 0;
		float ventasMensuales[12] = {};
		string mes[12] = { "Enero","Febrero","Marzo","Abril","Mayo","Junio","Julio","Agosto","Septiembre","Octubre","Noviembre","Diciembre"};

		for (int i = 0; i < cant; i++)
		{
			if (anio == ventas[i].getFecha().getAnio() && ventas[i].getEstado())
			{
				total += ventas[i].getGanancia();
				ventasMensuales[ventas[i].getFecha().getMes()-1] += ventas[i].getGanancia();
			}
		}

		system("cls");
		cout << "  GANANCIA NETA MENSUAL DEL ANIO "<<anio << endl;
		cout << "----------------------------------------" << endl;
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