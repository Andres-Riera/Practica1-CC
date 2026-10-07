#include "../include/alfabeto.h"

Alfabeto::Alfabeto() {
  simbolos_.begin() = simbolos_.end();
}

void Alfabeto::anadirSimbolo(char simbolo) {
  if (simbolo == '.') {
    throw ("No se puede añadir el símbolo '.'");
  }
  simbolos_.insert(simbolo);
}

bool Alfabeto::contiene(char simbolo) {
  return simbolos_.find(simbolo) != simbolos_.end();
}