#include <string>

#include "../include/alfabeto.h"
#include "../include/pilaDeSimbolos.h"

class AutomataConPila {
 public:
  AutomataConPila(Alfabeto& alfabeto, char simboloInicial);
  void push(char simbolo);
  char pop();
  bool empty() const;

 private:
  pilaDeSimbolos pila_;
  std::string estadoActual_;
}