
#include "cstring"
#include <iostream>
#include <string>
#include "Categoria.h"
#include "Archivo_Categoria.h"
#include "Producto.h"
using namespace std;


Categoria::Categoria()
{
    Archivo_Categoria Archivo;
    id_categoria = Archivo.cantidad_categorias() + 1;
    estado = true;
}

string Categoria::getNombre()
{
    return _nombre;
}

int Categoria::get_id()
{
    return id_categoria;
}

//sets
void Categoria::setNombre(string nombre)
{
    strcpy_s(_nombre, nombre.c_str());
}

void Categoria::set_id(int nuevo_id)
{
    id_categoria = nuevo_id;
}
void Categoria::cargar() {
    cout << "------------------" << endl;
    cout << "Ingrese nombre: ";
    cin >> _nombre;
}
void Categoria::mostrar()
{
    cout << "------------------" << endl;
    cout << "ID de categoria: " << get_id() << endl;
    cout << "Nombre: " << _nombre << endl;

}
/*void categorias::cargar_categias_vector(categorias vec[], int cantidad) {
    Archivo_Categoria ac;

    for (int i = 0; i < cantidad; i++) {
        vec[i] = ac.leer_categorias(i);
    }
}
*/
void Categoria::setEstado(bool nEstado)
{
    estado = nEstado;
}
bool Categoria::getEstado()
{

    return estado;
}
void Categoria::sobreescribir_categoria(Categoria cat, int pos)
{
    FILE* pFile;
    pFile = fopen("Categoria.dat", "rb+");
    if (pFile == nullptr) {
        cout << "error al abrir el archivo" << endl;
    }

    fseek(pFile, pos * sizeof(Categoria), 0);
    fwrite(this, sizeof(Categoria), 1, pFile);

    fclose(pFile);
}

