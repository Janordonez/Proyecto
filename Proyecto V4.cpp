#include <iostream> // Libreria para la entrada y salida de datos
#include <string> // Libreria para el uso de cadenas 
#include <vector> // Libreria para la implementacion de vectores "arreglos dinamicos"
#include <fstream> // Libreria para la manipulacion de archivos
#include <sstream> // Libreria para la manipulacion de cadena como flujos de datos del archivo txt
#include <stdlib.h> // Libreria estandar de C
#include <windows.h> // Libreria de windows para manejo mas intituivo de la consola
#include <ctime> // Liberia para acceder a la estructura time

using namespace std;

// Estructura para almacenar los productos
struct Productos {
    vector<string> nombre;
    vector<int> PU;         // Precio Unitario
    vector<int> Cantidad;   // Cantidad en inventario
    vector<int> ID;         // Identificador único del producto
};

// Estructura para manejar los productos individualmente
struct Productosid {
    string nombre;
    int PU;
    int Cantidad;
    int ID;
};

// Estructura para guardar cada factura
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

//Estructura para comparar y filtrar facturas
struct Comparador{
    string productocomp;
    int preciocomp;
    int cantidad;
    int id;
};

//Estructura para filtrar facturas desde una fecha hasta una fecha maxima
struct fecha{
    int año;
    int mes;
    int dias;

    int añoamax;
    int mesmax;
    int diasmax;
};

//Estructura para los resumenes a partir de las facturas filtradas por la estructura anterior
struct resumenesdats{
    int totalventas = 0;
    vector <string> productosvendidos;
    int productosvendidoscant = 0;
};


// Definir la función gotoxy
void gotoxy(int x, int y) {
    // Obtener el handle de la consola
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    
    // Definir la estructura COORD con la posicióno
    COORD pos;
    pos.X = x; // Obtiene la posicion en el eje x
    pos.Y = y; // obtiene la posicion en el eje y
    
    // Mover el cursor a la posición definida
    SetConsoleCursorPosition(hConsole, pos);
}


int año;
int mes;
int dia;

//Funcion para obtener la hora
void reloj(){
    time_t now = time(nullptr); //Obtiene el tiempo actual y lo inicializa en 0
    struct tm * time = localtime(&now); // Convierte la fecha a local
    
    año = 1900 + time->tm_year; // Año actual
    mes = 1 + time->tm_mon;     // Mes actual (1-12)
    dia = time->tm_mday;        // Día del mes (1-31)

}

//Declaracion de funciones a utilizar
void menu();
void crearfac();
void verfac();
void restarINV();
void añadirinvnuevo();
void añadiraexistente();
void verinv();
void añadirmenu();
void resumenes();
void eliminarfac();
void menufacs();
void menuinv();

// Funcion principal 
int main() {
    menu(); // Llama a menu
    return 0; 
}



void menu() {
    char opc;
    do {
        system("cls"); // Limpia la consola
        gotoxy(30, 5); // Llama a la funcion gotoxy o "iraxy" esta funcion ubica el cout siguiente dependiendo de los numeros que se le pasen
        cout << "------------------------------------------------------------\n";
        gotoxy(30, 6);
        cout << "------------------------------------------------------------\n";
        gotoxy(30, 7);
        cout << "----------------------------MENU----------------------------\n";
        gotoxy(50, 8);
        cout << "1. Menu de facturas\n";
        gotoxy(50, 9);
        cout << "2. Menu de Inventario\n";
        gotoxy(50, 10);
        cout << "3. Salir\n";
        gotoxy(30, 11);
        cout << "------------------------------------------------------------\n";
        gotoxy(30, 12);
        cout << "------------------------------------------------------------\n";
        cin >> opc;

        // Este es un switch con los respectivos casos dependiendo de el numero leido por opc llamara a una funcion u otra
        switch (opc) {
            case '1':
                menufacs();
                break;
            case '2':
                menuinv();
                break;
            case '3':
                return;
            default:
                cout << "Opcion no valida. Intentalo de nuevo.\n";
                break;
        }
    } while (opc != '4');
}

// Funcion del menu
void menufacs() {
    char opc;
    do {
        system("cls"); // Limpia la consola
        gotoxy(30, 5); // Llama a la funcion gotoxy o "iraxy" esta funcion ubica el cout siguiente dependiendo de los numeros que se le pasen
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

        // Este es un switch con los respectivos casos dependiendo de el numero leido por opc llamara a una funcion u otra
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
                cout << "Opcion no valida. Intentalo de nuevo.\n";
                break;
        }
    } while (opc != '4');
}



void crearfac() {
    system("cls"); // Limpia la pantalla para una interfaz limpia

    Factura FAC1; // Objeto para almacenar detalles de la factura
    char opc; // Opción de usuario para continuar ingresando productos
    Comparador COMP1; // Objeto para comparar y seleccionar productos del inventario
    int idcomp; // ID del producto seleccionado por el usuario
    string line1; // Variable para leer lineas del archivo de inventario

    ifstream INV("Basedatosinv.txt"); // Abre el archivo de inventario para lectura
    if (!INV) { // Verifica si el archivo de inventario se abrió correctamente
        return; // Sale de la función si hay un problema con el archivo
    }

    // Pregunta los datos del cliente y vendedor
    cout << "Ingrese el nombre del cliente:" << endl;
    cin.ignore();
    getline(cin, FAC1.nombrecl);
    cout << "\nDigite el numero celular del cliente:" << endl;
    cin >> FAC1.celular;
    cout << "\nIngrese el nombre del vendedor:" << endl;
    cin.ignore();
    getline(cin, FAC1.nombrevndr);

    // Muestra los productos disponibles en el inventario
    cout << "\nProductos en inventario:" << endl;
    while (getline(INV, line1)) {
        // Lee cada linea del archivo de inventario
        stringstream ss(line1); 
        ss >> COMP1.id;
        ss.ignore();
        getline(ss, COMP1.productocomp, ',');
        ss >> COMP1.preciocomp;
        ss.ignore();
        ss >> COMP1.cantidad;
        cout << "ID:" << COMP1.id << " " << "Producto: " << COMP1.productocomp << " " << "Precio: " << COMP1.preciocomp << " " << "Cantidad: " << COMP1.cantidad << endl; // Imprime los datos de cada productoo
    }

    // Selección de productos para la factura
    do {
        //Reincia el cursor de lectura al principio y limpia el flujo de datos de INV ya que pudo haber leido mas alla del final de archivo
        INV.clear();
        INV.seekg(0, ios::beg);

        // Solicita al usuario ingresar el ID del producto y la cantidad a facturar
        cout << "Digite el id del producto: " << endl;
        cin >> idcomp;
        cout << "Digite la cantidad que desea facturar: " << endl;
        cin >> FAC1.multpro;

        // Busca el producto en el inventario y lo agrega a la factura si coincide con el ID ingresado
        while (getline(INV, line1)) {
            stringstream ss(line1);
            ss >> COMP1.id;
            ss.ignore();
            getline(ss, COMP1.productocomp, ',');
            ss >> COMP1.preciocomp;
            ss.ignore();
            ss >> COMP1.cantidad;
            if (COMP1.id == idcomp) {
                FAC1.productos.push_back(COMP1.productocomp);
                FAC1.preciopro.push_back(COMP1.preciocomp);
                FAC1.id.push_back(idcomp);
                FAC1.cantidad.push_back(FAC1.multpro);
                FAC1.totalsinIVA += COMP1.preciocomp * FAC1.multpro;
                FAC1.TOTALIVA += 0.15 * FAC1.totalsinIVA;
                FAC1.TOTALIVA2 += FAC1.TOTALIVA + FAC1.totalsinIVA;
            }
        }

        // Pregunta al usuario si desea ingresar otro producto
        cout << "Desea ingresar otro producto? (S/N): ";
        cin >> opc;
        cin.ignore();

    } while (opc == 'S' || opc == 's');

    INV.close(); // Cierra el archivo de inventario después de usarlo

    reloj(); // Llama a la función reloj para capturar fecha y hora actual

    // Captura el tipo de cancelacion de la factura
    cout << "Digite el tipo de cancelacion:" << endl;
    getline(cin, FAC1.cancelacion);

    // Abre el archivo de facturas para escritura, agrega detalles de la factura y cierra el archivo al finalizar
    ofstream out("Basefacs.txt", ios::app);
    if (!out) {
        cerr << "Error al abrir el archivo para escritura." << endl;
        return;
    }

    out << FAC1.nombrecl << ',' << FAC1.nombrevndr << ',' << FAC1.totalsinIVA << ',' << FAC1.TOTALIVA << ',' << FAC1.TOTALIVA2 << ',' << FAC1.celular << ',' << FAC1.cancelacion << ',' << dia << ',' << mes << ',' << año << '\n';
    for (size_t i = 0; i < FAC1.productos.size(); ++i) {
        out << FAC1.productos[i] << ',' << FAC1.preciopro[i] << ',' << FAC1.cantidad[i] << '\n';
    }
    out << "Final" << '\n'; // Marca el final de la factura en el archivo
    out.close(); // Cierra el archivo de facturas

    menu(); // Retorna al menú principal después de completar la factura
}

void verfac() {
    ifstream in("Basefacs.txt"); // Abre el archivo de facturas para lectura
    if (!in) { // Verifica si el archivo se abrio correctamente
        cerr << "No se pudo abrir el archivo para lectura." << endl;
        return;
    }

    Factura FAC1; // Objeto para almacenar detalles de la factura
    fecha FECH1; // Objeto para almacenar la fecha de la factura
    string nombre; // Nombre del cliente para buscar la factura
    bool encontrado = false; // Indicador si se encontró la factura

    cout << "Digite el nombre del cliente para encontrar la factura:" << endl;
    cin.ignore();
    getline(cin, nombre); // Lee el nombre del cliente

    string line;
    while (getline(in, line)) {
        stringstream ss(line);
        getline(ss, FAC1.nombrecl, ','); // Lee el nombre del cliente de la linea
        if (FAC1.nombrecl == nombre) { // Compara con el nombre buscado
            encontrado = true;
            getline(ss, FAC1.nombrevndr, ','); // Lee el nombre del vendedor
            ss >> FAC1.totalsinIVA; // Lee el total sin IVA
            ss.ignore(); // Ignora la coma
            ss >> FAC1.TOTALIVA; // Lee el IVA
            ss.ignore();
            ss >> FAC1.TOTALIVA2; // Lee el total con IVA
            ss.ignore();
            ss >> FAC1.celular; // Lee el número de celular
            ss.ignore();
            getline(ss, FAC1.cancelacion, ','); // Lee el tipo de cancelación
            ss >> FECH1.dias; // Lee el dia de la fecha
            ss.ignore();
            ss >> FECH1.mes; // Lee el mes de la fecha
            ss.ignore();
            ss >> FECH1.año; // Lee el año de la fecha
    
            // Muestra los detalles de la factura y los productos
            cout << "Nombre del Cliente: " << FAC1.nombrecl << endl;
            cout << "Nombre del Vendedor: " << FAC1.nombrevndr << endl;
            cout << "Total sin IVA: " << FAC1.totalsinIVA << endl;
            cout << "IVA: " << FAC1.TOTALIVA << endl;
            cout << "Total: " << FAC1.TOTALIVA2 << endl;
            cout << "Celular: " << FAC1.celular << endl;
            cout << "Tipo de cancelacion: " << FAC1.cancelacion << endl;
            cout << "Productos:" << endl;

            FAC1.productos.clear(); // Limpia el vector de productos
            FAC1.preciopro.clear(); // Limpia el vector de precios de productos

            // Lee los productos de la factura
            while (getline(in, line) && line != "Final"){
                stringstream ss(line);
                string producto;
                int precio;
                int cantidad;
                getline(ss, producto, ','); // Lee el nombre del producto
                ss >> precio; // Lee el precio del producto
                ss.ignore();
                ss >> cantidad; // Lee la cantidad del producto
            
                // Muestra los detalles de cada producto
                cout << "Producto: " << producto << " - Precio: " << precio << " - Cantidad: " << cantidad << endl;
            }
            // Muestra la fecha de la factura
            cout << "Fecha: " << FECH1.dias << ":" << FECH1.mes << ":" << FECH1.año;
            cout << "\n------------------------------------" << endl;
        }
    }
    system ("pause"); // Pausa la ejecución para que el usuario pueda ver la información

    cout << "\n\n\n\n\n\n\n\n\n\n\n";

    // Si no se encontró ninguna factura para el cliente, muestra un mensaje
    if (!encontrado) {
        cout << "No se encontro ninguna factura para el cliente: " << nombre << endl;
        system ("pause");
    }

    in.close(); // Cierra el archivo de facturas
}

void eliminarfac() {
    ifstream in("Basefacs.txt"); // Abre el archivo de facturas para lectura
    if (!in) { // Verifica si el archivo se abrió correctamente
        cerr << "No se pudo abrir el archivo para lectura." << endl;
        return;
    }

    ofstream temp("Tempfacs.txt"); // Abre un archivo temporal para escribir las facturas
    if (!temp) { // Verifica si el archivo temporal se abrió correctamente
        cerr << "No se pudo abrir el archivo temporal para escritura." << endl;
        in.close();
        return;
    }

    Factura FAC1; // Objeto para almacenar detalles de la factura
    string nombre; // Nombre del cliente para buscar la factura
    bool encontrado = false; // Indicador si se encontró la factura

    cout << "Digite el nombre del cliente para eliminar la factura:" << endl;
    cin.ignore();
    getline(cin, nombre); // Lee el nombre del cliente

    string line;
    while (getline(in, line)) {
        stringstream ss(line);
        getline(ss, FAC1.nombrecl, ','); // Lee el nombre del cliente de la línea
        getline(ss, FAC1.nombrevndr, ','); // Lee el nombre del vendedor
        ss >> FAC1.totalsinIVA; // Lee el total sin IVA

        if (FAC1.nombrecl == nombre) { // Compara con el nombre buscado
            encontrado = true;
            // Saltar líneas de productos y no escribir en el archivo temporal
            while (getline(in, line) && line != "Final") {
                // No hace nada, salta las líneas de productos
            }
        } else {
            // Escribe la factura en el archivo temporal
            temp << FAC1.nombrecl << ',' << FAC1.nombrevndr << ',' << FAC1.totalsinIVA << '\n';

            // Escribe los productos de la factura en el archivo temporal
            while (getline(in, line) && line != "Final") {
                temp << line << '\n';
            }
            temp << "Final" << '\n'; // Marca el final de la factura en el archivo temporal
        }
    }
    // Si no se encontró ninguna factura para el cliente, muestra un mensaje
    if (!encontrado) {
        cout << "No se encontro ninguna factura para el cliente: " << nombre << endl;
    } else {
        cout << "Factura eliminada exitosamente." << endl;
    }

    in.close(); // Cierra el archivo de facturas
    temp.close(); // Cierra el archivo temporal

    // Reemplaza el archivo original con el archivo temporal
    remove("Basefacs.txt");
    rename("Tempfacs.txt", "Basefacs.txt");
}

void resumenes() {
    ifstream res("Basefacs.txt"); // Abre el archivo de facturas para lectura
    
    if (!res) { // Verifica si el archivo se abrió correctamente
        cout << "La base de datos de facturas no se pudo abrir" << endl;
        return;
    }

    resumenesdats resumen; // almacenar datos del resumen

    fecha FECHCOMP; // almacenar la fecha de inicio del resumen
    fecha FECHCOMPmax; // almacenar la fecha máxima del resumen

    // Solicita al usuario las fechas para filtrar el resumen
    cout << "Digite las fechas que desea ver el resumen (dia/mes/año):" << endl;
    cin >> FECHCOMP.dias >> FECHCOMP.mes >> FECHCOMP.año;

    cout << "Digite la fecha maxima que desea ver el resumen (dia/mes/año):" << endl;
    cin >> FECHCOMPmax.dias >> FECHCOMPmax.mes >> FECHCOMPmax.año;

    Factura FAC1; // almacenar detalles de la factura
    fecha FECH1; // almacenar la fecha de cada factura
    string line; // variable para almacenar cada línea del archivo de facturas

    while (getline(res, line)) { // Lee cada línea del archivo de facturas
        stringstream ss(line); // Crea un stringstream para analizar la línea
        
        // Lee los datos principales de la factura
        getline(ss, FAC1.nombrecl, ',');
        getline(ss, FAC1.nombrevndr, ',');
        ss >> FAC1.totalsinIVA;
        ss.ignore(); // Ignora la coma
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

        // Verifica si la factura está dentro del rango de fechas especificado por el usuario
        if ((FECH1.año > FECHCOMP.año || (FECH1.año == FECHCOMP.año && FECH1.mes > FECHCOMP.mes) || (FECH1.año == FECHCOMP.año && FECH1.mes == FECHCOMP.mes && FECH1.dias >= FECHCOMP.dias)) &&
            (FECH1.año < FECHCOMPmax.año || (FECH1.año == FECHCOMPmax.año && FECH1.mes < FECHCOMPmax.mes) || (FECH1.año == FECHCOMPmax.año && FECH1.mes == FECHCOMPmax.mes && FECH1.dias <= FECHCOMPmax.dias))) {

            // Muestra los detalles de la factura
            cout << "Nombre del Cliente: " << FAC1.nombrecl << endl;
            cout << "Nombre del Vendedor: " << FAC1.nombrevndr << endl;
            cout << "Total sin IVA: " << FAC1.totalsinIVA << endl;
            cout << "IVA: " << FAC1.TOTALIVA << endl;
            cout << "Total: " << FAC1.TOTALIVA2 << endl;
            cout << "Celular: " << FAC1.celular << endl;
            cout << "Tipo de cancelacion: " << FAC1.cancelacion << endl;
            cout << "Productos:" << endl;

            FAC1.productos.clear(); // Limpia el vector de productos
            FAC1.preciopro.clear(); // Limpia el vector de precios de productos

            resumen.totalventas += FAC1.TOTALIVA2; // Acumula la cantidad de total con IVA 
            // Lee y muestra los productos vendidos en la factura
            while (getline(res, line) && line != "Final") {
                stringstream ss(line);
                string producto;
                int precio;
                int cantidad;
                getline(ss, producto, ','); // Lee el nombre del producto
                ss >> precio; // Lee el precio del producto
                ss.ignore();
                ss >> cantidad; // Lee la cantidad del producto
                resumen.productosvendidoscant += cantidad; // Acumula la cantidad de productos vendidos
                resumen.productosvendidos.push_back(producto); // Guarda los nombres de todos los productos vendidos
                // Muestra los detalles de cada producto vendido
                cout << "Producto: " << producto << " - Precio: " << precio << " - Cantidad: " << cantidad << endl;
            }

            // Muestra la fecha de la factura
            cout << "Fecha: " << FECH1.dias << ":" << FECH1.mes << ":" << FECH1.año << endl;
            cout << "------------------------------------" << endl;
        }

        
    }

    cout << "Resumen:" << endl;

    cout << "Total de venta entre las fechas: " << resumen.totalventas << endl;
        
    cout << "Cantidad de productos vendidos: " << resumen.productosvendidoscant << endl;

    cout << "Productos vendidos: " << endl;
    for (size_t i = 0; i < resumen.productosvendidos.size(); i++){
            cout << resumen.productosvendidos[i] << endl;
        }

    system("pause"); // Pausa para que el usuario pueda ver la información
    res.close(); // Cierra el archivo de facturas
    menu(); // Regresa al menú principal
}

void menuinv() {
    system("cls");  // Limpiar la consola
    string line;
    Productosid idmenu;

    // Leer el archivo de inventario y mostrar productos bajos en stock
    ifstream in("Basedatosinv.txt");
    while (getline(in, line)) {
        stringstream ss(line);
        ss >> idmenu.ID;
        ss.ignore();
        getline(ss, idmenu.nombre, ',');
        ss >> idmenu.PU;
        ss.ignore();
        ss >> idmenu.Cantidad;

        if (idmenu.Cantidad < 5) {
            cout << "Producto bajo en stock: " << idmenu.nombre << endl;
        }
    }

    in.close(); // Cerrar archivo de inventario

    char opc;
    do {
        // Mostrar opciones del menú y leer la selección del usuario
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
                break; // Funcionalidad no implementada en este ejemplo
            default:
                cout << "Opcion no valida. Intentalo de nuevo.\n";
                break;
        }
    } while (opc != '4'); // Salir del menú cuando se selecciona la opción 4
}

// Función que muestra el menú de añadir productos
void añadirmenu() {
    system("cls");  // Limpiar la consola
    char opc;
    do {
        // Mostrar opciones del menú y leer la selección del usuario
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
                return menu();  // Volver al menú principal
            default:
                cout << "Opcion no valida. Intentalo de nuevo.\n";
                break;
        }
    } while (opc != '4'); // Salir del menú cuando se selecciona la opción 4
}

// Función para añadir productos existentes al inventario
void añadiraexistente() {
    ifstream in("Basedatosinv.txt"); // Abrir en modo de lectura la basededatos
    ofstream temp("Basedatosinvtemp.txt"); // Abre un archivo de escritura temporal

    Productosid Productosid;

    string idproducto;
    int ncantidad;
    string line;
    bool nuevosi = false;

    // Mostrar los productos actuales en inventario
    while (getline(in, line)) {
        cout << line << endl;
    };

    in.clear();
    in.seekg(0, ios::beg); // Reiniciar la lectura del archivo al inicio

    cin.ignore();
    cout << "Digite el producto que desea añadir: " << endl;
    getline(cin, idproducto);

    cout << "Cantidad: " << endl;
    cin >> ncantidad;

    // Procesar cada línea del archivo de inventario
    while (getline(in, line)) {
        stringstream ss(line);
        getline(ss, Productosid.nombre, ',');
        ss >> Productosid.PU;
        ss.ignore();
        ss >> Productosid.Cantidad;

        if (Productosid.nombre == idproducto) {
            nuevosi = true;
            temp << Productosid.nombre << ',' << Productosid.PU << ',' << Productosid.Cantidad + ncantidad << endl;
        } else {
            temp << Productosid.nombre << ',' << Productosid.PU << ',' << Productosid.Cantidad << endl;
        }
    }

    //Si el producto no se encontro se devuelve al menu
    if (!nuevosi) {
        cout << "El producto no fue encontrado!" << endl;
        system("pause");
        menu();
        // Si es true avisa que se actualizo
    } else {
        cout << "Cantidad en inventario actualizado correctamente!" << endl;
    }

    in.close();
    temp.close();

    remove("Basedatosinv.txt");                // Eliminar el archivo original
    rename("Basedatosinvtemp.txt", "Basedatosinv.txt");  // Renombrar el archivo temporal a original

    menu();  // Volver al menú principal
}

// Función para añadir nuevos productos al inventario
void añadirinvnuevo() {
    system("cls");  // Limpiar la consola

    Productos Producto1;
    char opc;
    string nombre;
    int PU;
    int cantidad;
    int ID;

    do {
        cin.ignore(); // Ignorar caracteres en el buffer

        cout << "Digite el ID del producto:";
        cin >> ID;

        cin.ignore(); // Ignorar caracteres en el buffer
        cout << "Escriba el producto a añadir: ";
        getline(cin, nombre);

        cout << "Digita el precio unitario: ";
        cin >> PU;

        cout << "Digita la cantidad en inventario: ";
        cin >> cantidad;

        cout << "Desea agregar otro producto? (S/N)";
        cin >> opc;

        // Almacenar los datos del producto en vectores dentro de la estructura Productos
        Producto1.nombre.push_back(nombre);
        Producto1.PU.push_back(PU);
        Producto1.Cantidad.push_back(cantidad);
        Producto1.ID.push_back(ID);
    } while (opc == 'S' || opc == 's');

    ofstream out("Basedatosinv.txt", ios::app); // Abrir el archivo de inventario en modo de añadir al final
    if (!out) {
        cout << "El archivo no se pudo abrir";
    }

    // Escribir cada producto añadido al archivo de inventario
    for (size_t i = 0; i < Producto1.nombre.size(); i++) {
        out << Producto1.ID[i] << ',' << Producto1.nombre[i] << ',' << Producto1.PU[i] << ',' << Producto1.Cantidad[i] << "\n";
    }

    out.close(); // Cerrar archivo de inventario
    menu();      // Volver al menú principal
}

// Función para ver todos los productos en inventario
void verinv() {
    system("cls");  // Limpiar la consola
    int PU;
    string Nombre;
    int cantidad;
    int id;

    ifstream in("Basedatosinv.txt");

    string line;
    // Leer cada linea del archivo de inventario y mostrar la información de cada producto
    while (getline(in, line)) {
        stringstream ss(line);
        ss >> id;
        ss.ignore();
        getline(ss, Nombre, ',');
        ss >> PU;
        ss.ignore();
        ss >> cantidad;
        cout << "ID:" << id << " ----- " << "Producto: " << Nombre << " ----- " << "Precio: " << PU << " ----- " << "Cantidad:" << cantidad << endl;
    }

    in.close(); // Cerrar archivo de inventario
    system("pause"); // Pausar la consola
    menu();      // Volver al menú principal
}
