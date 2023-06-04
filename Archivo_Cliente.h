#pragma once
#include "Cliente.h"

class Archivo_Cliente
{
public:
	bool guardarEnDisco(int);
	void guardar(Cliente cli);
	bool Guardar_Modificado(Cliente, int);
	int cantidad_clientes();
	Cliente leer_clientes(int pos);
	int get_cantidad_Activa(int);
	void listar_clientes(int);
	void modificar_cliente();
	void baja_Logica();
	bool ExisteCliente(int id);
};

