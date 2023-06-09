#include "Archivo_Vendedor.h"
#include "Archivo_Cliente.h"
#include "Cliente.h"
#include "Fecha.h"
#include "Producto.h"
#include "Venta.h"
#include <iostream>
#include <string>
#include <fstream>
#include "Persona.h"


using namespace std;

bool Archivo_Vendedor::GuardarEnDisco(int pos) {
	FILE* p;
	p = fopen("Vendedores.dat", "rb+");
	if (p == NULL) {
		return false;
	}
	bool ok;
	fseek(p, pos * sizeof(Vendedor), SEEK_SET);
	ok = fwrite(this, sizeof(Vendedor), 1, p);
	fclose(p);
	return ok;
}

void Archivo_Vendedor::Guardar(Vendedor ven) {

	FILE* pFile;
	pFile = fopen("Vendedores.dat", "ab");
	if (pFile == nullptr) {
		cout << "No se pudo abrir el archivo" << endl;
	}
	fwrite(&ven, sizeof(Vendedor), 1, pFile);
	fclose(pFile);
}

int Archivo_Vendedor::Cantidad_vendedores() {
	FILE* pFile;
	int cantidad = 0;

	pFile = fopen("Vendedores.dat", "rb");

	if (pFile == nullptr)
	{
		return 0;
	}

	fseek(pFile, 0, SEEK_END);
	cantidad = ftell(pFile) / sizeof(Vendedor);

	fclose(pFile);

	return cantidad;
}

Vendedor Archivo_Vendedor::Leer_vendedores(int pos) {

	Vendedor vendedor;
	FILE* p;
	p = fopen("Vendedores.dat", "rb");

	if (p == nullptr) {
		std::cout << "Error al abrir el archivo" << std::endl;
	}

	fseek(p, pos * sizeof(Vendedor), SEEK_SET);
	fread(&vendedor, sizeof(Vendedor), 1, p);
	fclose(p);

	return vendedor;
}

int Archivo_Vendedor::Get_cantidad_Activa(int cantidad)
{
	int contador = 0;

	for (int i = 0; i < cantidad; i++)
	{
		Vendedor vendedor;
		vendedor = Leer_vendedores(i);
		if (vendedor.getEstado())
		{
			contador++;
		}
	}
	return contador;
}

void Archivo_Vendedor::Listar_Vendedor(int cantidad) {
	Vendedor vendedor;
	for (int i = 0; i < cantidad; i++) {
		vendedor = Leer_vendedores(i);
		if (vendedor.getEstado() == true) {
			vendedor.Mostrar();
		}
	}
}

void Archivo_Vendedor::Modificar_Vendedor() {
	int op;
	Vendedor vendedor;
	int cant = Cantidad_vendedores();
	Listar_Vendedor(cant);
	std::cout << std::endl;
	std::cout << "Ingrese de ID del vendedor que desea modificar: ";
	std::cin >> op;

	vendedor = Leer_vendedores(op - 1);

	while (op<0 || op>cant || vendedor.getEstado() == false)
	{
		std::cout << "ingrese una opcion correcta: ";
		std::cin >> op;
	}
	if (op > 0 && op < cant)
	{
		vendedor = Leer_vendedores(op - 1);
		vendedor.Cargar();

		char op2;
		std::cout << "esta seguro de que desea modificar el vendedor" << std::endl;
		std::cout << "[S/N]: ";
		std::cin >> op2;
		if (op2 == 's' || op2 == 'S')
		{
			Guardar_Modificado(vendedor, op - 1);
		}
	}
}

bool Archivo_Vendedor::Guardar_Modificado(Vendedor ven, int pos)
{

	FILE* p;
	p = fopen("Vendedores.dat", "rb+");
	if (p == nullptr) {
		std::cout << "No se pudo abrir el archivo" << std::endl;
		return false;
	}
	fseek(p, pos * sizeof(Vendedor), SEEK_SET);
	fwrite(&ven, sizeof(Vendedor), 1, p);
	fclose(p);

	return true;
}

void Archivo_Vendedor::Baja_Logica() {
	int op;
	Vendedor vendedor;
	int cant = Cantidad_vendedores();
	Listar_Vendedor(cant);
	std::cout << std::endl;
	std::cout << "Ingrese de ID del vendedor que desea eliminar: ";
	std::cin >> op;

	while (op<0 || op>cant)
	{
		std::cout << "ingrese una opcion correcta: ";
		std::cin >> op;
	}
	vendedor = Leer_vendedores(op - 1);
	if (vendedor.getEstado() == false)
	{
		std::cout << "ingrese una opcion correcta: ";
		std::cin >> op;
	}
	else {

		char op2;
		std::cout << "esta seguro de que desea eliminar el vendedor?" << std::endl;
		std::cout << "[S/N]: ";
		std::cin >> op2;
		if (op2 == 's' || op2 == 'S')
		{

			vendedor.setEstado(false);
			Guardar_Modificado(vendedor, op - 1);
		}
	}
}

bool Archivo_Vendedor::ExisteVendedor(int id)
{
	int cantidadNoActiva = Cantidad_vendedores();
	int cantidadActiva = Get_cantidad_Activa(cantidadNoActiva);
	Vendedor vendedor;

	for (int i = 0; i < cantidadActiva; i++)
	{
		vendedor = Leer_vendedores(i);
		if (vendedor.getId_Vendedor() == id)
		{
			return true;
		}
	}
	return false;
}

void Archivo_Vendedor::obtener_vendedor(Vendedor* vendedor, int cant)
{
	FILE* p;
	p = fopen("Vendedores.dat", "rb");
	if (p == NULL)
	{
		std::cout << "Error al abrir el archivo" << endl;
	}
	fread(vendedor, sizeof(Vendedor), cant, p);
	fclose(p);
}