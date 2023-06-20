#include "Archivo_producto.h"
#include "Producto.h"
#include "Archivo_Categoria.h"
#include "Categoria.h"
#include "Menu.h"
#include <iostream>
#include <string>
#include "rlutil.h"

using namespace std;

void archivo_producto::guardar(Producto producto)
{
    FILE* p;
    p = fopen("Producto.dat", "ab");
    if (p == nullptr)
    {
       cout << "Error para guardar el Producto" << endl;
    }
    fwrite(&producto, sizeof(Producto), 1, p);
    fclose(p);
}
bool archivo_producto::guardar(Producto producto, int posicion)
{
    FILE* p;
    p = fopen("Producto.dat", "rb+");
    if (p == nullptr) {
        cout << "No se pudo abrir el archivo" << endl;
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
        cout << "Error al abrir el archivo" <<endl;
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
            rlutil::locate(45, 11);
        //cout<<"------------------------------------------------"<<endl;
        producto.Mostrar();
        }
        }
    }
        
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
    cout << endl;
    cout << "Ingrese de ID del producto que desea eliminar: ";
    cin >> op;

    while (op<0 || op>cant)
    {
        cout << "ingrese una opcion correcta" << endl;
        cin >> op;
    }
    producto = leer_de_disco(op - 1);
    if (producto.getEstado() == false)
    {
        cout << "ingrese una opcion correcta" << endl;
        cin >> op;
    }
    else {

        char op2;
        system("cls");
        cout << "----------------------------------------" << endl;
        producto.Mostrar();
        cout << "----------------------------------------" << endl << endl;
        cout << endl;
        cout << "esta seguro de que desea eliminar al producto?" << endl;
        cout << "[S/N]: ";
        cin >> op2;
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

void archivo_producto::modificar()
{
    int op;
    Producto producto;
    int cant = cantidad_de_registros();
    listar(cant);
    cout << "Ingrese de ID del producto que desea modificar: ";
    cin >> op;
    producto = leer_de_disco(op - 1);

    while (op<=0 || !Existe(op))
    {
        cout << "ingrese una opcion correcta: ";
        cin >> op;
    }
        producto = leer_de_disco(op - 1);
        producto.Cargar();
        char op2;
        cout << "esta seguro de que desea modificar al producto?" << endl;
        cout << "[S/N]: ";
        cin >> op2;
        if (op2 == 's' || op2 == 'S')
        {
            guardar(producto, op -1);
            system("cls");
            cout << "Se modifico el producto exitosamente..." << endl;
        }
        else if (op2 == 'n' || op2 == 'N') {
            cout << "No se pudo modificar..." << endl;
        
        }
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
    if (prod == nullptr) {
        cout << "ERROR CON LA MEMORIA DINAMICA" << endl;
        return;
    }
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
    int cantidad = cantidad_de_registros();

    for (int i = 0; i < cantidad; i++)
    {
        prod = leer_de_disco(i);
        if ((prod.getId_Producto() == op) && (prod.getEstado()))
        {
            return true;
        }
    }
    return false;
}

void archivo_producto::listaXrango()
{
    system("cls");
    int cant = cantidad_de_registros();
    Producto reg;
    float precio1, precio2;
    cout << "Ingrese los rangos de precios: " << endl;
    cout << "de: ";
    cin>>precio1;
    cout << "a: ";
    cin>> precio2;
    if (precio1 > precio2) {
        cout << "Ingrese un rango correcto" << endl;
        cout << "Ingrese los rangos de precios: " << endl;
        cout << "de: ";
        cin >> precio1;
        cout << "a: ";
        cin >> precio2;
    }
    else {
        cout << "Los productos cuyo precio ronda entre " << precio2 << " y " << precio1 << " son:" << endl << endl;
    }
    for (int i = 0; i < cant; i++) {
        reg = leer_de_disco(i);
        if ((reg.getPrecio() >= precio1) && (reg.getPrecio() <= precio2) && (reg.getEstado()) )
        {  cout << "----------------------------------------------" << endl;
            reg.Mostrar();
        }
    }
    cout<< "----------------------------------------------" << endl;
}

bool archivo_producto::guardarVec(Producto * prod, int cantidadRegistrosAEscribir) {
   
    FILE* p = fopen("Producto.dat", "ab");
    if (p == NULL)
    {
        return false;
    }

    int cantidadRegistrosEscritos = fwrite(prod, sizeof(Producto), cantidadRegistrosAEscribir, p);
    fclose(p);
    return cantidadRegistrosEscritos == cantidadRegistrosAEscribir;
}

void archivo_producto::Stock(int id)
{
    Producto producto;
    int cant = cantidad_de_registros();
    listar(cant);
    system("cls");
    producto = leer_de_disco(id - 1);

    while (id<0 || producto.getEstado() == false)
    {
        cout << "ingrese una opcion correcta: ";
        cin >> id;
    }
    if (id != 0)
    {
        int encontrado = 0;
        int posicion = 0;

        for (int i = 0; i < cant; i++) {
            producto = leer_de_disco(i);

            if (producto.getId_Producto() == id && producto.getEstado()) {
                encontrado = 1;
                posicion = i;
                break;
            }
        }
        int st;
        cout << "INGRESE CANTIDAD DE STOCK: ";
        cin >> st;
        producto.AgregarStock(st);
        char op2;
        cout << "esta seguro de que desea modificar al producto?" << endl;
        cout << "[S/N]: ";
        cin >> op2;
        if (op2 == 's' || op2 == 'S')
        {
            guardar(producto, posicion);
        }
        system("pause");
        system("cls");
        cout << "PRODUCTO CON EL STOCK NUEVO" << endl;
        cout << "----------------------------------------------" << endl;
        producto.Mostrar();
        cout << "----------------------------------------------" << endl;
        system("pause");
    }

}

int archivo_producto::PosicionEnDisco(int id)
{
    Producto producto;
    int cant = cantidad_de_registros();
    int encontrado = 0;
    int posicion = 0;

    for (int i = 0; i < cant; i++) {
        producto = leer_de_disco(i);

        if (producto.getId_Producto() == id && producto.getEstado()) {
            encontrado = 1;
            posicion = i;
            return posicion;
        }
    }

    return -1;
}
