#include "Archivo_Venta.h"
#include "Venta.h"
#include "Archivo_Categoria.h"
#include "Archivo_Producto.h"
#include "Archivo_Cliente.h"
#include "Cliente.h"
#include <iostream>
#include <string>
#include <iomanip>

using namespace std;

bool Archivo_Venta::guardarEnDisco(int cantidad_ventas)
{
	bool guardo;
	FILE *p;
	p = fopen("Ventas.dat", "ab");
	if (p == NULL)
	{
		std::cout << "Error al abrir el archivo" << endl;
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
		std::cout << "Error al abrir el archivo" << endl;
	}
	fread(venta, sizeof(Venta), cant, p);
	fclose(p);
}


void Archivo_Venta::guardar(Venta venta)
{
	FILE* pFile;
	pFile = fopen("Ventas.dat", "ab");
	if (pFile == nullptr) {
		std::cout << "No se pudo abrir el archivo" << endl;
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
		std::cout << "Error al abrir el archivo" << std::endl;
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
			std::cout << "Error al abrir el archivo" << std::endl;;
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
		}
	}
}	
/*void Archivo_Venta::listar_ventasDin(vector<Venta>ventas)
{
	Venta venta;
	for (int i = 0; i < sizeof(ventas); i++) {
		ventas[i].mostrar();
		}
	}*/


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
	obtener_venta(ventas, cant);
	Cliente cliente;
	int idCliente;
	std::cout << "ingrese el ID# del cliente a listar: " << endl;
	cin >> idCliente;
	while (idCliente <= 0 || idCliente > cant)
	{
		std::cout << "ID# de cliente invalido: " << endl;
		std::cout << "ingrese el ID# del cliente a listar: " << endl;
		cin >> idCliente;
	}
	cliente=Clientes.leer_clientes(idCliente - 1);
	while(cliente.getEstado()!= true)
	{
		std::cout << "ID# de cliente invalido: " << endl;
		std::cout << "ingrese el ID# del cliente a listar: " << endl;
		cin >> idCliente;
		cliente = Clientes.leer_clientes(idCliente - 1);

	}
	std::system("cls");

	std::cout << "Productos con ID# de Cliente: " << idCliente << endl << endl;
	while (idCliente<0 || idCliente>cantClientes)
	{
		std::cout << "ID# de cliente no posee compras " << endl;
		std::cout << "ingrese otro ID# del cliente a listar: " << endl;
		cin >> idCliente;
		cliente = Clientes.leer_clientes(idCliente - 1);
	}
	
	for (int i = 0; i < cant; i++)
	{

		if (idCliente == ventas[i].getIdCliente().getId_Cliente() && ventas[i].getEstado())
		{
			ventas[i].mostrar();
		}

	}
	std::cout << endl;

	delete[] ventas;
}

void Archivo_Venta::listar_x_fecha()
{
	int cant = cantidad_ventas();
	Venta* ventas = new Venta[cant];
	obtener_venta(ventas, cant);
	int dia, mes, anio;
	int op;
	bool menu_activo = true;
	while (menu_activo)
	{
		std::system("cls");
		std::cout << "---Fecha de Ventas----" << endl << endl;
		std::cout << " 1- Mes" << endl;
		std::cout << " 2- Anio" << endl;
		std::cout << " 3- Recaudacion anual" << endl;
		std::cout << "-----------------" << endl;
		std::cout << " 0- SALIR" << endl;
		std::cout << "-----------------" << endl;
		cin >> op;
		while (op < 0 || op>3)
		{
			std::cout << "opcion incorrecta, vuelva a ingresar una opcion" << endl;
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
			std::cout << "ingrese el Mes a listar: ";
			cin >> mes;
			while (mes < 1 || mes > 12)
			{
				std::cout << "Mes invalido" << endl;
				std::cout << "ingrese el Mes a listar: ";
				cin >> mes;
			}
			std::cout << "Ventas con mes: " << mes << endl;
			system("cls");
			for (int i = 0; i < cant; i++)
			{
				if (mes == ventas[i].getFecha().getMes() && ventas[i].getEstado())
				{
					ventas[i].mostrar();
				}
			}
			std::system("pause");
			std::cout << endl;
		}
		break;
		case 2:
		{
			std::cout << "ingrese el anio a listar" << endl;
			cin >> anio;
			while (anio < 2016)
			{
				std::cout << "Anio invalido" << endl;
				std::cout << "ingrese el Anio a listar: ";
				cin >> anio;
			}
			system("cls");
			std::cout << "          VENTAS CON ANIO " << anio << endl << endl;
			for (int i = 0; i < cant; i++)
			{
				if (anio == ventas[i].getFecha().getAnio() && ventas[i].getEstado())
				{
					ventas[i].mostrar();
				}
			}
			std::system("pause");

		}
		break;
		case 3:
		{
			std::cout << "ingrese el anio a listar" << endl;
			cin >> anio;
			while (anio < 2016)
			{
				std::cout << "Anio invalido" << endl;
				std::cout << "ingrese el Anio a listar: ";
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
			std::cout << "	RECAUDACION ANUAL: " << anio << endl;
			cout << "---------------------------------------" << endl;
			for (int i = 0; i < 12; i++)
			{
				if (mes[i].size() < 7) {
					std::cout << mes[i] << "\t\t\t" << "$" << ventasMensuales[i] << endl;
				}
				else {
					std::cout << mes[i] << "  \t\t" << "$" << ventasMensuales[i] << endl;
				}
			}
			cout << "----------------------------------------" << endl;
			std::cout << "       RECAUDACION TOTAL: $" << total << endl << endl;
			std::system("pause");
		}break;

		}
	}
			delete[] ventas;
		}

void Archivo_Venta::listar_x_producto()
{
	int cant = cantidad_ventas();
	Venta* ventas = new Venta[cant];
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
		if (idProducto == ventas[i].getProducto().getId_Producto() && ventas[i].getEstado())
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
		std::cout << "No se pudo abrir el archivo" << std::endl;
		return false;
	}
	fseek(p, pos * sizeof(Venta), SEEK_SET);
	fwrite(&venta, sizeof(Venta), 1, p);
	fclose(p);

	return true;
}

void Archivo_Venta::recaudacion_x_vendedor()
{
	int cant = cantidad_ventas();
	Venta* ventas = new Venta[cant];
	obtener_venta(ventas, cant);
	int anio;
	std::cout << "ingrese el anio a listar" << endl;
	cin >> anio;
	while (anio < 2016)
	{
		std::cout << "Anio invalido" << endl;
		std::cout << "ingrese el Anio a listar: ";
		cin >> anio;
	}
	std::cout << "ingrese el ID del Vendedor " << endl;
	std::cout << "1 - Juan " << endl;
	std::cout << "2 - Pedro " << endl;
	std::cout << "3 - Romina " << endl;
	std::cout << "4 - Carla " << endl;
	int id;
	cin >> id;
	while (id < 0 || id > 4)
	{
		std::cout << "ID invalido" << endl;
		std::cout << "ingrese el ID del Vendedor: ";
		cin >> id;
	}
	float total = 0;
	for (int i = 0; i < cant; i++)
	{
		if (anio == ventas[i].getFecha().getAnio() && ventas[i].getEstado() && ventas[i].getIdVendedor()==id)
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
	if (id == 1) {std::cout <<"RECAUDACION ANUAL DE JUAN EN EL ANIO : " << anio << endl;
	}else if(id == 2){ std::cout << "RECAUDACION ANUAL DE PEDRO EN EL ANIO: " << anio << endl; }
	else if(id == 3){ std::cout << "RECAUDACION ANUAL DE ROMINA EN EL ANIO: " << anio << endl; }
	else if(id == 4){std::cout << "RECAUDACION ANUAL DE CARLA EN EL ANIO: " << anio << endl; }

	cout << "---------------------------------------" << endl;
	for (int i = 0; i < 12; i++)
	{
		if (mes[i].size() < 7) {
			std::cout << mes[i] << "\t\t\t" << "$" << ventasMensuales[i] << endl;
		}
		else {
			std::cout << mes[i] << "  \t\t" << "$" << ventasMensuales[i] << endl;
		}
	}
	cout << "----------------------------------------" << endl;
	std::cout << "       RECAUDACION TOTAL: $" << total << endl << endl;
	std::system("pause");	
	delete[] ventas;	
}

void Archivo_Venta::recaudacion_x_producto()
{
	archivo_producto archiProd;
	int cant = cantidad_ventas();
	Venta* ventas = new Venta[cant];
	obtener_venta(ventas, cant);

	int cantProd = archiProd.cantidad_de_registros();
	Producto* productos = new Producto[cantProd];
	archiProd.obtener_productos(productos, cantProd);
	
	int anio;
	std::cout << "ingrese el anio a listar" << endl;
	cin >> anio;
	while (anio < 2016)
	{
		std::cout << "Anio invalido" << endl;
		std::cout << "ingrese el Anio a listar: ";
		cin >> anio;
	}
	system("cls");
	float total = 0;
	cout << "-------------------------- " << anio << " ----------------------------" << endl << endl;
	cout << "PRODUCTO""  \t\t""CATEGORIA""  \t\t" "RECAUDADO" "  \t\t" << endl << endl;
	for (int i = 0; i < cantProd; i++)
	{
		for (int j = 0; j < cant; j++)
		{
			if (productos[i].getId_Producto() == ventas[j].getProducto().getId_Producto() && anio == ventas[j].getFecha().getAnio() && ventas[j].getEstado())
			{
				total += ventas[j].getTotal();
			}
		}

			cout <<  setw(28) << setiosflags(ios::left) << productos[i].getNombre() << setw(22) << setiosflags(ios::left)<< productos[i].getId_Categoria()  << "$" << total << endl;
	
	}
	cout<<endl;
	cout << "-------------------------------------------------------------" << endl << endl;
	cout << endl;
			system("pause");
}

void Archivo_Venta::recaudacion_x_categoria()
{
	Archivo_Categoria archiCat;
	int cant = cantidad_ventas();
	Venta* ventas = new Venta[cant];
	obtener_venta(ventas, cant);
	int cantCat = archiCat.cantidad_categorias();
	Categoria* categorias = new Categoria[cantCat];
	archiCat.obtener_categorias(categorias, cantCat);
	int anio;
	std::cout << "ingrese el anio a listar" << endl;
	cin >> anio;
	while (anio < 2016)
	{
		std::cout << "Anio invalido" << endl;
		std::cout << "ingrese el Anio a listar: ";
		cin >> anio;
	}
	system("cls");
	float total = 0;
	cout << "-------------------------- " << anio << " ----------------------------" << endl << endl;
	cout << "CATEGORIA""  \t\t" "RECAUDADO" "  \t\t" << endl << endl;
	for (int i = 0; i < cantCat; i++)
	{
		for (int j = 0; j < cant; j++)
		{
			if (categorias[i].get_id() == ventas[j].getProducto().getId_Categoria() && anio == ventas[j].getFecha().getAnio() && ventas[j].getEstado())
			{
				total += ventas[j].getTotal();
			}
		}
		cout << setw(28) << setiosflags(ios::left) << categorias[i].getNombre() << "$" << total << endl;
	}
	cout << endl;
	cout << "-------------------------------------------------------------" << endl << endl;
	cout << endl;
	system("pause");
}

/*void Archivo_Venta::guardarVentas(const vector<Venta>& ventas)
{
	FILE* pFile;
	pFile = fopen("Ventas.dat", "wb");
	if (pFile == nullptr) {
		std::cout << "No se pudo abrir el archivo" << endl;
	}
	//for (int i = 0; i < ventas.size(); i++)
	
		fwrite(&ventas, sizeof(Venta), ventas.size(), pFile);
	
	fclose(pFile);

}*/



