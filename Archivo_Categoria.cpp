#include "archivo_Producto.h"
#include "Archivo_Categoria.h"

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

    while (!cat.Existe(op))
    {
        cout << "ingrese una opcion correcta" << endl;
        cin >> op;
    }
    categoria = leer_de_disco(op - 1);

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
        cout << "Se elimino la categoria exitosamente..." << endl;
      }
      else {
          system("cls");
          cout << "No se elimino la categoria..." << endl;
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
        return categoria;
    }

    fseek(p, posicion * sizeof(Categoria), SEEK_SET);
    fread(&categoria, sizeof(Categoria), 1, p);
    fclose(p);

    return categoria;
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


void Archivo_Categoria::obtener_categorias(Categoria* cat, int cantidad)
{
    FILE* pFile = fopen("categoria.dat", "rb");

    if (pFile == NULL)
    {
        cout << "Error al abrir el archivo" << endl;
        return;
    }

    fread(cat, sizeof(Categoria), cantidad, pFile);

    fclose(pFile);
}


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
    Categoria c;
    int cant_cat = cantidad_categorias();
    Categoria* cat = new Categoria[cant_cat];
    if (cat == nullptr) {
        cout << "ERROR CON LA MEMORIA DINAMICA" << endl;
        return;
    }
   
    obtener_categorias(cat, cant_cat);
    listar_categorias(cant_cat);
    int cod;
    cout << endl << "Ingresar codigo a modificar: ";
    cin >> cod;

    while (!Existe(cod))
    {
        cout << "ingrese una opcion correcta" << endl;
        cin >> cod;
    }
    c = leer_de_disco(cod-1);
    system("pause");
    system("cls");
          
    c.mostrar();
    cout << endl;
    char nuevo_nombre[30];
    cat[cod-1].cargar();
    system("pause");
    system("cls");
    cat[cod-1].sobreescribir_categoria(c, cod-1);
    cout << "Categoria modificada..." << endl << endl;
    cat[cod-1].mostrar();
    system("pause");
    system("cls");
        
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
