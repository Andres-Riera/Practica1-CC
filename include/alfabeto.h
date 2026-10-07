#include <set>

class Alfabeto {
 public:
  Alfabeto();

  void anadirSimbolo(char simbolo);
  bool contiene(char simbolo);

 private:
    std::set<char> simbolos_;
};