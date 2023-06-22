#include "Producto.h"
#include <iostream>
#include <cstring>
#include <fstream>
#include "archivo_producto.h"
#include "Archivo_Categoria.h"
#include "Menu.h"
#include "rlutil.h"

using namespace std;

Producto::Producto()
{
    archivo_producto Archivo;
    id_producto = Archivo.cantidad_de_registros() + 1;
    estado = true;
    stock = 0;
  
}

void Producto::setNombre(string Nombre)
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

string Producto::getNombre()
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

void Producto::AgregarStock(int can)
{
	stock += can;
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
        cout << "Ingrese el nombre del Producto: ";
        cin.ignore();
        cin.getline(_nombre , 50);
        for (int i = 0; i < strlen(_nombre); i++)
        {
            if (isdigit(_nombre[i])) {
               rlutil::setColor(rlutil::RED);
                cout << "El nombre no puede contener numeros" << endl;
                rlutil::setColor(rlutil::WHITE);
                cout << "Ingrese el nombre: ";
                cin.getline(_nombre, 30);
            }
        }
        setNombre(_nombre);
        cout << "Ingrese el precio de compra del Producto: ";
        cin >> precio_compra;

        if (precio_compra < 0 || precio_compra > 100000)
        {
            rlutil::setColor(rlutil::RED);
            cout << "ingrese un precio razonable" << endl;
            rlutil::setColor(rlutil::WHITE);
            cout << "Ingrese el precio de compra del Producto: ";
            cin >> precio;
        }
  
        setPrecioCompra(precio_compra);
       
        cout << "Ingrese el precio de venta del Producto: ";
        cin >> precio;
      
        if (precio < 0 || precio > 100000)
        {
            rlutil::setColor(rlutil::RED);
            cout<<"ingrese un precio razonable"<<endl;
            rlutil::setColor(rlutil::WHITE);
            cout << "Ingrese el precio de venta del Producto: ";
            cin >> precio;
        }
        setPrecio(precio);
        cout << "ingrese la cantidad a Stockear: ";
        cin >> stock;
        if (stock < 0)
        {
            rlutil::setColor(rlutil::RED);
            cout<<"ingrese un stock razonable"<<endl;
            rlutil::setColor(rlutil::WHITE);
            cout << "ingrese la cantidad a Stockear: " << endl;
            cin >> stock;
        }
        setStock(stock);
        return true;
    }
    else {
        rlutil::setColor(rlutil::RED);
        cout << "Primero deben haber Categorias activas" << endl;
        system("pause");
        rlutil::setColor(rlutil::WHITE);
        char desicion;
        Menu menu;
        cout << "¿Desea generar una categoria nueva? (S/N): ";
        cin >> desicion;
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
    cout << endl;
    cout << "Ingrese de ID de la categoria a la que pertenece el producto: ";
    cin >> op;

    while (ArchivoC.Existe(op) == false)
    {
        rlutil::setColor(rlutil::RED);
        cout << "ingrese una opcion correcta" << endl;
        rlutil::setColor(rlutil::WHITE);
        cin >> op;
    }
    if (op != 0)
    {
        setId_Categoria(op);
    }

}

void Producto::Mostrar()
{
    cout << "-Nombre del Producto: " << getNombre() << endl;
    cout << "#ID del Producto: " << getId_Producto() << endl;
    cout << "#ID de la Categoria: " << getId_Categoria()<< endl;
    cout << "-Precio de Venta del Producto: " << getPrecio() << endl;
    cout << "-Precio de Compra del Producto: " << getPrecioCompra() << endl;
    cout << "-Stock del Producto: " << getStock() << endl;
}


