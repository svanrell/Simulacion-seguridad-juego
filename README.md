# 🎮 Simulador de Seguridad y Modificación de Memoria en C++

¡Bienvenido al proyecto **Simulación de Seguridad en Juego**! Este repositorio es un laboratorio educativo diseñado para entender los fundamentos de la manipulación de memoria de procesos en Windows y cómo se implementan los sistemas básicos de defensa (Anticheat).

El proyecto se compone de tres módulos principales (juego vulnerable, inyector/atacante y juego protegido) que interactúan entre sí, además de un archivo de pruebas para repasar conceptos clave de C++.

---

## 📁 Estructura del Proyecto

El repositorio cuenta con los siguientes archivos fuente:

*   **`gameTarget.cpp`**: Un juego simple de consola. Al iniciarse, muestra su ID de proceso (PID) y la dirección de memoria exacta en la que se almacena la vida del jugador. Es vulnerable a modificaciones externas de memoria.
*   **`attacker.cpp`**: Una herramienta de inyección de memoria (cheat). Permite al usuario introducir un PID y una dirección de memoria en hexadecimal para sobrescribir directamente el valor de la vida del jugador con `999`.
*   **`anticheat.cpp`**: Una versión mejorada y segura del juego. Protege la salud del jugador cifrándola al vuelo en la memoria RAM mediante un algoritmo de máscara XOR (`CLAVE_SECRETA`). Si un atacante intenta sobrescribir la vida, el juego detectará un valor inválido o descifrado incorrectamente y reaccionará de manera segura.
*   **`pruebas.cpp`**: Una guía práctica explicativa sobre el uso de **Punteros (`*`)** y **Referencias (`&`)** en C++ con ejemplos detallados y esquemas conceptuales.

---

## ⚙️ Cómo Funciona la Simulación

### Escenario 1: Ataque Exitoso (Sin Protección)
1. Ejecutas `gameTarget.cpp`. El juego mostrará algo como esto:
   ```text
   JUEGO INICIADO
   PID DEL PROCESO: 12345
   DIRECCION DEL JUGADOR: 0x9f5c4ffd20
   DIRECCION DE LA SALUD: 0x9f5c4ffd28
   ```
2. Ejecutas `attacker.cpp` en otra consola.
3. Te pedirá el PID (`12345`) y la dirección de la salud (`9f5c4ffd28`).
4. El atacante escribirá directamente en la memoria del juego. Al presionar ENTER en el juego, verás que la salud ha cambiado mágicamente a `999`.

### Escenario 2: Intento de Ataque Fallido (Con Anticheat)
1. Ejecutas `anticheat.cpp`. Mostrará la dirección de la vida, pero indicará que está cifrada:
   ```text
   PID: 12345
   Direccion de la SALUD CIFRADA: 0x9f5c4ffd28
   [DEBUG] Lo que realmente hay en la RAM: 23149 (vida real de 100 XOR clave)
   ```
2. Si intentas usar `attacker.cpp` en esa dirección para escribir `999`, el juego descifrará ese `999` usando la clave XOR y obtendrá un valor absurdo o negativo, haciendo que el jugador sea eliminado o que el juego tome medidas defensivas inmediatas, demostrando cómo funciona la ofuscación de memoria RAM.

---

## 🛠️ Conceptos de Programación y APIs de Windows Demostrados

El código contiene comentarios explicativos muy detallados de las siguientes tecnologías:
*   **`GetCurrentProcessId`**: Obtiene el identificador único del proceso ejecutable.
*   **`OpenProcess`**: Solicita permisos al sistema operativo para abrir y manipular otro proceso.
*   **`WriteProcessMemory`**: Escribe datos directamente en el espacio de memoria RAM reservado por otro proceso.
*   **Punteros y Referencias**: Entender cómo se pasa la información por dirección de memoria física (`uintptr_t`, `LPVOID`).
*   **Ofuscación XOR**: Técnica criptográfica ligera para proteger variables críticas en memoria frente a escaneos simples (como Cheat Engine).

---

## 🚀 Compilación y Ejecución

Para compilar los archivos utilizando cualquier compilador de C++ (por ejemplo, GCC/g++ en Windows a través de MinGW):

```bash
# Compilar el juego vulnerable
g++ gameTarget.cpp -o gameTarget.exe

# Compilar el inyector/atacante
g++ attacker.cpp -o attacker.exe

# Compilar el juego protegido con anticheat
g++ anticheat.cpp -o anticheat.exe

# Compilar el archivo de pruebas conceptuales
g++ pruebas.cpp -o pruebas.exe
```

> ⚠️ **Nota de Seguridad**: Para que `attacker.exe` pueda abrir y modificar la memoria de otro proceso con `OpenProcess`, es posible que necesites ejecutar la consola como **Administrador** si la configuración de seguridad de tu sistema Windows es estricta.

---

## 📚 Repaso rápido de C++ (`pruebas.cpp`)

Si tienes dudas de cómo interactúa el atacante con las direcciones de memoria, puedes leer o compilar `pruebas.cpp`. Explica de forma visual la diferencia entre:
*   **`int* p`** (Declarar puntero) vs **`*p`** (Acceder al valor al que apunta).
*   **`int& ref`** (Declarar alias/referencia) vs **`&var`** (Obtener dirección de memoria de una variable).
