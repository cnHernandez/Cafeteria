#include "Persona.h"
#include <iostream>
#include <cstring>

using namespace std;

void Persona::setNombre(string nombre)
{
	strcpy(this->_nombre, nombre.c_str());
}

void Persona::setApellido(string apellido)
{
	strcpy(this->_apellido, apellido.c_str());
}

void Persona::setEdad(int edad)
{
	this->_edad = edad;
}

void Persona::setDireccion(string direccion)
{
	strcpy(this->_direccion, direccion.c_str());
}

void Persona::setTelefono(string telefono)
{
	strcpy(this->_telefono, telefono.c_str());
}

void Persona::setEstado(bool estado)
{
	this->_estado = estado;
}

string Persona::getNombre()
{
	return _nombre;
}

string Persona::getApellido()
{
	return _apellido;
}

int Persona::getEdad()
{
	return _edad;
}

string Persona::getDireccion()
{
	return _direccion;
}

string Persona::getTelefono()
{
	return _telefono;
}

bool Persona::getEstado()
{
	return _estado;
}

void Persona::CargarPersona()
{
	cout << "Ingrese el nombre: ";
	cin.ignore();
	cin.getline(_nombre, 30);
	cout << "Ingrese el apellido: ";
	cin.getline(_apellido, 50);
	cout << "Ingrese edad: ";
	cin >> _edad;
	cin.ignore();
	cout << "Ingrese direccion: ";
	cin.getline(_direccion, 50);
	cout << "Ingrese telefono: ";
	cin.getline(_telefono, 10);
}

void Persona::MostrarPersona()
{
	cout << "Nombre: " << _nombre << endl;
	cout << "Apellido: " << _apellido << endl;
	cout << "Direccion: " << _direccion << endl;
	cout << "Edad: " << _edad << endl;
	cout << "Telefono: " << _telefono << endl;
}