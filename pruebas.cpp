#include <cstdint>
#include <iostream>
#include <vector>

// =========================================================================
// OPCIÓN RECOMENDADA: Pasar por REFERENCIA CONSTANTE (const Tipo&)
// =========================================================================
// El símbolo '&' aquí significa que 'info' es una REFERENCIA (un alias)
// de la variable original. No se crea una copia del vector en memoria.
// 'const' garantiza que no podemos modificar el vector original por accidente.
void mostrarInfoReferencia(const std::vector<int>& info) {
    // Como 'info' es una referencia, se comporta exactamente igual
    // que el vector original. Podemos recorrerlo directamente:
    for (int dato : info) {
        std::cout << dato << " ";
    }
    std::cout << "\nDireccion en memoria del vector (usando &info): " << &info << std::endl;
}

// =========================================================================
// OPCIÓN ALTERNATIVA: Pasar por PUNTERO (Tipo*)
// =========================================================================
// El símbolo '*' aquí significa que 'info' es un PUNTERO a un vector.
// Guarda la dirección de memoria de un vector, no el vector en sí.
void mostrarInfoPuntero(const std::vector<int>* info) {
    // Como 'info' es un puntero (una dirección de memoria),
    // no podemos recorrerlo directamente. Tenemos que DESREFERENCIARLO
    // usando el operador '*' antes de su nombre para obtener el vector real:
    for (int dato : *info) {
        std::cout << dato << " ";
    }
    // 'info' ya guarda la dirección de memoria, no hace falta usar '&' aquí:
    std::cout << "\nDireccion en memoria del vector (valor de info): " << info << std::endl;
}

int main() {
    std::vector<int> valores = {10, 20, 30};

    std::cout << "--- LLAMADA POR REFERENCIA ---" << std::endl;
    // Pasamos 'valores' directamente. Al usar referencias, C++ se encarga
    // de pasar la dirección de memoria por detrás de escena sin cambiar la sintaxis.
    mostrarInfoReferencia(valores);

    std::cout << "\n--- LLAMADA POR PUNTERO ---" << std::endl;
    // Como la función espera un puntero (std::vector<int>*),
    // tenemos que pasarle explícitamente la dirección usando el operador '&':
    mostrarInfoPuntero(&valores);

    return 0;
}

/*
  RESUMEN DE SÍMBOLOS EN C++:
  
  1. EN DECLARACIONES (Definición de tipos):
     - int* p;   -> El '*' declara que 'p' es un puntero (guarda direcciones de memoria).
     - int& ref; -> El '&' declara que 'ref' es una referencia (un alias de otra variable).

  2. EN EXPRESIONES (Instrucciones ejecutables):
     - &variable; -> El '&' obtiene la dirección de memoria de esa variable.
     - *puntero;  -> El '*' va a la dirección guardada en el puntero y saca su valor (desreferencia).
*/