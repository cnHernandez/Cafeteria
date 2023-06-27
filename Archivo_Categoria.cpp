#include "archivo_producto.h"
#include "Producto.h"
#include "Archivo_Categoria.h"
#include "Categoria.h"
#include <iostream>
#include <string>
#include <fstream>

using namespace std;

void Archivo_Categoria::baja_Logica()
{
    int op;
    Categoria categoria;
    Archivo_Categoria cat;
    int cant = cantidad_categorias();
    listar_categorias(cant);
    cout << endl;
    cout << "Ingrese de ID del categoria que desea eliminar: ";
    cin >> op;

    while (op<0 || op>cant)
    {
        cout << "ingrese una opcion correcta" << endl;
        cin >> op;
    }
    categoria = leer_de_disco(op - 1);
    if (categoria.getEstado() == false)
    {
        cout << "ingrese una opcion correcta" << endl;
        cin >> op;
    }
    else {

        char op2;
        system("cls");
        categoria.mostrar();
        cout << "esta seguro de que desea eliminar la categoria?" << endl;
        cout << "[S/N]: ";
        cin >> op2;
        if (op2 == 's' || op2 == 'S')
        {

            categoria.setEstado(false);
            guardar_Categorias(categoria, op-1);
        }
    }
}

bool Archivo_Categoria::guardar_Categorias(Categoria cat, int posicion)
{
    FILE* p;
    p = fopen("categoria.dat", "rb+");
    if (p == nullptr) {
        cout << "No se pudo abrir el archivo" <<endl;
        return false;
    }
    fseek(p, posicion * sizeof(Categoria), SEEK_SET);
    fwrite(&cat, sizeof(Categoria), 1, p);
    fclose(p);

    return true;
}

void Archivo_Categoria::guardar(Categoria cat)
{

    FILE* pFile;

    pFile = fopen("categoria.dat", "ab");

    if (pFile == nullptr)
    {
        cout << "Error para guardar la Categoria" << endl;
        return;
    }
    else {
        fwrite(&cat, sizeof(Categoria), 1, pFile);

        fclose(pFile);
    }
}

Categoria Archivo_Categoria::leer_de_disco(int posicion)
{
    Categoria categoria;
    FILE* p;
    p = fopen("categoria.dat", "rb");

    if (p == nullptr) {
        cout << "Error al abrir el archivo" <<endl;
    }

    fseek(p, posicion * sizeof(Categoria), SEEK_SET);
    fread(&categoria, sizeof(Categoria), 1, p);
    fclose(p);

    return categoria;
}


int Archivo_Categoria::generar_categoria()
{
    return cantidad_categorias() + 1;
}

int Archivo_Categoria::cantidad_categorias()
{
    FILE* pFile;
    int cantidad = 0;

    pFile = fopen("categoria.dat", "rb");

    if (pFile == nullptr)
    {
        return 0;
    }

    fseek(pFile, 0, SEEK_END);
    cantidad = ftell(pFile) / sizeof(Categoria);

    fclose(pFile);

    return cantidad;
}
/*Categoria Archivo_Categoria::leer_categorias(int pos)
{
    Categoria cat;
    FILE* pFile;
    pFile = fopen("categoria.dat", "rb");
    if (pFile == nullptr)
    {
        cout << "No se pudo abrir el archivo" << endl;
        return cat;
    }

    fseek(pFile, pos * sizeof(Categoria), SEEK_SET);
    bool ok = fread(this, sizeof(Categoria), 1, pFile);
    if (ok == false)
    {
        cout << "No se pudo leer el archivo" << endl;
    }

    fclose(pFile);
    return cat;
}
*/

FILE* Archivo_Categoria::abrirArchivo()
{
    FILE* pFile;
    pFile = fopen("categoria.dat", "rb");

    if (pFile == NULL)
    {
        cout << "Error al abrir el archivo" << endl;
    }
    return pFile;
}


void Archivo_Categoria::obtener_categorias(Categoria* cat, int cantidad)
{
    FILE* pFile = abrirArchivo();

    fread(cat, sizeof(Categoria), cantidad, pFile);

    fclose(pFile);
}


/*bool Archivo_Categoria::guardarEnDisco(int pos) {
    FILE* p;
    p = fopen("categoria.dat", "rb+");
    if (p == NULL) {
        return false;
    }
    bool ok;
    fseek(p, pos * sizeof(Categoria), SEEK_SET);
    ok = fwrite(this, sizeof(Categoria), 1, p);
    fclose(p);
    return ok;
}
*/
/*int Archivo_Categoria::buscarCategoria(int ID) {
    Categoria c;
    int i, cant = cantidad_categorias();
    for (i = 0; i < cant; i++) {
        c = leer_categorias(i);
        if (ID == c.get_id()) {
            return i;
        }
    }
    return -1;
}*/

void Archivo_Categoria::listar_categorias(int cantidad)
{

    for (int i = 0; i < cantidad; i++)
    {
        Categoria categoria;
        categoria = leer_de_disco(i);
        if (categoria.getEstado())
        {
          categoria.mostrar();
        }
    }
}
void Archivo_Categoria::modificar_categorias()
{
    Archivo_Categoria ac;
    Categoria c;
    int cant_cat = ac.cantidad_categorias();
    Categoria* cat = new Categoria[cant_cat];
    if (cat == nullptr) {
        cout << "ERROR CON LA MEMORIA DINAMICA" << endl;
        return;
    }
   
    ac.obtener_categorias(cat, cant_cat);
    ac.listar_categorias(cant_cat);
    int cod;
    cout << endl << "ingresar codigo a modificar: ";
    cin >> cod;
    system("pause");
    system("cls");
    for (int i = 0; i < cant_cat; i++)
    {
        if (cod == cat[i].get_id())
        {
            cat[i].mostrar();
            cout << endl;
            char nuevo_nombre[30];
            cat[i].cargar();
            system("pause");
            system("cls");
            cat[i].sobreescribir_categoria(c, i);
            cout << "Categoria modificada..." << endl << endl;
            cat[i].mostrar();
            system("pause");
            system("cls");
        }
    }
delete[] cat;
}
void Archivo_Categoria::agregar_categoria()
{
    Categoria cat;
    Archivo_Categoria ac;
    system("cls");

    cat.cargar();
    ac.guardar(cat);
    system("cls");
    cout << "Se guardo la categoria " << cat.getNombre() << " exitosamente" << endl;
    system("pause");
    system("cls");
    cat.mostrar();
    cout << endl;
    system("pause");
}

int Archivo_Categoria::get_cantidad_Activa(int cantidad)
{
    int contador = 0;

    for (int i = 0; i < cantidad; i++)
    {
        Categoria categoria;
        categoria = leer_de_disco(i);
        if (categoria.getEstado())
        {
            contador++;
        }
    }
    return contador;
}


bool Archivo_Categoria::Existe(int op)
{
    Categoria cat;
    for (int i = 0; i < cantidad_categorias(); i++)
    {
        cat = leer_de_disco(i);
        if (cat.get_id() == op && cat.getEstado())
        {
            return true;
        }
    }
    return false;
}
