//Clase especificamente hecha para ser relacionada con la cantidad de productos en una misma venta
#pragma once
#include <string>
using namespace std;

class DetalleVenta
{
private:
	int id_producto;
	int id_categoria;
	int cantidad;
	float precio;
	float precio_compra;
	char _nombre[50];

public:
	//SETS
    DetalleVenta();
    void setPrecioCompra(float precio_compra);
    void setPrecio(float nPrecio);
    void setNombre(string _nombre);
    void setId_Categoria(int id_categoria);
    void setId_Producto(int id_producto);
    void setCantidad(int cant);
    //GETS
    float getPrecioCompra();
    string getNombre();
    int getId_Categoria();
    float getPrecio();
    int getId_Producto();
    int getCantidad();
};

