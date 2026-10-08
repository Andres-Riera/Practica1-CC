#pragma once

#include <algorithm>
#include <iostream>
#include <fstream>
#include <string>

#include "alfabeto.h"
#include "automata.h"
#include "pilaDeSimbolos.h"
#include "transicion.h"

// comprueba si un estado que se quiere añadir se encuentra ya añadido
// para evitar estados duplicados y comprobar que el estado inicial es válido
bool estadoAnadido(std::string estado, std::vector<std::string> estados) {
  return std::find(estados.begin(), estados.end(), estado) != estados.end();
}

// comprueba si una transición es válida
bool comprobarTransicion(std::vector<std::string> estados, Alfabeto alfabeto, Alfabeto alfabetoPila,
                         Transicion transicion) {
  // comprobar que los estados pertenecen a Q
  if (!estadoAnadido(transicion.estado_actual, estados) || 
      !estadoAnadido(transicion.estado_siguiente, estados)) {
    return false;
  }

  // comprobar que el símbolo de entrada pertenece al alfabeto o es epsilon
  if (transicion.entrada != '.' && !alfabeto.contiene(transicion.entrada)) {
    return false;
  }

  // comprobar el símbolo de pila
  if (!alfabetoPila.contiene(transicion.entrada_pila)) {
    return false;
  }

  // comprobar símbolos que se quieren añadir a la pila
  if (transicion.accion_pila != ".") {
    for (char c : transicion.accion_pila) {
      if (!alfabetoPila.contiene(c)) {
        return false;
      }
    }
  }
  return true;
}

AutomataConPila cargarArchivo(std::ifstream& archivo) {
  std::string linea;
  int numeroLinea = 0;
  int lineasComentarios = 0;
  
  std::vector<std::string> estados;
  Alfabeto alfabeto;
  Alfabeto alfabetoPila;
  std::string estadoInicial;
  char simboloInicialPila;
  std::vector<Transicion> transiciones;
  short id_transicion = 1;

  while (std::getline(archivo, linea)) {
    if (linea.empty() || linea[0] == '#') {
      lineasComentarios++;
      continue;    
    }

    std::istringstream iss(linea);
    if (numeroLinea == 0) {
      // conjunto Q
      std::string q;
      while (iss >> q) {
        if (!estadoAnadido(q, estados)) {
          estados.push_back(q);
        }
      }
      if (estados.empty()) {
        throw std::invalid_argument("Error: El conjunto de estados Q está vacío.");
      }
      numeroLinea++;
    } 
    else if (numeroLinea == 1) {
      // alfabeto del lenguaje
      char s;
      while (iss >> s) {
        alfabeto.anadirSimbolo(s);
      }
      numeroLinea++;
    } 
    else if (numeroLinea == 2) {
      // alfabeto de la pila
      char s;
      while (iss >> s) {
        alfabetoPila.anadirSimbolo(s);
      }
      numeroLinea++;
    } 
    else if (numeroLinea == 3) {
      // estado inicial
      iss >> estadoInicial;
      if (!estadoAnadido(estadoInicial, estados)) {
        throw std::invalid_argument("Error: El estado inicial no pertenece al conjunto de estados Q.");
      }
      numeroLinea++;
    } 
    else if (numeroLinea == 4) {
      // simbolo inicial de la pila
      iss >> simboloInicialPila;
      PilaDeSimbolos pilaAux(alfabetoPila, simboloInicialPila);
      numeroLinea++;
    } 
    else {
      // transiciones
      Transicion t;
      if (iss >> t.estado_actual >> t.entrada >> t.entrada_pila >> t.estado_siguiente >> t.accion_pila) {
        t.id = id_transicion++;
        transiciones.push_back(t);
      }
      if(!comprobarTransicion(estados, alfabeto, alfabetoPila, t)) {
        throw std::invalid_argument("Error: Transición inválida en la línea " + std::to_string(numeroLinea + 1 + lineasComentarios));
      }
      numeroLinea++;
    }
  }
  return AutomataConPila(estados, alfabeto, alfabetoPila, estadoInicial, simboloInicialPila, transiciones);
}
