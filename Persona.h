#pragma once
#include <iostream>
#include <cstring>

using namespace std;
class Persona
{
protected:
	char nombre[30];
	char apellido [50];
	int edad;
	char direccion[50];
	char telefono[10];
	public:
		
		void setNombre(string );
		void setApellido(string);
		void setEdad(int);
		void setDireccion(string);
		void setTelefono(string);
		string getNombre();
		string getApellido();
		int getEdad();
		string getDireccion();
		string getTelefono();		
};

