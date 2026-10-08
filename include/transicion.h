#pragma once


#include <istream>
#include <iostream>
#include <sstream>
#include <string>

struct Transicion {
  std::string estado_actual;
  char entrada;
  char entrada_pila;
  std::string estado_siguiente;
  std::string accion_pila;
  short id;

  void imprimir(std::ostream& os) const {
    os << id << " - (" << estado_actual << ", " << entrada << ", " << entrada_pila << ") -> ("
       << estado_siguiente << ", " << accion_pila << ")";
  }
};