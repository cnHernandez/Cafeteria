#pragma once
#include "Vendedor.h"
class Archivo_Vendedor
{
public:
	void Guardar(Vendedor ven);
	bool Guardar_Modificado(Vendedor, int);
	int Cantidad_vendedores();
	Vendedor Leer_vendedores(int pos);
	int Get_cantidad_Activa(int);
	void Listar_Vendedor(int);
	void Modificar_Vendedor();
	void Baja_Logica();
	bool ExisteVendedor(int id);
	void obtener_vendedor(Vendedor* vendedor, int cant);
};

