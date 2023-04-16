#pragma once
#include <iostream>
#include <string>

using namespace std;
class Categoria
{
private:
    char _nombre[50];
    int id_categoria;
    bool estado;

public:
    //gets
    Categoria();
    int get_id();
    string getNombre();
    bool getEstado();

    //sets
    void set_id(int nuevo_id);
    void setNombre(string n_nombre);
    void setEstado(bool n_estado);
    void cargar();
    void mostrar();
    void sobreescribir_categoria(Categoria cat, int pos);
};

