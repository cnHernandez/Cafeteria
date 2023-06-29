#include <iostream>
#include "cstring"
#include "Archivo_Categoria.h"
#include "rlutil.h"

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
    cout << "Ingrese nombre de la nueva categoria: ";
    cin.ignore();
    cin.getline(_nombre, 50);
    for (int i = 0; i < strlen(_nombre); i++)
    {
        while (isdigit(_nombre[i])) {
            rlutil::setColor(rlutil::RED);
            cout << "El nombre no puede contener numeros" << endl;
            rlutil::setColor(rlutil::BLACK);
            cout << "Ingrese el nombre: ";
            cin.getline(_nombre, 30);
        }
    }
    setNombre(_nombre);
}
void Categoria::mostrar()
{
    cout << "------------------------------------" << endl;
    cout << "ID de categoria: " << get_id() << endl;
    cout << "Nombre: " << _nombre << endl;
    cout << "------------------------------------" << endl;

}

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
        cout << "ERROR" << endl;
        return ;
    }

    fseek(pFile, pos * sizeof(Categoria), 0);
    fwrite(this, sizeof(Categoria), 1, pFile);

    fclose(pFile);
}