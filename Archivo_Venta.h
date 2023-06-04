#pragma once
#include <iostream>
#include <string>
#include "Venta.h"

class Archivo_Venta
{
	public:

		bool guardarEnDisco(int);
		bool guardar_modificado(Venta, int);
		void obtener_venta(Venta * prod, int cantidad);
		void guardar(Venta venta);
		int cantidad_ventas();
		Venta leer_ventas(int pos);
		Venta leer_ventaBK(Venta* vec, int pos);
		bool guardar_bkp(Venta* vec, int cantidad);
		int get_cantidad_Activa(int);
		void listar_ventas(int);
		void listar_x_cliente();
		void listar_x_fecha();
		void listar_x_producto();
		void recaudacion_x_vendedor();
		void recaudacion_x_producto();
		void recaudacion_x_categoria();
		void BajaLogica();
		int Modificar_Venta();




		//void guardarVentas(const vector<Venta>& ventas);
		//void listar_ventasDin(vector<Venta>ventas);
		
};

		

		


		
		



