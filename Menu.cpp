#include "Menu.h"
#include <iostream>
#include <string>
#include <cstring>
#include "Producto.h"
#include "archivo_producto.h"
#include "Archivo_Categoria.h"
#include "Categoria.h"

void Menu::menuPrincipal()
{

    int op;
	bool menu_activo = true;
    while (menu_activo)
    {
		system("cls");
		cout << "----Menu Principal----" << endl << endl;
		cout << " 1- Productos" << endl;
		cout << " 2- Categorias" << endl;
		cout << "-----------------" << endl;
		cout << " 0- SALIR" << endl;
		cout << "-----------------" << endl;
		cin >> op;
        while (op < 0 || op>2)
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
			menu_productos();
		}
		break;
		case 2:
        {
			menu_categorias();
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
        cout << "----Productos----" << endl << endl;
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
            bool menu2activo = true;

            while (menu2activo)
            {
                system("cls");
                cout << "Listar Productos" << endl << endl;;


                cout << "1- Todos" << endl;
                cout << "2- Listar por categorias" << endl << endl;
                cout << "0- volver" << endl;
                cin >> op;

                while (op < 0 || op>2)
                {
                    cout << "opcion incorrecta, vuelva a ingresar una opcion" << endl;
                    cin >> op;
                }

                switch (op)
                {

                case 1:
                {
                    system("cls");
                    cout << "Lista de todos los productos" << endl;
                    archivo_producto archivo;
                    int cant = archivo.cantidad_de_registros();
                    int cantActiva = archivo.get_cantidad_Activa(cant);
                    if (cantActiva == 0)
                    {
                        cout << "No se encuentran guardados Productos Activos" << endl << endl;
                    }
                    else
                    {
                        archivo.listar(cant);
                    }
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
                        cout << "No se encuentran guardados Productos Activos" << endl << endl;
                    }
                    else
                    {
                        archivo.listaXcategoria();
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
            system("cls");
            cout << " 2- Agregar producto" << endl;
            Producto producto;
            bool leyo = producto.Cargar();
            if (leyo)
            {
                archivo_producto archivo;
                archivo.guardar(producto);
                producto.Mostrar();
                system("pause");
                cout << endl;

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
                cout << "No se encuentran guardados Productos Activos" << endl << endl;
                system("pause");

            }
            else {
                system("cls");
                cout << " 3-Modificar producto" << endl;
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
                cout << "No se encuentran guardados Productos Activos" << endl << endl;
                system("pause");

            }
            else {
                cout << " 4- Eliminar producto" << endl;
                archivo_producto archivo;
                archivo.baja_Logica();
                system("pause");
            }}
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
            cout << " 1- Lista de categorias" << endl;
            Archivo_Categoria archivo;
            int cant = archivo.cantidad_categorias();
            int cantActiva = archivo.get_cantidad_Activa(cant);
            if (cantActiva == 0)
            {
                cout << "No se encuentran guardadas categorias Activas" << endl << endl;
                system("pause");

            }
            else
            {
                archivo.listar_categorias(cant);
                cout << endl << endl;
                system("pause");

            }

        }
        break;

        case 2:
        {
            cout << " 2- Agregar categoria" << endl;

            Archivo_Categoria ac;
            ac.agregar_categoria();
        }
        break;
        case 3:
        {
            system("cls");

            cout << " 3-Modificar categoria" << endl;
            Archivo_Categoria archivo;
            Categoria cat;
            int cant = archivo.cantidad_categorias();
            int cantActiva = archivo.get_cantidad_Activa(cant);
            if (cantActiva == 0)
            {
                cout << "No se encuentran guardadas categorias Activas" << endl << endl;
                system("pause");

            }
            else {
                archivo.modificar_categorias();
                
                //archivo.sobreescribir_categoria(cat,);
            }

        }
        break;
        case 4:
        {
            system("cls");
            cout << " 4- Eliminar categoria" << endl;
            Archivo_Categoria archivo;
            Categoria ca;
            int cant = archivo.cantidad_categorias();
            int cantActiva = archivo.get_cantidad_Activa(cant);
            if (cantActiva == 0)
            {
                cout << "No se encuentran guardadas categorias Activas" << endl << endl;
                system("pause");

            }
            else {
                archivo.baja_Logica();
            }

        }
        break;

        }
    }

}
