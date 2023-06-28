#pragma once
#include <string>

using namespace std;
class Persona
{
protected:
	char _nombre[30];
	char _apellido [30];
	int _edad;
	char _direccion[50];
	char _telefono[10];
	bool _estado;

public:	
	void setNombre(string );
	void setApellido(string);
	void setEdad(int);
	void setDireccion(string);
	void setTelefono(string);
	void setEstado(bool);
	void CargarPersona();
	void MostrarPersona();

	string getNombre();
	string getApellido();
	int getEdad();
	string getDireccion();
	string getTelefono();		
	bool getEstado();
};

