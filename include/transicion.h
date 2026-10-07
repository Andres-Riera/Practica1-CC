#include <string>

struct Transiciones {
 public:
     Transiciones() = default;
     ~Transiciones() = default;

     void agregarTransicion(std::string estado, char simbolo, char simboloPila, std::string estadoDestino, std::string accionPila);
     std::set<int> obtenerEstadosDestino(char simbolo) const;
 private:
     std::map<char, std::set<int>> transiciones_;
};