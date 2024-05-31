#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>

using namespace std;

struct Factura {
    string nombrecl;
    string nombrevndr;
    vector<string> productos;
    vector<int> preciopro;
    int total = 0;
};

void menu();
void crearfac();
void verfac();

int main() {
    menu();
    return 0;
}

void menu() {
    char opc;
    do {
        cout << "------------------------------------------------------------\n";
        cout << "------------------------------------------------------------\n";
        cout << "----------------------------MENU----------------------------\n";
        cout << "------------------------1. Crear Factura--------------------\n";
        cout << "------------------------2. Ver Facturas---------------------\n";
        cout << "------------------------3. Salir----------------------------\n";
        cout << "------------------------------------------------------------\n";
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
                cout << "Saliendo...\n";
                break;
            default:
                cout << "Opción no válida. Inténtalo de nuevo.\n";
                break;
        }
    } while (opc != '3');
}

void crearfac() {
    Factura FAC1;
    string producto;
    int precioproducto;
    char opc;

    cout << "Ingrese el nombre del cliente:" << endl;
    cin.ignore();
    getline(cin, FAC1.nombrecl);
    cout << "Ingrese el nombre del vendedor:" << endl;
    getline(cin, FAC1.nombrevndr);

    do {
        cout << "Ingrese los productos:" << endl;
        getline(cin, producto);

        cout << "Digite el precio del producto que ingreso:" << endl;
        cin >> precioproducto;

        cout << "Desea ingresar otro producto? (S/N): ";
        cin >> opc;
        cin.ignore();

        FAC1.total += precioproducto;
        FAC1.productos.push_back(producto);
        FAC1.preciopro.push_back(precioproducto);
    } while (opc == 'S' || opc == 's');

    ofstream out("Basefacs.txt", ios::app);
    if (!out) {
        cerr << "Error al abrir el archivo para escritura." << endl;
        return;
    }

    out << FAC1.nombrecl << ',' << FAC1.nombrevndr << ',' << FAC1.total << '\n';
    for (size_t i = 0; i < FAC1.productos.size(); ++i) {
        out << FAC1.productos[i] << ',' << FAC1.preciopro[i] << '\n';
    }
    out << "Final" << '\n';
    out.close();
}

void verfac() {
    ifstream in("Basefacs.txt");
    if (!in) {
        cerr << "No se pudo abrir el archivo para lectura." << endl;
        return;
    }

    Factura FAC1;
    string nombre;
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
            ss >> FAC1.total;

            cout << "Nombre del Cliente: " << FAC1.nombrecl << endl;
            cout << "Nombre del Vendedor: " << FAC1.nombrevndr << endl;
            cout << "Total: " << FAC1.total << endl;
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
            cout << "------------------------------------" << endl;
        }
    }

    if (!encontrado) {
        cout << "No se encontró ninguna factura para el cliente: " << nombre << endl;
    }

    in.close();
}
