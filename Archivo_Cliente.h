#pragma once
#include "Cliente.h"
class Archivo_Cliente
{
public:
	bool guardarEnDisco(int);
	void guardar(Cliente cli);
	int cantidad_clientes();
	Cliente leer_clientes(int pos);
	int get_cantidad_Activa(int);
	void listar_clientes(int);

};

