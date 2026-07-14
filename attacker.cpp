#include <iostream>
#include <windows.h>

int main() {
  DWORD pid;
  uintptr_t direccionSalud;
  int nuevaSalud = 999;

  std::cout << "INJECTOR DE MEMORIA" << std::endl;
  std::cout << "INTRODUCE EL PID DEL JUEGO" << std::endl;
  std::cin >> pid;

  std::cout << "INTRODUCE LA DIRRECION DE MEMORIA DE LA SALUD (SIN el 0x, ej. 1e433eb0b40)" << std::endl;
  std::cin >> std::hex >> direccionSalud;

  HANDLE hProceso = OpenProcess(PROCESS_ALL_ACCESS, FALSE, pid);

  if (!hProceso) {
    std::cout << "NO SE HA ENCONTRADO EL PROCESO" << std::endl;
    return 1;
  } else {
    std::cout << "SE HA CONECTADO CORRECTAMENTE AL PROCESO" << std::endl;

    BOOL exito = WriteProcessMemory(hProceso, (LPVOID)direccionSalud,
                                    &nuevaSalud, sizeof(nuevaSalud), NULL);

    if (!exito) {
      std::cout << "NO SE HA PODIDO MODIFICAR LA MEMORIA, EL ANTICHEAT ESTA ACTIVO" << std::endl;
      return 1;
    } else {
      std::cout << "SALUD MODIFICADA A " << nuevaSalud << "CON EXITO" << std::endl;
    }
  }

  CloseHandle(hProceso);

  return 0;
}