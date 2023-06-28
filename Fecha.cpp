#include <string>
#include "fecha.h"
#include "rlutil.h"

using namespace std;


void Fecha::establecerFechaPorDefecto() {
    _dia = 1;
    _mes = 1;
    _anio = 2023;
}

bool Fecha::esBisiesto() {
    if ((_anio % 4 == 0 && _anio % 100 != 0) || _anio % 400 == 0) {
        return true;
    }
    return false;
}

void Fecha::agregarDia() {
    int dias[12] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
    if (esBisiesto()) {
        dias[1]++;
    }

    _dia++;
    if (_dia > dias[_mes - 1]) {
        _dia = 1;
        _mes++;
        if (_mes > 12) {
            _mes = 1;
            _anio++;
        }
    }
}

void Fecha::agregarDias(int cantidadDias) {

    if (cantidadDias > 0) {
        for (int i = 0; i < cantidadDias; i++) {
            agregarDia();
        }
    }

}

Fecha::Fecha() {
    establecerFechaPorDefecto();
}

Fecha::Fecha(int dia, int mes, int anio) {
    _dia = dia;
    _mes = mes;
    _anio = anio;

    if (_dia <= 0 || _mes <= 0 || _anio <= 0 || _mes > 12) {
        establecerFechaPorDefecto();
    }
    else {
        int dias[12] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
        if (esBisiesto()) {
            dias[1]++;
        }

        if (_dia > dias[_mes - 1]) {
            establecerFechaPorDefecto();
        }
    }
}

int Fecha::getDia() {
    return _dia;
}
int Fecha::getMes() {
    return _mes;
}
int Fecha::getAnio() {
    return _anio;
}

void Fecha::setDia(int dia) {
	_dia = dia;
}
void Fecha::setMes(int mes) {
	_mes = mes;
}
void Fecha::setAnio(int anio) {
	_anio = anio;
}



string Fecha::toString(string formatoFecha) {
    string fechaFormateada = "";

    string DD = to_string(_dia);
    string MM = to_string(_mes);
    string YYYY = to_string(_anio);
    // DD/MM/YYYY
    if (_dia < 10) {
        DD = "0" + to_string(_dia);
    }
    if (_mes < 10) {
        MM = "0" + to_string(_mes);
    }

    if (formatoFecha == "DD/MM/YYYY") {
        fechaFormateada = DD + "/" + MM + "/" + YYYY;
    }
    else if (formatoFecha == "YYYY/MM/DD") {
        fechaFormateada = YYYY + "/" + MM + "/" + DD;
    }
    else {
        fechaFormateada = DD + "/" + MM + "/" + YYYY;
    }

    return fechaFormateada;
}

void Fecha::Cargar()
{
    string input1;
    bool esNumero = false;
    bool cumpleCondicion = false;
    cout << "Dia: ";
    cin.ignore();
    getline(cin, input1);

    while (!esNumero || !cumpleCondicion) {
        bool todosDigitos = true;
        for (char c : input1) {
            if (!isdigit(c)) {
                todosDigitos = false;
                break;
            }
        }

        if (!todosDigitos) {
            rlutil::setColor(rlutil::RED);
            cout << "El dia debe ser un valor numerico. Ingrese nuevamente: ";
            rlutil::setColor(rlutil::BLACK);
            getline(cin, input1);
            continue;
        }

        int num = stoi(input1);
        if (num > 0 && num <= 31) {
            esNumero = true;
            cumpleCondicion = true;
        }
        else {
            rlutil::setColor(rlutil::RED);
            cout << "El dia debe ser mayor a 0 y menor o igual a 31. Ingrese nuevamente: ";
            rlutil::setColor(rlutil::BLACK);
            getline(cin, input1);
        }
    }

    _dia = stoi(input1);

    string input2;
    esNumero = false;
    cumpleCondicion = false;
    cout << "Mes: ";
    getline(cin, input2);

    while (!esNumero || !cumpleCondicion) {
        bool todosDigitos = true;
        for (char c : input2) {
            if (!isdigit(c)) {
                todosDigitos = false;
                break;
            }
        }

        if (!todosDigitos) {
            rlutil::setColor(rlutil::RED);
            cout << "El mes debe ser un valor numerico. Ingrese nuevamente: ";
            rlutil::setColor(rlutil::BLACK);
            getline(cin, input2);
            continue;
        }

        int num2 = stoi(input2);
        if (num2 > 0 && num2 <= 12) {
            esNumero = true;
            cumpleCondicion = true;
        }
        else {
            rlutil::setColor(rlutil::RED);
            cout << "El mes debe ser mayor a 0 y menor o igual a 12. Ingrese nuevamente: ";
            rlutil::setColor(rlutil::BLACK);
            getline(cin, input2);
        }
    }
    _mes = stoi(input2);
    

    string input3;
    esNumero = false;
    cumpleCondicion = false;
    cout << "Anio: ";
    getline(cin, input3);

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
            cout << "El anio debe ser un valor numerico. Ingrese nuevamente: ";
            rlutil::setColor(rlutil::BLACK);
            getline(cin, input3);
            continue;
        }

        int num3 = stoi(input3);
        if (num3 >= 2020 && num3 <= 2023) {
            esNumero = true;
            cumpleCondicion = true;
        }
        else {
            rlutil::setColor(rlutil::RED);
            cout << "El anio debe ser mayor o igual a 2020 y menor o igual a 2023. Ingrese nuevamente: ";
            rlutil::setColor(rlutil::BLACK);
            getline(cin, input3);
        }
    }

    _anio = stoi(input3);
}