#pragma once
#include <iostream>
#include <string>



using namespace std;

class Producto
{
private:
    int id_producto;
    int id_categoria;
    char _nombre[50];
    bool estado;
public:
    Producto();
    void setNombre(std::string _nombre);
    void setId_Categoria(int id_categoria);
    void setId_Producto(int id_producto);
    void setEstado(bool nEstado);

    std::string getNombre();
    int getId_Categoria();
    int getId_Producto();
    bool getEstado();

    bool Cargar();
    void CargarCategoria();
    void Mostrar();
};

