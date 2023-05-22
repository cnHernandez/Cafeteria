#pragma once
#include "Producto.h"
class archivo_producto
{
public:
    void guardar(Producto producto);
    bool guardar(Producto producto, int posicion);
    int cantidad_de_registros();
    Producto leer_de_disco(int posicion);
    void listar(int cantidad);
    int get_cantidad_Activa(int cantidad);
    void baja_Logica();
    int modificar();
    void obtener_productos(Producto* prod, int cantidad);
    void listaXcategoria();
    bool Existe(int opcion);
    void baja_Logica(int id);
};

