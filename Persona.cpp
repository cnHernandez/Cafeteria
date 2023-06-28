#include "Persona.h"
#include "rlutil.h"


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
	bool contieneNumeros = false;
	while (!contieneNumeros) {
		bool soloLetras = true;
		for (int i = 0; i < strlen(_nombre); i++) {
			if (isdigit(_nombre[i])) {
				soloLetras = false;
				break;
			}
		}

		if (!soloLetras) {
			rlutil::setColor(rlutil::RED);
			cout << "El nombre no puede contener numeros" << endl;
			rlutil::setColor(rlutil::BLACK);
			cout << "Ingrese el nombre: ";
			cin.getline(_nombre, 30);
		}
		else {
			contieneNumeros = true;
		}
	}

	cout << "Ingrese el apellido: ";
	cin.getline(_apellido, 30);
	contieneNumeros = false;
	while (!contieneNumeros) {
		bool soloLetras = true;
		for (int i = 0; i < strlen(_apellido); i++) {
			if (isdigit(_apellido[i])) {
				soloLetras = false;
				break;
			}
		}

		if (!soloLetras) {
			rlutil::setColor(rlutil::RED);
			cout << "El apellido no puede contener numeros" << endl;
			rlutil::setColor(rlutil::BLACK);
			cout << "Ingrese el apellido: ";
			cin.getline(_apellido, 30);
		}
		else {
			contieneNumeros = true;
		}
	}

	string input;
	cout << "Ingrese edad: ";
	getline(cin, input);

	bool esNumero = false;
	bool cumpleCondicion = false;

	while (!esNumero || !cumpleCondicion) {
		bool todosDigitos = true;
		for (char c : input) {
			if (!isdigit(c)) {
				todosDigitos = false;
				break;
			}
		}

		if (!todosDigitos) {
			rlutil::setColor(rlutil::RED);
			cout << "La edad debe ser un valor numerico. Ingrese nuevamente: ";
			rlutil::setColor(rlutil::BLACK);
			getline(cin, input);
			continue;
		}

		int edad = stoi(input);
		if (edad > 5 && edad < 100) {
			esNumero = true;
			cumpleCondicion = true;
		}
		else {
			rlutil::setColor(rlutil::RED);
			cout << "La edad debe ser mayor a 5 y menor a 100. Ingrese nuevamente: ";
			rlutil::setColor(rlutil::BLACK);
			getline(cin, input);
		}
	}
	_edad = stoi(input);

	cout << "Ingrese direccion: ";
	cin.getline(_direccion, 50);

	cout << "Ingrese telefono: ";
	cin.getline(_telefono, 30);
	for (int i = 0; i < strlen(_telefono); i++) {
		if (i > 10)
		{
			cout << "El telefono debe contener maximo 10 caracteres" << endl;
			cout << "Ingrese telefono: ";
			cin.getline(_telefono, 30);
		}
		bool contieneLetras = false;
		while (!contieneLetras) {
			bool soloNumeros = true;
			for (int i = 0; i < strlen(_telefono); i++) {

				if (!isdigit(_telefono[i])) {
					soloNumeros = false;
					break;
				}
			}

			if (!soloNumeros) {
				rlutil::setColor(rlutil::RED);
				cout << "El telefono no puede contener letras" << endl;
				rlutil::setColor(rlutil::BLACK);
				cout << "Ingrese el telefono: ";
				cin.getline(_telefono, 10);
			}
			else {
				contieneLetras = true;
			}
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