#include "Persona.h"
#include <iostream>
#include <cstring>

using namespace std;

void Persona::setNombre(string nombre)
{
	strcpy(this->nombre, nombre.c_str());
}

void Persona::setApellido(string apellido)
{
	strcpy(this->apellido, apellido.c_str());
}

void Persona::setEdad(int edad)
{
	this->edad = edad;
}

void Persona::setDireccion(string direccion)
{
	strcpy(this->direccion, direccion.c_str());
}

void Persona::setTelefono(string telefono)
{
	strcpy(this->telefono, telefono.c_str());
}

string Persona::getNombre()
{
	return nombre;
}

string Persona::getApellido()
{
	return apellido;
}

int Persona::getEdad()
{
	return edad;
}

string Persona::getDireccion()
{
	return direccion;
}

string Persona::getTelefono()
{
	return telefono;
}

