#pragma once

#include <vector>
#include <string>

#include "alfabeto.h"

class PilaDeSimbolos {
 public:
  PilaDeSimbolos(Alfabeto& alfabeto, char inicial);
  void push(char simbolo);
  char pop();
  bool empty() const;

  std::string toString() const;
 
 private:
  Alfabeto& alfabeto_;
  std::vector<char> stack_;
};