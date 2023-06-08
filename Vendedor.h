#pragma once
class Vendedor
{
	private:
	int id_vendedor;
	
	public:
		void setId_Vendedor(int id_vendedor);
		int getId_Vendedor();
		bool Cargar();
		void Mostrar();
};

