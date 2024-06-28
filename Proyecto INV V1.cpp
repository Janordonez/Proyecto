#include <iostream>
#include <sstream>
#include <fstream>
#include <vector>
#include <windows.h>  // Para usar funciones de la consola en Windows
#include <string>
#include <cstdio>

using namespace std;



// Función para posicionar el cursor en la consola
void gotoxy(int x, int y) {
    // Obtener el handle de la consola
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    
    // Definir la estructura COORD con la posición
    COORD pos;
    pos.X = x;
    pos.Y = y;
    
    // Mover el cursor a la posición definida
    SetConsoleCursorPosition(hConsole, pos);
}

// Declaraciones de funciones
void menu();


// Función principal
int main() {
    system("cls");  // Limpiar la consola
    menu();         // Llamar al menú principal
    return 0;
}

// Función que muestra el menú principal
