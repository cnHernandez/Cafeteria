#pragma once
#include "Venta.h" 
#include "Archivo_Venta.h"

using namespace std;

class Archivo_bkp
{
private: 
string _ruta;

public:
	void HacerCopiaDeSeguridad();
	void RestaurarCopiaDeSeguridad();
	bool guardar_copia(Venta * venta, int );
	Archivo_bkp(string ruta);
	Archivo_bkp();
	int getCantidadRegistros();
	Venta leer_ventasBK(int);
	void vaciar_ventas();
	void vaciar_BKP();
	void leer_BK(Venta* vec, int pos);
};

