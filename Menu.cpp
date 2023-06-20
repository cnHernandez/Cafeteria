#include "Menu.h"
#include <iostream>
#include <string>
#include <cstring>
#include "Producto.h"
#include "archivo_producto.h"
#include "Archivo_Categoria.h"
#include "Categoria.h"
#include "Cliente.h"
#include "Archivo_Cliente.h"
#include "Venta.h"
#include "Archivo_Venta.h"
#include "Archivo_Vendedor.h"
#include "Vendedor.h"
#include "Archivo_bkp.h"
#include "rlutil.h"
#include <iomanip>

#include <iostream>

using namespace std;
void Menu::menuPrincipal()
{
    rlutil::setBackgroundColor(rlutil::LIGHTMAGENTA);
    rlutil::setColor(rlutil::WHITE);
    int op,y=0;
    bool menu_activo = true;
    while (menu_activo)
    {
        system("cls");
        rlutil::locate(30, 10);
        cout<<"-*-*-Bienvenido al sistema de gestion-*-*-"<<endl<<endl;
       
        rlutil::locate(45, 11);
        cout <<"Menu Principal" << endl << endl;
        rlutil::locate(45, 12);
        cout << " 1- Productos " << endl;
        rlutil::locate(45, 13);
        cout << " 2- Categorias " << endl;
        rlutil::locate(45, 14);
        cout << " 3- Ventas " << endl;
        rlutil::locate(45, 15);
        cout << " 4- Clientes " << endl;
        rlutil::locate(45, 16);
        cout << " 5- Vendedores " << endl;
        rlutil::locate(45, 17);
        cout << "----------------" << endl;
        rlutil::locate(45, 18);
        cout << " 0- SALIR" << endl;
       
        cin >> op;
        while (op < 0 || op>5)
        {
            rlutil::setColor(rlutil::RED);
            cout << "opcion incorrecta, vuelva a ingresar una opcion: ";
            rlutil::setColor(rlutil::WHITE);
            cin >> op;
        }
        switch (op)
        {
        case 0:
        {
            menu_activo = false;
        }
        break;
        case 1:
        {
            menu_productos();
        }
        break;
        case 2:
        {
            menu_categorias();
        }
        break;
        case 3:
        {
            menu_ventas();
        }
        break;
        case 4:
        {
            menu_clientes();
        }
        break;
        case 5:
        {
            menu_vendedores();
        }
        break;
        }
    }
}

void Menu::menu_productos()
{
    int op;
    bool menu_activo = true;
    while (menu_activo)
    {
        system("cls");
        rlutil::locate(45, 11);
        cout << "----Productos----" << endl;
rlutil::locate(45, 12);
        cout << " 1- Listar" << endl;
rlutil::locate(45, 13);
        cout << " 2- Agregar" << endl;
rlutil::locate(45, 14);
        cout << " 3- Modificar" << endl;
rlutil::locate(45, 15);
        cout << " 4- Eliminar" << endl;
rlutil::locate(45, 16);
        cout << "-----------------" << endl;
            rlutil::locate(45, 17);
        cout << " 0- SALIR" << endl;
       

        cin >> op;

        while (op < 0 || op>4)
        {
            rlutil::setColor(rlutil::RED);
            rlutil::locate(45, 11);
            cout << "opcion incorrecta, vuelva a ingresar una opcion: ";
rlutil::setColor(rlutil::WHITE);
            cin >> op;
        }
        switch (op)
        {
        case 0:
        {
            menu_activo = false;
        }
        break;
        case 1:
        {
            bool menu2activo = true;

            while (menu2activo)
            {
                system("cls");
                rlutil::locate(45, 11);
                cout << "Listar Productos" << endl;
                rlutil::locate(45, 11);
                cout << "-------------------------" << endl;
rlutil::locate(45, 12);
                cout << "1- Todos" << endl;
rlutil::locate(45, 13);
                cout << "2- Listar por categorias" << endl;
rlutil::locate(45, 14);
                cout << "3- Por rango de precio " << endl;
rlutil::locate(45, 15);
                cout << "-------------------------" << endl;
rlutil::locate(45, 16);
                cout << "0- Volver" << endl;
                cin >> op;

                while (op < 0 || op>3)
                {
                    rlutil::setColor(rlutil::RED);
                    cout << "opcion incorrecta, vuelva a ingresar una opcion: ";
rlutil::setColor(rlutil::WHITE);
                    cin >> op;
                }

                switch (op)
                {

                case 1:
                {
                    system("cls");
                    rlutil::locate(45, 11);
                    cout << "Lista de todos los productos" << endl;
                    archivo_producto archivo;
                    int cant = archivo.cantidad_de_registros();
                    int cantActiva = archivo.get_cantidad_Activa(cant);
                    if (cantActiva == 0)
                    {
                        rlutil::setColor(rlutil::RED);
                        cout << "No se encuentran guardados Productos Activos" << endl << endl;
                    }
                    else
                    {
                       
                        archivo.listar(cant);
                        rlutil::locate(45, 17);
                        cout<<"-------------------------"<<endl;
                    }
                    rlutil::locate(45, 18);
                    system("pause");

                }

                break;
                case 2:
                {
                    system("cls");
                    cout << " Lista por categoria" << endl;
                    archivo_producto archivo;
                    int cant = archivo.cantidad_de_registros();
                    int cantActiva = archivo.get_cantidad_Activa(cant);
                    if (cantActiva == 0)
                    {
                        rlutil::setColor(rlutil::RED);
                        cout << "No se encuentran guardados Categorias Activas" << endl << endl;
                    }
                    else
                    {
                        archivo.listaXcategoria();
                    }
                    system("pause");

                }
                break;
                case 3:
                {
                    system("cls");
                    cout << " Lista por rango de precio" << endl << endl;
                    archivo_producto archivo;
                    int cant = archivo.cantidad_de_registros();
                    int cantActiva = archivo.get_cantidad_Activa(cant);
                    if (cantActiva == 0)
                    {
                        rlutil::setColor(rlutil::RED);
                        cout << "No se encuentran guardados Productos Activos" << endl << endl;
                    }
                    else
                    {
                        archivo.listaXrango();
                    }
                    system("pause");
                }
                break;
                case 0:
                {
                    menu2activo = false;
                }
                }

            }
        }break;

        case 2:
        {
            bool menu3activo = true;

            while (menu3activo)
            {
                system("cls");
                cout << "Agregar Productos" << endl;
                cout << "----------------------------" << endl;
                cout << "1- Agregar producto nuevo" << endl;
                cout << "2- Agregar stock de producto" << endl;
                cout << "----------------------------" << endl;
                cout << "0- Volver" << endl;
                cin >> op;

                while (op < 0 || op>2)
                {
                    rlutil::setColor(rlutil::RED);
                    cout << "opcion incorrecta, vuelva a ingresar una opcion: ";
rlutil::setColor(rlutil::WHITE);
                    cin >> op;
                }

                switch (op)
                {
                case 0:
                {
                    menu3activo = false;
                }

                case 1:
                {
                    system("cls");
                    cout << "Eliga categoria del producto" << endl;
                    Producto producto;
                    bool leyo = producto.Cargar();
                    if (leyo)
                    {
                        archivo_producto archivo;
                        archivo.guardar(producto);
                        system("cls");
                        cout << "Producto cargado" << endl;
                        cout << "-----------------------------------" << endl;
                        producto.Mostrar();
                        cout << "-----------------------------------" << endl << endl;
                        system("pause");
                        cout << endl;
                    }
                }

                break;
                case 2:
                {
                    system("cls");
                    cout << "AGREGAR STOCK" << endl;
                    archivo_producto ar;
                    int cant = ar.cantidad_de_registros();
                    ar.listar(cant);
                    int id;
                    archivo_producto archivo;
                    Producto producto, aux;
                    cout << "Ingrese ID del producto al que desea agregarle stock: " ;
                    cin >> id;
                    system("cls");
                    if (archivo.Existe(id)) {
                        archivo.Stock(id);
                    }
                }
                break;
                }
                break;
            }
        }
        break;
        case 3:
        {
            system("cls");
            archivo_producto archivo;
            int cant = archivo.cantidad_de_registros();
            int cantActiva = archivo.get_cantidad_Activa(cant);
            if (cantActiva == 0)
            {
                rlutil::setColor(rlutil::RED);
                cout << "No se encuentran guardados Productos Activos" << endl << endl;
rlutil::setColor(rlutil::WHITE);
                system("pause");
            }
            else {
                system("cls");
                cout << "Modificar producto" << endl;
                archivo_producto archivo;
                archivo.modificar();
                system("pause");
            }
        }
        break;
        case 4:
        {
            system("cls");
            archivo_producto archivo;
            int cant = archivo.cantidad_de_registros();
            int cantActiva = archivo.get_cantidad_Activa(cant);
            if (cantActiva == 0)
            {
                rlutil::setColor(rlutil::RED);
                cout << "No se encuentran guardados Productos Activos" << endl << endl;
rlutil::setColor(rlutil::WHITE);
                system("pause");

            }
            else {
                cout << "Eliminar producto" << endl;
                archivo_producto archivo;
                archivo.baja_Logica();
                system("pause");
            }
        }
        break;

        }
    }
}

void Menu::menu_categorias()
{
    int op;
    bool menu_activo = true;
    while (menu_activo)
    {
        system("cls");
        cout << "---Categorias----" << endl << endl;
        cout << " 1- Listar" << endl;
        cout << " 2- Agregar" << endl;
        cout << " 3- Modificar" << endl;
        cout << " 4- Eliminar" << endl;
        cout << "-----------------" << endl;
        cout << " 0- SALIR" << endl;
        cout << "-----------------" << endl;

        cin >> op;

        while (op < 0 || op>4)
        {
            rlutil::setColor(rlutil::RED);
            cout << "opcion incorrecta, vuelva a ingresar una opcion: ";
rlutil::setColor(rlutil::WHITE);
            cin >> op;
        }
        switch (op)
        {
        case 0:
        {
            menu_activo = false;
        }
        break;
        case 1:
        {
            system("cls");
            cout << "Lista de categorias" << endl << endl;
            Archivo_Categoria archivo;
            int cant = archivo.cantidad_categorias();
            int cantActiva = archivo.get_cantidad_Activa(cant);
            if (cantActiva == 0)
            {
                rlutil::setColor(rlutil::RED);
                cout << "No se encuentran guardadas categorias Activas" << endl << endl;
                system("pause");

            }
            else
            {
                rlutil::setColor(rlutil::WHITE);
                archivo.listar_categorias(cant);
                cout << endl << endl;
                system("pause");
            }
        }
        break;

        case 2:
        {
            cout << "Agregar categoria" << endl;
            Archivo_Categoria ac;
            ac.agregar_categoria();
        }
        break;
        case 3:
        {
            system("cls");
            cout << "Modificar categoria" << endl;
            Archivo_Categoria archivo;
            Categoria cat;
            int cant = archivo.cantidad_categorias();
            int cantActiva = archivo.get_cantidad_Activa(cant);
            if (cantActiva == 0)
            {
                rlutil::setColor(rlutil::RED);
                cout << "No se encuentran guardadas categorias Activas" << endl << endl;
                system("pause");
                rlutil::setColor(rlutil::WHITE);
            }
            else {
                archivo.modificar_categorias();
            }

        }
        break;
        case 4:
        {
            system("cls");
            cout << "Eliminar categoria" << endl;
            Archivo_Categoria archivo;
            Categoria ca;
            int cant = archivo.cantidad_categorias();
            int cantActiva = archivo.get_cantidad_Activa(cant);
            if (cantActiva == 0)
            {
rlutil::setColor(rlutil::RED);
                cout << "No se encuentran guardadas categorias Activas" << endl << endl;
                rlutil::setColor(rlutil::WHITE);
                system("pause");

            }
            else {
                archivo.baja_Logica();
                cout << endl;
                cout << "Se elimino la categoria exitosamente..." << endl;
                system("pause");
                system("cls");
            }

        }
        break;

        }
    }

}

void Menu::menu_ventas()
{
    int op;
    bool menu_activo = true;
    while (menu_activo)
    {
        system("cls");
        cout << "---Ventas----" << endl;
        cout << " 1- Listar" << endl;
        cout << " 2- Agregar" << endl;
        cout << " 3- Modificar" << endl;
        cout << " 4- Eliminar" << endl;
        cout << " 5- Hacer copia de Seguridad" << endl;
        cout << " 6- Restaurar copia de Seguridad" << endl;
        cout << "-----------------" << endl;
        cout << " 0- SALIR" << endl;
        cout << "-----------------" << endl;
        cin >> op;
        while (op < 0 || op>6)
        {
            rlutil::setColor(rlutil::RED);
            cout << "opcion incorrecta, vuelva a ingresar una opcion" << endl;
rlutil::setColor(rlutil::WHITE);
            cin >> op;
        }
        switch (op)
        {
        case 0:
        {
            menu_activo = false;
        }
        break;

        case 1:
        {
            bool menu2activo = true;

            while (menu2activo)
            {
                system("cls");
                cout << "Listar Ventas" << endl;
                cout << "-----------------------" << endl;
                cout << "1- Todos" << endl;
                cout << "2- Listar por Cliente" << endl;
                cout << "3- Listar por Fecha" << endl;
                cout << "4- Recaudacion anual por vendedor" << endl;
                cout << "5- Recaudacion anual por Productos" << endl;
                cout << "6- Recaudacion anual por Categorias" << endl;
                cout << "7- Ganancia neta mensual por anio" << endl;
                cout << "-----------------------" << endl;
                cout << "0- volver" << endl;
                cout << "-----------------------" << endl;
                cin >> op;

                while (op < 0 || op>7)
                {
                    rlutil::setColor(rlutil::RED);
                    cout << "opcion incorrecta, vuelva a ingresar una opcion" << endl;
rlutil::setColor(rlutil::WHITE);
                    cin >> op;
                }

                switch (op)
                {
                case 0:
                {
                    menu2activo = false;
                }
                break;
                case 1:
                {

                    system("cls");
                    cout << " 1- Lista de ventas" << endl;
                    Archivo_Venta archivo;


                    int cant = archivo.cantidad_ventas();
                    int cantActiva = archivo.get_cantidad_Activa(cant);
                    if (cantActiva == 0)
                    {
                        rlutil::setColor(rlutil::RED);
                        cout << "No se encuentran guardadas ventas Activas" << endl << endl;
rlutil::setColor(rlutil::WHITE);
                        system("pause");
                    }
                    else
                    {
                        system("cls");
                        cout << "        ******** VENTAS ********" << endl;
                        archivo.listar_ventas(cant);
                        cout << "*********************" << endl;
                        system("pause");
                    }
                }
                break;
                case 2:
                {
                    system("cls");
                    cout << " 2- Lista de ventas por cliente" << endl << endl;
                    Archivo_Venta archivo;
                    Archivo_Cliente cliente;
                    int cant = archivo.cantidad_ventas();
                    int cantClientes = cliente.cantidad_clientes();
                    int cantActiva = archivo.get_cantidad_Activa(cant);
                    if (cantActiva == 0)
                    {
                        rlutil::setColor(rlutil::RED);
                        cout << "No se encuentran guardadas ventas Activas" << endl << endl;
rlutil::setColor(rlutil::WHITE);
                        system("pause");
                    }

                    else
                    {
                        archivo.listar_x_cliente();
                        cout << endl << endl;
                        system("pause");
                    }
                }
                break;
                case 3:
                {
                    system("cls");
                    cout << " 3- Lista de ventas por fecha" << endl;

                    Archivo_Venta archivo;
                    int cant = archivo.cantidad_ventas();
                    int cantActiva = archivo.get_cantidad_Activa(cant);
                    if (cantActiva == 0)
                    {
                        rlutil::setColor(rlutil::RED);
                        cout << "No se encuentran guardadas ventas Activas" << endl << endl;
rlutil::setColor(rlutil::WHITE);
                        system("pause");
                    }
                    else
                    {
                        archivo.listar_x_fecha();
                        cout << endl << endl;
                    }
                }
                break;
                case 4:
                {
                    Archivo_Venta archivo;
                    system("cls");
                    cout << "RECAUDACION ANUAL POR VENDEDOR: " << endl;
                    archivo.recaudacion_x_vendedor();
                }
                break;
                case 5:
                {
                    Archivo_Venta archivo;
                    system("cls");
                    cout << "RECAUDACION ANUAL POR PRODUCTO: " << endl;
                    archivo.recaudacion_x_producto();
                }
                break;
                case 6:
                {
                    Archivo_Venta archivo;
                    system("cls");
                    cout << "RECAUDACION ANUAL POR PRODUCTO: " << endl;
                    archivo.recaudacion_x_categoria();
                }
                break;
                case 7:
                {
                    Archivo_Venta archivo;
                    system("cls");
                    cout << "RECAUDACION ANUAL POR PRODUCTO: " << endl;
                    archivo.ganancia_x_mes_Anual();
                }
                break;
                }
            }
        }
        break;
        case 2:
        {
            system("cls");
            cout << "2- Agregar venta" << endl;
            Archivo_Venta av;
            Venta venta;

            venta.cargar();
            system("cls");
            cout << "Se cargo la venta exitosamente..." << endl;
            system("pause");
            system("cls");
            venta.mostrar();
            system("pause");
            av.guardar(venta);
        }
        break;
        case 3:
        {
            system("cls");
            Archivo_Venta archivo;
            int cant = archivo.cantidad_ventas();
            int cantActiva = archivo.get_cantidad_Activa(cant);
            if (cantActiva == 0)
            {
                rlutil::setColor(rlutil::RED);
                cout << "No se encuentran guardadas ventas activas" << endl << endl;
rlutil::setColor(rlutil::WHITE);
                system("pause");
            }
            else {
                system("cls");
                cout << "Modificar venta" << endl;
                int pro = archivo.Modificar_Venta();
                system("pause");
                system("cls");
                Venta aux = archivo.leer_ventas(pro - 1);
                cout << "----------------------------------------" << endl;
                aux.mostrar();
                cout << "----------------------------------------" << endl << endl;
                system("pause");
            }
        }
        break;
        case 4:
        {
            system("cls");
            cout << "4- Eliminar venta" << endl;
            Archivo_Venta venta;
            venta.BajaLogica();
            system("cls");
            cout << "Se elimino la venta correctamente..." << endl;
            system("pause");
        }
        break;
        case 5:
        {
            system("cls");
            cout << "5- Hacer copia de seguridad" << endl;
            Archivo_bkp Backup;
            Backup.HacerCopiaDeSeguridad();
            cout << "Se realizo la copia de seguridad exitosamente..." << endl;

            system("pause");
        }
        break;
        case 6:
        {
            system("cls");
            cout << "6- Restaurar copia de seguridad" << endl;
            Archivo_bkp Backup;
            Backup.RestaurarCopiaDeSeguridad();
            cout << "Se restauro la copia de seguridad exitosamente..." << endl;
            system("pause");
        }
        break;
        }
    }
}


void Menu::menu_clientes()
{

    int op;
    bool menu_activo = true;
    while (menu_activo)
    {
        system("cls");
        cout << "---Clientes----" << endl << endl;
        cout << " 1- Listar" << endl;
        cout << " 2- Agregar" << endl;
        cout << " 3- Modificar" << endl;
        cout << " 4- Eliminar" << endl;
        cout << "-----------------" << endl;
        cout << " 0- SALIR" << endl;
        cout << "-----------------" << endl;
        cin >> op;
        while (op < 0 || op>4)
        {
            cout << "opcion incorrecta, vuelva a ingresar una opcion" << endl;
            cin >> op;
        }
        switch (op)
        {
        case 0:
        {
            menu_activo = false;
        }
        break;
        case 1:
        {
            system("cls");
            Archivo_Cliente archivo;
            Cliente cliente;
            int cant = archivo.cantidad_clientes();
            int cantActiva = archivo.get_cantidad_Activa(cant);
            cout << "Lista de clientes" << endl;
            if (cantActiva == 0)
            {
                char desicion;
                rlutil::setColor(rlutil::RED);
                cout << "No se encuentran guardados clientes Activos" << endl << endl;
rlutil::setColor(rlutil::WHITE);
                cout << "¿Desea ingresar un cliente nuevo? (S/N): ";
                cin >> desicion;
                if (desicion == 's' || desicion == 'S')
                {
                    cliente.Cargar();
                    archivo.guardar(cliente);
                }
                else if (desicion == 'n' || desicion == 'N')
                {
                    return;
                }
                else
                {
                    rlutil::setColor(rlutil::RED);
                    cout << "Opcion incorrecta" << endl << endl;
rlutil::setColor(rlutil::WHITE);
                    system("pause");
                }
                system("pause");

            }
            else
            {
                archivo.listar_clientes(cant);
                cout << endl;
                system("pause");
            }
        }
        break;
        case 2:
        {
            Archivo_Cliente archivo;
            Cliente cliente;
            system("cls");
            cout << "Agregar cliente" << endl << endl;
            cliente.Cargar();
            system("cls");
            cout << "Se cargo el cliente exitosamente..." << endl << endl;
            system("pause");
            system("cls");
            cliente.Mostrar();
            system("pause");
            archivo.guardar(cliente);
        }
        break;
        case 3:
        {
            Archivo_Cliente archivo;
            Cliente cliente;
            system("cls");
            cout << "Modificar cliente" << endl;
            int cant = archivo.cantidad_clientes();
            int cantActiva = archivo.get_cantidad_Activa(cant);
            if (cantActiva == 0)
            {
                rlutil::setColor(rlutil::RED);
                cout << "No se encuentran guardados clientes Activos" << endl << endl;
rlutil::setColor(rlutil::WHITE);
                system("pause");
            }
            else
            {
                archivo.modificar_cliente();
                system("pause");
            }
        }
        break;
        case 4:
        {
            system("cls");
            cout << "Eliminar cliente" << endl;
            Archivo_Cliente cliente;
            cliente.baja_Logica();
            system("pause");
        }
        break;
        }
    }
}

void Menu::menu_vendedores()
{
    int op;
    bool menu_activo = true;
    while (menu_activo)
    {
        system("cls");
        cout << "---Vendedores----" << endl << endl;
        cout << " 1- Listar" << endl;
        cout << " 2- Agregar" << endl;
        cout << " 3- Modificar" << endl;
        cout << " 4- Eliminar" << endl;
        cout << "-----------------" << endl;
        cout << " 0- SALIR" << endl;
        cout << "-----------------" << endl;
        cin >> op;
        while (op < 0 || op>4)
        {
            rlutil::setColor(rlutil::RED);
            cout << "opcion incorrecta, vuelva a ingresar una opcion" << endl;
rlutil::setColor(rlutil::WHITE);
            cin >> op;
        }
        switch (op)
        {
        case 0:
        {
            menu_activo = false;
        }
        break;
        case 1:
        {
            Archivo_Vendedor archivo;
            Vendedor vendedor;
            int cant = archivo.Cantidad_vendedores();
            int cantActiva = archivo.Get_cantidad_Activa(cant);
            system("cls");
            cout << "Lista de Vendedores" << endl;
            if (cantActiva == 0)
            {
                char desicion;
                rlutil::setColor(rlutil::RED);
                cout << "No se encuentran guardados vendedores Activos" << endl << endl;
rlutil::setColor(rlutil::WHITE);
                cout << "¿Desea ingresar un vendedor nuevo? (S/N): ";
                cin >> desicion;
                if (desicion == 's' || desicion == 'S')
                {
                    vendedor.Cargar();
                    archivo.Guardar(vendedor);
                }
                else if (desicion == 'n' || desicion == 'N')
                {
                    return;
                }
                else
                {
                    rlutil::setColor(rlutil::RED);
                    cout << "Opcion incorrecta" << endl << endl;
rlutil::setColor(rlutil::WHITE);
                    system("pause");
                }
                system("pause");

            }
            else
            {
                archivo.Listar_Vendedor(cant);
                cout << endl;
                system("pause");
            }
        }break;
        case 2:
        {
            Archivo_Vendedor archivo;
            Vendedor vendedor;
            system("cls");
            cout << "Agregar Vendedor" << endl << endl;
            vendedor.Cargar();
            system("cls");
            cout << "Se cargo el cliente exitosamente..." << endl << endl;
            system("pause");
            system("cls");
            vendedor.Mostrar();
            system("pause");
            archivo.Guardar(vendedor);
        }
        break;
        case 3:
        {
            Archivo_Vendedor archivo;
            Vendedor vendedor;
            int cant = archivo.Cantidad_vendedores();
            int cantActiva = archivo.Get_cantidad_Activa(cant);
            system("cls");
            cout << "Modificar Vendedor" << endl;

            if (cantActiva == 0)
            {
                rlutil::setColor(rlutil::RED);
                cout << "No se encuentran guardados vendedores Activos" << endl << endl;
rlutil::setColor(rlutil::WHITE);
                system("pause");
            }
            else
            {
                archivo.Modificar_Vendedor();
                system("pause");
            }

        }
        break;
        case 4:
        {
            Archivo_Vendedor archivo;
            Vendedor vendedor;
            system("cls");
            cout << "Eliminar Vendedor" << endl;
            archivo.Baja_Logica();
            system("pause"); }
        break;
        }
    }
}