#include <iostream>
#include <windows.h>


int main() {
  // DWORD (Double Word) es un tipo de dato definido por Windows. Representa un entero sin signo de 32 bits.
  // Se usa comunmente en la API de Windows para almacenar identificadores de procesos (PIDs).
  DWORD pid;

  // uintptr_t es un tipo de entero especial en C++ capaz de almacenar una direccion de memoria (puntero)
  // de forma segura, adaptándose al tamaño de palabra del sistema (32 bits o 64 bits).
  uintptr_t direccionSalud;
  int nuevaSalud = 999;

  std::cout << "INJECTOR DE MEMORIA" << std::endl;
  std::cout << "INTRODUCE EL PID DEL JUEGO" << std::endl;
  std::cin >> pid;

  // Usamos std::hex para indicarle a std::cin que lea la entrada del usuario directamente en base 16 (hexadecimal)
  std::cout << "INTRODUCE LA DIRRECION DE MEMORIA DE LA SALUD (SIN el 0x, ej. "
               "1e433eb0b40)"
            << std::endl;
  std::cin >> std::hex >> direccionSalud;

  // HANDLE (Manejador) es un tipo de dato opaco que usa Windows para referenciar y administrar
  // recursos del sistema operativo (como procesos, hilos, archivos, etc.).
  //
  // OpenProcess es una funcion de la API de Windows que abre un objeto de proceso local existente.
  // Parámetros:
  //   1. PROCESS_ALL_ACCESS: Solicita todos los derechos de acceso posibles para el proceso.
  //   2. FALSE: Indica que los procesos creados por este proceso no heredaran el handle.
  //   3. pid: El identificador del proceso que queremos abrir.
  HANDLE hProceso = OpenProcess(PROCESS_ALL_ACCESS, FALSE, pid);

  // Si OpenProcess falla, devuelve NULL (o 0). Esto ocurre si el PID no existe o no tenemos permisos de administrador.
  if (!hProceso) {
    std::cout << "NO SE HA ENCONTRADO EL PROCESO" << std::endl;
    return 1;
  } else {
    std::cout << "SE HA CONECTADO CORRECTAMENTE AL PROCESO" << std::endl;

    // WriteProcessMemory escribe datos en una region de memoria dentro del espacio de direcciones de un proceso.
    // Parámetros:
    //   1. hProceso: El manejador (HANDLE) del proceso cuya memoria queremos modificar.
    //   2. (LPVOID)direccionSalud: Direccion de memoria destino en el proceso objetivo. Se castea a LPVOID (puntero generico de Windows).
    //   3. &nuevaSalud: Puntero al bufer local de nuestro programa que contiene los datos que queremos escribir (en este caso, el valor 999).
    //   4. sizeof(nuevaSalud): Cantidad de bytes a escribir (para un entero de 32 bits, son 4 bytes).
    //   5. NULL: Un puntero opcional para recibir el numero de bytes escritos. Al pasar NULL, ignoramos este valor.
    BOOL exito = WriteProcessMemory(hProceso, (LPVOID)direccionSalud,
                                    &nuevaSalud, sizeof(nuevaSalud), NULL);

    if (!exito) {
      std::cout << "EL ANTICHEAT NOS HA FOLLADO" << std::endl;
      return 1;
    } else {
      std::cout << "SALUD MODIFICADA A " << nuevaSalud << "CON EXITO"
                << std::endl;
    }
  }

  // Es fundamental cerrar siempre los handles abiertos una vez terminamos de usarlos.
  // CloseHandle libera la referencia al proceso en el sistema operativo y evita "fugas de recursos" (handle leaks).
  CloseHandle(hProceso);

  return 0;
}