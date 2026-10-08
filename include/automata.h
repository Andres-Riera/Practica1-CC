#pragma once

#include <string>

#include "alfabeto.h"
#include "pilaDeSimbolos.h"
#include "transicion.h"

class AutomataConPila {
 public:
  AutomataConPila(const std::vector<std::string>& estados, const Alfabeto& alfabeto, const Alfabeto& alfabetoPila,
                  std::string estadoInicial, char simboloInicialPila, const std::vector<Transicion>& transiciones);

  bool pertenece(std::string cadena, bool modoTraza = false);

  void imprimirTransiciones(std::ostream& os) const {
    std::cout << "Transiciones: " << std::endl;
    for (const auto transicion: transiciones_) {
      transicion.imprimir(std::cout);
      std::cout << std::endl;
    }
  }

 private:
  // no cambian luego del constructor
  std::vector<std::string> estados_;
  Alfabeto alfabeto_;
  Alfabeto alfabetoPila_;
  std::string estadoInicial_;
  char simboloInicialPila_;
  std::vector<Transicion> transiciones_;

  // método que realiza la siguiente iteración
  bool siguienteIteracion(const std::string& cadena, int indiceCadena, std::string estadoActual,
                          PilaDeSimbolos pila, bool modoTraza, std::ostream& out);

  // Método auxiliar para buscar transiciones válidas
  std::vector<Transicion> obtenerTransicionesValidas(const std::string& estadoActual, char simboloCadena,
                                                     char simboloPila) const;
};