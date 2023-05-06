#pragma once
#include <iostream>
#include <string>
#include "Venta.h"

class Archivo_Venta
{
	public:

		bool guardarEnDisco(int);
		void obtener_venta(Venta * prod, int cantidad);
		void guardar(Venta venta);
		int cantidad_ventas();
		Venta leer_ventas(int pos);
		int get_cantidad_Activa(int);
		void listar_ventas(int);
		void listar_x_cliente();
		void listar_x_fecha();


		
		

};

