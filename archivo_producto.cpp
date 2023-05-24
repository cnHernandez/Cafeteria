#include "archivo_producto.h"
#include "Producto.h"
#include "Archivo_Categoria.h"
#include "Categoria.h"
#include "Menu.h"
#include <iostream>
#include <string>
#include <fstream>

using namespace std;

void archivo_producto::guardar(Producto producto)
{
    FILE* p;
    p = fopen("Producto.dat", "ab");
    if (p == nullptr)
    {
        std::cout << "Error para guardar el Producto" << std::endl;
    }
    fwrite(&producto, sizeof(Producto), 1, p);
    fclose(p);
}
bool archivo_producto::guardar(Producto producto, int posicion)
{
    FILE* p;
    p = fopen("Producto.dat", "rb+");
    if (p == nullptr) {
        std::cout << "No se pudo abrir el archivo" << std::endl;
        return false;
    }
    fseek(p, posicion * sizeof(Producto), SEEK_SET);
    fwrite(&producto, sizeof(Producto), 1, p);
    fclose(p);

    return true;
}

int archivo_producto::cantidad_de_registros()
{
    int cantidad = 0;
    FILE* p;
    p = fopen("Producto.dat", "rb");
    if (p == nullptr)
    {
        return cantidad;
    }
    fseek(p, 0, SEEK_END);//mueve e cursor al final del archivo
    cantidad = ftell(p) / sizeof(Producto); // cuenta la cantidad de registros
    fclose(p);
    return cantidad;
}

Producto archivo_producto::leer_de_disco(int posicion)
{
    Producto producto;
    FILE* p;
    p = fopen("Producto.dat", "rb");

    if (p == nullptr) {
        std::cout << "Error al abrir el archivo" << std::endl;
    }

    fseek(p, posicion * sizeof(Producto), SEEK_SET);
    fread(&producto, sizeof(Producto), 1, p);
    fclose(p);

    return producto;
}

void archivo_producto::listar(int cantidad)
{ 
    for (int i = 0; i < cantidad; i++)
    {
        Producto producto;
        producto=leer_de_disco(i);
        if(producto.getEstado())
        {
        Archivo_Categoria acat;
        Categoria cat;
        cat=acat.leer_de_disco(producto.getId_Categoria()-1);
        if(cat.getEstado())
        {

        std::cout<<"------------------------------------------------"<<std::endl;
        producto.Mostrar();
        }
        }
    }
    std::cout << "------------------------------------------------" << std::endl;
}

int archivo_producto::get_cantidad_Activa(int cantidad)
{
    int contador = 0;

    for (int i = 0; i < cantidad; i++)
    {
        Producto producto;
        producto = leer_de_disco(i);
        if (producto.getEstado())
        {
            contador++;
        }
    }
    return contador;
}

void archivo_producto::baja_Logica()
{
    int op;
    Producto producto;
    int cant = cantidad_de_registros();
    listar(cant);
    std::cout << std::endl;
    std::cout << "Ingrese de ID del producto que desea eliminar: ";
    std::cin >> op;

    while (op<0 || op>cant)
    {
        std::cout << "ingrese una opcion correcta" << std::endl;
        std::cin >> op;
    }
    producto = leer_de_disco(op - 1);
    if (producto.getEstado() == false)
    {
        std::cout << "ingrese una opcion correcta" << std::endl;
        std::cin >> op;
    }
    else {

        char op2;
        system("cls");
        cout << "----------------------------------------" << endl;
        producto.Mostrar();
        cout << "----------------------------------------" << endl << endl;
        cout << endl;
        std::cout << "esta seguro de que desea eliminar al producto?" << std::endl;
        std::cout << "[S/N]: ";
        std::cin >> op2;
        if (op2 == 's' || op2 == 'S')
        {

            producto.setEstado(false);
            guardar(producto, op - 1);
        }
    }
}

void archivo_producto::baja_Logica(int id)
{

    Producto Producto;
    int i = 0;
    while (i < cantidad_de_registros())
    {
        Producto = leer_de_disco(i);
        if (Producto.getId_Producto() == id)
        {
            Producto.setEstado(false);
            guardar(Producto, id - 1);
            break;
        }
        i++;
    }
}

int archivo_producto::modificar()
{
    int op;
    Producto producto;
    int cant = cantidad_de_registros();
    listar(cant);
    std::cout << "Ingrese de ID del producto que desea modificar: ";
    std::cin >> op;
    system("cls");
    cout << "Categorias existentes: " << endl;
    producto = leer_de_disco(op - 1);

    while (op<0 || op>cant || producto.getEstado() == false)
    {
        std::cout << "ingrese una opcion correcta: ";
        std::cin >> op;
    }
    if (op != 0)
    {
        producto = leer_de_disco(op - 1);
        producto.Cargar();

        char op2;
        std::cout << "esta seguro de que desea modificar al producto?" << std::endl;
        std::cout << "[S/N]: ";
        std::cin >> op2;
        if (op2 == 's' || op2 == 'S')
        {
            guardar(producto, op - 1);
        }
    }
    return op;
}
void archivo_producto::obtener_productos(Producto* prod, int cantidad)
{
    FILE* pFile;
    pFile = fopen("Producto.dat", "rb");

    if (pFile == nullptr)
    {
        cout << "Error al abrir el archivo" << endl;
    }

    fread(prod, sizeof(Producto), cantidad, pFile);

    fclose(pFile);
}
void archivo_producto::listaXcategoria()
{

    int cant = cantidad_de_registros();
    Archivo_Categoria Categorias;
    int CantCat = Categorias.cantidad_categorias();
    Categorias.listar_categorias(CantCat);
    Producto* prod = new Producto[cant];
    obtener_productos(prod, cant);
    Categoria Cat;
    int idcat;
    cout << "ingrese el ID# de la Categoria a listar: " ;
    cin >> idcat;
   
    while (idcat <= 0 || idcat > cant)
    {
		cout << "ID# de Categoria invalido: " << endl;
		cout << "ingrese el ID# de la Categoria a listar: " ;
		cin >> idcat;
	}
    Cat = Categorias.leer_de_disco(idcat - 1);
    while (Cat.getEstado() != true)
    {
        cout << "ID# de Categoria invalido: " << endl;
        cout << "ingrese el ID# de la Categoria a listar: " ;
        cin >> idcat;
        Cat = Categorias.leer_de_disco(idcat - 1);

    }
    
    system("cls");

    cout << "Productos con ID# de Categoria: " << idcat << endl << endl;
            while (idcat < 0 || idcat > CantCat)
            {
					cout << "No existe la categoria a listar " << endl;
                    cout << "ingrese el ID# de la Categoria a listar: " ;
                    cin >> idcat;
                    Cat = Categorias.leer_de_disco(idcat - 1);
			}
    int cont = 0;
    for (int i = 0; i < cant; i++)
    {
        if (idcat == prod[i].getId_Categoria() && prod[i].getEstado())
        {
                cont++;
                cout << "------------------------------" << endl;
                prod[i].Mostrar();
                cout << "------------------------------" << endl;    
        }
    }
        Menu menu;
        char desicion;
        if (cont == 0)
        { 
			cout << "No hay productos con ID# de Categoria: " << idcat << endl;
            cout << "¿Desea cargar uno? (S/N)" << endl;
            cin >> desicion;
            system("cls");
            if (desicion == 'S' || desicion == 's')
            {
                menu.menu_productos();
            }
            else if(desicion == 'N' || desicion == 'n'){
                return;
            }
		}
    

    delete[] prod;
}

bool archivo_producto::Existe(int op)
{
    Producto prod;
    for (int i = 0; i < cantidad_de_registros(); i++)
    {
        prod = leer_de_disco(i);
        if (prod.getId_Producto() == op)
        {
            return true;
        }

    }
    return false;

}

void archivo_producto::listaXrango(float precio1, float precio2)
{
    system("cls");
    int cant = cantidad_de_registros();
    Producto reg;
    if (precio1 < precio2) {
        cout << "Los productos cuyo precio rondan entre " << precio1 << " y " << precio2 << " son:" << endl << endl;
    }
    else {
        cout << "Los productos cuyo precio ronda entre " << precio2 << " y " << precio1 << " son:" << endl << endl;
    }
    for (int i = 0; i < cant; i++) {
        reg = leer_de_disco(i);
        if ((reg.getPrecio() >= precio1) && (reg.getPrecio() <= precio2) && (reg.getEstado()) || (reg.getPrecio() >= precio2) && (reg.getPrecio() <= precio1) && (reg.getEstado())) {
            cout << "----------------------------------------------" << endl;
            reg.Mostrar();
        }
    }
    cout << "----------------------------------------------" << endl;
}
