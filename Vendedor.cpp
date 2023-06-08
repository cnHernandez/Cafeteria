#include "Vendedor.h"
#include <iostream>
using namespace std;
void Vendedor::setId_Vendedor(int id_vendedor)
{
	this->id_vendedor = id_vendedor;
}

int Vendedor::getId_Vendedor()
{
	return id_vendedor;
}

bool Vendedor::Cargar()
{
	return true;
}

void Vendedor::Mostrar()
{
	
}