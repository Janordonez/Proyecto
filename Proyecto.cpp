#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include <stdlib.h>
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
    int totalsinIVA = 0;
    int IVA;
    int Numerofac;
    int TOTALIVA = 0;
    int TOTALIVA2 = 0;
    int celular;
    int RUC;
    int multpro;
    
};

struct fecha{
    int año;
    int mes;
    int dias;
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
        time_t now = time(0);
        tm * time = localtime(&now);
        año = time->tm_year;
        mes = time->tm_mon;
        dia = time->tm_mday;
        
}


void menu();
void crearfac();
void verfac();
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
        cout << "4. Salir\n";
        gotoxy(30, 12);
        cout << "------------------------------------------------------------\n";
        gotoxy(30, 13);
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
                cout << "Saliendo...\n";
                break;
            default:
                cout << "Opción no válida. Inténtalo de nuevo.\n";
                break;
        }
    } while (opc != '4');
}

void crearfac() {
    system("cls");
    thread relojcontador (reloj);
    Factura FAC1;
    string producto;
    int precioproducto;
    char opc;

    string productocomp;
    int preciocomp;
    int cantidad;
    int ninv;

    ifstream INV("Basedatosinv.txt");
    string line;

    ofstream temp("Basefacstemp.txt");
    if(!temp){
        return;
    }
    
    
    cout << "Ingrese el nombre del cliente:" << endl;
    cin.ignore();
    getline(cin, FAC1.nombrecl);
    cout << "Digite el numero celular del cliente:" << endl;
    cin >> FAC1.celular;
    cout << "Ingrese el nombre del vendedor:" << endl;
    cin.ignore();
    getline(cin, FAC1.nombrevndr);

    do {
       cout << "Ingrese los productos:" << endl;
        getline(cin, producto);

        cout << "Digite el precio del producto que ingreso:" << endl;
        cin >> precioproducto;
    
        cout << "Digite la cantidad del producto que desea facturar:" << endl;
        cin >> FAC1.multpro;

        cout << "Desea ingresar otro producto? (S/N): ";
        cin >> opc;
        cin.ignore();

        while(getline(INV, line)){
            stringstream ss(line);
            getline(ss, productocomp, ',');
            ss >> preciocomp;
            ss.ignore();
            ss >> cantidad;
            if(productocomp == producto){
                ninv = cantidad - FAC1.multpro;
                temp << productocomp << "," << preciocomp << "," << ninv;
            }
            else{
                temp << "\n" << line;
            }
        }
        
        remove("Basedatoinv.txt");
        rename("Basefacstemp.txt", "Basedatoinv.txt");

        FAC1.totalsinIVA += precioproducto * FAC1.multpro;
        FAC1.TOTALIVA = 0.15 * FAC1.totalsinIVA;
        FAC1.TOTALIVA2 = FAC1.TOTALIVA + FAC1.totalsinIVA;
        FAC1.productos.push_back(producto);
        FAC1.preciopro.push_back(precioproducto);

        
    } while (opc == 'S' || opc == 's');

    cout << "Digite el tipo de cancelacion:" << endl;
    getline(cin, FAC1.cancelacion);



    ofstream out("Basefacs.txt", ios::app);
    if (!out) {
        cerr << "Error al abrir el archivo para escritura." << endl;
        return;
    }

    out << FAC1.nombrecl << ',' << FAC1.nombrevndr << ',' << FAC1.totalsinIVA << ',' << FAC1.TOTALIVA << ',' << FAC1.TOTALIVA2 << ',' << FAC1.celular << ',' << FAC1.cancelacion << ',' << dia << ',' << mes + 1 << ',' << año - 100 << '\n';
    for (size_t i = 0; i < FAC1.productos.size(); ++i) {
        out << FAC1.productos[i] << ',' << FAC1.preciopro[i] << '\n';
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
                stringstream ssProduct(line);
                string producto;
                int precio;
                getline(ssProduct, producto, ',');
                ssProduct >> precio;
            
                cout << "Producto: " << producto << " - Precio: " << precio << endl;
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
            // Skip lines related to this factura
            while (getline(in, line) && line != "Final") {
                // do nothing
            }
        } else {
            // Write the factura to the temp file
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

    // Replace original file with temp file
    remove("Basefacs.txt");
    rename("Tempfacs.txt", "Basefacs.txt");
}