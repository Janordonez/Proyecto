#include <iostream>
#include <sstream>
#include <fstream>
#include <vector>
#include <windows.h>
#include <string>
#include <cstdio>

using namespace std;

struct Productos{
    vector <string> nombre;
    vector <int> PU;
    vector <int> Cantidad;
    vector <int> ID;
};

struct Productosid{
    string nombre;
    int PU;
    int Cantidad;
    int ID;
};

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


void menu();
void añadirinvnuevo();
void añadiraexistente();
void verinv();
void añadirmenu();

int main(){
    system("cls");
    menu();
}

void menu(){
    system("cls");
    string line;
    Productosid idmenu;

    ifstream in("Basedatosinv.txt");
    while(getline(in, line)){
        stringstream ss(line);
        ss >> idmenu.ID;
        ss.ignore();
        getline(ss, idmenu.nombre, ',');
        ss >> idmenu.PU;
        ss.ignore();
        ss >> idmenu.Cantidad;

        if(idmenu.Cantidad < 5){
            cout << "Producto bajo en stock: " << idmenu.nombre << endl;
        } else{

        }
    }

    in.close();

    
    char opc;
    do {
        
        gotoxy(50, 6);
        cout << "--------------------------------------------\n";
        gotoxy(50, 7);
        cout << "--------------------MENU--------------------\n";
        gotoxy(63, 8);
        cout << "1. Ingresar Productos\n";
        gotoxy(63, 9);
        cout << "2. Ver Productos\n";
        gotoxy(63, 10);
        cout << "3. Eliminar Productos\n";
        gotoxy(63, 11);
        cout << "4. Salir\n";
        gotoxy(50, 12);
        cout << "--------------------------------------------\n";
        gotoxy(50, 13);
        cout << "--------------------------------------------\n";
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
        gotoxy(50, 6);
        cout << "--------------------------------------------\n";
        gotoxy(50, 7);
        cout << "--------------------MENU--------------------\n";
        gotoxy(63, 8);
        cout << "1. Ingresar Productos Nuevo\n";
        gotoxy(63, 9);
        cout << "2. Ingresar Productos Existentes\n";
        gotoxy(63, 10);
        cout << "3. Eliminar Productos\n";
        gotoxy(63, 11);
        cout << "4. Salir\n";
        gotoxy(50, 12);
        cout << "--------------------------------------------\n";
        gotoxy(50, 13);
        cout << "--------------------------------------------\n";
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
            temp << Productosid.nombre << ',' << Productosid.PU << ',' << Productosid.Cantidad + ncantidad << endl;
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

    fflush(stdout);

    in.close();
    temp.close();

    remove("Basedatosinv.txt");
    rename("Basedatosinvtemp.txt", "Basedatosinv.txt");

    menu();
}

void añadirinvnuevo(){
    system("cls");

    

    Productos Producto1;
    char opc;
    string nombre;
    int PU;
    int cantidad;
    int ID;

    do{
    
    cin.ignore();

    cout << "Digite el ID del producto:";
    cin >> ID;

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
    Producto1.ID.push_back(ID);
    }while(opc == 'S');

    ofstream out("Basedatosinv.txt", ios :: app);
    if(!out){
        cout << "El archivo no se pudo abrir";
    }

    for(size_t i = 0; i < Producto1.nombre.size(); i++ ){
        out << Producto1.ID[i] << ',' << Producto1.nombre[i] << ',' << Producto1.PU[i] << ',' << Producto1.Cantidad[i] << "\n";
    }

    out.close();
    menu();
}

void verinv(){
    system("cls");
    int PU;
    string Nombre;
    int cantidad;
    int id;

    ifstream in("Basedatosinv.txt");

    string line;
    while(getline(in, line)){
        stringstream ss(line);
        cin >> id;
        ss.ignore();
        getline(ss, Nombre, ',');
        ss >> PU;
        ss.ignore();
        ss >> cantidad;
        cout << "ID:" << id << " ----- " << "Producto: " << Nombre << " ----- " << "Precio: " << PU << " ----- " << "Cantidad:" << cantidad << endl;
    
    }
    in.close();
    system("pause");
    menu();
}