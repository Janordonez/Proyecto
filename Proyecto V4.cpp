#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include <stdlib.h>
#include <cstdio>
#include <windows.h>
#include <ctime>
#include <thread>

using namespace std;

struct Factura {
    string nombrecl;
    string nombrevndr;
    vector<string> productos;
    vector<int> preciopro;
    string direccion = "Almacen SONY 2 cuadras y media al Oeste.";
    string cancelacion;
    vector <int> id;
    vector <int> cantidad;
    int totalsinIVA = 0;
    int IVA;
    int Numerofac;
    int TOTALIVA = 0;
    int TOTALIVA2 = 0;
    int celular;
    int RUC;
    int multpro;
    
};

struct Comparador{
    string productocomp;
    int preciocomp;
    int cantidad;
    int id;
};

struct fecha{
    int año;
    int mes;
    int dias;

    int añoamax;
    int mesmax;
    int diasmax;
};

struct resumenesdats{
    int totalventas;
    vector <string> productosvendidos;
    int productosvendidoscant;
};


// Definir la función gotoxy
void gotoxy(int x, int y) {
    // Obtener el handle de la consola
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    
    // Definir la estructura COORD con la posicióno
    COORD pos;
    pos.X = x;
    pos.Y = y;
    
    // Mover el cursor a la posición definida
    SetConsoleCursorPosition(hConsole, pos);
}


int año;
int mes;
int dia;

void reloj(){
    time_t now = time(nullptr);
    struct tm * time = localtime(&now);
    
    año = 1900 + time->tm_year; // Año actual
    mes = 1 + time->tm_mon;     // Mes actual (1-12)
    dia = time->tm_mday;        // Día del mes (1-31)

}


void menu();
void crearfac();
void verfac();
void restarINV();
void resumenes();
void eliminarfac();

int main() {
    fflush(stdout);
    menu();
    return 0;
}

void menu() {
    char opc;
    do {
        system("cls");
        gotoxy(30, 5);
        cout << "------------------------------------------------------------\n";
        gotoxy(30, 6);
        cout << "------------------------------------------------------------\n";
        gotoxy(30, 7);
        cout << "----------------------------MENU----------------------------\n";
        gotoxy(50, 8);
        cout << "1. Crear Factura\n";
        gotoxy(50, 9);
        cout << "2. Ver Facturas\n";
        gotoxy(50, 10);
        cout << "3. Eliminar Factura\n";
        gotoxy(50, 11);
        cout << "4. Resumenes\n";
        gotoxy(50, 12);
        cout << "5. Salir\n";
        gotoxy(30, 13);
        cout << "------------------------------------------------------------\n";
        gotoxy(30, 14);
        cout << "------------------------------------------------------------\n";
        cin >> opc;

        switch (opc) {
            case '1':
                crearfac();
                break;
            case '2':
                verfac();
                break;
            case '3':
                eliminarfac();
                break;
            case '4':
                resumenes();
            case '5':
                return;
            default:
                cout << "Opción no válida. Inténtalo de nuevo.\n";
                break;
        }
    } while (opc != '4');
}



void crearfac() {
    system("cls");
   
    Factura FAC1;
    
    char opc;

    Comparador COMP1;

    int idcomp;


    string line1;
    
    ifstream INV("Basedatosinv.txt");
    if(!INV){
        return;
    }
    
    
    cout << "Ingrese el nombre del cliente:" << endl;
    cin.ignore();
    getline(cin, FAC1.nombrecl);
    cout << "\nDigite el numero celular del cliente:" << endl;
    cin >> FAC1.celular;
    cout << "\nIngrese el nombre del vendedor:" << endl;
    cin.ignore();
    getline(cin, FAC1.nombrevndr);

    

    cout << "\nProductos en inventario:" << endl;

    while(getline(INV, line1)){
        stringstream ss(line1);
        ss >> COMP1.id;
        ss.ignore();
        getline(ss, COMP1.productocomp, ',');
        ss >> COMP1.preciocomp;
        ss.ignore();
        ss >> COMP1.cantidad;
        cout << "ID:" << COMP1.id << " " << "Producto: " << COMP1.productocomp << " "<< "Precio: " << COMP1.preciocomp << " "<< "Cantidad: " << COMP1.cantidad << endl;
    }

    
    do {
        INV.clear();
        INV.seekg(0, ios::beg);

        cout << "Digite el id del producto: " << endl;
        cin >> idcomp;

        cout << "Digite la cantidad que desea facturar: " << endl;
        cin >> FAC1.multpro;
        
        while(getline(INV, line1)){
            stringstream ss(line1);
            ss >> COMP1.id;
            ss.ignore();
            getline(ss, COMP1.productocomp, ',');
            ss >> COMP1.preciocomp;
            ss.ignore();
            ss >> COMP1.cantidad;
            if(COMP1.id == idcomp){
                FAC1.productos.push_back(COMP1.productocomp);
                FAC1.preciopro.push_back(COMP1.preciocomp);
                FAC1.id.push_back(idcomp);
                FAC1.cantidad.push_back(FAC1.multpro);
                FAC1.totalsinIVA += COMP1.preciocomp * FAC1.multpro;
                FAC1.TOTALIVA += 0.15 * FAC1.totalsinIVA;
                FAC1.TOTALIVA2 += FAC1.TOTALIVA + FAC1.totalsinIVA;
            }
        }

        cout << "Desea ingresar otro producto? (S/N): ";
        cin >> opc;
        cin.ignore();
        
    } while (opc == 'S' || opc == 's');

    INV.close();

    reloj();

    cout << "Digite el tipo de cancelacion:" << endl;
    getline(cin, FAC1.cancelacion);

    ofstream out("Basefacs.txt", ios::app);
    if (!out) {
        cerr << "Error al abrir el archivo para escritura." << endl;
        return;
    }

    out << FAC1.nombrecl << ',' << FAC1.nombrevndr << ',' << FAC1.totalsinIVA << ',' << FAC1.TOTALIVA << ',' << FAC1.TOTALIVA2 << ',' << FAC1.celular << ',' << FAC1.cancelacion << ',' << dia << ',' << mes << ',' << año << '\n';
    for (size_t i = 0; i < FAC1.productos.size(); ++i) {
        out << FAC1.productos[i] << ',' << FAC1.preciopro[i] << ',' << FAC1.cantidad[i] << '\n';
    }
    out << "Final" << '\n';
    out.close();
    menu();
}

void verfac() {
    
    ifstream in("Basefacs.txt");
    if (!in) {
        cerr << "No se pudo abrir el archivo para lectura." << endl;
        return;
    }

    Factura FAC1;
    fecha FECH1;
    string nombre;
    string años, mes, dia;
    bool encontrado = false;

    cout << "Digite el nombre del cliente para encontrar la factura:" << endl;
    cin.ignore();
    getline(cin, nombre);

    string line;
    while (getline(in, line)) {
        stringstream ss(line);
        getline(ss, FAC1.nombrecl, ',');
        if (FAC1.nombrecl == nombre) {
            encontrado = true;
            getline(ss, FAC1.nombrevndr, ',');
            ss >> FAC1.totalsinIVA;
            ss.ignore(); // Ignorar la coma
            ss >> FAC1.TOTALIVA;
            ss.ignore();
            ss >> FAC1.TOTALIVA2;
            ss.ignore();
            ss >> FAC1.celular;
            ss.ignore();
            getline(ss, FAC1.cancelacion, ',');
            ss >> FECH1.dias;
            ss.ignore();
            ss >> FECH1.mes;
            ss.ignore();
            ss >> FECH1.año;
    
            cout << "Nombre del Cliente: " << FAC1.nombrecl << endl;
            cout << "Nombre del Vendedor: " << FAC1.nombrevndr << endl;
            cout << "Total sin IVA: " << FAC1.totalsinIVA << endl;
            cout << "IVA: " << FAC1.TOTALIVA << endl;
            cout << "Total: " << FAC1.TOTALIVA2 << endl;
            cout << "Celular: " << FAC1.celular << endl;
            cout << "Tipo de cancelacion: " << FAC1.cancelacion << endl;
            cout << "Productos:" << endl;

            FAC1.productos.clear();
            FAC1.preciopro.clear();

            while (getline(in, line) && line != "Final"){
                stringstream ss(line);
                string producto;
                int precio;
                int cantidad;
                getline(ss, producto, ',');
                ss >> precio;
                ss.ignore();
                ss >> cantidad;
            
                cout << "Producto: " << producto << " - Precio: " << precio << " - Cantidad: " << cantidad << endl;
            }
            cout << "Fecha: " << FECH1.dias << ":" << FECH1.mes << ":" << FECH1.año;
            cout << "\n------------------------------------" << endl;
        }
    }
    system ("pause");
    cout << "\n\n\n\n\n\n\n\n\n\n\n";

    if (!encontrado) {
        cout << "No se encontró ninguna factura para el cliente: " << nombre << endl;
        system ("pause");
    }

    in.close();
}

void eliminarfac() {
    ifstream in("Basefacs.txt");
    if (!in) {
        cerr << "No se pudo abrir el archivo para lectura." << endl;
        return;
    }

    ofstream temp("Tempfacs.txt");
    if (!temp) {
        cerr << "No se pudo abrir el archivo temporal para escritura." << endl;
        in.close();
        return;
    }

    Factura FAC1;
    string nombre;
    bool encontrado = false;

    cout << "Digite el nombre del cliente para eliminar la factura:" << endl;
    cin.ignore();
    getline(cin, nombre);

    string line;
    while (getline(in, line)) {
        stringstream ss(line);
        getline(ss, FAC1.nombrecl, ',');
        getline(ss, FAC1.nombrevndr, ',');
        ss >> FAC1.totalsinIVA;

        if (FAC1.nombrecl == nombre) {
            encontrado = true;
            // Saltar lineas
            while (getline(in, line) && line != "Final") {
                // No hacer nada
            }
        } else {
            // Escribir factura en el archivo temporal
            temp << FAC1.nombrecl << ',' << FAC1.nombrevndr << ',' << FAC1.totalsinIVA << '\n';

            while (getline(in, line) && line != "Final") {
                temp << line << '\n';
            }
            temp << "Final" << '\n';
        }
    }
    if (!encontrado) {
        cout << "No se encontró ninguna factura para el cliente: " << nombre << endl;
    } else {
        cout << "Factura eliminada exitosamente." << endl;
    }

    in.close();
    temp.close();

    // Reemplaza el original borrando el original y renombrando el temporal
    remove("Basefacs.txt");
    rename("Tempfacs.txt", "Basefacs.txt");
}

void resumenes(){
    ifstream res("Basefacs.txt");
    
    if(!res){
        cout << "La base de datos de facturas no se pudo abrir";
    }

    fecha FECHCOMP;

    cout << "Digite las fechas que desea ver el resumen(dia/mes/año)" << endl;
    cin >> FECHCOMP.dias;
    cin >> FECHCOMP.mes;
    cin >> FECHCOMP.año;

    cout << "Digite la fecha maxima que desea ver el resumen(dia/mes/año)" << endl;
    cin >> FECHCOMP.diasmax;
    cin >> FECHCOMP.mesmax;
    cin >> FECHCOMP.añoamax;

    Factura FAC1;
    fecha FECH1;
    string line;
    while(getline(res, line)){
        stringstream ss(line);
            getline(ss, FAC1.nombrecl, ',');
            getline(ss, FAC1.nombrevndr, ',');
            ss >> FAC1.totalsinIVA;
            ss.ignore(); // Ignorar la coma
            ss >> FAC1.TOTALIVA;
            ss.ignore();
            ss >> FAC1.TOTALIVA2;
            ss.ignore();
            ss >> FAC1.celular;
            ss.ignore();
            getline(ss, FAC1.cancelacion, ',');
            ss >> FECH1.dias;
            ss.ignore();
            ss >> FECH1.mes;
            ss.ignore();
            ss >> FECH1.año;
            

        if((FECH1.dias >= FECHCOMP.dias && FECH1.mes >= FECHCOMP.mes && FECH1.año >=  FECHCOMP.año) && (FECH1.dias <= FECHCOMP.diasmax && FECH1.mes <= FECHCOMP.mesmax && FECH1.año <=  FECHCOMP.añoamax) ){

            cout << "Nombre del Cliente: " << FAC1.nombrecl << endl;
            cout << "Nombre del Vendedor: " << FAC1.nombrevndr << endl;
            cout << "Total sin IVA: " << FAC1.totalsinIVA << endl;
            cout << "IVA: " << FAC1.TOTALIVA << endl;
            cout << "Total: " << FAC1.TOTALIVA2 << endl;
            cout << "Celular: " << FAC1.celular << endl;
            cout << "Tipo de cancelacion: " << FAC1.cancelacion << endl;
            cout << "Productos:" << endl;

            FAC1.productos.clear();
            FAC1.preciopro.clear();
            

            while (getline(res, line) && line != "Final"){
                stringstream ss(line);
                string producto;
                resumenesdats resumenes;
                resumenes.productosvendidoscant++;
                int precio;
                int cantidad;
                getline(ss, producto, ',');
                ss >> precio;
                ss.ignore();
                ss >> cantidad;
                resumenes.productosvendidos.push_back(producto);
                resumenes.totalventas += precio;
                cout << "Producto: " << producto << " - Precio: " << precio << " - Cantidad: " << cantidad << endl;
            }
            cout << "Fecha: " << FECH1.dias << ":" << FECH1.mes << ":" << FECH1.año;
            cout << "\n------------------------------------" << endl;
            }
            
    
}

system("pause");
res.close();
return menu();
}