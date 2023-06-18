#include "Archivo_Cliente.h"
#include "Cliente.h"
#include "Fecha.h"
#include "Producto.h"
#include "Venta.h"
#include <iostream>
#include <string>
#include <fstream>

using namespace std;

bool Archivo_Cliente::guardarEnDisco(int pos) {
    FILE* p;
    p = fopen("Clientes.dat", "rb+");
    if (p == NULL) {
        return false;
    }
    bool ok;
    fseek(p, pos * sizeof(Cliente), SEEK_SET);
    ok = fwrite(this, sizeof(Cliente), 1, p);
    fclose(p);
    return ok;
}

void Archivo_Cliente::guardar(Cliente cli) {
	
	FILE* pFile;
	pFile = fopen("Clientes.dat", "ab");
	if (pFile == nullptr) {
		cout << "No se pudo abrir el archivo" << endl;
	}
	fwrite(&cli, sizeof(Cliente), 1, pFile);
	fclose(pFile);
}

int Archivo_Cliente::cantidad_clientes() {
	FILE* pFile;
	int cantidad = 0;

	pFile = fopen("clientes.dat", "rb");

	if (pFile == nullptr)
	{
		return 0;
	}
	fseek(pFile, 0, SEEK_END);
	cantidad = ftell(pFile) / sizeof(Cliente);

	fclose(pFile);

	return cantidad;
}

Cliente Archivo_Cliente::leer_clientes(int pos) {
	
	Cliente clientes;
	FILE* p;
	p = fopen("clientes.dat", "rb");

	if (p == nullptr) {
		cout << "Error al abrir el archivo" << endl;
	}

	fseek(p, pos * sizeof(Cliente), SEEK_SET);
	fread(&clientes, sizeof(Cliente), 1, p);
	fclose(p);

	return clientes;
}

int Archivo_Cliente::get_cantidad_Activa(int cantidad)
{
	  int contador = 0;

	for (int i = 0; i < cantidad; i++)
	{
		Cliente clientes;
		clientes = leer_clientes(i);
		if (clientes.getEstado())
		{
			contador++;
		}
	}
	return contador;
}

void Archivo_Cliente::listar_clientes(int cantidad) {
	Cliente cli;
	for (int i = 0; i < cantidad; i++) {
		cli = leer_clientes(i);
		if (cli.getEstado() == true) {
			cli.Mostrar();
		}
	}
}

void Archivo_Cliente::modificar_cliente() {
	int op;
	Cliente cliente;
	int cant = cantidad_clientes();
	listar_clientes(cant);
	cout << endl;
	cout << "Ingrese de ID del cliente que desea modificar: ";
	cin >> op;

	cliente = leer_clientes(op - 1);

	while (op<0 || op>cant || cliente.getEstado() == false)
	{
		cout << "ingrese una opcion correcta: ";
		cin >> op;
	}
	if (op != 0)
	{
		cliente = leer_clientes(op - 1);
		cliente.Cargar();

		char op2;
		cout << "esta seguro de que desea modificar el cliente?" << endl;
		cout << "[S/N]: ";
		cin >> op2;
		if (op2 == 's' || op2 == 'S')
		{
			Guardar_Modificado(cliente, op -1);
			system("cls");
			cout << "Se modifico el cliente exitosamente..." << endl;
		}
		else if (op2 == 'n' || op2 == 'N') {
			system("cls");
			cout << "No se pudo modificar..." << endl;
		}
	}
}

bool Archivo_Cliente::Guardar_Modificado(Cliente cliente, int pos)
{
	FILE* p;
	p = fopen("clientes.dat", "rb+");
	if (p == nullptr) {
		cout << "No se pudo abrir el archivo" << endl;
		return false;
	}
	fseek(p, pos * sizeof(Cliente), SEEK_SET);
	fwrite(&cliente, sizeof(Cliente), 1, p);
	fclose(p);

	return true;
}

void Archivo_Cliente::baja_Logica(){
	int op;
	Cliente cliente;
	int cant = cantidad_clientes();
	listar_clientes(cant);
	cout << std::endl;
	cout << "Ingrese de ID del cliente que desea eliminar: ";
	cin >> op;

	cliente = leer_clientes(op - 1);
	while (op<0 || !ExisteCliente(op) || !cliente.getEstado())
	{
		cout << "ingrese una opcion correcta: ";
		cin >> op;
		cliente = leer_clientes(op - 1);
	}
		char op2;
		cout << "esta seguro de que desea eliminar el cliente?" << endl;
		cout << "[S/N]: ";
		cin >> op2;
		if (op2 == 's' || op2 == 'S')
		{

			cliente.setEstado(false);
			Guardar_Modificado(cliente, op -1);
			system("cls");
			cout << "Se elimino el cliente exitosamente..." << endl;
		}
		else {
			system("cls");
			cout << "No se elimino el cliente..." << endl;
		}
}

bool Archivo_Cliente::ExisteCliente(int id)
{
	int cantidadNoActiva = cantidad_clientes();
	Cliente cliente;

	for (int i = 0; i < cantidadNoActiva; i++)
	{
		cliente = leer_clientes(i);
		if (cliente.getId_Cliente() == id && cliente.getEstado())
		{
			return true;
		}
	}
	return false;
}