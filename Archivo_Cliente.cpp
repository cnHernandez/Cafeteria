#include "Archivo_Cliente.h"
#include "Cliente.h"
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
		std::cout << "Error al abrir el archivo" << std::endl;
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

