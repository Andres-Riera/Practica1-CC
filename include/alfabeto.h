#pragma once

#include <set>
#include <stdexcept>

class Alfabeto {
 public:
  Alfabeto();

  void anadirSimbolo(char simbolo);
  bool contiene(char simbolo);
  const std::set<char>& getSimbolos() const { return simbolos_; }

 private:
    std::set<char> simbolos_;
};