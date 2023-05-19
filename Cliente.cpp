#include "Cliente.h"
#include "Archivo_Cliente.h"
#include <iostream>
#include <cstring>
using namespace std;
Cliente::Cliente()
{
	Archivo_Cliente Archivo;
	id_cliente = Archivo.cantidad_clientes() + 1;
	estado = true;
}

void Cliente::setNombre(char _nombre[50])
{
	strcpy(this->_nombre, _nombre);
}

void Cliente::setEstado(bool estado)
{
	this->estado = estado;
}

void Cliente::setId_Cliente(int id_cliente)
{
	this->id_cliente = id_cliente;
}

char* Cliente::getNombre()
{
	return _nombre;
}

bool Cliente::getEstado()
{
	return estado;
}

int Cliente::getId_Cliente()
{
	return id_cliente;
}

bool Cliente::Cargar()
{
	bool estado = false;
	
	cout << "Ingrese el nombre del cliente: ";
	cin.ignore();
	cin.getline(_nombre, 50);
	
	
	return estado;
}

void Cliente::Mostrar()
{
	cout << "-----------------------" << endl;
	cout << "Id: " << id_cliente << endl;
	cout << "Nombre: " << _nombre << endl;
	cout << "-----------------------" << endl << endl;
	
}






