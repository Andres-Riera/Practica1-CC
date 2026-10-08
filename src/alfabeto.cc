#include "../include/alfabeto.h"

Alfabeto::Alfabeto() {
  simbolos_.begin() = simbolos_.end();
}

void Alfabeto::anadirSimbolo(char simbolo) {
  if (simbolo == '.') {
    throw std::invalid_argument("Error: No se puede añadir el símbolo '.' al alfabeto");
  }
  simbolos_.insert(simbolo);
}

bool Alfabeto::contiene(char simbolo) {
  return simbolos_.find(simbolo) != simbolos_.end();
}