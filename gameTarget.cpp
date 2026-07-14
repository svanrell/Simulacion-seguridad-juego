#include <iostream>
#include <minwindef.h>
#include <ostream>
#include <processthreadsapi.h>
#include <string>
#include <windows.h>

struct Fighter {
    std::string name;
    int health;
    int shield;
};

int main() {
    DWORD processID = GetCurrentProcessId();

    std::cout << "JUEGO INICIADO" << std::endl;
    std::cout << "PID DEL PROCESO:" << processID << std::endl;

    Fighter* shumi = new Fighter;

    shumi->name = "Enrique";
    shumi->health = 100;
    shumi->shield = 50;

    std::cout << "\nDIRECCION DEL JUGADOR:" << shumi << std::endl;
    std::cout << "\nDIRRECION DE LA SALUD:" << &shumi->health << std::endl;

    while (shumi->health > 0) {
        std::cout << "\nJUGADOR:" << shumi->name << "SALUD:" << shumi->health << std::endl;
        std::cout << "\nPRESIONA ENTER PARA SIMULAR HERIDAS..." << std::endl;

        std::cin.ignore();

        shumi->health -= 15;
    }

    std::cout << "\nJUGADOR:" << shumi->name << "ELIMINADO. FIN DE LA PARTIDA" << std::endl;

    // liberamos la memoria sin dejar rastro
    delete shumi;
    shumi = nullptr;

    return 0;
}