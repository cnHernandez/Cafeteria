#pragma once
#include "Persona.h"
class Cliente: public Persona
{
private:
	int id_cliente;

public:
	Cliente();
	void setId_Cliente(int id_cliente);
	int getId_Cliente();
	void Cargar();
	void Mostrar();	
};

