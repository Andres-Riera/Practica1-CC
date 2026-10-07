#include "../include/pilaDeSimbolos.h"

pilaDeSimbolos::pilaDeSimbolos(Alfabeto& alfabeto, char inicial) : alfabeto_(alfabeto) {
  stack_.push_back(inicial);
}

void pilaDeSimbolos::push(char simbolo) {
    if (!alfabeto_.contiene(simbolo)) {
        throw ("El símbolo no pertenece al alfabeto");
    }
     stack_.push_back(simbolo);
}


char pilaDeSimbolos::pop() {
  if (empty()) {
    throw ("La pila está vacía");
  }
  char simbolo = stack_.back();
    stack_.pop_back();
    return simbolo;
}

bool pilaDeSimbolos::empty() const {
  return stack_.empty();
}