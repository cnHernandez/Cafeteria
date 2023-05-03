#include "Archivo_Venta.h"
#include "Venta.h"
#include "Archivo_Categoria.h"
#include "Archivo_Producto.h"
#include "Archivo_Cliente.h"
#include "Cliente.h"
#include <iostream>
#include <string>

using namespace std;

bool Archivo_Venta::guardarEnDisco(int cantidad_ventas)
{
	bool guardo;
	FILE *p;
	p = fopen("Ventas.dat", "ab");
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
	Clientes.listar_clientes(cant);
	
	Venta* ventas = new Venta[cant];
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

	cout << "Productos con ID# de Cliente: " << idCliente << endl << endl;

	for (int i = 0; i < cant; i++)
	{

		if (idCliente == ventas[i].getIdCliente().getId_Cliente() && ventas[i].getEstado())
		{
			cout << "-----------------" << endl;
			ventas[i].mostrar();
		}

	}
	cout << endl;

	delete[] ventas;
}

