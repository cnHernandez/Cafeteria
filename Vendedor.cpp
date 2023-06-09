#include "Vendedor.h"
#include "Archivo_Vendedor.h"
#include <iostream>
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
	cout << "-----------------------" << endl;
	cout << "Cargue los datos del vendedor " << id_vendedor << endl;
	cout << "Nombre: " << endl;
		cin >> _nombre;
	cout << "Apellido: " << endl;
	cin >> _apellido;
	cout << "Edad: " << endl;
	cin >> _edad;
	cout << "Direccion: " <<endl;
	cin >> _direccion;
	cout << "Telefono: " << endl;
	cin >> _telefono;
	cout << "-----------------------" << endl;
}

void Vendedor::Mostrar()
{
	cout << "-----------------------" << endl;
	cout << "ID del vendedor: " << id_vendedor << endl;
	cout << "Nombre: " << getNombre() << endl;
	cout << "Apellido: " << getApellido() << endl;
	cout << "Edad: " << getEdad() << endl;
	cout << "Direccion: " << getDireccion() << endl;
	cout << "Telefono: " << getTelefono() << endl;
	cout << "-----------------------" << endl;
}