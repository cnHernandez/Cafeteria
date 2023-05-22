#include "archivo_producto.h"
#include "Producto.h"
#include "Archivo_Categoria.h"
#include "Categoria.h"
#include <iostream>
#include <string>
#include <fstream>




using namespace std;

/*void Archivo_Categoria::baja_Logica()
{
    Categoria c;
    int cant_cat = cantidad_categorias();
    Categoria* cat = new Categoria[cant_cat];

    obtener_categorias(cat, cant_cat);
    listar_categorias();
    int cod;
    cout << endl << "ingresar el codigo de la Categoria a eliminar" << endl;
    cin >> cod;

    for (int i = 0; i < cant_cat; i++)
    {
        if (cod == cat[i].get_id())
        {
            std::cout << "Si elimina la Categoria se borrara/n el/los siguiente/s producto/s y sus precios asociados" << std::endl;
            Producto prod;
            archivo_producto aprod;
            int pos = 0;
           
            while (pos < aprod.cantidad_de_registros())
            {
                prod = aprod.leer_de_disco(pos);
                if (prod.getId_Producto() == cod && prod.getEstado())
                {
                    prod.Mostrar();
                    std::cout << std::endl;
                    pos++;
                }
                else {
                    pos++;
                }
            }

            char op2;
            std::cout << "esta seguro de que desea eliminar la Categoria?" << std::endl;
            std::cout << "[S/N]" << std::endl;
            std::cin >> op2;
            if (op2 == 's' || op2 == 'S')
            {

                cat[i].setEstado(false);
                
                delete[] cat;
                int posi = 0;
                while (posi < aprod.cantidad_de_registros())
                {
                    prod = aprod.leer_de_disco(posi);
                    if (prod.getId_Categoria() == cod)
                    {
                        
                        aprod.baja_Logica(prod.getId_Producto());
                        std::cout << std::endl;
                        posi++;

                    }
                    else {
                        posi++;
                    }
                        cat[i].sobreescribir_categoria(c, i);

                }
            }
            else {
                delete[] cat;
            }
        }
    }
}*/

void Archivo_Categoria::baja_Logica()
{

    int op;
    Categoria categoria;
    Archivo_Categoria cat;
    int cant = cantidad_categorias();
    listar_categorias(cant);
    std::cout << std::endl;
    std::cout << "Ingrese de ID del categoria que desea eliminar: ";
    std::cin >> op;

    while (op<0 || op>cant)
    {
        std::cout << "ingrese una opcion correcta" << std::endl;
        std::cin >> op;
    }
    categoria = leer_de_disco(op - 1);
    if (categoria.getEstado() == false)
    {
        std::cout << "ingrese una opcion correcta" << std::endl;
        std::cin >> op;
    }
    else {

        char op2;
        system("cls");
        categoria.mostrar();
        std::cout << "esta seguro de que desea eliminar la categoria?" << std::endl;
        std::cout << "[S/N]: ";
        std::cin >> op2;
        if (op2 == 's' || op2 == 'S')
        {

            categoria.setEstado(false);
            guardar_Categorias(categoria, op - 1);
        }
    }
}

bool Archivo_Categoria::guardar_Categorias(Categoria cat, int posicion)
{
    FILE* p;
    p = fopen("categoria.dat", "rb+");
    if (p == nullptr) {
        std::cout << "No se pudo abrir el archivo" << std::endl;
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
    }

    fwrite(&cat, sizeof(Categoria), 1, pFile);

    fclose(pFile);

}

Categoria Archivo_Categoria::leer_de_disco(int posicion)
{
    Categoria categoria;
    FILE* p;
    p = fopen("categoria.dat", "rb");

    if (p == nullptr) {
        std::cout << "Error al abrir el archivo" << std::endl;
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
Categoria Archivo_Categoria::leer_categorias(int pos)
{
    Categoria cat;
    FILE* pFile;
    pFile = fopen("categoria.dat", "rb");
    if (pFile == nullptr)
    {
        cout << "No se pudo abrir el archivo" << endl;
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
bool Archivo_Categoria::guardarEnDisco(int pos) {
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

int Archivo_Categoria::buscarCategoria(int ID) {
    Archivo_Categoria ac;
    Categoria c;
    int i, cant = ac.cantidad_categorias();
    for (i = 0; i < cant; i++) {
        ac.leer_categorias(i);
        if (ID == c.get_id()) {
            return i;
        }
    }
    return -1;
}
void Archivo_Categoria::listar_categorias(int cantidad)
{

    for (int i = 0; i < cantidad; i++)
    {
        Categoria categoria;
        categoria = leer_de_disco(i);
        if (categoria.getEstado())
        {
            Archivo_Categoria acat;
            Categoria cat;
            cat = acat.leer_de_disco(categoria.get_id());
            if (cat.getEstado())
            {
                categoria.mostrar();
            }
        }
    }
}
void Archivo_Categoria::modificar_categorias()
{
    Archivo_Categoria ac;
    Categoria c;
    int cant_cat = ac.cantidad_categorias();
    Categoria* cat = new Categoria[cant_cat];
   
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
            cout << "ingresar nuevo nombre" << endl;
            cin >> nuevo_nombre;
            cat[i].setNombre(nuevo_nombre);
            system("pause");
            system("cls");
            cat[i].sobreescribir_categoria(c, i);
            cout << "Categoria modificada..." << endl << endl;
            cat[i].mostrar();
            system("pause");
            system("cls");
            delete[] cat;
        }
    }

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
        if (cat.get_id() == op)
        {
            return true;
        }

    }
    return false;

}




