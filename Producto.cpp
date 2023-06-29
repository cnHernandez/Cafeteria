#include "Archivo_Producto.h"
#include "Archivo_Categoria.h"
#include "Menu.h"
#include "rlutil.h"

using namespace std;

Producto::Producto()
{
    archivo_producto Archivo;
    id_producto = Archivo.cantidad_de_registros() + 1;
    estado = true;
    stock = 0; 
}

void Producto::setNombre(string Nombre)
{
    strcpy_s(_nombre, Nombre.c_str());
}

void Producto::setId_Producto(int ID)
{
    id_producto = ID;
}
void Producto::setId_Categoria(int ID)
{
    id_categoria = ID;
}

void Producto::setEstado(bool nEstado)
{
    estado = nEstado;
}

void Producto::setStock(int nStock)
{
	stock = nStock;
}

void Producto::setPrecioCompra(float precio_compra)
{
	this->precio_compra = precio_compra;
}

float Producto::getPrecioCompra()
{
	return precio_compra;
}

int Producto::getStock()
{
	return stock;
}

string Producto::getNombre()
{
    return _nombre;
}

int Producto::getId_Categoria()
{
    return id_categoria;
}
int Producto::getId_Producto()
{
    return id_producto;
}

bool Producto::getEstado()
{
    return estado;
}
float Producto::getPrecio()
{
	return precio;
}
void Producto::setPrecio(float nPrecio)
{
	precio = nPrecio;
}

void Producto::AgregarStock(int can)
{
	stock += can;
}

void Producto::RestarStock(int cantidad)
{
	stock -= cantidad;
}

bool Producto::Cargar()
{
    Archivo_Categoria arch;
    if (arch.cantidad_categorias() > 0) {
        CargarCategoria();
        cout << "Ingrese el nombre del Producto: ";
        cin.getline(_nombre , 30);
        bool contieneNumeros = false;
        while (!contieneNumeros) {
            bool soloLetras = true;
            for (int i = 0; i < strlen(_nombre); i++) {
                if (isdigit(_nombre[i])) {
                    soloLetras = false;
                    break;
                }
            }

            if (!soloLetras) {
                rlutil::setColor(rlutil::RED);
                cout << "El nombre no puede contener numeros" << endl;
                rlutil::setColor(rlutil::BLACK);
                cout << "Ingrese el nombre: ";
                cin.getline(_nombre, 30);
            }
            else {
                contieneNumeros = true;
            }
        }
        setNombre(_nombre);

        string input;
        bool esNumero = false;
        bool cumpleCondicion = false;
        bool esDecimal = false;
        cout << "Ingrese el precio de compra del Producto: ";
        getline(cin, input);
        while (!esNumero || !cumpleCondicion || !esDecimal) {
            bool todosDigitos = true;
            for (char c : input) {
                if (!isdigit(c)) {
                    if (c == '.') {
                        esDecimal = true;
                    }
                    else {
                        todosDigitos = false;
                        break;
                    }
                }
            }

            if (!todosDigitos) {
                rlutil::setColor(rlutil::RED);
                cout << "El precio de compra debe ser un valor numerico. Ingrese nuevamente: " << endl;
                rlutil::setColor(rlutil::BLACK);
                getline(cin, input);
                continue;
            }

            float precioC = stof(input);
            if (precioC > 0 && precioC < 100000) {
                esNumero = true;
                cumpleCondicion = true;
                esDecimal = true;
            }
            else {
                rlutil::setColor(rlutil::RED);
                cout << "El precio de compra debe ser mayor a 0 y menor a 100,000. Ingrese nuevamente: " << endl;
                rlutil::setColor(rlutil::BLACK);
                getline(cin, input);
            }
        }

        precio_compra = stof(input);
        setPrecioCompra(precio_compra);
       
        string input2;
        esNumero = false;
        cumpleCondicion = false;
        esDecimal = false;
        cout << "Ingrese el precio de venta del Producto: ";
        getline(cin, input2);
        while (!esNumero || !cumpleCondicion || !esDecimal) {
            bool todosDigitos = true;
            for (char c : input2) {
                if (!isdigit(c)) {
                    if (c == '.') {
                        esDecimal = true;
                    }
                    else {
                        todosDigitos = false;
                        break;
                    }
                }
            }

            if (!todosDigitos) {
                rlutil::setColor(rlutil::RED);
                cout << "El precio de venta debe ser un valor numerico, Ingrese nuevamente: ";
                rlutil::setColor(rlutil::BLACK);
                getline(cin, input2);
                continue;
            }

            float precioV = stof(input2);
            if (precioV > 0 && precioV < 100000) {
                esNumero = true;
                cumpleCondicion = true;
                esDecimal = true;
            }
            else {
                rlutil::setColor(rlutil::RED);
                cout << "el precio de venta debe ser mayor a 0 y menor a 100.000, Ingrese nuevamente: ";
                rlutil::setColor(rlutil::BLACK);
                getline(cin, input2);
            }
        }
        precio = stof(input2);
        setPrecio(precio);

        string input3;
        cout << "ingrese la cantidad a Stockear: ";
        getline(cin, input3);
       
        esNumero = false;
        cumpleCondicion = false;

        while (!esNumero || !cumpleCondicion) {
            bool todosDigitos = true;
            for (char c : input3) {
                if (!isdigit(c)) {
                    todosDigitos = false;
                    break;
                }
            }

            if (!todosDigitos) {
                rlutil::setColor(rlutil::RED);
                cout << "El stock debe ser un valor numerico, Ingrese nuevamente: ";
                rlutil::setColor(rlutil::BLACK);
                getline(cin, input3);
                continue;
            }

            int num = stoi(input3);
            if (num > 0 && num < 100000) {
                esNumero = true;
                cumpleCondicion = true;
            }
            else {
                rlutil::setColor(rlutil::RED);
                cout << "El stock debe ser mayor a 0 y menor a 100.000, Ingrese nuevamente: ";
                rlutil::setColor(rlutil::BLACK);
                getline(cin, input3);
            }
        }
        stock = stoi(input3);
        setStock(stock);
        return true;
    }
    else {
        rlutil::setColor(rlutil::RED);
        cout << "Primero deben haber Categorias activas" << endl;
        rlutil::setColor(rlutil::BLACK);
        system("pause");
        rlutil::setColor(rlutil::BLACK);
        char desicion;
        Menu menu;
        cout << "¿Desea generar una categoria nueva? (S/N): ";
        cin >> desicion;
        if (desicion == 'S' || desicion == 's') {
            
            menu.menu_Categorias();
            return false;
        }
        else if (desicion == 'N' || desicion == 'n')
        {
            menu.menu_Productos();
        }

        return false;
    }
}

void Producto::CargarCategoria()
{
    int op;
    Archivo_Categoria ArchivoC;
    int cant = ArchivoC.cantidad_categorias();
    ArchivoC.listar_categorias(ArchivoC.cantidad_categorias());
    cout << endl;


    string input;
    cout << "Ingrese el ID de la categoria a la que pertenece el producto: ";
    cin.ignore();
    getline(cin, input);
    op = stoi(input);
    while (!ArchivoC.Existe(op)) {
        rlutil::setColor(rlutil::RED);
        cout << "No existe la categoria" << endl;
        rlutil::setColor(rlutil::BLACK);
        cout<<"Ingrese el ID de la categoria a la que pertenece el producto : ";
        getline(cin, input);
        op = stoi(input);
    }
        bool esNumero = false;
        bool cumpleCondicion = false;

        while (!esNumero || !cumpleCondicion) {
            bool todosDigitos = true;
            for (char c : input) {
                if (!isdigit(c)) {
                    todosDigitos = false;
                    break;
                }
            }

            if (!todosDigitos) {
                rlutil::setColor(rlutil::RED);
                cout << "El ID debe ser un valor numerico. Ingrese nuevamente: ";
                rlutil::setColor(rlutil::BLACK);
                getline(cin, input);
                continue;
            }

            int num = stoi(input);
            if (num > 0 && num <= cant) {
                esNumero = true;
                cumpleCondicion = true;
            }
            else {
                rlutil::setColor(rlutil::RED);
                cout << "El ID debe ser mayor a 0 y menor o igual a la cantidad de categorias. Ingrese nuevamente: ";
                rlutil::setColor(rlutil::BLACK);
                getline(cin, input);
            }
        
        op = stoi(input);
        setId_Categoria(op);
    }
}

void Producto::Mostrar()
{
    cout << "-Nombre del Producto: " << getNombre() << endl;
    cout << "#ID del Producto: " << getId_Producto() << endl;
    cout << "#ID de la Categoria: " << getId_Categoria()<< endl;
    cout << "-Precio de Venta del Producto: " << getPrecio() << endl;
    cout << "-Precio de Compra del Producto: " << getPrecioCompra() << endl;
    cout << "-Stock del Producto: " << getStock() << endl;
}


