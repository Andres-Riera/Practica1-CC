#include <vector>

#include "alfabeto.h"

class pilaDeSimbolos {
 public:
  pilaDeSimbolos(Alfabeto& alfabeto, char inicial);
  void push(char simbolo);
  char pop();
  bool empty() const;
 
 private:
  Alfabeto& alfabeto_;
  std::vector<char> stack_;
};