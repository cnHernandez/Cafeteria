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
#include "Archivo_bkp.h"
#include "rlutil.h"
#include <vector>
#include <iostream>

using namespace std;
void Menu::menuPrincipal()
{
    rlutil::setBackgroundColor(rlutil::LIGHTMAGENTA);
    rlutil::setColor(rlutil::WHITE);
    int op;
	bool menu_activo = true;
    while (menu_activo)
    {
       
		system("cls");
        cout << "----Menu Principal----" << endl << endl;
        cout << " 1- Productos" << endl;
        cout << " 2- Categorias" << endl;
        cout << " 3- Ventas" << endl;
        cout << " 4- Clientes" << endl;
        cout << "-----------------" << endl;
        cout << " 0- SALIR" << endl;
        cout << "-----------------" << endl;
        
		cin >> op;
        while (op < 0 || op>4)
        {
			cout << "opcion incorrecta, vuelva a ingresar una opcion: ";
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
        cout << "----Productos----" << endl;
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
            cout << "opcion incorrecta, vuelva a ingresar una opcion: ";
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
                cout << "Listar Productos" << endl;
                cout << "-------------------------" << endl;
                cout << "1- Todos" << endl;
                cout << "2- Listar por categorias" << endl ;
                cout << "3- Por rango de precio " << endl;
                cout << "-------------------------" << endl;
                cout << "0- Volver" << endl;
                cin >> op;

                while (op < 0 || op>3)
                {
                    cout << "opcion incorrecta, vuelva a ingresar una opcion: ";
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
                cout << "-----------------------------------" << endl<<endl;
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
                cout << "Modificar producto" << endl;
                archivo_producto archivo;
                int pro = archivo.modificar();   
                system("pause");
                system("cls");
                Producto aux = archivo.leer_de_disco(pro-1);
                cout << "----------------------------------------" << endl;
                aux.Mostrar();
                cout << "----------------------------------------" << endl << endl;
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
            cout << "opcion incorrecta, vuelva a ingresar una opcion: ";
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
                cout << "No se encuentran guardadas categorias Activas" << endl << endl;
                system("pause");
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
                cout << "No se encuentran guardadas categorias Activas" << endl << endl;
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
        //cout << " 3- Modificar" << endl;
        //cout << " 4- Eliminar" << endl;
        cout << " 5- Hacer copia de Seguridad" << endl;
        cout << " 6- Restaurar copia de Seguridad" << endl;
        cout << "-----------------" << endl;
        cout << " 0- SALIR" << endl;
        cout << "-----------------" << endl;
        cin >> op;
        while (op < 0 || op>6)
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
                cout << "Listar Ventas" << endl;
                cout << "-----------------------" << endl;
                cout << "1- Todos" << endl;
                cout << "2- Listar por Cliente" << endl;
                cout << "3- Listar por Fecha" << endl;
                cout << "4- Recaudacion anual por vendedor" << endl;
                cout << "5- Recaudacion anual por Productos" << endl;
                cout << "6- Recaudacion anual por Categorias" << endl;
                cout << "-----------------------" << endl;
                cout << "0- volver" << endl;
                cout << "-----------------------" << endl;
                cin >> op;

                while (op < 0 || op>6)
                {
                    cout << "opcion incorrecta, vuelva a ingresar una opcion" << endl;
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
                        cout << "No se encuentran guardadas ventas Activas" << endl << endl;
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
                        cout << "No se encuentran guardadas ventas Activas" << endl << endl;
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
                        cout << "No se encuentran guardadas ventas Activas" << endl << endl;
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
                    std::cout << "RECAUDACION ANUAL POR VENDEDOR: " << endl;
                    archivo.recaudacion_x_vendedor();
                }
                break;
                case 5:
                {
					Archivo_Venta archivo;
					system("cls");
					std::cout << "RECAUDACION ANUAL POR PRODUCTO: " << endl;
					archivo.recaudacion_x_producto();
                }
                break;
                case 6:
                {
                    Archivo_Venta archivo;
                    system("cls");
                    std::cout << "RECAUDACION ANUAL POR PRODUCTO: " << endl;
                    archivo.recaudacion_x_categoria();
                }
                break;
                }
            }
        }
        break;
        case 2:
        {
            vector <Venta> ventas;
            
            system("cls");
            cout << "2- Agregar venta" << endl;
            Archivo_Venta av;
            Venta venta;
            venta.cargar();
            system("cls");
            cout << "Se cargo la venta exitosamente..." << endl;
            ventas.push_back(venta);
            system("pause");
            system("cls");
            venta.mostrar();
            system("pause");
           // av.guardarVentas(ventas);
            av.guardar(venta);
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
            cout << "Lista de clientes" << endl;
            Archivo_Cliente archivo;
            Cliente cliente;
            int cant = archivo.cantidad_clientes();
            int cantActiva = archivo.get_cantidad_Activa(cant);
            if (cantActiva == 0)
            {
                char desicion;
                cout << "No se encuentran guardados clientes Activos" << endl << endl;
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
					cout << "Opcion incorrecta" << endl << endl;
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
            system("cls");
            cout << "Agregar cliente" << endl << endl;
            Archivo_Cliente ac;
            Cliente cli;
            cli.Cargar();
            system("cls");
            cout << "Se cargo el cliente exitosamente..." << endl << endl;
            system("pause");
            system("cls");
            cli.Mostrar();
            system("pause");
            ac.guardar(cli);

        }
        break;
        case 3:
        {
            system("cls");
			cout << "Modificar cliente" << endl;
			Archivo_Cliente ac;
			int cant = ac.cantidad_clientes();
			int cantActiva = ac.get_cantidad_Activa(cant);
            if (cantActiva == 0)
            {
				cout << "No se encuentran guardados clientes Activos" << endl << endl;
				system("pause");
			}
            else
            {
				ac.modificar_cliente();
                system("cls");
                cout << "Se modifico el cliente exitosamente..." << endl;
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
            system("cls");
            cout << "Se elimino el cliente exitosamente..." << endl;
            system("pause");           
        }
        break;
        }
    }
}