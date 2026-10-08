#include "../include/automata.h"


AutomataConPila::AutomataConPila(const std::vector<std::string>& estados, const Alfabeto& alfabeto,
                                 const Alfabeto& alfabetoPila, std::string estadoInicial,
                                 char simboloInicialPila, const std::vector<Transicion>& transiciones)
    : estados_(estados), alfabeto_(alfabeto), alfabetoPila_(alfabetoPila), estadoInicial_(estadoInicial),
      simboloInicialPila_(simboloInicialPila), transiciones_(transiciones) {}

bool AutomataConPila::pertenece(std::string cadena, bool modoTraza) {
  PilaDeSimbolos pilaInicial(alfabetoPila_, simboloInicialPila_);
  return siguienteIteracion(cadena, 0, estadoInicial_, pilaInicial, modoTraza, std::cout);
}

bool AutomataConPila::siguienteIteracion(const std::string& cadena, int indiceCadena, std::string estadoActual,
                                         PilaDeSimbolos pila, bool modoTraza, std::ostream& out) {
  // Casos base
  // pila vacía y cadena leída completamente
  if (indiceCadena == cadena.size() && pila.empty()) {
    // traza de la última iteración
    if (modoTraza) {
      out << "Estado: " << estadoActual << " | Cadena: " << " | Pila: " << pila.toString()
          << " | Transiciones: " << std::endl;
    }
    return true;
  }
  // pila vacía y cadena sin leer completamente
  if (pila.empty()) {
    if (modoTraza) {
      out << "Estado: " << estadoActual << " | Cadena: " << cadena.substr(indiceCadena)
          << " | Pila: " << pila.toString() << " | Transiciones: " << std::endl;
    }
    return false;
  }

  // obtener transiciones posibles
  char simboloPila = pila.pop();
  char simboloCadena = (indiceCadena < cadena.length()) ? cadena[indiceCadena] : '.';
  std::vector<Transicion> transiciones = obtenerTransicionesValidas(estadoActual, simboloCadena, simboloPila);
  if (indiceCadena < cadena.length() && simboloCadena != '.') {
    std::vector<Transicion> transicionesEpsilon = obtenerTransicionesValidas(estadoActual, '.', simboloPila);
    transiciones.insert(transiciones.end(), transicionesEpsilon.begin(), transicionesEpsilon.end());
  }
  
  // traza
  if (modoTraza) {
    pila.push(simboloPila); // para que no salga la pila incorrectamente
    out << "Estado: " << estadoActual << " | Cadena: " << cadena.substr(indiceCadena)
        << " | Pila: " << pila.toString() << " | Transiciones: "; 
    for (const auto transicion: transiciones) {
      out << transicion.id << " ";
    }
    pila.pop();
    out << std::endl;
  }

  // ver caminos
  for (const auto transicion: transiciones) {
    PilaDeSimbolos copiaPila = pila;
    if (transicion.accion_pila != ".") {
      for (int i = transicion.accion_pila.length() - 1; i >= 0; --i) {
        copiaPila.push(transicion.accion_pila[i]);
      }
    }

    int nuevoIndice = (transicion.entrada == '.') ? indiceCadena : indiceCadena + 1;

    if (siguienteIteracion(cadena, nuevoIndice, transicion.estado_siguiente, copiaPila, modoTraza, out)) {
      return true; 
    }
  }
  // si no hay transiciones posibles
  return false;
}

std::vector<Transicion> AutomataConPila::obtenerTransicionesValidas(
    const std::string& estadoActual, char simboloCadena, char simboloPila) const {
  
  std::vector<Transicion> validas;
  for (const auto& transicion : transiciones_) {
    if (transicion.estado_actual == estadoActual && 
        transicion.entrada == simboloCadena && 
        transicion.entrada_pila == simboloPila) {
      validas.push_back(transicion);
    }
  }
  return validas;
}