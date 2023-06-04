#pragma once
#include <iostream>
#include <string>
#include <vector>


using namespace std;

class Producto
{
private:
   
    int id_producto;
    int id_categoria;
    char _nombre[50];
    bool estado;
    float precio;
    int stock;
public:
    Producto();
    void setStock(int nStock);
    void setPrecio(float nPrecio);
    void setNombre(std::string _nombre);
    void setId_Categoria(int id_categoria);
    void setId_Producto(int id_producto);
    void setEstado(bool nEstado);

    int getStock();
    void AgregarStock();
    void RestarStock(int cantidad);
    std::string getNombre();
    int getId_Categoria();
    float getPrecio();
    int getId_Producto();
    bool getEstado();

    bool Cargar();
    void CargarCategoria();
    void Mostrar();
    
};

