#include <iostream>
#include <string>

// Definimos una estructura simple
struct Persona {
    int id;
    std::string nombre;
};

int main() {
    // Creamos un puntero a la estructura Persona
    Persona *pPersona;

    // Asignamos memoria dinámica para el struct Persona
    pPersona = new Persona;

    // Leer datos del usuario
    std::cout << "Ingrese el ID: ";
    std::cin >> pPersona->id;

    std::cout << "Ingrese el nombre: ";
    std::cin.ignore(); // Para ignorar el salto de línea que queda en el buffer
    std::getline(std::cin, pPersona->nombre);

    // Mostramos los valores para comprobar que se ha hecho correctamente
    std::cout << "ID: " << pPersona->id << std::endl;
    std::cout << "Nombre: " << pPersona->nombre << std::endl;

    // Liberamos la memoria cuando ya no la necesitamos
    delete pPersona;

    return 0;
}
