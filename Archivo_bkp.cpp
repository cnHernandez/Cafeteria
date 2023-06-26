#include "Archivo_bkp.h"
#include "Venta.h"
#include "Archivo_Venta.h"
#include <iostream>
#include "rlutil.h"

using namespace std;

Archivo_bkp::Archivo_bkp(string ruta)
{
	ruta = "ventas.bpk";
	_ruta = ruta;
}

Archivo_bkp::Archivo_bkp()
{
	_ruta = "ventas.bpk";
}

void Archivo_bkp::HacerCopiaDeSeguridad()
{
	Archivo_Venta _archivo;
	Archivo_bkp _archivoBkp("ventas.bpk");
	int cantidadRegistros = _archivo.cantidad_ventas();
	Venta* vec = new Venta[cantidadRegistros];

	if (vec == nullptr) {
		rlutil::setColor(rlutil::RED);
		cout << "Falla al realizar backup" << endl;
		rlutil::setColor(rlutil::BLACK);
		return;
	}

	_archivo.leer_ventaBK(vec, cantidadRegistros);
	_archivoBkp.vaciar_ventas();
	if (_archivoBkp.guardar_copia(vec, cantidadRegistros)) {
		cout << "Backup realizado correctamente" << endl;
	}
	else {
		rlutil::setColor(rlutil::RED);
		cout << "Falla al realizar backup" << endl;
		rlutil::setColor(rlutil::BLACK);
	}

	delete[]vec;
}

void Archivo_bkp::RestaurarCopiaDeSeguridad()
{
	Archivo_bkp _archivoBkp("ventas.bpk");
	Archivo_Venta _archivo;
	int cantidadRegistros = _archivoBkp.getCantidadRegistros();
	Venta * vec = new Venta [cantidadRegistros];

	if (vec == nullptr) {
		rlutil::setColor(rlutil::RED);
		cout << "Falla al restaurar backup" << endl;
		rlutil::setColor(rlutil::BLACK);
		return;
	}

	_archivoBkp.leer_BK(vec, cantidadRegistros);
	_archivoBkp.vaciar_BKP();
	if (_archivo.guardar_bkp(vec, cantidadRegistros)) {
		cout << "Backup restaurado correctamente" << endl;
	}
	else {
		rlutil::setColor(rlutil::RED);
		cout << "Falla al restaurar backup" << endl;
		rlutil::setColor(rlutil::BLACK);
	}

	delete[]vec;
}

int Archivo_bkp::getCantidadRegistros()
{
	FILE* p = fopen(_ruta.c_str(), "rb");

	if (p == NULL)
	{
		return 0;
	}

	fseek(p, 0, SEEK_END);
	int bytes = ftell(p);
	fclose(p);

	return bytes / sizeof(Venta);
}

bool Archivo_bkp::guardar_copia(Venta * reg, int cantidadRegistrosAEscribir)
{
	FILE* p = fopen(_ruta.c_str(), "ab");
	if (p == NULL)
	{
		return false;
	}

	int cantidadRegistrosEscritos = fwrite(reg, sizeof(Venta), cantidadRegistrosAEscribir, p);
	fclose(p);
	return cantidadRegistrosEscritos == cantidadRegistrosAEscribir;
}

Venta Archivo_bkp::leer_ventasBK(int nroRegistro)
{
	Venta aux;
	FILE* p = fopen(_ruta.c_str(), "rb");
	if (p == NULL)
	{
		return aux;
	}

	fseek(p, nroRegistro * sizeof(Venta), SEEK_SET);
	fread(&aux, sizeof(Venta), 1, p);
	fclose(p);
	return aux;
}

void Archivo_bkp::vaciar_ventas() {
	FILE* p = fopen("Ventas.dat", "wb");
	if (p == NULL)
	{
		return;
	}
	fclose(p);
}
void Archivo_bkp::vaciar_BKP() {
	FILE* p = fopen( _ruta.c_str() , "wb");
	if (p == NULL)
	{
		return;
	}
	fclose(p);
}

void Archivo_bkp::leer_BK(Venta* vec, int pos)
{
	FILE* p = fopen(_ruta.c_str(), "rb");
	if (p == NULL)
	{
		return;
	}

	fread(vec, sizeof(Venta), pos, p);
	fclose(p);
}