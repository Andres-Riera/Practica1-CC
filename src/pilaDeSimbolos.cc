#include "../include/pilaDeSimbolos.h"

PilaDeSimbolos::PilaDeSimbolos(Alfabeto& alfabeto, char inicial) : alfabeto_(alfabeto) {
  stack_.push_back(inicial);
}

void PilaDeSimbolos::push(char simbolo) {
    if (!alfabeto_.contiene(simbolo)) {
        throw std::runtime_error("El símbolo no pertenece al alfabeto");
    }
     stack_.push_back(simbolo);
}


char PilaDeSimbolos::pop() {
  if (empty()) {
    throw std::runtime_error("La pila está vacía");
  }
  char simbolo = stack_.back();
    stack_.pop_back();
    return simbolo;
}

bool PilaDeSimbolos::empty() const {
  return stack_.empty();
}

std::string PilaDeSimbolos::toString() const {
  if (stack_.empty()) {
    return "";
  }
  return std::string(stack_.rbegin(), stack_.rend());
}