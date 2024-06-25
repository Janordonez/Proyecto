#include <iostream>
#include <sstream>
#include <fstream>
#include <vector>
#include <string>
#include <cstdio>

using namespace std;

struct Productos{
    vector <string> nombre;
    vector <int> PU;
    vector <int> Cantidad;
};

struct Productosid{
    string nombre;
    int PU;
    int Cantidad;
};

void menu();
void añadirinvnuevo();
void añadiraexistente();
void verinv();
void añadirmenu();

int main(){
    menu();
}

void menu(){
    system("cls");
    char opc;
    do {
        cout << "------------------------------------------------------------\n";
        cout << "------------------------------------------------------------\n";
        cout << "----------------------------MENU----------------------------\n";
        cout << "------------------------1. Añadir---------------------------\n";
        cout << "------------------------2. Ver Inventario-------------------\n";
        cout << "------------------------3. Salir----------------------------\n";
        cout << "------------------------------------------------------------\n";
        cout << "------------------------------------------------------------\n";
        cin >> opc;

        switch (opc) {
            case '1':
                añadirmenu();    
                break;
            case '2':
                verinv();
                break;
            case '3':
                break;
            default:
                cout << "Opción no válida. Inténtalo de nuevo.\n";
                break;
        }
    } while (opc != '3');
}

void añadirmenu(){
    system("cls");
    char opc;
    do {
        cout << "------------------------------------------------------------\n";
        cout << "------------------------------------------------------------\n";
        cout << "----------------------------MENU----------------------------\n";
        cout << "------------------------1. Añadir nuevo---------------------\n";
        cout << "------------------------2. Añadir existente-----------------\n";
        cout << "------------------------3. volver---------------------------\n";
        cout << "------------------------------------------------------------\n";
        cout << "------------------------------------------------------------\n";
        cin >> opc;

        switch (opc) {
            case '1':
                añadirinvnuevo();    
                break;
            case '2':
                añadiraexistente();
                break;
            case '3':
                return menu();
            default:
                cout << "Opción no válida. Inténtalo de nuevo.\n";
                break;
        }
    } while (opc != '3');

}

void añadiraexistente(){
    ifstream in("Basedatosinv.txt");
    ofstream temp("Basedatosinvtemp.txt");

    Productosid Productosid;
    string idproducto;
    int ncantidad;
    string line;
    bool nuevosi = false;

    

    while(getline(in, line)){
        cout << line << endl;
    };

    in.clear();
    in.seekg(0, ios::beg);


    cin.ignore();
    cout << "Digite el producto que desea añadir: " << endl;
    getline(cin, idproducto);

    cout << "Cantidad: " << endl;
    cin >> ncantidad;

    while(getline(in, line)){
        stringstream ss(line);
        getline(ss, Productosid.nombre, ',');
        ss >> Productosid.PU;
        ss.ignore();
        ss >> Productosid.Cantidad;
        if(Productosid.nombre == idproducto){
            nuevosi = true;
            temp << idproducto << ',' << Productosid.PU << ',' << ncantidad << endl;
        } else{
            temp << Productosid.nombre << ',' << Productosid.PU << ',' << Productosid.Cantidad << endl;
        }
    }

    if(!nuevosi){
            cout << "El producto no fue encontrado!"<< endl;
            system("pause");
        } else{
            cout << "Cantidad en inventario actualizado correctamente!" << endl;
        }
    in.close();
    temp.close();

    remove("Basedatosinv.txt");
    rename("Basedatosinvtemp.txt", "Basedatosinv.txt");
}
void añadirinvnuevo(){
    system("cls");

    

    Productos Producto1;
    char opc;
    string nombre;
    int PU;
    int cantidad;

    do{
    
    cin.ignore();

    cout << "Escriba el producto a añadir: ";
    getline(cin, nombre);

    cout << "Digita el precio unitario: ";
    cin >> PU;

    cout << "Digita la cantidad en inventario: ";
    cin >> cantidad;

    cout << "Desea agregar otro producto?";
    cin >> opc;

    Producto1.nombre.push_back(nombre);
    Producto1.PU.push_back(PU);
    Producto1.Cantidad.push_back(cantidad);
    }while(opc == 'S');

    ofstream out("Basedatosinv.txt", ios :: app);
    if(!out){
        cout << "El archivo no se pudo abrir";
    }

    for(size_t i = 0; i < Producto1.nombre.size(); i++ ){
        out << Producto1.nombre[i] << ',' << Producto1.PU[i] << ',' << Producto1.Cantidad[i] << "\n";
    }

    out.close();
    menu();
}

void verinv(){
    system("cls");
    int PU;
    string Nombre;
    int cantidad;

    ifstream in("Basedatosinv.txt");

    string line;
    while(getline(in, line)){
        stringstream ss(line);
        getline(ss, Nombre, ',');
        ss >> PU;
        ss.ignore();
        ss >> cantidad;
        cout << "Producto: " << Nombre << " ----- " << "Cantidad:" << cantidad << " ----- " << "Precio: " << PU << endl;
    
    }
    in.close();
    system("pause");
    menu();
}