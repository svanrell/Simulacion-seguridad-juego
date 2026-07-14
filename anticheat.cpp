#include <iostream>
#include <string>
#include <windows.h>

// Generamos una clave secreta (puede ser cualquier numero, incluso aleatorio al inicio)
const int CLAVE_SECRETA = 0x5A3C; 

struct HeroeSeguro {
    std::string nombre;
    int saludCifrada; 
    
    // Método para leer la salud real descifrandola al vuelo
    int obtenerSalud() {
        return saludCifrada ^ CLAVE_SECRETA;
    }

    // Método para guardar la salud aplicandole el candado
    void setSalud(int nuevaSalud) {
        saludCifrada = nuevaSalud ^ CLAVE_SECRETA;
    }
};

int main() {
    DWORD processId = GetCurrentProcessId();
    std::cout << "PID: " << processId << std::endl;

    HeroeSeguro* jugadorLocal = new HeroeSeguro;
    jugadorLocal->nombre = "Enrique";
    
    // En lugar de poner = 100 directamente
    jugadorLocal->setSalud(100);

    std::cout << "Direccion de la SALUD CIFRADA: " << &(jugadorLocal->saludCifrada) << std::endl;

    while (jugadorLocal->obtenerSalud() > 0) {
        std::cout << "\n[" << jugadorLocal->nombre << "] Salud mostrada en HUD: " << jugadorLocal->obtenerSalud() << std::endl;
        std::cout << "[DEBUG] Lo que realmente hay en la RAM: " << jugadorLocal->saludCifrada << std::endl;
        
        std::cout << "Presiona ENTER para simular dano...";
        std::cin.ignore(); 

        int saludActual = jugadorLocal->obtenerSalud();
        jugadorLocal->setSalud(saludActual - 45); 
    }

    delete jugadorLocal;
    jugadorLocal = nullptr;
    
    return 0;
}