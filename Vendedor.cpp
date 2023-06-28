#include <iostream>
#include "Archivo_Vendedor.h"

using namespace std;

Vendedor::Vendedor()
{
	Archivo_Vendedor Archivo;
	id_vendedor = Archivo.Cantidad_vendedores() + 1;
	_estado = true;
}

void Vendedor::setId_Vendedor(int id_vendedor)
{
	this->id_vendedor = id_vendedor;
}

int Vendedor::getId_Vendedor()
{
	return id_vendedor;
}

void Vendedor::Cargar()
{
	cout << "-------------------------------" << endl;
	cout << "Cargue los datos del vendedor " << id_vendedor << endl;
	Persona::CargarPersona();
	cout << "-------------------------------" << endl;
}

void Vendedor::Mostrar()
{
	cout << "-------------------------------" << endl;
	cout << "ID del vendedor: " << id_vendedor << endl;
	Persona::MostrarPersona();
	cout << "-------------------------------" << endl;
}