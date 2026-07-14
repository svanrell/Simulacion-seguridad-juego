# Simulacion de seguridad en juegos con C++

Este repositorio lo he creado para ir guardando y ordenando lo que voy aprendiendo sobre cómo funciona la memoria de los procesos en Windows, cómo se modifica (hacer trampas) y cómo se puede proteger (anticheat básico).

Es un laboratorio de pruebas propio con tres programas sencillos que interactúan entre sí.

## Qué hay en este proyecto

*   **gameTarget.cpp**: Es la simulación de un juego de consola muy básico. Simplemente crea un jugador con vida y escudo, y te va mostrando en pantalla el PID (Process ID) y la dirección de memoria exacta en la RAM de la variable de la vida. Esto hace que sea muy fácil encontrarla para atacarla.
*   **attacker.cpp**: Este es el programa "atacante" o inyector. Le pides al usuario el PID del juego anterior y la dirección de memoria de la vida, y escribe directamente un nuevo valor (en este caso, 999 de vida) usando funciones de Windows.
*   **anticheat.cpp**: Es la versión protegida del juego. Para evitar que un programa como el inyector te cambie la vida tan fácil, aquí la vida está cifrada en memoria RAM usando una máscara XOR simple. Si el atacante intenta cambiar el valor directamente, al descifrarse saldrá un número corrupto y el programa se cerrará o detectará el cambio.

*Nota: Tenía también un archivo pruebas.cpp para repasar punteros y referencias en C++, pero lo he quitado del repositorio y lo he dejado solo en local para no ensuciar.*

## Cómo probar la simulación

### Paso 1: El ataque sin protección
1. Compila y ejecuta `gameTarget.cpp`. Apunta el PID y la dirección de memoria que te muestra en consola.
2. Compila y ejecuta `attacker.cpp`.
3. Introduce el PID y la dirección cuando te lo pida. Verás cómo la vida del juego cambia automáticamente al valor que ha inyectado el atacante.

### Paso 2: La defensa con el anticheat
1. Ejecuta `anticheat.cpp`.
2. Verás que en la memoria RAM el valor que hay guardado no es 100, sino un número raro porque está cifrado.
3. Si intentas usar `attacker.cpp` en esta dirección de memoria para ponerle 999, el anticheat descifrará ese 999 con la clave XOR y dará un resultado totalmente loco (probablemente negativo o muy bajo), haciendo que el jugador muera o que el programa se dé cuenta de que ha sido modificado.

## Conceptos que estoy practicando aquí

*   **Punteros y memoria**: Direcciones de memoria física y punteros (`uintptr_t`, `LPVOID`).
*   **APIs de Windows**: Funciones del sistema como `OpenProcess` para conectarse a un proceso y `WriteProcessMemory` para escribir en su espacio de memoria.
*   **Ofuscación básica**: Cifrado XOR para proteger datos críticos en RAM frente a escaneos sencillos.

## Cómo compilar

Uso g++ para compilar los ejecutables desde la terminal de Windows:

```bash
g++ gameTarget.cpp -o gameTarget.exe
g++ attacker.cpp -o attacker.exe
g++ anticheat.cpp -o anticheat.exe
```

*Nota: Para que el atacante funcione correctamente, a veces hay que abrir la consola como administrador para que Windows le permita leer/escribir en la memoria de otros procesos.*
