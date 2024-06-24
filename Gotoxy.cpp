#include <iostream>
#include <windows.h>  // Necesario para SetConsoleCursorPosition y otras funciones de la consola

// Definir la función gotoxy
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

int main() {
    // Mover el cursor a la posición (10, 5) y mostrar un mensaje
    gotoxy(10, 5);
    std::cout << "Hola desde gotoxy" << std::endl;
    
    // Mover el cursor a otra posición y mostrar otro mensaje
    gotoxy(20, 10);
    std::cout << "Otro mensaje en una posición diferente" << std::endl;
    
    return 0;
}
