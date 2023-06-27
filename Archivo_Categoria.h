#pragma once
#include "Categoria.h"
class Archivo_Categoria
{
public:
	//bool guardarEnDisco(int);
	void guardar(Categoria cat);
	int generar_categoria();
	int cantidad_categorias();
	//Categoria leer_categorias(int pos);
	FILE* abrirArchivo();
	void obtener_categorias(Categoria* cat, int cantidad);
	//int buscarCategoria(int ID);
	int get_cantidad_Activa(int cantidad);
	Categoria leer_de_disco(int posicion);
	void baja_Logica();
	void listar_categorias(int);
	void modificar_categorias();
	void agregar_categoria();
	bool guardar_Categorias(Categoria cat, int posicion);
	bool Existe(int opcion);
};

