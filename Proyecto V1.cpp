#include <iostream>
#include <string>
#include <stdio.h>
#include <stdlib.h>
#include <vector>

using namespace std; 




struct Factura
{
    string nombrecl;
    string nombrevndr;
    vector <string>productos;
    vector <int>preciopro;
    int total = 0;

};


void menu();
void crearfac();
void verfac();

int main(){
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


void crearfac(){
    FILE *factura;
    Factura FAC1;
    string productos;
    int precioproducto;

    char opc;

    factura = fopen("Basefacs.dat","ab");

    cout<<"Ingrese el nombre del cliente:"<<endl;
    scanf("%s",&FAC1.nombrecl);
    cout<<"Ingrese el nombre del vendedor:"<<endl;
    cin>>FAC1.nombrevndr;

    do{
    cout<<"Ingrese los productos:"<<endl;
    cin>>productos;
    
    cout<<"Digite el precio del producto que ingreso:"<<endl;
    cin>>precioproducto;
    
    cout<<"Desea ingresar otro producto?";
    cin>>opc;

    FAC1.total +=precioproducto;
    FAC1.productos.push_back(productos);
    FAC1.preciopro.push_back(precioproducto);
    }while(opc == 'S');

    fseek(factura, 0L, SEEK_END);
    fwrite(&FAC1, sizeof(Factura), 1, factura);
    fclose(factura);

    printf("\n\n\n\n\n\n\n\n\n\n\n\n");
    
    menu();
}

void verfac(){
    FILE *factura;
    Factura FAC1;
    string nombre;
    int econtrado = 0;

    factura = fopen("Basefacs.dat","rb");

    if(factura == NULL){
        cout<<"No se pudo abrir!";
    }
    cout<<"Digite el nombre del cliente para encontrar la factura:"<<endl;
    cin>>nombre;

    while (fread(&FAC1, sizeof(Factura),1,factura)==1)
    {
        if(FAC1.nombrecl == nombre)
        econtrado = 1;
        cout<<FAC1.nombrecl,FAC1.nombrevndr,FAC1.preciopro,FAC1.productos,FAC1.total;

    }
    
}