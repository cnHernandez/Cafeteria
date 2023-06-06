#include "Producto.h"
#include <iostream>
#include <cstring>
#include <fstream>
#include "archivo_producto.h"
#include "Archivo_Categoria.h"
#include "Menu.h"


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

void Producto::setStock(int nStock)
{
	stock = nStock;
}

void Producto::setPrecioCompra(float precio_compra)
{
	this->precio_compra = precio_compra;
}

float Producto::getPrecioCompra()
{
	return precio_compra;
}

int Producto::getStock()
{
	return stock;
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

void Producto::AgregarStock()
{
	int cantidad;
	std::cout << "Ingrese la cantidad de stock a agregar: ";
	std::cin >> cantidad;
	stock += cantidad;
}

void Producto::RestarStock(int cantidad)
{
	stock -= cantidad;
}

bool Producto::Cargar()
{
    Archivo_Categoria arch;
    if (arch.cantidad_categorias() > 0) {
        CargarCategoria();
        std::string Nombre;
        std::cout << "Ingrese el nombre del Producto: ";
        std::cin.ignore();
        getline(std::cin, Nombre);
        setNombre(Nombre);
        std::cout << "Ingrese el precio de compra del Producto: ";
        std::cin >> precio_compra;
        setPrecioCompra(precio_compra);
        std::cout << "Ingrese el precio de venta del Producto: ";
        std::cin >> precio;
        setPrecio(precio);
        cout << "ingrese la cantidad a Stockear: " << endl;
        cin >> stock;
        setStock(stock);
        return true;
    }
    else {
        std::cout << "Primero deben haber Categorias activas" << std::endl;
        system("pause");
        char desicion;
        Menu menu;
        std::cout << "¿Desea generar una categoria nueva? (S/N): ";
        std::cin >> desicion;
        if (desicion == 'S' || desicion == 's') {
            
            menu.menu_categorias();
        }
        else if (desicion == 'N' || desicion == 'n')
        {
            menu.menu_productos();
        }

        return false;
    }
}

void Producto::CargarCategoria()
{
    int op;
    Archivo_Categoria ArchivoC;
    ArchivoC.listar_categorias(ArchivoC.cantidad_categorias());
    std::cout << std::endl;
    std::cout << "Ingrese de ID de la categoria a la que pertenece el producto: ";
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
    std::cout << "-Stock del Producto: " << getStock() << std::endl;
}


