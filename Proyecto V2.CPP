#include <iostream>
#include <string>
#include <vector>
#include <fstream>

using namespace std; 

struct Factura
{
    string nombrecl;
    string nombrevndr;
    vector<string> productos;
    vector<int> preciopro;
    int total = 0;

    // Método para serializar una factura
    void serialize(ofstream &out) const {
        size_t length = nombrecl.size();
        out.write(reinterpret_cast<const char*>(&length), sizeof(length));
        out.write(nombrecl.c_str(), length);

        length = nombrevndr.size();
        out.write(reinterpret_cast<const char*>(&length), sizeof(length));
        out.write(nombrevndr.c_str(), length);

        size_t size = productos.size();
        out.write(reinterpret_cast<const char*>(&size), sizeof(size));
        for (size_t i = 0; i < size; ++i) {
            length = productos[i].size();
            out.write(reinterpret_cast<const char*>(&length), sizeof(length));
            out.write(productos[i].c_str(), length);
            out.write(reinterpret_cast<const char*>(&preciopro[i]), sizeof(preciopro[i]));
        }

        out.write(reinterpret_cast<const char*>(&total), sizeof(total));
    }

    // Método para deserializar una factura
    void deserialize(ifstream &in) {
        size_t length, size;
        char buffer[256];

        in.read(reinterpret_cast<char*>(&length), sizeof(length));
        in.read(buffer, length);
        nombrecl.assign(buffer, length);

        in.read(reinterpret_cast<char*>(&length), sizeof(length));
        in.read(buffer, length);
        nombrevndr.assign(buffer, length);

        in.read(reinterpret_cast<char*>(&size), sizeof(size));
        productos.resize(size);
        preciopro.resize(size);
        for (size_t i = 0; i < size; ++i) {
            in.read(reinterpret_cast<char*>(&length), sizeof(length));
            in.read(buffer, length);
            productos[i].assign(buffer, length);
            in.read(reinterpret_cast<char*>(&preciopro[i]), sizeof(preciopro[i]));
        }

        in.read(reinterpret_cast<char*>(&total), sizeof(total));
    }
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
    } while(opc == 'S' || opc == 's');

    ofstream out("Basefacs.dat", ios::binary | ios::app);
    if (!out) {
        cerr << "Error al abrir el archivo para escritura." << endl;
        return;
    }
    FAC1.serialize(out);
    out.close();

    printf("\n\n\n\n\n\n\n\n\n\n\n\n");
}

void verfac() {
    ifstream in("Basefacs.dat", ios::binary);
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

    while (in.peek() != EOF) {
        FAC1.deserialize(in);
        if (FAC1.nombrecl == nombre) {
            encontrado = true;
            cout << "Nombre del Cliente: " << FAC1.nombrecl << endl;
            cout << "Nombre del Vendedor: " << FAC1.nombrevndr << endl;
            for (size_t i = 0; i < FAC1.productos.size(); ++i) {
                cout << "Producto: " << FAC1.productos[i] << " - Precio: " << FAC1.preciopro[i] << endl;
            }
            cout << "Total: " << FAC1.total << endl;
            cout << "------------------------------------" << endl;
        }
    }

    if (!encontrado) {
        cout << "No se encontró ninguna factura para el cliente: " << nombre << endl;
    }

    in.close();
}
