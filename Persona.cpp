#include "Persona.h"
#include <iostream>
#include <cstring>
#include "rlutil.h"

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
	for (int i = 0; i < strlen(_nombre); i++)
	{
		if (isdigit(_nombre[i])) {
			rlutil::setColor(rlutil::RED);
			cout << "El nombre no puede contener numeros" << endl;
rlutil::setColor(rlutil::WHITE);
			cout << "Ingrese el nombre: ";
			cin.getline(_nombre, 30);
		}
	}
	cout << "Ingrese el apellido: ";
	cin.getline(_apellido, 50);
	for (int i = 0; i < strlen(_apellido); i++)
	{
		if (isdigit(_apellido[i])) {
			rlutil::setColor(rlutil::RED);
			cout << "El apellido no puede contener numeros" << endl;
rlutil::setColor(rlutil::WHITE);
			cout << "Ingrese el apellido: ";
			cin.getline(_apellido, 50);
		}
	}
	cout << "Ingrese edad: ";
	cin >> _edad;
	if (_edad < 15 || _edad > 100)
	{
		rlutil::setColor(rlutil::RED);
		cout << "La edad debe ser mayor a 12 y menor a 100" << endl;
rlutil::setColor(rlutil::WHITE);
		cout << "Ingrese edad: ";
		cin >> _edad;
	}
	cin.ignore();
	cout << "Ingrese direccion: ";
	cin.getline(_direccion, 50);
	cout << "Ingrese telefono: ";
	cin.getline(_telefono, 10);
	for (int i = 0; i < strlen(_telefono); i++)
	{
		if (!isdigit(_telefono[i])) {
rlutil::setColor(rlutil::RED);
			cout << "El telefono no puede contener letras" << endl;
rlutil::setColor(rlutil::WHITE);
			cout << "Ingrese telefono: ";
			cin.getline(_telefono, 10);
		}
	}
}

void Persona::MostrarPersona()
{
	cout << "Nombre: " << _nombre << endl;
	cout << "Apellido: " << _apellido << endl;
	cout << "Direccion: " << _direccion << endl;
	cout << "Edad: " << _edad << endl;
	cout << "Telefono: " << _telefono << endl;
}