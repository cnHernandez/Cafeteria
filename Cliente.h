#pragma once
#include "Persona.h"
class Cliente: public Persona
{
	private:
		int id_cliente;
		char _nombre[50];
		bool estado;
	public:
		Cliente();
		void setNombre(char _nombre[50]);
		void setEstado(bool estado);
		void setId_Cliente(int id_cliente);
		
		char* getNombre();
		bool getEstado();
		int getId_Cliente();
		
		bool Cargar();
		void Mostrar();
};

