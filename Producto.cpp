#include "Producto.h"
#include <iostream>
#include <cstring>
#include <fstream>
#include "archivo_producto.h"
#include "Archivo_Categoria.h"


Producto::Producto()
{
    archivo_producto Archivo;
    id_producto = Archivo.cantidad_de_registros() + 1;
    estado = true;
  
}

void Producto::setNombre(std::string Nombre)
{
    strcpy_s(_nombre, Nombre.c_str());
}

void Producto::setId_Producto(int ID)
{
    id_producto = ID;
}
void Producto::setId_Categoria(int ID)
{
    id_categoria = ID;
}

void Producto::setEstado(bool nEstado)
{
    estado = nEstado;
}

std::string Producto::getNombre()
{
    return _nombre;
}

int Producto::getId_Categoria()
{
    return id_categoria;
}
int Producto::getId_Producto()
{
    return id_producto;
}

bool Producto::getEstado()
{
    return estado;
}
float Producto::getPrecio()
{
	return precio;
}
void Producto::setPrecio(float nPrecio)
{
	precio = nPrecio;
}

bool Producto::Cargar()
{
    Archivo_Categoria arch;
    if (arch.cantidad_categorias() > 0) {
        CargarCategoria();
        std::string Nombre;
        std::cout << "Ingrese el nombre del Producto: " << std::endl;
        std::cin.ignore();
        getline(std::cin, Nombre);
        setNombre(Nombre);
        std::cout << "Ingrese el precio del Producto: " << std::endl;
        std::cin >> precio;
        setPrecio(precio);
        return true;
    }
    else {
        std::cout << "Primero deben haber Categorias activas" << std::endl;
        return false;
    }
}

void Producto::CargarCategoria()
{
    int op;
    Archivo_Categoria ArchivoC;
    ArchivoC.listar_categorias(ArchivoC.cantidad_categorias());
    std::cout << std::endl;
    std::cout << "Ingrese de ID de la categoria a..." << std::endl;
    std::cout << " ...la que pertenece el producto" << std::endl;
    std::cout << std::endl;
    std::cin >> op;

    while (ArchivoC.Existe(op) == false)
    {
        std::cout << "ingrese una opcion correcta" << std::endl;
        std::cin >> op;
    }
    if (op != 0)
    {
        setId_Categoria(op);
    }

}

void Producto::Mostrar()
{
    std::cout << "-Nombre del Producto: " << getNombre() << std::endl;
    std::cout << "#ID del Producto: " << getId_Producto() << std::endl;
   std::cout << "#ID de la Categoria: " << getId_Categoria()<< std::endl;
    std::cout << "-Precio del Producto: " << getPrecio() << std::endl;
}
