#include "../include/tools.h"

int main(int argc, char* argv[]) {
  std::string archivoConfig = "";
  std::string opcionTraza = "";

  // parsear argumentos
  for (int i = 1; i < argc; ++i) {
    std::string argumento = argv[i];
    if (argumento == "-config" && i + 1 < argc) {
      archivoConfig = argv[++i];
    } else if (argumento == "-trace" && i + 1 < argc) {
      opcionTraza = argv[++i];
    } else {
      std::cerr << "Argumento desconocido o incompleto: " << argumento << "\n";
      std::cerr << "Uso: ./automata_pila -config <fichero> -trace <y|n> [-in <fichero>] [-out <fichero>]\n";
      return 1;
    }
  }

  // comprobar argumentos obligatorios
  if (archivoConfig.empty() || (opcionTraza != "y" && opcionTraza != "n")) {
    std::cerr << "Uso: ./automata_pila -config <fichero> -trace <y|n> [-in <fichero>] [-out <fichero>]\n";
    return 1;
  }

  bool modoTraza = (opcionTraza == "y") ? true : false;

  // carga y validación del autómata
  std::ifstream fConfig(archivoConfig);
  if (!fConfig.is_open()) {
    std::cerr << "Error: No se pudo abrir el archivo de configuración: " << archivoConfig << "\n";
    return 1;
  }

  AutomataConPila automata({}, Alfabeto(), Alfabeto(), "", ' ', {});
  try {
    automata = cargarArchivo(fConfig);
  } catch (const std::exception& e) {
    std::cerr << e.what() << std::endl;
    return 1;
  }
  fConfig.close();

  if (modoTraza) {
    std::cout << "Modo traza activado." << std::endl;
    automata.imprimirTransiciones(std::cout);
    std::cout << std::endl;
  }

  std::string cadena;
  while (true) {
    std::cout << "Introduce una cadena: ";
    std::getline(std::cin, cadena);
    if (cadena.empty()) {
      break; // salir si la cadena está vacía
    }
    if (cadena == ".") {
      cadena = "";
    }
    bool resultado;
    if (modoTraza) {
      resultado = automata.pertenece(cadena, true);
    } else {
      resultado = automata.pertenece(cadena, false);
    }
    if (resultado) {
      std::cout << "La cadena pertenece al lenguaje del autómata." << std::endl << std::endl;
    } else {
      std::cout << "La cadena no pertenece al lenguaje del autómata." << std::endl << std::endl;
    }
  }

  return 0;
}